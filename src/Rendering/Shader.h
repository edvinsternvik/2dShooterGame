#pragma once
#include <glm/glm.hpp>
#include <unordered_map>

class Shader {
public:
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
    ~Shader();
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) = delete;

    void useShader();
    bool compiledSuccessfully() const;

    void setUniform1f(const char* name, const float& v);
    void setUniform2f(const char* name, const float& v1, const float& v2);
    void setUniform3f(const char* name, const float& v1, const float& v2, const float& v3);
    void setUniform4f(const char* name, const float& v1, const float& v2, const float& v3, const float& v4);
    void setUniform1i(const char* name, const int& v);
    void setUniform2i(const char* name, const int& v1, const int& v2);
    void setUniform3i(const char* name, const int& v1, const int& v2, const int& v3);
    void setUniform4i(const char* name, const int& v1, const int& v2, const int& v3, const int& v4);
    void setUniform1ui(const char* name, const unsigned int& v);
    void setUniform2ui(const char* name, const unsigned int& v1, const unsigned int& v2);
    void setUniform3ui(const char* name, const unsigned int& v1, const unsigned int& v2, const unsigned int& v3);
    void setUniform4ui(const char* name, const unsigned int& v1, const unsigned int& v2, const unsigned int& v3, const unsigned int& v4);
    void setUniform1fv(const char* name, const unsigned int count, const float* v);
    void setUniform2fv(const char* name, const unsigned int count, const float* v);
    void setUniform3fv(const char* name, const unsigned int count, const float* v);
    void setUniform4fv(const char* name, const unsigned int count, const float* v);
    void setUniform1iv(const char* name, const unsigned int count, const int* v);
    void setUniform2iv(const char* name, const unsigned int count, const int* v);
    void setUniform3iv(const char* name, const unsigned int count, const int* v);
    void setUniform4iv(const char* name, const unsigned int count, const int* v);
    void setUniform1uiv(const char* name, const unsigned int count, const unsigned int* v);
    void setUniform2uiv(const char* name, const unsigned int count, const unsigned int* v);
    void setUniform3uiv(const char* name, const unsigned int count, const unsigned int* v);
    void setUniform4uiv(const char* name, const unsigned int count, const unsigned int* v);
    void setUniformMat2(const char* name, const glm::mat2& matrix);
    void setUniformMat3(const char* name, const glm::mat3& matrix);
    void setUniformMat4(const char* name, const glm::mat4& matrix);

    unsigned int getShaderProgramID() const { return m_shaderProgramID; }

    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other) = delete;

private:
    int getUniformLocation(const char* name);

private:
    unsigned int m_shaderProgramID;

    std::unordered_map<const char*, int> m_uniformLocations;
};
