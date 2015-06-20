#include <shaders.h>
#include <files.h>
#include <string>
#include <cstring>

using namespace std;

GLuint LoadShaders(const char * vertex_file_path, SHADER_TYPE s) {
  
  std::string result = read_source(vertex_file_path);
  const char* c_haisee = result.c_str();

  const char* const* source = &c_haisee;
  
  GLuint vertexShader = glCreateShader(s == VERTEX? GL_VERTEX_SHADER: GL_FRAGMENT_SHADER);
  glShaderSource(vertexShader, 1, source, NULL);
  glCompileShader(vertexShader);

  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("Loading shader %s failed: %s\n", vertex_file_path, infoLog);
  }

  return vertexShader;
}

GLuint CreateShaderProgram(GLuint vertex_shader, GLuint fragment_shader) {

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertex_shader);
  glAttachShader(shaderProgram, fragment_shader);
  glLinkProgram(shaderProgram);
  GLint success;
  GLchar infolog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
    printf("Linking shader program failed: %s\n", infolog);
    return -1;
  }

  return shaderProgram;
}
