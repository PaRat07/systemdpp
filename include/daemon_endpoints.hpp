#pragma once

#include <string_view>

void StartEP(std::string_view body);
void StopEP(std::string_view body);
std::string StatusEP(const std::string& body);
