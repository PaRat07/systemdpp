#pragma once

#include <optional>
#include <string>
#include <vector>

struct Config {
    using ServiceRef = std::string;
    using Command = std::string;

    struct Unit {
        std::optional<std::string> Description;
        std::optional<std::string> Documentation;
        std::optional<std::vector<ServiceRef>> Wants;
    } Unit;

    struct Service {
        Command ExecStart;
        std::optional<Command> ExecReload;
        std::optional<Command> ExecStop;
    } Service;
};
