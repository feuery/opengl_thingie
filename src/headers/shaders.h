#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif //SHADERS_H
