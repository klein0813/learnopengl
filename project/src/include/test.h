#ifndef __SHADER_H__
  #define __SHADER_H__
  #include <iostream>
  #include <fstream>
  #include <sstream>

  using namespace std;

  void rdFile (const char* path) {
    string str;
    ifstream file;
    file.exceptions(ifstream::failbit | ifstream::badbit);
    try {
      file.open(path);
      stringstream strStream << file.rdbuf();
      file.close();
      str = strStream.str();
      const char* target = str.c_str();
    } catch (ifstream::failure e) {
      cout << e << endl;
    }
  }
#endif

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

char* loadFile (const char* path) {
  ifstream file;
  file.exceptions(ifstream::failbit | ifstream::badbit);
  try {
    file.open(path);
    stringstream strstream;
    strstream << file.rdbuf();
    file.close(); 
    string str = strstream.str();

    return str.c_str();
  } catch (ifstream::failure e) {
    cout << e << endl;
    return NULL;
  }
}

