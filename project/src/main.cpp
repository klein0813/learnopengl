#include <iostream>
#include <time.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "common.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

unsigned int windowWidth = 800;
unsigned int windowHeight = 600;
// 监听上下键
float mixAlpha = 0.2;
const char* windowTitle = "OpenGL";
const char* vertexPath = "D:/document/workplace/Repo/learnopengl/project/src/shader/vertex.vert";
const char* fragmentPath = "D:/document/workplace/Repo/learnopengl/project/src/shader/fragment.frag";
const char* texPath1 = "D:/document/workplace/Repo/learnopengl/project/textures/tex_container.jpg";
const char* texPath2 = "D:/document/workplace/Repo/learnopengl/project/textures/awesomeface.png";

int main () {
  GLFWwindow* window = initOpenGLENV(windowWidth, windowHeight, windowTitle);
  Shader shader = Shader(vertexPath, fragmentPath);

  float vertices[] = {
    // positions      // colors           // texture coords
    // 0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.7f, 0.5f,
    // 0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   0.7f, 0.7f,
    // -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.5f, 0.5f,
    // -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.5f, 0.7f
    0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   2.7f, 0.0f,
    0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   2.7f, 2.7f,
    -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 2.7f
  };
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  int width, height, nrChannels;
  unsigned int texture1;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  unsigned char* data = stbi_load(texPath1, &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    shader.setInt("texture1", 0);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cout << "Failed to load texture" << endl;
  }
  stbi_image_free(data);

  unsigned int texture2;
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  const float borderColor[4] = { 0.0f, 0.0f, 0.5f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_set_flip_vertically_on_load(true);
  data = stbi_load(texPath2, &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cout << "Failed to load texture" << endl;
  }
  stbi_image_free(data);
  shader.use(); // 不要忘记在设置uniform变量之前激活着色器程序！
  shader.setInt("texture1", 0);
  shader.setInt("texture2", 1);
  glm::mat4 trans;
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    glfwProcessInput(window);
    glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // shader.use();
    trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.3f, 0.3f, 0.0f));
    // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.7f, 0.7f, 0.7f));
    // (float)(glfwGetTime() * 0.0001)
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    shader.setMat4("transform", glm::value_ptr(trans));
    shader.setFloat("alpha", mixAlpha);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    trans = glm::mat4(1.0f);
    float scaleAmount = sin(glfwGetTime());
    trans = glm::translate(trans, glm::vec3(-0.3f, 0.0f, 0.0f));
    trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
    shader.setMat4("transform", glm::value_ptr(trans));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  shader.del();
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
}
