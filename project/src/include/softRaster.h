#include <math.h>

/**
 * 遇到的问题：如何返回不定长度的数组
 * 如何只传入指针，而没有分配内存，会报错（Segmentation fault）：访问的内存超过了系统所给这个程序的内存空间
 * 如果返回动态数组，则用户需要调用 delete 释放内存
 * 解决方案：使用智能指针
*/
float* DDALine (const int x0, const int y0, const int x1, const int y1, const int width, const int height, int& length) {
  int dx = x1 -x0;
  int dy = y1 - y0;
  const unsigned int aps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
  length = (aps + 1) * 2;
  float xInce = (float)dx / aps;
  float yInce = (float)dy / aps;
  float x = x0;
  float y = y0;
  float* points = new float[length];

  for (int i = 0; i <= aps; i++) {
    points[2 * i] = (int)(x + 0.5) / (float)width;
    points[2 * i + 1] = (int)(y + 0.5) / (float)height;

    x += xInce;
    y += yInce;
  }

  return points;
}
