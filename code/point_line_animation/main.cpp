#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>

#include "shader.h"
#include "common.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

unsigned int windowWidth = 800;
unsigned int windowHeight = 600;
const char* windowTitle = "OpenGL";
const char* vertexPath = "D:/document/workplace/Repo/learnopengl/project/src/shader/vertex.vert";
const char* fragmentPath = "D:/document/workplace/Repo/learnopengl/project/src/shader/fragment.frag";
const unsigned int nodeCount = 1;
const unsigned int backgroundDuration = 4000;
const float fromBackgroundColor[3] = { 10, 25, 100 };
const float toBackgroundColor[3] = { 25, 50, 150 };
unsigned long curClock = clock();
const unsigned int speed = 20;

int main () {
  GLFWwindow* window = initOpenGLENV(windowWidth, windowHeight, windowTitle);
  Shader shader = Shader(vertexPath, fragmentPath);
  // 6 个背景点，nodeCount * (nodeCount - 1) 个线点，nodeCount 个点
  const int maxTotalPointCount = 3 * 6 + (nodeCount + nodeCount * (nodeCount - 1)) * 3;
  float data[maxTotalPointCount] = {
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 
    1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
  };
  unsigned int dt = 0;
  const unsigned int initCount = 6 * 3 + nodeCount * 3;
  const unsigned int pointDatasLength = nodeCount * 3;
  int pointDatas[nodeCount * 3];
  for (unsigned int i = 0; i < pointDatasLength; i += 3) {
    pointDatas[i] = (int)(rand() * 1.0 / RAND_MAX * (windowWidth - 0 + 1));
    pointDatas[i + 1] = (int)(rand() * 1.0 / RAND_MAX * (windowHeight - 0 + 1));
    pointDatas[i + 2] = (int)(rand() * 1.0 / RAND_MAX * (M_PI * 2 - 0 + 1));
  }
  
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  unsigned int aposAttrib = glGetAttribLocation(shader.ID, "apos");
  glVertexAttribPointer(aposAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(aposAttrib);

  unsigned int alphaAttrib = glGetAttribLocation(shader.ID, "alpha");
  glVertexAttribPointer(alphaAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(alphaAttrib);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    glfwProcessInput(window);
    glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int count = initCount; 
    for (unsigned int i = 0; i < pointDatasLength; i = i + 3) {
      pointDatas[i] = pointDatas[i] + cos(pointDatas[i + 2]) * speed * (dt / 1000.0);
      pointDatas[i + 1] = pointDatas[i + 1] + sin(pointDatas[i + 2]) * speed * (dt / 1000.0);

      if (pointDatas[i] < 0) {
        pointDatas[i] = windowWidth - (pointDatas[i] % windowWidth);
      } else if (pointDatas[i] > windowWidth) {
        pointDatas[i] %= windowWidth;
      }

      if (pointDatas[i + 1] < 0) {
        pointDatas[i + 1] = windowHeight - (pointDatas[i + 1] % windowHeight);
      } else if (pointDatas[i + 1] > windowHeight) {
        pointDatas[i + 1] = pointDatas[i + 1] % windowHeight;
      }
      data[6 * 3 + i] = pointDatas[i] * 2.0 / windowWidth - 1;
      data[6 * 3 + i + 1] = pointDatas[i + 1] * 2.0 / windowHeight - 1;
    }
    for (unsigned int i = 0; i < pointDatasLength; i = i + 3) {
      for (unsigned int j = i + 3; j < pointDatasLength; j = j + 3) {
        double dx = abs(pointDatas[i] - pointDatas[j]);
        double dy = abs(pointDatas[i + 1] - pointDatas[j + 1]);
        double d = sqrt(pow(dx, 2) + pow(dy, 2));

        float alpha = d <= 300 ? 0.3 - ((0.3 * d) / 200) : 0;
        if (alpha <= 0) {
          continue;
        }

        data[count + 0] = data[6 * 3 + i];
        data[count + 1] = data[6 * 3 + i + 1];
        data[count + 2] = alpha;
        data[count + 3] = data[6 * 3 + j];
        data[count + 4] = data[6 * 3 + j + 1];
        data[count + 5] = alpha;
        count += 6;
      }
    }

    shader.use();
    shader.set3Float("u_fromColor", fromBackgroundColor);
    shader.set3Float("u_toColor", toBackgroundColor);
    shader.setFloat("u_time", (sin(M_PI * 2.0 * clock() / backgroundDuration - M_PI_2) + 1) / 2);
    glPointSize(10.0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawArrays(GL_POINTS, 6, nodeCount);
    glfwSwapBuffers(window);
    glfwPollEvents();
    dt = clock() - curClock;
    curClock = clock();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  shader.del();
  glfwTerminate();
}
