#ifndef glft_init_h
  #define glft_init_h
  #include <glad/glad.h>
  #include <GLFW/glfw3.h>
  #include <iostream>
  using namespace std;

  void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
  }

  GLFWwindow* initOpenGLENV(const unsigned int windowWidth, const unsigned int widthHeight, const char* windowTilte) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    GLFWwindow* window = glfwCreateWindow(windowWidth, widthHeight, windowTilte, NULL, NULL);
    if (window == NULL) {
      cout << "CREATE WINDOW FAILED." << endl;
      return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      cout << "INITIALIZE GLAD FAILED." << endl;
      return NULL;
    }
    return window;
  }

  void glfwProcessInput (GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, 1);
    }
  }
#endif
