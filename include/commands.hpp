#pragma once

#include <vector>
#include <string>

enum class ServiceStatus {
  Inactive,
  Active,
  Failed,
};

struct ServiceState {
  ServiceStatus state;
  int exit_code;
  int pid;
};

void Start(std::vector<std::string> services);
void Stop(std::vector<std::string> services);
ServiceState Status(const std::string& service);

