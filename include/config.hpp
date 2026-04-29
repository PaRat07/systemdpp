#pragma once

#include <optional>

struct Config {
    using ServiceRef = std::string;
    using Command = std::string;

    struct Unit {
        std::string Description;
        std::string Documentation;
        std::vector<ServiceRef> Requires;
    } unit;

    struct Service {
        Command ExecStart;
        Command ExecReload;
        Command ExecStop;
    } service;
};
