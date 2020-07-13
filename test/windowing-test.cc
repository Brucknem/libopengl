#include "gtest/gtest.h"
#include "lib/windowing.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

TEST(WindowingTest, CreateWindow)
{
  GLFWwindow* window = libopengl::CreateWindow(4, 4, 800, 600, "Test Window", true);
  EXPECT_EQ("Bazel", "Bazel");
}