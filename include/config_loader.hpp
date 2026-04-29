#pragma once

#include <config.hpp>

#include <filesystem>

Config LoadConfig(const std::filesystem::path& path);
