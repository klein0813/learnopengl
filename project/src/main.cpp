#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>
#include <common.h>

using namespace std;

const unsigned int windowWidth = 800;
const unsigned int windowHeight = 600;
const char* windowTitle = "OpenGL";
const char* vertexPath = "D:/document/workplace/Repo/learnopengl/project/src/shader/vertex.vert";
const char* fragmentPath = "D:/document/workplace/Repo/learnopengl/project/src/shader/fragment.frag";

int main () {
  GLFWwindow* window = initOpenGLENV(windowWidth, windowHeight, windowTitle);
  Shader shader = Shader(vertexPath, fragmentPath);
  float firstTriangle[] = {
    -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // left 
    -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
    -0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top 
  };
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
  unsigned int aposAttrib = glGetAttribLocation(shader.ID, "apos");
  glVertexAttribPointer(aposAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(aposAttrib);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(0);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    glfwProcessInput(window);
    glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  shader.del();
  glfwTerminate();
}
