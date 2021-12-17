#ifndef glft_init_h
  #define glft_init_h
  #include <glad/glad.h>
  #include <GLFW/glfw3.h>
  #include <iostream>
  #include "glm/glm.hpp"
  #include "glm/gtc/matrix_transform.hpp"
  #include "glm/gtc/type_ptr.hpp"

  using namespace std;
  extern unsigned int windowWidth, windowHeight;
  extern float mixAlpha;
  extern glm::vec3 cameraPos;
  extern glm::vec3 cameraFront;
  extern glm::vec3 cameraUp;

  float deltaTime = 0.0f;
  float lastTime = 0.0f;
  bool firstMouse = true;
  float lastX = windowWidth / 2.0;
  float lastY = windowHeight / 2.0;
  const float sensitivity = 0.05f;
  float pitch = 0.0f;
  float yaw = 0.0f;

  void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
  }

  void cursor_callback (GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
    }
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    xOffset *= sensitivity;
    yOffset *= sensitivity;
    pitch += yOffset;
    yaw += xOffset;
    if (pitch > 89.0f) {
      pitch = 89.0f;
    } else if (pitch < -89.0f) {
      pitch = -89.0f;
    }
    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront *= glm::normalize(front);
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
    glfwSetCursorPosCallback(window, cursor_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      cout << "INITIALIZE GLAD FAILED." << endl;
      return NULL;
    }
    return window;
  }

  void glfwProcessInput (GLFWwindow* window) {
    float cameraSpeed = 2.5f * deltaTime;
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastTime;
    lastTime = currentFrame;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, 1);
    } else if (glfwGetKey(window, GLFW_KEY_UP)) {
      mixAlpha += 0.001;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN)) {
      mixAlpha -= 0.001;
    } else if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) { // =
      cameraPos += cameraSpeed * cameraFront;
    } else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) { // -
      cameraPos -= cameraSpeed * cameraFront;
    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { // w
      glm::vec3 rightAxio = glm::cross(cameraUp, cameraFront);
      cameraPos += cameraSpeed * glm::normalize(glm::cross(rightAxio, cameraFront));
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { // s
      glm::vec3 rightAxio = glm::cross(cameraUp, cameraFront);
      cameraPos -= cameraSpeed * glm::normalize(glm::cross(rightAxio, cameraFront));
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { // a
      cameraPos -= glm::normalize(glm::cross(cameraUp, cameraFront)) * cameraSpeed;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { // d
      cameraPos += glm::normalize(glm::cross(cameraUp, cameraFront)) * cameraSpeed;
    }
  }
#endif
