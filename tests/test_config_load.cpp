#include <config_loader.hpp>

#include <gtest/gtest.h>

TEST(ConfigLoader, Basic) {
  const std::filesystem::path path = "data/tests/config_test.yaml";

  Config conf = LoadConfig(path);

  EXPECT_EQ(conf.Unit.Description, "some basic test");
}
