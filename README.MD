# OpenGL(3.3)

## 基础

> 源于：<https://learnopengl-cn.github.io/>

- 是 API，包含了一系列可以操作图形、图像的函数
- 是 一个由Khronos组织制定并维护的规范(Specification)

- 由于OpenGL的大多数实现都是由显卡厂商编写的，当产生一个bug时通常可以通过升级显卡驱动来解决
- OpenGL自身 是一个巨大的状态机(State Machine)：一系列的变量描述OpenGL此刻应当如何运行

- 核心模式与立即渲染模式
  - 立即渲染模式下，OpenGL的大多数功能都被库隐藏起来，开发者很少有控制OpenGL如何进行计算的自由，确实容易使用和理解，但是效率太低
  - OpenGL3.2开始，规范文档开始废弃立即渲染模式，并鼓励开发者在OpenGL的核心模式(Core-profile)下进行开发，这个分支的规范完全移除了旧的特性
  - 当使用OpenGL的核心模式时，OpenGL迫使我们使用现代的函数，现代函数要求使用者真正理解OpenGL和图形编程，提供了更多的灵活性，更高的效率
  - 所有OpenGL的更高的版本都是在3.3的基础上，引入了额外的功能，并没有改动核心架构

### 环境搭建

- CMake
  > CMake是一个工程文件生成工具。用户可以使用预定义好的CMake脚本，根据自己的选择（像是Visual Studio, Code::Blocks, Eclipse）生成不同IDE的工程文件

- 窗口
  - 创建OpenGL上下文(Context)和一个用于显示的窗口在每个系统上都是不一样的；需要自己处理创建窗口，定义OpenGL上下文以及处理用户输入
  - 最流行的几个库有 GLUT，SDL，SFML 和 GLFW

- GLFW
  > GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文，定义窗口参数以及处理用户输入
  - 下载源代码包：<http://www.glfw.org/download.html>
  - 只需要：编译生成的库 和 include文件夹

- GLAD
  > OpenGL只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的；由于OpenGL驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询；开发者需要在运行时获取函数地址并将其保存在一个函数指针中供以后使用；GLAD 库能简化此过程
  - 是一个在线服务 <http://glad.dav1d.de/>
    - 语言(Language)：C/C++
    - gl：3.3以上
    - Profile：Core
    - 生成加载器：是
  - 获取 zip 包

#### 基于 VS

- CMake 编译 GLFW 源码
  - 点击 Configure 选择 Visual Studio 版本

    ![cmake_compile_sourcecode_vs](../../assets/cmake_compile_sourcecode_vs.png)
  - 点击 Generate 生成

#### 基于 VS Code

<https://www.cnblogs.com/zhong-dev/p/13859282.html>
<https://blog.csdn.net/sarono/article/details/86564726>

- MinGW
  - 下载离线包，解压，配置 path
  - 验证：gcc -v

- CMake 编译 GLFW 源码
  - 似上图，点击 Configure 选择 MinGW
  - 勾选 BUILD_SHARED_LIBS，点击 Generate 生成
  - 进入 build 目录，打开控制台，执行 mingw32-make 命令
  - 从 build/src 目录下得到 glfw3.dll，libglfw3dll.a 两个文件
  - 从 glfw-3.3.5\include\GLFW\ 获取 glfw3.h

- 配置 GLAD
  - 将 glad 编译成了静态库
  - 进入 glad 的目录（含有 include 和 src）

  ```sh
    gcc .\src\glad.c -c -I. \include\
    ar -rc libglad.a glad.o
  ```

  - 得到 glad.o 和 libglad.a 文件，libglad.a 是所需要的

- Vs Code OpenGL C++ 项目

  - 添加扩展 `C/C++ Project Generator`
    - Ctrl + Shift + P
    - Create c++ project

  - libopengl32 在 mingw 中

  - 2.0
    - main.cpp

      ```cpp
        #include <GL/gl.h>
        #include "glfw3.h"
      ```

    - Makefile，更新 `LFLAGS = ./lib/libglfw3dll.a ./lib/libopengl32.a`

    - 项目结构树

      ![项目结构树](../../assets/openGL_env_vscode_structruetree.png)

  - 3.3
    - main.cpp

    ```cpp
      #include <glad/glad.h>
      #include <GLFW/glfw3.h>
    ```

    - Makefile，更新 `LFLAGS = ./lib/libglfw3dll.a ./lib/libopengl32.a ./lib/libglad.a`

    - 项目结构树

      ![项目结构树](../../assets/openGL3.3_env_vscode_structruetree.png)

  - Run - `mingw32-make run`

