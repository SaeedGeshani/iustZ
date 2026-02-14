#pragma once

#include <string>

namespace ui
{
constexpr int UI_WIDTH = 92;

std::string centeredText(const std::string& text, int width = UI_WIDTH);
void centeredLine(const std::string& text = "", int width = UI_WIDTH);
void drawDivider(char fill = '=', int width = 64);
void drawHeader(const std::string& title);
void drawFooter(const std::string& hint);
int readIntInRange(const std::string& prompt, int lo, int hi);
void clearScreen();
}
