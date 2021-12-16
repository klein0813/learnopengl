#ifndef SHADER_H
  #define SHADER_H
  #include <glad/glad.h>
  #include <iostream>
  #include <fstream>
  #include <sstream>
  
  using namespace std;

  class Shader {
    public:
      unsigned int ID;
      Shader (const char* vertexPath, const char* fragmentPath) {
        string vertexCode;
        string fragmentCode;
        ifstream vShaderFile;
        ifstream fShaderFile;
        // 保证ifstream对象可以抛出异常：
        vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
        fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
        try {
          // 打开文件
          vShaderFile.open(vertexPath);
          fShaderFile.open(fragmentPath);
          stringstream vShaderStream, fShaderStream;
          // 读取文件的缓冲内容到数据流中
          vShaderStream << vShaderFile.rdbuf();
          fShaderStream << fShaderFile.rdbuf();
          // 关闭文件处理器
          vShaderFile.close();
          fShaderFile.close();
          // 转换数据到 string
          vertexCode = vShaderStream.str();
          fragmentCode = fShaderStream.str();
        } catch (ifstream::failure e) {
          cout<< "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ." << endl;
        }
        // 返回一个指向正规C字符串的指针常量
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vShaderCode, NULL);
        glCompileShader(vertexShader);
        checkCompileErrors(vertexShader, "VERTEX");
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
        glCompileShader(fragmentShader);
        checkCompileErrors(fragmentShader, "FRAGMENT");
        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
      };
      void use () {
        glUseProgram(ID);
      };
      void setBool (const char* name, bool value) {
        glUniform1i(glGetUniformLocation(ID, name), (int)value);
      };
      void setInt (const char* name, int value) {
        glUniform1i(glGetUniformLocation(ID, name), value);
      };
      void setFloat (const char* name, float value) {
        glUniform1f(glGetUniformLocation(ID, name), value);
      };
      void set3Float (const char* name, const float* values) {
        glUniform3f(glGetUniformLocation(ID, name), values[0], values[1], values[2]);
      };
      void del () {
        glDeleteProgram(ID);
      };
    private:
      void checkCompileErrors(unsigned int shader, const char* type) {
        int success;
        char infoLog[512];
        if (type != "PROGRAM") {
          glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
          if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            cout<< "ERROR::SHADER::" << type << "::COMPILATION FAILED.\n" << infoLog << endl;
          }
        } else {
          glGetProgramiv(shader, GL_LINK_STATUS, &success);
          if (!success) {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            cout << "ERROR::PROGRAM::" << type << "::LINK FAILED.\n" << infoLog << endl;
          }
        }
      };
  };
#endif
