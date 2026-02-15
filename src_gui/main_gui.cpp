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
    for (const std::string& line : session.combatLog)
    {
        ImGui::TextWrapped("%s", line.c_str());
    }
    ImGui::SetScrollHereY(1.0f);
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

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("IUSTZ Frontend");
        ImGui::Text("Dear ImGui GUI Frontend");
        if (!status.empty())
        {
            ImGui::Separator();
            ImGui::TextWrapped("%s", status.c_str());
        }
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
            if (ImGui::Button("Back"))
            {
                screen = Screen::MainMenu;
            }
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
            if (ImGui::Button("Back"))
            {
                screen = Screen::MainMenu;
            }
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

                ImGui::Text("Battle #%d", session.battleIndex);
                ImGui::Text("Enemy: %s (HP: %d)", enemy.name.c_str(), enemy.hp);
                ImGui::Separator();

                ImGui::Text("Party");
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

                ImGui::Separator();
                ImGui::Text("Actions (Player: %d)", selectedPlayer + 1);
                if (ImGui::Button("Attack"))
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
                ImGui::SameLine();
                if (ImGui::Button("Use Item"))
                {
                    BattleStepResult action = PlayerAction(session, selectedPlayer, ActionType::UseItem, 0);
                    status = action.message;
                }
                ImGui::SameLine();
                if (ImGui::Button("Switch Weapon"))
                {
                    BattleStepResult action = PlayerAction(session, selectedPlayer, ActionType::SwitchWeapon, 1);
                    status = action.message;
                }
                ImGui::SameLine();
                if (ImGui::Button("Run"))
                {
                    BattleStepResult action = PlayerAction(session, selectedPlayer, ActionType::Run, 0);
                    status = action.message;
                }

                if (ImGui::Button("Inventory"))
                {
                    screen = Screen::Inventory;
                }
                ImGui::SameLine();
                if (ImGui::Button("Shop"))
                {
                    screen = Screen::Shop;
                }
                ImGui::SameLine();
                if (ImGui::Button("Save"))
                {
                    std::string err;
                    const std::string slot = session.activeSlotId.empty() ? "" : session.activeSlotId;
                    if (SaveSession(session, slot, err, "GUI Save"))
                    {
                        status = "Session saved.";
                    }
                    else
                    {
                        status = err;
                    }
                }

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
            if (ImGui::Button("Back to Battle"))
            {
                screen = Screen::Battle;
            }
        }
        else if (screen == Screen::Shop)
        {
            static int buyer = 0;
            ImGui::InputInt("Buyer index", &buyer);
            buyer = std::max(0, std::min(buyer, static_cast<int>(session.party.size()) - 1));

            if (ImGui::Button("Buy Katana"))
            {
                std::string err;
                status = BuyWeapon(session, buyer, "Katana", err) ? "Purchased Katana" : err;
            }
            ImGui::SameLine();
            if (ImGui::Button("Buy Blaster"))
            {
                std::string err;
                status = BuyWeapon(session, buyer, "Blaster", err) ? "Purchased Blaster" : err;
            }
            if (ImGui::Button("Buy Egg"))
            {
                std::string err;
                status = BuyItem(session, buyer, "Egg", err) ? "Purchased Egg" : err;
            }
            ImGui::SameLine();
            if (ImGui::Button("Buy Energy Drink"))
            {
                std::string err;
                status = BuyItem(session, buyer, "Energy Drink", err) ? "Purchased Energy Drink" : err;
            }

            if (ImGui::Button("Back to Battle"))
            {
                screen = Screen::Battle;
            }
        }

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
