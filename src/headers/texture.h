#ifndef TEXTURE_H
#define TEXTURE_H

#include <SOIL/SOIL.h>

class Texture{
public:
  int w, h;
  GLuint texture;
  
  Texture(const char* filename)
  {
    unsigned char* img = SOIL_load_image(filename, &w, &h, 0, SOIL_LOAD_RGB);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  void render();
  
private:

};

#endif //TEXTURE_H
