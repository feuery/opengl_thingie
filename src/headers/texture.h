#ifndef TEXTURE_H
#define TEXTURE_H

#include <SOIL/SOIL.h>

class Texture{
public:
  int w, h;
  GLuint texture;
  
  Texture(const char* filename)
  {
  }

  ~Texture()
  {
    glDeleteTextures(1, &texture);
  }

  // void render();
  
private:

};

#endif //TEXTURE_H
