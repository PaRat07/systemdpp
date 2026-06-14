#include <config_loader.hpp>

#include <gtest/gtest.h>

TEST(ConfigLoader, Basic) {
  const std::filesystem::path path = "data/tests/config_test.toml";

  Config conf = LoadConfig(path);

  EXPECT_EQ(conf.Unit.Description, "some basic test");
  EXPECT_EQ(conf.Service.ExecStart, "echo test");
}
