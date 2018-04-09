#pragma once

#include "Proto.h"

#include <string>
#include <vector>

BEGIN_NAMESPACE(ImGui)

bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);
bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values);

END_NAMESPACE(ImGui)
