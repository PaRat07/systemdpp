#include "daemon_endpoints.hpp"

#include <rfl/json.hpp>

#include <commands.hpp>

void StartEP(std::string_view body) {
  auto args = rfl::json::read<std::vector<std::string>>(body).value();
  Start(std::move(args));
}
void StopEP(std::string_view body) {
  auto args = rfl::json::read<std::vector<std::string>>(body).value();
  Stop(std::move(args));
}

std::string StatusEP(const std::string& body) {
  return rfl::json::write(Status(body));
}