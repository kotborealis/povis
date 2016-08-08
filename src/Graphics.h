/*
 * Graphics.h
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <fstream>

#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#include <SDL2/SDL_image.h>

#include "Logger.h"

namespace PovisEngine {

class Texture{
public:
	Texture(GLuint id)
		:m_id(id){}
	~Texture(){
		glDeleteTextures(1,&m_id);
	}
	GLuint id(){
		return m_id;
	}
private:
	GLuint m_id;
};

class Shader{
public:
	Shader(GLuint id)
		:m_id(id){}
	~Shader(){
		glDeleteProgram(m_id);
	}
	GLuint id(){
		return m_id;
	}
private:
	GLuint m_id;
};

typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Shader> ShaderPtr;

class Graphics {
public:
	Graphics(std::string title, unsigned int width, unsigned int height);
	virtual ~Graphics();

	TexturePtr loadTexture(std::string filename);
	TexturePtr reserveTexture();

	ShaderPtr loadShader(std::string vertex_filename, std::string fragment_filename);

	void clear();
	void render();

	unsigned int width(){
		return m_width;
	}
	unsigned int height(){
		return m_height;
	}

private:
	unsigned int m_width, m_height;
	SDL_Window* window;
	SDL_GLContext gl;

	GLuint textureIdCounter = 1;
	std::map<TexturePtr,std::string> loadedTextures;

	std::vector<ShaderPtr> loadedShaders;

	TexturePtr lookUpTextureByFilename(std::string filename);
};

} /* namespace PovisEngine */

#endif /* GRAPHICS_H_ */
