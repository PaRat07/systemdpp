#include "config_loader.hpp"

#include <rfl/toml.hpp>
#include <rfl.hpp>

#include <fstream>

Config LoadConfig(const std::filesystem::path& path) {
  std::fstream config_file(path);
  return rfl::toml::read<Config>(config_file)
    .or_else([] (rfl::Error&& err) -> std::expected<Config, rfl::Error> {
      throw std::runtime_error(std::move(err).what());
    })
    .value();
}
