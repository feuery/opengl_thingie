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

void main_loop(GLFWwindow* w)
{
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  static const GLfloat vertices[] =
    {
      -1.0f, -1.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
    };

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  do
    {
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

      // Starting from vertex 0; 3 vertices total -> 1 triang
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(0);
      
      glfwSwapBuffers(w);
      glfwPollEvents();
    } while(glfwGetKey(w, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(w) == 0);
}

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

  main_loop(w);
  
  return 0;
}
