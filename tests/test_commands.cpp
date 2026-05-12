#include <commands.hpp>

#include <filesystem>

namespace fs = std::filesystem;

#include <gtest/gtest.h>

TEST(Commands, FailingTest) {
  const fs::path config = "data/tests/failing_service.toml";
  std::string old_home = std::getenv("HOME");
  setenv("HOME", "/tmp/systemdpp-tests", 1);
  const fs::path install_to = "/tmp/systemdpp-tests/failing_service.toml";
  fs::copy_file(config, install_to);

  EXPECT_EQ(Status("failing_service").state, ServiceStatus::Inactive);
  setenv("HOME", old_home.c_str(), 1);
}
