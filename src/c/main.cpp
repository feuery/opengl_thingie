#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cstdio>

// bool init()
// {
//   if(SDL_Init(SDL_INIT_EVERYTHING) <0)
//     return false;
// }

using namespace glm;

int main(int argc, char** argv)
{
  if(!glfwInit())
    {
      printf("Failed to initialize GLFW\n");
      return -1;
    }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* w;
  w = glfwCreateWindow(1024, 768, "Hello world!", NULL, NULL);

  if(!w)
    {
      printf("Making of GLFW window failed");
      glfwTerminate();
      return -1;
    }

  glfwMakeContextCurrent(w);
  glewExperimental = true;
  if(glewInit() != GLEW_OK)
    {
      printf("Failed to init GLEW");
      return -1;
    }

  glfwSetInputMode(w, GLFW_STICKY_KEYS, GL_TRUE);

  do
    {
      glfwSwapBuffers(w);
      glfwPollEvents();
    } while(glfwGetKey(w, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(w) == 0);
  
  return 0;
}
