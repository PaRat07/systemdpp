#include <commands.hpp>

#include <filesystem>

namespace fs = std::filesystem;

#include <gtest/gtest.h>

TEST(Commands, FailingTest) {
  const fs::path config = "/home/parat07/CLionProjects/systemdpp/data/tests/failing_service.toml";
  std::string old_home = std::getenv("HOME");
  setenv("HOME", "/tmp/systemdpp-tests", 1);
  const fs::path install_to = "/tmp/systemdpp-tests/failing_service.toml";
  fs::remove(install_to);
  fs::create_directory("/tmp/systemdpp-tests/");
  fs::copy_file(config, install_to);

  EXPECT_EQ(Status("failing_service").state, ServiceStatus::Inactive);


  fs::remove(install_to);
  // EXPECT_EQ(conf.Unit.Description, "some basic test");
}
