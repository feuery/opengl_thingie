#ifndef OBJ_H
#define OBJ_H

#include <texture.h>
#include <point.h>

class immutable_obj{
public:
  Texture text;
  GLuint vao_handle;
  GLuint shader_handle;
  Point left_up;
  const char* vertex_shader_path;
  const char* fragment_shader_path;
  bool shader_loaded;
  
  immutable_obj(const char* texture_path,
		const char* vertex_shader_path,
		const char* fragment_shader_path,
		Point left_up);
  ~immutable_obj();

  Rect getSize();
  void render();

  bool reload_shaders();
};

#endif //OBJ_H
