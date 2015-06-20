#ifndef SHADERS_H
#define SHADERS_H

#include <main.h>

enum SHADER_TYPE {
  VERTEX,
  FRAGMENT
};
  
GLuint LoadShaders(const char * vertex_file_path, SHADER_TYPE s);
GLuint CreateShaderProgram(GLuint vertex_shader, GLuint fragment_shader);

#endif //SHADERS_H