- `g++ main.cpp -o test libglfw3dll.a libopengl32.a`

### 概念

- `图形渲染管线(Graphics Pipeline)`

  ![opengl-render-piplineflow-chart(berief)](../../assets/opengl-render-piplineflow-chart(berief).png)

- `顶点着色器(Vertex Shader)`：是把3D坐标转为另一种3D坐标，同时允许我们对顶点属性进行一些基本处理
  - 例：`GL_POINTS`、`GL_TRIANGLES`、`GL_LINE_STRIP`
- `图元装配(Primitive Assembly)`：将顶点着色器输出的所有顶点作为输入（如果是GL_POINTS，那么就是一个顶点），并所有的点装配成指定图元的形状
  - `图元(Primitive)`：基本图形元素是任何一个图形表达都是由若干不同的点、线、面图案或相同的图案循环组合而成的。这些点、线、面图案即为基本图形元素
- `几何着色器(Geometry Shader)`：可以通过产生新顶点构造出新的（或是其它的）图元来生成其他形状
- `裁切(Clipping)`：裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率
- `光栅化阶段(Rasterization Stage)`：会把图元映射为最终屏幕上相应的像素，生成供片段着色器(Fragment Shader)使用的片段(Fragment)
  - `片段(Fragment)`：OpenGL中的一个片段是OpenGL渲染一个像素所需的所有数据
- `片段着色器(Fragment Shader)`：主要目的是计算一个像素的最终颜色，这也是所有OpenGL高级效果产生的地方

- `标准化设备坐标(Normalized Device Coordinates, NDC)`：一旦你的顶点坐标已经在顶点着色器中处理过，它们就应该是标准化设备坐标了，标准化设备坐标是一个x、y和z值在-1.0到1.0的一小段空间。任何落在范围外的坐标都会被丢弃/裁剪，不会显示在你的屏幕上
  - 标准化设备坐标接着会变换为屏幕空间坐标(Screen-space Coordinates)，这是使用你通过glViewport函数提供的数据，进行视口变换(Viewport Transform)完成的。所得的屏幕空间坐标又会被变换为片段输入到片段着色器中
- 深度：可以理解为z坐标，它代表一个像素在空间中和你的距离，如果离你远就可能被别的像素遮挡，你就看不到它了，它会被丢弃，以节省资源
- 视口(Viewport)：渲染窗口的尺寸大小
- 顶点数组对象(Vertex Array Object，VAO)：可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中。这样的好处就是，当配置顶点属性指针时，你只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定相应的VAO就行了。这使在不同顶点数据和属性配置之间切换变得非常简单，只需要绑定不同的VAO就行了。刚刚设置的所有状态都将存储在VAO中
  - OpenGL的核心模式要求我们使用VAO，所以它知道该如何处理我们的顶点输入。如果我们绑定VAO失败，OpenGL会拒绝绘制任何东西。

### 简易流程

- 环境准备
  - glfw 初始化
  - glfw 设置 opengl 主次版本、启用核心模式等
  - glfw 创建窗口(并设置窗口变化时的视口调整回调函数)
  - gladLoadGLLoader，管理OpenGL的函数指针
- 绘制前准备
  - 创建着色器及程序对象
  - 链接程序后删除着色器对象
  - 使用glGenVertexArrays创建一个VAO
  - 使用glGenBuffers函数和一个缓冲ID生成一个VBO对象
  - 使用glBindVertexArray绑定VAO(需要放在`设置顶点属性指针`之前)
  - 使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标
    - 顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER，OpenGL允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型
  - 调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
  - glVertexAttribPointer 设置顶点属性指针
  - glEnableVertexAttribArray 启用顶点属性（此时数据已链接顶点属性）
  - 取消ARRAY_BUFFER的绑定
  - 取消 VAO 的绑定
- 窗口绘制
  - 清屏
  - 使用程序对象
  - 绑定 VAO
  - 绘制
  - 窗口相关
    - 交换窗口前后缓冲
    - 查看触发的事件
- 结束绘制
  - 清除 VAO
  - 清除 VBO
  - 删除 程序对象
  - 释放窗口资源

### Example

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void frame_buffer_size_callback (GLFWwindow* window, int width, int height);
void processInput (GLFWwindow* window);

