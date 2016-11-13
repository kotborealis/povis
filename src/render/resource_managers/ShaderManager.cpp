//
// Created by kotborealis on 10.08.2016.
//

#include "ShaderManager.h"

#include <fstream>
#include <vector>

namespace PovisEngine{

ShaderManager::ShaderManager(){}

ShaderManager::~ShaderManager(){}

Shader::WeakPtr ShaderManager::search(std::string filename){
    auto it = list.find(filename);
    if(it != list.end())
        return it->second;
    return Shader::WeakPtr();
}

Shader::Ptr ShaderManager::load(std::string vert, std::string frag){
    Logger::info("Loading shader " << vert << " " << frag);

    Shader::WeakPtr cached_shader = search(vert + frag);
    if(!cached_shader.expired()){
        Logger::info("Already loaded");
        return cached_shader.lock();
    }else{
        Logger::info("NOT LOADED");
    }


    GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);

    std::string line;

    //load vertex shader
    std::string vert_code;
    std::ifstream vert_stream(vert, std::ios::in);
    if(!vert_stream.is_open()){
        Logger::error("Could not open vert shader " << vert);
        throw new Exception();
    }
    line = "";
    while(std::getline(vert_stream, line))
        vert_code += "\n" + line;
    vert_stream.close();

    //load fragment shader
    std::string frag_code;
    std::ifstream frag_stream(frag, std::ios::in);
    if(!frag_stream.is_open()){
        Logger::error("Could not open frag shader " << frag);
        throw new Exception();
    }
    line = "";
    while(std::getline(frag_stream, line))
        frag_code += "\n" + line;
    frag_stream.close();

    GLint result = GL_FALSE;
    GLint log_length;

    //compile vertex shader
    Logger::info("Compiling vert shader " << vert);
    char const* vert_source = vert_code.c_str();
    glShaderSource(vert_id, 1, &vert_source, NULL);
    glCompileShader(vert_id);

    //check
    glGetShaderiv(vert_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vert_id, GL_INFO_LOG_LENGTH, &log_length);
    if(log_length > 1){
        std::vector<char> vert_error((unsigned int)(log_length + 1));
        glGetShaderInfoLog(vert_id, log_length, NULL, &vert_error[0]);
        Logger::error(&vert_error[0]);
        throw new Exception();
    }

    //compile fragment shader
    Logger::info("Compiling frag shader " << frag);
    char const* frag_source = frag_code.c_str();
    glShaderSource(frag_id, 1, &frag_source, NULL);
    glCompileShader(frag_id);

    //check
    glGetShaderiv(frag_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(frag_id, GL_INFO_LOG_LENGTH, &log_length);
    if(log_length > 1){
        std::vector<char> frag_error((unsigned int)(log_length + 1));
        glGetShaderInfoLog(frag_id, log_length, NULL, &frag_error[0]);
        Logger::error(&frag_error[0]);
        throw new Exception();
    }

    //linking
    Logger::info("Linking");
    GLuint prog_id = glCreateProgram();
    glAttachShader(prog_id, vert_id);
    glAttachShader(prog_id, frag_id);
    glLinkProgram(prog_id);

    //check
    glGetShaderiv(prog_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(prog_id, GL_INFO_LOG_LENGTH, &log_length);
    if(log_length > 1){
        std::vector<char> prog_error((unsigned int)(log_length + 1));
        glGetShaderInfoLog(prog_id, log_length, NULL, &prog_error[0]);
        Logger::error(&prog_error[0]);
    }

    glDetachShader(prog_id, vert_id);
    glDetachShader(prog_id, frag_id);

    glDeleteShader(vert_id);
    glDeleteShader(frag_id);

    Shader::Ptr shader(new Shader(prog_id));
    Shader::WeakPtr shaderWeakPtr(shader);

    //Save shader to shaders list
    list.insert(std::make_pair(vert + frag, shaderWeakPtr));

    return shader;
}


}