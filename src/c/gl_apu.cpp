#include <main.h>

#include <gl_apu.h>

GLuint generateRectangle (Point p1, Point p2, Point p3, Point p4)
{
  GLfloat vertices[] = {
    // Positions      // Colors           //Texture coords 
    p1.x, p1.y, 0.0f, 1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // Top Right
    p2.x, p2.y, 0.0f, 0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Bottom right
    p3.x, p3.y, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // Bottom left
    p4.x, p4.y, 0.0f, 1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // Top Left
  };

  GLuint indices[] = {  // Note that we start from 0!
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
  };
  GLuint EBO, VBO, VAO;
  glGenBuffers(1, &EBO);
  
  glGenBuffers(1, &VBO);

  // glVertexAttribPointer(0,4, GL_FLOAT, GL_FALSE, 4*sizeof(GL_FLOAT), (GLvoid*)0);
  // glEnableVertexAttribArray(0);

  
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO); {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //Text coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
  }
  glBindVertexArray(0);

  return VAO;
}
