//
// Created by kotborealis on 10.08.2016.
//

#include "ShaderManager.h"

#include <fstream>
#include <vector>

namespace pse{

ShaderManager::ShaderManager(){}

ShaderManager::~ShaderManager(){}

Shader::WeakPtr ShaderManager::search(std::string filename){
    auto it = list.find(filename);
    if(it != list.end())
        return it->second;
    return Shader::WeakPtr();
}

Shader::Ptr ShaderManager::load(ShaderInfo* shaderInfo, size_t size){
    GLuint* shaders_id = new GLuint(size);
    std::string name;

    for(size_t i = 0; i < size; i++) name += shaderInfo[i].file;

    Shader::WeakPtr cached_shader = search(name);
    if(!cached_shader.expired()){
        return cached_shader.lock();
    }

    for(size_t i = 0; i < size; i++){
        std::string code = loadCode(shaderInfo[i].file);
        shaders_id[i] = compileShader(code, shaderInfo[i].shaderType);
    }

    GLuint prog_id = compileProgram(shaders_id, size);

    for(size_t i = 0; i < size; i++){
        glDeleteShader(shaders_id[i]);
    }

    delete shaders_id;

    Shader::Ptr shader(new Shader(prog_id));
    Shader::WeakPtr shaderWeakPtr(shader);

    //Save shader to shaders list
    list.insert(std::make_pair(name, shaderWeakPtr));

    return shader;
}

Shader::Ptr ShaderManager::load(std::string vert, std::string frag){
    ShaderInfo shaderInfo[2];
    shaderInfo[0] = {vert, GL_VERTEX_SHADER};
    shaderInfo[1] = {frag, GL_FRAGMENT_SHADER};

    return load(shaderInfo, 2);
}

Shader::Ptr ShaderManager::load(std::string geom, std::string vert, std::string frag){
    ShaderInfo shaderInfo[3];
    shaderInfo[0] = {vert, GL_VERTEX_SHADER};
    shaderInfo[1] = {frag, GL_FRAGMENT_SHADER};
    shaderInfo[2] = {geom, GL_GEOMETRY_SHADER};

    return load(shaderInfo, 3);
}

std::string ShaderManager::loadCode(std::string& file){
    std::string code;
    std::ifstream stream(file, std::ios::in);
    if(!stream.is_open()){
        Logger::error("Could not open file " << file);
        throw new Exception();
    }
    std::string line = "";
    while(std::getline(stream, line))
        code += "\n" + line;
    stream.close();

    return code;
}

GLuint ShaderManager::compileShader(std::string& code, GLenum shaderType){
    GLuint id = glCreateShader(shaderType);
    char const* source = code.c_str();
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    GLint result = GL_FALSE;
    GLint log_length;

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
    if(log_length > 1){
        std::vector<char> frag_error((unsigned int)(log_length + 1));
        glGetShaderInfoLog(id, log_length, NULL, &frag_error[0]);
        Logger::info(code);
        Logger::error(&frag_error[0]);
        throw new Exception();
    }

    return id;
}

GLuint ShaderManager::compileProgram(GLuint* shaders, size_t shaders_size){
    GLuint id = glCreateProgram();

    for(size_t i = 0; i < shaders_size; i++){
        glAttachShader(id, shaders[i]);
    }

    glLinkProgram(id);

    for(size_t i = 0; i < shaders_size; i++){
        glDetachShader(id, shaders[i]);
    }

    return id;
}


}