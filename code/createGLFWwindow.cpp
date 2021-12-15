#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void frame_buffer_size_callback (GLFWwindow* window, int width, int height);
void processInput (GLFWwindow* window);

int main () {
  glfwInit(); // 初始化 glfw
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // openGL 主版本号
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // openGL 次版本号
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用核心模式

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // 创建窗口，失败时返回 NULL
  GLFWwindow* window = glfwCreateWindow(800, 600, "CreateGLFWWindow", NULL, NULL);
  if (!window) {
    cout<<"Failed to create GLFWwindow."<<endl;
    return -1;
  }
  glfwMakeContextCurrent(window);
  // 窗口调整大小时，回调
  glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

  // GLAD是用来管理OpenGL的函数指针
  // GLFW给的是glfwGetProcAddress，它根据编译的系统定义了正确的函数
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout<<"Failed to initialize GLAD"<<endl;
    glfwTerminate();
    return -1;
  }

  // 每次循环前检查一次GLFW是否被要求退出，如果是的话该函数返回true
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    // 渲染指令
    // ...
    // 设置清空屏幕所用的颜色（状态设置）
    glClearColor(.2f, .3f, .3f, 1.0f);
    // 当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色（状态使用）
    glClear(GL_COLOR_BUFFER_BIT);

    // 前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制
    // 所有的渲染指令执行完毕后，交换(Swap)前缓冲和后缓冲，图像就立即呈显出来，不真实感就消除了
    glfwSwapBuffers(window);
    // 查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
    glfwPollEvents();
  }

  // 正确释放/删除之前的分配的所有资源
  glfwTerminate();

  return 1;
}

void frame_buffer_size_callback (GLFWwindow* window, int width, int height) {
  // 调整视口
  glViewport(0, 0, width, height);
}

void processInput (GLFWwindow* window) {
  // 如果没有按下，glfwGetKey将会返回GLFW_RELEASE
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
