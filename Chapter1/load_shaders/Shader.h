#ifndef CHAPTER1_SHADER_H
#define CHAPTER1_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use()const;
    void setBool(const std::string &name, bool value)const;
    void setInt(const std::string &name, int value)const;
    void setFloat(const std::string &name, float value)const;

private:
    void checkCompileErrors(unsigned int shader, const std::string &type);

};


#endif //CHAPTER1_SHADER_H
