#include <iostream>
#include <time.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "common.h"

#define _USE_MATH_DEFINES
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

unsigned int windowWidth = 800;
unsigned int windowHeight = 600;
const char* windowTitle = "OpenGL";
const char* vertexPath = "D:/document/workplace/Repo/learnopengl/project/src/shader/vertex.vert";
const char* fragmentPath = "D:/document/workplace/Repo/learnopengl/project/src/shader/fragment.frag";

int main () {
  GLFWwindow* window = initOpenGLENV(windowWidth, windowHeight, windowTitle);
  Shader shader = Shader(vertexPath, fragmentPath);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    glfwProcessInput(window);
    glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // shader.use();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // shader.del();
  glfwTerminate();
}
