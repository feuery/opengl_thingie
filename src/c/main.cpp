//http://www.learnopengl.com/#!Getting-started/Hello-Triangle
// neliönpiirto rikkic
#include <main.h>
#include <keyboard_handler.h>
#include <shaders.h>

struct Point { GLfloat x, y; };

GLuint generateRectangle (Point p1, Point p2, Point p3, Point p4)
{
  GLfloat vertices[] = {
    p1.x, p1.y, 0.0f,
    p2.x, p2.y, 0.0f,
    p3.x, p3.y, 0.0f,
    p4.x, p4.y, 0.0f
  };

  GLuint indices[] = {  // Note that we start from 0!
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
  };
  GLuint EBO;
  glGenBuffers(1,&EBO);
  
  GLuint VBO;
  glGenBuffers(1, &VBO);

  glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  GLuint VAO;
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO); {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (GLvoid*) 0);
    glEnableVertexAttribArray(0);
  }
  glBindVertexArray(0);

  return VAO;
}
  

//Does shit and returns useful vertex array object handle
GLuint generateTriangle(GLfloat x1, GLfloat y1,GLfloat x2, GLfloat y2,GLfloat x3, GLfloat y3)
{
  GLfloat vertices[] = {
    x1, y1, 0.0f,
    x2, y2, 0.0f,
    x3, y3, 0.0f
  };

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  GLuint VAO;
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO); {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (GLvoid*) 0);
    glEnableVertexAttribArray(0);
  }
  glBindVertexArray(0);

  return VAO;
}

void renderTriangle(GLuint VAO, GLuint shaderProgram, bool drawElements=false)
{
    glUseProgram (shaderProgram);
    glBindVertexArray(VAO);
 
    if(drawElements) {
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glBindVertexArray(0);
}

int main()
{
  //init shit and set the system to use corret ogl-version
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  //Our window <3
  GLFWwindow * w = glfwCreateWindow(800, 600, "MOI MAAILMA", nullptr, nullptr);

  if(!w) {
    printf("Initing GLFWwindow failed\n");
    return -1;
  }

  //prepare glew
  glfwMakeContextCurrent(w);
  glewExperimental = GL_TRUE;

  GLenum init_success;

  //init glew
  if((init_success = glewInit()) != GLEW_OK) {
    printf("Initing glew failed: %s\n", glewGetErrorString(init_success));
    return -1;
  }

  //How big is the viewport?
  glViewport(0,0, 800, 600);

  //Keyboard-eventlistener-thingie
  glfwSetKeyCallback(w, key_callback);

  //Setup the shaders
  auto vShader = LoadShaders("vertexShader.glsl", VERTEX);
  auto fShader = LoadShaders("fragmentShader.glsl", FRAGMENT),
    triangleFShader = LoadShaders("triangleFragment.glsl", FRAGMENT);
  
  GLuint shaderProgram = CreateShaderProgram(vShader,
				    fShader);
  GLuint triangleShader = CreateShaderProgram(vShader, triangleFShader);
  
  glDeleteShader(vShader);
  glDeleteShader(fShader);
  glDeleteShader(triangleFShader);

  //Tell the system how to read our vertices

  GLuint vao = /*generateTriangle(-0.5f, 0.2f,
				0.5f, 0.2f,
				0.0f, 0.9f); */
    generateRectangle({ 0.5f,  0.5f},
		      {     0.5f, -0.5f},
		      {    -0.5f, -0.5f}, 
		      {    -0.5f,  0.5f}),
    otherVao = generateTriangle(-1.0f, -1.0f,
				1.0f, -1.0f,
				0.0f, 0.0f);
  
  //main-loop <3
  
  while(!glfwWindowShouldClose(w)) {
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderTriangle(vao, shaderProgram, true);
    renderTriangle(otherVao, triangleShader);
    
    glfwSwapBuffers(w);

    GLenum error;
    const GLubyte* errorStr;
    while((error = glGetError()) != GL_NO_ERROR) {
      errorStr = gluErrorString(error);
      printf("We has errors: %s\n", errorStr);
    }
  }

  glfwTerminate();
  return 0;
}
