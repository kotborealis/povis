/*
 * Graphics.cpp
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "Graphics.h"

namespace PovisEngine {

Graphics::Graphics(std::string title, unsigned int width, unsigned int height)
	:m_width(width)
	,m_height(height){

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	if(SDL_Init(SDL_INIT_VIDEO)<0)
		Logger::error(SDL_GetError());

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(window == nullptr)
		Logger::error(SDL_GetError());

	if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		Logger::error(SDL_GetError());

	gl = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if(glewError != GLEW_OK)
		Logger::error(glewGetErrorString(glewError));

	if(SDL_GL_SetSwapInterval(1)<0)
		Logger::warn("No v-sync for you fag "<<SDL_GetError());

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

Graphics::~Graphics() {
	for(GLuint i = 0; i < textureIdCounter; i++)
		glDeleteTextures(1,&i);

	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

TexturePtr Graphics::loadTexture(std::string filename){
	Logger::info("Loading texture "<<filename);

	TexturePtr t = lookUpTextureByFilename(filename);
	if(t != nullptr)
		return t;

	auto surface = IMG_Load(filename.c_str());

	if(surface==nullptr){
		Logger::warn(IMG_GetError());
		return 0;
	}

	GLuint tId = textureIdCounter++;

	int mode = GL_RGB;
	if(surface->format->BytesPerPixel == 4) mode = GL_RGBA;

	glGenTextures(1,&tId);
	glBindTexture(GL_TEXTURE_2D,tId);
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(surface);

	t.reset(new Texture(tId));
	loadedTextures.insert(std::make_pair(t,filename));

	return t;
}

TexturePtr Graphics::lookUpTextureByFilename(std::string filename){
	for(auto it = loadedTextures.begin(); it != loadedTextures.end(); it++)
		if(it->second == filename)
			return it->first;
	return nullptr;
}

TexturePtr Graphics::reserveTexture(){
	auto t = TexturePtr(new Texture(textureIdCounter++));
	loadedTextures.insert(std::make_pair(t,""));
	return t;
}

ShaderPtr Graphics::loadShader(std::string vert, std::string frag){
	GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);

	std::string line;

	//load vertex shader
	std::string vert_code;
	std::ifstream vert_stream(vert, std::ios::in);
	if(!vert_stream.is_open()){
		Logger::error("Could not open vert shader "<<vert);
		return ShaderPtr(nullptr);
	}
	line = "";
	while(std::getline(vert_stream, line))
		vert_code += "\n" + line;
	vert_stream.close();

	//load fragment shader
	std::string frag_code;
	std::ifstream frag_stream(frag, std::ios::in);
	if(!frag_stream.is_open()){
		Logger::error("Could not open frag shader "<<frag);
		return ShaderPtr(nullptr);
	}
	line = "";
	while(std::getline(frag_stream, line))
		frag_code += "\n" + line;
	frag_stream.close();

	GLint result = GL_FALSE;
	int log_length;

	//compile vertex shader
	Logger::info("Compiling vert shader "<<vert);
	char const * vert_source = vert_code.c_str();
	glShaderSource(vert_id, 1, &vert_source, NULL);
	glCompileShader(vert_id);

	//check
	glGetShaderiv(vert_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vert_id, GL_INFO_LOG_LENGTH, &log_length);
	if(log_length > 0){
		std::vector<char> vert_error(log_length+1);
		glGetShaderInfoLog(vert_id, log_length, NULL, &vert_error[0]);
		Logger::error(&vert_error[0]);
	}

	//compile fragment shader
	Logger::info("Compiling frag shader "<<frag);
	char const * frag_source = frag_code.c_str();
	glShaderSource(frag_id, 1, &frag_source, NULL);
	glCompileShader(frag_id);

	//check
	glGetShaderiv(frag_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(frag_id, GL_INFO_LOG_LENGTH, &log_length);
	if(log_length > 0){
		std::vector<char> frag_error(log_length+1);
		glGetShaderInfoLog(frag_id, log_length, NULL, &frag_error[0]);
		Logger::error(&frag_error[0]);
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
	if(log_length > 0){
		std::vector<char> prog_error(log_length+1);
		glGetShaderInfoLog(prog_id, log_length, NULL, &prog_error[0]);
		Logger::error(&prog_error[0]);
	}

	glDetachShader(prog_id, vert_id);
	glDetachShader(prog_id, frag_id);

	glDeleteShader(vert_id);
	glDeleteShader(frag_id);

	auto shader = ShaderPtr(new Shader(prog_id));
	loadedShaders.push_back(shader);

	return shader;
}

void Graphics::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::render() {
    glFlush();
	SDL_GL_SwapWindow(window);
}

} /* namespace PovisEngine */