/*
 * 330: OpenGL3.3
 * core: 核心模式
 * layout (location = 0): 设定了输入变量的位置值(Location)
 * in: TODO
*/
const char* vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";
const char* fragShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main () {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit(); // 初始化 glfw
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // openGL 主版本号
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // openGL 次版本号
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用核心模式

// 如果使用的是Mac OS X系统
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  // 创建窗口，失败时返回 NULL
  GLFWwindow* window = glfwCreateWindow(800, 600, "CreateGLFWWindow", NULL, NULL);
  if (!window) {
    cout<<"Failed to create GLFWwindow."<<endl;
    return -1;
  }
  glfwMakeContextCurrent(window);
  // 窗口调整大小时，回调
  glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  // GLAD是用来管理OpenGL的函数指针
  // GLFW给的是glfwGetProcAddress，它根据编译的系统定义了正确的函数
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout<<"Failed to initialize GLAD"<<endl;
    glfwTerminate();
    return -1;
  }

  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  unsigned int vertexShader;
  // 创建一个顶点着色器
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // 把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数先设置为NULL
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  // 如果编译失败，我们会用glGetShaderInfoLog获取错误消息
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    return -1;
  }
  // fragment shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    return -1;
  }
  // program
  // 创建一个程序，并返回新创建程序对象的ID引用
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    cout << "ERROR::PROGRAM::LINK FAILED."<< endl;
    return -1;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
  };

  // 0. 复制顶点数组到缓冲中供OpenGL使用
  unsigned int VBO;
  // 使用glGenBuffers函数和一个缓冲ID生成一个VBO对象
  glGenBuffers(1, &VBO);
  // 把新创建的缓冲绑定到GL_ARRAY_BUFFER目标
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // OpenGL的核心模式要求我们使用VAO，所以它知道该如何处理我们的顶点输入。如果我们绑定VAO失败，OpenGL会拒绝绘制任何东西
  unsigned int VAO;
  // 1. 绑定VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  // 1. 设置顶点属性指针
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  // 解除当前 ARRAY_BUFFER 的绑定
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  // 取消 VAO 的绑定
  glBindVertexArray(0);

  // 每次循环前检查一次GLFW是否被要求退出，如果是的话该函数返回true
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    // 渲染指令
    // ...
    // 设置清空屏幕所用的颜色（状态设置）
    glClearColor(.2f, .3f, .3f, 1.0f);
    // 当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色（状态使用）
    glClear(GL_COLOR_BUFFER_BIT);

    /* 第一个参数指定配置的顶点属性：`layout(location = 0)`
     * 第二个参数指定顶点属性的大小
     * 第三个参数指定数据的类型
     * 下个参数定义我们是否希望数据被标准化(Normalize)
     * 第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔
     * 最后一个参数的类型是void*
    */
    // 2. 当我们渲染一个物体时要使用着色器程序
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    // 3. 绘制物体
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制
    // 所有的渲染指令执行完毕后，交换(Swap)前缓冲和后缓冲，图像就立即呈显出来，不真实感就消除了
    glfwSwapBuffers(window);
    // 查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  // 正确释放/删除之前的分配的所有资源
  glfwTerminate();

  return 1;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void frame_buffer_size_callback (GLFWwindow* window, int width, int height) {
  // 调整视口
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void processInput (GLFWwindow* window) {
  // 如果没有按下，glfwGetKey将会返回GLFW_RELEASE
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
```

### 注意点

- 从CPU把数据发送到显卡相对较慢，所以只要可能我们都要尝试尽量一次性发送尽可能多的数据

### 函数

#### `Shader`

- glCreateShader(GL_VERTEX_SHADER);
- glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  - 第二参数指定了传递的源码字符串数量
- glCompileShader(vertexShader);
  - glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success)
    - 检测在调用glCompileShader后编译是否成功
    - int  success;
  - glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    - 获取消息
    - char infoLog[512];

#### `Program`

- shaderProgram = glCreateProgram();
- glAttachShader(shaderProgram, vertexShader);
- glLinkProgram(shaderProgram);
  - glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  - glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog)

- glUseProgram(shaderProgram);
- glDeleteShader(vertexShader);

#### `Buffer`

- glGenBuffers(1, &VBO);
- glBindBuffer(GL_ARRAY_BUFFER, VBO);
- glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  - GL_STATIC_DRAW ：数据不会或几乎不会改变
  - GL_DYNAMIC_DRAW：数据会被改变很多
  - GL_STREAM_DRAW ：数据每次绘制时都会改变

#### `Pointer`

- glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 *sizeof(float), (void*)0);

#### `Vertex Array Object`

- glBindVertexArray(VAO);
- glEnableVertexAttribArray(0);
- glDisableVertexAttribArray [?]

#### `Viewport`

- glViewport(0, 0, 800, 600);
  - 设置窗口的维度
  - 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）

#### Status

- 状态设置函数
  - glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
    - 设置清空屏幕所用的颜色

- 状态使用函数
  - glClear(GL_COLOR_BUFFER_BIT)