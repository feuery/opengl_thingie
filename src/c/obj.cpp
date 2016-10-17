#include <main.h>
#include <gl_apu.h>
#include <shaders.h>

immutable_obj::immutable_obj(const char* texture_path,
			     const char* vertex_shader_path,
			     const char* fragment_shader_path,
			     Point left_up): text(texture_path),
					     vertex_shader_path(vertex_shader_path),
					     fragment_shader_path(fragment_shader_path),
					     shader_loaded(false)
{
  vao_handle = generateRectangle(left_up, //vasen ylä
				 {left_up.x + (GLfloat)text.w, left_up.y}, //oikee ylä
				 {left_up.x, left_up.y - (GLfloat)text.h}, // vasen ala
				 {left_up.x + (GLfloat)text.w, left_up.y - (GLfloat)text.h}); //oikee ala
  if(!reload_shaders())
    throw "Reloading shaders failed";
}

Rect immutable_obj::getSize()
{
  return {text.w, text.h};
}

void immutable_obj::render()
{
  glUseProgram (shader_handle);
  glBindVertexArray(vao_handle);
 
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

bool immutable_obj::reload_shaders()
{
  if(shader_loaded)
    glDeleteProgram(shader_handle);
  
  auto vShader = LoadShaders(vertex_shader_path, VERTEX),
    fShader = LoadShaders(fragment_shader_path, FRAGMENT);

  shader_handle = CreateShaderProgram(vShader, fShader);

  glDeleteShader(vShader);
  glDeleteShader(fShader);
}
