#pragma once

#include <string>
#include <vector>

struct Config {
    using ServiceRef = std::string;
    using Command = std::string;

    struct Unit {
        std::string Description;
        std::string Documentation;
        std::vector<ServiceRef> Requires;
    } Unit;

    struct Service {
        Command ExecStart;
        Command ExecReload;
        Command ExecStop;
    } Service;
};
