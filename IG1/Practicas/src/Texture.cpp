#include "Texture.h"

#include "Image.h"

constexpr const char* TEXTURES_ROOT = "../assets/images/";

Texture::~Texture()
{
	if (mId != 0)
		glDeleteTextures(1, &mId);
}

void
Texture::init()
{
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);

	// Filters and clamping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // GL_CLAMP
}

void
Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, mId);
}

void
Texture::load(const std::string& name, GLubyte alpha)
{
	if (mId == 0)
		init();

	Image image;
	image.load(TEXTURES_ROOT + name);

	if (alpha != 255)
		image.setAlpha(alpha);

	mWidth = image.width();
	mHeight = image.height();

	GLint level = 0;  // Base image level
	GLint border = 0; // No border

	glBindTexture(GL_TEXTURE_2D, mId);
	glTexImage2D(GL_TEXTURE_2D,
	             level,
	             GL_RGBA,
	             mWidth,
	             mHeight,
	             border,
	             GL_RGBA,
	             GL_UNSIGNED_BYTE,
	             image.data());

	glBindTexture(GL_TEXTURE_2D, 0);
}

void 
Texture::loadColorBuffer(GLsizei width, GLsizei height, GLuint buffer)
{
	// Si la textura no tiene ID asignado se llama a init para asignarle uno
	if (mId == 0)
		init();
	
	// marca la textura como activa para que las operaciones siguientes se hagan sobre ella
	glBindTexture(GL_TEXTURE_2D, mId);
		glReadBuffer(buffer);
		// Copia 
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, width, height, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void
Texture::setWrap(GLuint wp) // GL_REPEAT, GL_CLAMP_TO_EDGE, ...
{
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wp);
	glBindTexture(GL_TEXTURE_2D, 0);
}
