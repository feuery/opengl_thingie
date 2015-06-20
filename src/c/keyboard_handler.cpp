#include <keyboard_handler.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  printf("Painoit sitte nappulaa\n");
  if(key==GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}
