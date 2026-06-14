#include "config_loader.hpp"

#include <rfl/toml.hpp>

#include <fstream>

Config LoadConfig(const std::filesystem::path& path) {
  std::ifstream config_file(path);
  if (!config_file.is_open()) {
    throw std::runtime_error("Failed to open file: " + path.string());
  }
  return rfl::toml::read<Config>(config_file)
    .or_else([] (rfl::Error&& err) -> std::expected<Config, rfl::Error> {
      throw std::runtime_error(std::move(err).what());
    })
    .value();
}

std::string Dump(Config conf) {
  return rfl::toml::write(conf);
}
