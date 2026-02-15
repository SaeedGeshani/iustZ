#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "GameEngine.h"

namespace
{
enum class Screen
{
    MainMenu,
    NewGame,
    LoadGame,
    Battle,
    Inventory,
    Shop
};

void DrawCombatLog(const GameSession& session)
{
    ImGui::Begin("Combat Log");
    ImGui::BeginChild("combat-log-child", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
    const bool shouldAutoScroll = (ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 5.0f);
    for (const std::string& line : session.combatLog)
    {
        ImGui::TextWrapped("%s", line.c_str());
    }
    if (shouldAutoScroll)
    {
        ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();
    ImGui::End();
}
} // namespace

int main()
{
    if (!glfwInit())
    {
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "IUSTZ GUI", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Screen screen = Screen::MainMenu;
    bool hasSession = false;
    GameSession session;
    std::string status;
    std::string singleName = "Player1";
    std::vector<std::string> multiNames = {"Player1", "Player2"};
    int selectedPlayer = 0;
    std::vector<int> selectedWeaponIndices;
    std::vector<int> selectedItemIndices;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("IUSTZ Frontend");
        ImGui::Text("Dear ImGui GUI Frontend");

        const auto navigateTo = [&](Screen destination)
        {
            if ((destination == Screen::Battle || destination == Screen::Inventory || destination == Screen::Shop) && !hasSession)
            {
                status = "No active session. Start or load a game first.";
                screen = Screen::MainMenu;
                return;
            }
            screen = destination;
        };

        ImGui::Separator();

        ImGui::BeginDisabled(screen == Screen::MainMenu);
        if (ImGui::Button("Main Menu"))
        {
            navigateTo(Screen::MainMenu);
        }
        ImGui::EndDisabled();

        ImGui::SameLine();
        ImGui::BeginDisabled(screen == Screen::Battle);
        if (ImGui::Button("Battle"))
        {
            navigateTo(Screen::Battle);
        }
        ImGui::EndDisabled();

        ImGui::SameLine();
        ImGui::BeginDisabled(screen == Screen::Inventory);
        if (ImGui::Button("Inventory"))
        {
            navigateTo(Screen::Inventory);
        }
        ImGui::EndDisabled();

        ImGui::SameLine();
        ImGui::BeginDisabled(screen == Screen::Shop);
        if (ImGui::Button("Shop"))
        {
            navigateTo(Screen::Shop);
        }
        ImGui::EndDisabled();

        ImGui::SameLine();
        ImGui::BeginDisabled(!hasSession);
        if (ImGui::Button("Save"))
        {
            std::string err;
            const std::string slot = session.activeSlotId.empty() ? "" : session.activeSlotId;
            status = SaveSession(session, slot, err, "GUI Save") ? "Session saved." : err;
        }
        ImGui::EndDisabled();

        ImGui::SameLine();
        ImGui::BeginDisabled(screen == Screen::LoadGame);
        if (ImGui::Button("Load"))
        {
            navigateTo(Screen::LoadGame);
        }
        ImGui::EndDisabled();

        ImGui::Separator();

        if (screen == Screen::MainMenu)
        {
            if (ImGui::Button("New Game"))
            {
                screen = Screen::NewGame;
            }
            if (ImGui::Button("Load Game"))
            {
                screen = Screen::LoadGame;
            }
            if (ImGui::Button("Quit"))
            {
                glfwSetWindowShouldClose(window, 1);
            }
        }
        else if (screen == Screen::NewGame)
        {
            static bool multiplayer = false;
            ImGui::Checkbox("Multiplayer", &multiplayer);

            if (!multiplayer)
            {
                char buf[128]{};
                std::snprintf(buf, sizeof(buf), "%s", singleName.c_str());
                if (ImGui::InputText("Player Name", buf, sizeof(buf)))
                {
                    singleName = buf;
                }
                if (ImGui::Button("Start Single Player"))
                {
                    DestroySession(session);
                    session = CreateNewSessionSingle(singleName);
                    hasSession = true;
                    StartBattle(session);
                    status = "Started single-player game.";
                    screen = Screen::Battle;
                }
            }
            else
            {
                for (size_t i = 0; i < multiNames.size(); ++i)
                {
                    char buf[128]{};
                    std::snprintf(buf, sizeof(buf), "%s", multiNames[i].c_str());
                    const std::string label = "Player " + std::to_string(i + 1);
                    if (ImGui::InputText(label.c_str(), buf, sizeof(buf)))
                    {
                        multiNames[i] = buf;
                    }
                }
                if (ImGui::Button("Add Player") && multiNames.size() < 4)
                {
                    multiNames.push_back("Player" + std::to_string(multiNames.size() + 1));
                }
                if (ImGui::Button("Start Multiplayer"))
                {
                    DestroySession(session);
                    session = CreateNewSessionMulti(multiNames);
                    hasSession = true;
                    StartBattle(session);
                    status = "Started multiplayer game.";
                    screen = Screen::Battle;
                }
            }
            ImGui::TextDisabled("Use top navigation to switch screens.");
        }
        else if (screen == Screen::LoadGame)
        {
            const std::vector<SlotInfo> slots = ListSessionSlots();
            for (const SlotInfo& slot : slots)
            {
                ImGui::PushID(slot.slotId.c_str());
                ImGui::Text("%s | %s", slot.slotLabel.c_str(), slot.updatedAt.c_str());
                ImGui::TextWrapped("Party: %s", slot.partyPreview.c_str());
                if (!slot.isCorrupt && ImGui::Button("Load"))
                {
                    std::string err;
                    if (LoadSession(session, slot.slotId, err))
                    {
                        hasSession = true;
                        if (!session.inBattle)
                        {
                            StartBattle(session);
                        }
                        status = "Loaded slot " + slot.slotId;
                        screen = Screen::Battle;
                    }
                    else
                    {
                        status = err;
                    }
                }
                ImGui::Separator();
                ImGui::PopID();
            }
            ImGui::TextDisabled("Use top navigation to switch screens.");
        }
        else if (screen == Screen::Battle)
        {
            if (!hasSession)
            {
                status = "No active session.";
                screen = Screen::MainMenu;
            }
            else
            {
                const std::vector<PlayerSnapshot> party = GetPartySnapshot(session);
                const EnemySnapshot enemy = GetEnemySnapshot(session);

                if (party.empty())
                {
                    selectedPlayer = 0;
                }
                else
                {
                    selectedPlayer = std::max(0, std::min(selectedPlayer, static_cast<int>(party.size()) - 1));
                }

                selectedWeaponIndices.resize(party.size(), 0);
                selectedItemIndices.resize(party.size(), 0);
                for (size_t i = 0; i < party.size(); ++i)
                {
                    if (party[i].weapons.empty())
                    {
                        selectedWeaponIndices[i] = 0;
                    }
                    else
                    {
                        selectedWeaponIndices[i] = std::max(0, std::min(selectedWeaponIndices[i], static_cast<int>(party[i].weapons.size()) - 1));
                    }

                    if (party[i].items.empty())
                    {
                        selectedItemIndices[i] = 0;
                    }
                    else
                    {
                        selectedItemIndices[i] = std::max(0, std::min(selectedItemIndices[i], static_cast<int>(party[i].items.size()) - 1));
                    }
                }

                const bool validPlayerSelection = !party.empty() && selectedPlayer >= 0 && selectedPlayer < static_cast<int>(party.size());
                const PlayerSnapshot* selected = validPlayerSelection ? &party[selectedPlayer] : nullptr;
                const bool playerAlive = selected != nullptr && selected->hp > 0;
                const bool hasItems = selected != nullptr && !selected->items.empty();
                const bool hasWeapons = selected != nullptr && !selected->weapons.empty();

                ImGui::Text("Battle #%d", session.battleIndex);
                ImGui::Text("Enemy: %s (HP: %d/%d)", enemy.name.c_str(), enemy.hp, enemy.maxHp);
                ImGui::Separator();

                ImGui::Columns(3, "battle-panels", true);

                ImGui::Text("Party");
                ImGui::BeginChild("party-panel", ImVec2(0, 300), true);
                for (size_t i = 0; i < party.size(); ++i)
                {
                    const PlayerSnapshot& p = party[i];
                    ImGui::PushID(static_cast<int>(i));
                    if (ImGui::Selectable(p.name.c_str(), selectedPlayer == static_cast<int>(i)))
                    {
                        selectedPlayer = static_cast<int>(i);
                    }
                    ImGui::ProgressBar(std::max(0.0f, std::min(1.0f, p.maxHp > 0 ? (p.hp / static_cast<float>(p.maxHp)) : 0.0f)), ImVec2(-1, 0), ("HP: " + std::to_string(p.hp)).c_str());
                    ImGui::PopID();
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Enemy & Actions");
                ImGui::BeginChild("actions-panel", ImVec2(0, 300), true);
                ImGui::Text("%s", enemy.name.c_str());
                ImGui::ProgressBar(std::max(0.0f, std::min(1.0f, enemy.maxHp > 0 ? (enemy.hp / static_cast<float>(enemy.maxHp)) : 0.0f)), ImVec2(-1, 0), ("HP: " + std::to_string(enemy.hp)).c_str());
                ImGui::Separator();
                ImGui::Text("Actions (Player: %d)", selectedPlayer + 1);

                ImGui::BeginDisabled(!(validPlayerSelection && playerAlive));
                if (ImGui::Button("Attack", ImVec2(-1, 0)))
                {
                    BattleStepResult action = PlayerAction(session, selectedPlayer, ActionType::Attack, 0);
                    status = action.message;
                    if (!action.battleEnded)
                    {
                        EnemyTurnResult enemyTurn = EnemyTurn(session);
                        if (enemyTurn.battleEnded)
                        {
                            status = "Party defeated.";
                        }
                    }
                }
                ImGui::EndDisabled();

                ImGui::BeginDisabled(!(validPlayerSelection && playerAlive && hasItems));
                if (ImGui::Button("Use Item", ImVec2(-1, 0)))
                {
                    BattleStepResult action = PlayerAction(session, selectedPlayer, ActionType::UseItem, selectedItemIndices[selectedPlayer]);
                    status = action.message;
                }
                ImGui::EndDisabled();

                ImGui::BeginDisabled(!(validPlayerSelection && playerAlive && hasWeapons));
                if (ImGui::Button("Switch Weapon", ImVec2(-1, 0)))
                {
                    BattleStepResult action = PlayerAction(session, selectedPlayer, ActionType::SwitchWeapon, selectedWeaponIndices[selectedPlayer]);
                    status = action.message;
                }
                ImGui::EndDisabled();

                ImGui::BeginDisabled(!(validPlayerSelection && playerAlive));
                if (ImGui::Button("Run", ImVec2(-1, 0)))
                {
                    BattleStepResult action = PlayerAction(session, selectedPlayer, ActionType::Run, 0);
                    status = action.message;
                }
                ImGui::EndDisabled();
                ImGui::EndChild();

                ImGui::NextColumn();

                ImGui::Text("Selected Player");
                ImGui::BeginChild("player-detail-panel", ImVec2(0, 300), true);
                if (selected != nullptr)
                {
                    ImGui::Text("Name: %s", selected->name.c_str());
                    ImGui::Text("HP: %d / %d", selected->hp, selected->maxHp);
                    ImGui::Text("Stamina: %d", selected->stamina);
                    ImGui::Text("Coins: %d", selected->coins);
                    ImGui::Text("Level: %d", selected->level);
                    ImGui::Separator();

                    if (selected->weapons.empty())
                    {
                        ImGui::TextDisabled("No weapons available.");
                    }
                    else
                    {
                        std::vector<const char*> weaponNames;
                        weaponNames.reserve(selected->weapons.size());
                        for (const std::string& weapon : selected->weapons)
                        {
                            weaponNames.push_back(weapon.c_str());
                        }
                        ImGui::Combo("Weapon", &selectedWeaponIndices[selectedPlayer], weaponNames.data(), static_cast<int>(weaponNames.size()));
                    }

                    if (selected->items.empty())
                    {
                        ImGui::TextDisabled("No usable items available.");
                    }
                    else
                    {
                        std::vector<const char*> itemNames;
                        itemNames.reserve(selected->items.size());
                        for (const std::string& item : selected->items)
                        {
                            itemNames.push_back(item.c_str());
                        }
                        ImGui::ListBox("Usable Items", &selectedItemIndices[selectedPlayer], itemNames.data(), static_cast<int>(itemNames.size()), 4);
                    }
                }
                else
                {
                    ImGui::TextDisabled("No player selected.");
                }
                ImGui::EndChild();

                ImGui::Columns(1);

                DrawCombatLog(session);
            }
        }
        else if (screen == Screen::Inventory)
        {
            const std::vector<PlayerSnapshot> party = GetPartySnapshot(session);
            for (const PlayerSnapshot& p : party)
            {
                ImGui::Text("%s", p.name.c_str());
                ImGui::Text("Weapons:");
                for (const std::string& w : p.weapons)
                {
                    ImGui::BulletText("%s", w.c_str());
                }
                ImGui::Text("Items:");
                for (const std::string& it : p.items)
                {
                    ImGui::BulletText("%s", it.c_str());
                }
                ImGui::Separator();
            }
            ImGui::TextDisabled("Use top navigation to switch screens.");
        }
        else if (screen == Screen::Shop)
        {
            static int buyer = 0;
            static int selectedWeapon = 0;
            static int selectedItem = 0;

            const std::vector<std::string> availableWeapons = GetAvailableWeapons();
            const std::vector<std::string> availableItems = GetAvailableItems();

            ImGui::InputInt("Buyer index", &buyer);
            buyer = std::max(0, std::min(buyer, static_cast<int>(session.party.size()) - 1));

            if (availableWeapons.empty())
            {
                selectedWeapon = 0;
            }
            else
            {
                selectedWeapon = std::max(0, std::min(selectedWeapon, static_cast<int>(availableWeapons.size()) - 1));
            }

            if (availableItems.empty())
            {
                selectedItem = 0;
            }
            else
            {
                selectedItem = std::max(0, std::min(selectedItem, static_cast<int>(availableItems.size()) - 1));
            }

            ImGui::Columns(2, "shop-columns", true);

            ImGui::Text("Weapons");
            if (ImGui::BeginTable("shop-weapons", 1, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
            {
                for (size_t i = 0; i < availableWeapons.size(); ++i)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    if (ImGui::Selectable(availableWeapons[i].c_str(), selectedWeapon == static_cast<int>(i), ImGuiSelectableFlags_SpanAllColumns))
                    {
                        selectedWeapon = static_cast<int>(i);
                    }
                }
                ImGui::EndTable();
            }

            ImGui::BeginDisabled(availableWeapons.empty());
            if (ImGui::Button("Buy Selected Weapon", ImVec2(-1, 0)) && !availableWeapons.empty())
            {
                const std::string& weaponName = availableWeapons[selectedWeapon];
                std::string err;
                status = BuyWeapon(session, buyer, weaponName, err) ? ("Purchased " + weaponName) : err;
            }
            ImGui::EndDisabled();

            ImGui::NextColumn();

            ImGui::Text("Items");
            if (ImGui::BeginTable("shop-items", 1, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
            {
                for (size_t i = 0; i < availableItems.size(); ++i)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    if (ImGui::Selectable(availableItems[i].c_str(), selectedItem == static_cast<int>(i), ImGuiSelectableFlags_SpanAllColumns))
                    {
                        selectedItem = static_cast<int>(i);
                    }
                }
                ImGui::EndTable();
            }

            ImGui::BeginDisabled(availableItems.empty());
            if (ImGui::Button("Buy Selected Item", ImVec2(-1, 0)) && !availableItems.empty())
            {
                const std::string& itemName = availableItems[selectedItem];
                std::string err;
                status = BuyItem(session, buyer, itemName, err) ? ("Purchased " + itemName) : err;
            }
            ImGui::EndDisabled();

            ImGui::Columns(1);

            ImGui::TextDisabled("Use top navigation to switch screens.");
        }

        ImGui::Separator();
        ImGui::BeginChild("status-bar", ImVec2(0, ImGui::GetFrameHeightWithSpacing() * 1.4f), true);
        ImGui::TextUnformatted(status.empty() ? "Ready." : status.c_str());
        ImGui::EndChild();

        ImGui::End();

        ImGui::Render();
        int displayW = 0;
        int displayH = 0;
        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClearColor(0.10f, 0.12f, 0.16f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    DestroySession(session);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
