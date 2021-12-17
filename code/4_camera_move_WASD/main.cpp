
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#include <math.h>
#include "stb_image.h"

#include <iostream>
#include <time.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "common.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

unsigned int windowWidth = 800;
unsigned int windowHeight = 600;
const char* windowTitle = "OpenGL";
const char* vertexPath = "D:/document/workplace/Repo/learnopengl/project/src/shader/vertex.vert";
const char* fragmentPath = "D:/document/workplace/Repo/learnopengl/project/src/shader/fragment.frag";
const char* texPath1 = "D:/document/workplace/Repo/learnopengl/project/textures/tex_container.jpg";
const char* texPath2 = "D:/document/workplace/Repo/learnopengl/project/textures/awesomeface.png";
// 监听上下键
float mixAlpha = 0.2;
// 监听 WASD
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

int main () {
  GLFWwindow* window = initOpenGLENV(windowWidth, windowHeight, windowTitle);
  Shader shader = Shader(vertexPath, fragmentPath);

  float vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f
  };
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glEnable(GL_DEPTH_TEST);

  glm::mat4 trans = glm::mat4(1.0f);
  glm::mat4 model = trans;
  shader.setMat4("model", glm::value_ptr(model));

  while (!glfwWindowShouldClose(window)) {
    glfwProcessInput(window);
    glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 模型矩阵 => 将该顶点坐标变换到世界坐标
    // glm::mat4 model = glm::rotate(trans, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // 观察矩阵 => 将矩阵向我们要进行移动场景的反方向移动
    // 我们需要沿着z轴的正方向移动。我们会通过将场景沿着z轴负方向平移来实现。它会给我们一种我们在往后移动的感觉
    // (float)(glfwGetTime() * glm::radians(50.0f))

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100.0f);

    shader.setMat4("view", glm::value_ptr(view));
    shader.setMat4("projection", glm::value_ptr(projection));
    shader.setFloat("alpha", mixAlpha);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  shader.del();
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
}
