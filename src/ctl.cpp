#include <httplib.h>

#include <rfl/json.hpp>
#include <rfl.hpp>

#include <cstdlib>
#include <ranges>

int main(int argc, char** argv) {
    if (argc < 2) {
        throw std::runtime_error("Expected: systemctl COMMAND SERVICE...");
    }
    httplib::Client daemon("localhost", 8080);
    auto services = std::views::counted(argv + 2, argc - 2) | std::ranges::to<std::vector<std::string>>();
    std::string_view command = argv[1];
    if (command == "start") {
        auto res = daemon.Post("/start", rfl::json::write(services), "application/json");
        if (!res || res->status != 200) {
            throw std::runtime_error("Failed to start services");
        }
    } else if (command == "stop") {
        auto res = daemon.Post("/stop", rfl::json::write(services), "application/json");
        if (!res || res->status != 200) {
            throw std::runtime_error("Failed to stop services");
        }
    } else if (command == "status") {
        if (services.size() != 1) {
            throw std::runtime_error("Expected exactly one service for status command");
        }
        auto res = daemon.Post("/status", services[0], "text/plain");
        if (!res || res->status != 200) {
            throw std::runtime_error("Failed to get status of services");
        }
        std::cout << res->body << std::endl;
    } else {
        throw std::runtime_error("Unknown command: " + std::string(command));
    }
}
