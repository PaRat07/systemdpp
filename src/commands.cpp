#include <commands.hpp>

#include <config_loader.hpp>
#include <map>
#include <mutex>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>

static Config ResolveService(std::string_view name) {
  using std::filesystem::path;
  return LoadConfig(path(std::getenv("HOME")) / path(".config/systemdpp") / path(name));
}

static std::map<std::string, ServiceState> service_states;
static std::mutex service_states_mutex;

ServiceState Status(const std::string& name) {
  std::lock_guard _(service_states_mutex);
  return service_states.contains(name) ? service_states.at(name) : ServiceState{ServiceStatus::Inactive, 0, -1};
}


void Start(std::vector<std::string> services) {
  std::map<std::string, Config> need_start;
  {
    auto add_service = [&need_start] (this auto self, std::string name) {
      if (need_start.contains(name)) return;
      Config& config = need_start[std::move(name)] = ResolveService(name);
      if (config.Unit.Wants) {
        for (std::string want : *config.Unit.Wants) {
          self(std::move(want));
        }
      }
    };
    for (const std::string& service : services) {
      add_service(service);
    }
  }
  for (const auto& [name, config] : need_start) {
    std::thread([name, config] {
      if (pid_t child = fork(); child != 0) {
        {
          std::lock_guard _(service_states_mutex);
          service_states[name] = {
            .state = ServiceStatus::Active,
            .exit_code = 0,
            .pid = child
          };
        }
        int status;
        waitpid(child, &status, 0);
        if (Status(name).state == ServiceStatus::Active) {
          int exit_code;
          if (WIFEXITED(status)) {
            exit_code = WEXITSTATUS(status);
          } else if (WIFSIGNALED(status)) {
            exit_code = 128 + WTERMSIG(status);
          } else {
            exit_code = -1;
          }
          std::lock_guard _(service_states_mutex);
          service_states[name] = {
            .state = ServiceStatus::Failed,
            .exit_code = exit_code,
            .pid = -1
          };
        }
      } else {
        execlp(config.Service.ExecStart.c_str(), config.Service.ExecStart.c_str(), nullptr);
        std::exit(132);
      }
    }).detach();
  }
}

void Stop(std::vector<std::string> services) {
  for (const auto& name : services) {
    auto config = ResolveService(name);
    pid_t service_pid = Status(name).pid;
    std::lock_guard _(service_states_mutex);
    service_states[name] = {
      .state = ServiceStatus::Inactive,
      .exit_code = 0,
      .pid = -1
    };
    if (config.Service.ExecStop) {
      std::system(config.Service.ExecStop.value().c_str());
    } else {
      kill(service_pid, SIGTERM);
    }
  }
}

