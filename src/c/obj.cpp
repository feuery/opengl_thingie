#include <main.h>
#include <gl_apu.h>
#include <shaders.h>

immutable_obj::immutable_obj(const char* texture_path,
			     const char* vertex_shader_path,
			     const char* fragment_shader_path,
			     Point left_up): vertex_shader_path(vertex_shader_path),
					     fragment_shader_path(fragment_shader_path),
					     shader_loaded(false)
{
  vao_handle = generateRectangle({left_up.x + 1.0f, left_up.y}, //oikee ylä
				 {left_up.x + 1.0f, left_up.y - 1.0f}, //oikee ala
				 {left_up.x, left_up.y - 1.0f}, // vasen ala
				 left_up //vasen ylä
				 );

  if(!reload_shaders())
    throw "Reloading shaders failed";

  setup_texture(texture_path);
}

immutable_obj::~immutable_obj() {
  
}

void immutable_obj::setup_texture(const char* filename)
{
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned char* img = SOIL_load_image(filename, &text_w, &text_h, 0, SOIL_LOAD_RGB);  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text_w, text_h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(img);
  glBindTexture(GL_TEXTURE_2D, 0);
}

Rect immutable_obj::getSize()
{
  return {text_w, text_h};
}

void immutable_obj::render()
{
  glBindTexture(GL_TEXTURE_2D, texture);
  glUseProgram (shader_handle);

  glBindVertexArray(vao_handle);
  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

bool immutable_obj::reload_shaders()
{
  try {
    if(shader_loaded)
      glDeleteProgram(shader_handle);
  
    auto vShader = LoadShaders(vertex_shader_path, VERTEX),
      fShader = LoadShaders(fragment_shader_path, FRAGMENT);

    shader_handle = CreateShaderProgram(vShader, fShader);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    printf("Shaders loaded at paths %s, %s", vertex_shader_path, fragment_shader_path);
    
    return true;
  }
  catch (...) {
    puts("Caught unknown exception at immutable_obj::reload_shaders()");
    return false;
  }
}
