#include "stdafx.h"

Texture::Texture(GLuint newTextureID, int newHeight, int newWidth, GLubyte* newImg,Color newColor):
	height(newHeight),
	width(newWidth),
	textureImg(newImg),
	c(newColor),
	textureID(newTextureID)
{
	genMipMapTexture(false);
}

Texture::~Texture(void)
{
}


Texture::Texture():
	height(0),
	width(0),
	textureImg(0),
	c(1,1,1,1),
	textureID(0)
{
}


void Texture::applyTexture()
{
		if (textureImg==0)
		{
			 //glDisable( GL_TEXTURE_2D );
			 glEnable(GL_COLOR_MATERIAL);
			 glColor4f(c.red,c.green,c.blue,c.transparency);
		}else
		{
			glBindTexture(GL_TEXTURE_2D ,textureID);
		}

}

void Texture::genMipMapTexture(bool isAlpha)
{
	glGenTextures(1, &textureID);
 	 
glEnable(GL_TEXTURE_2D);
std::cout << "Binding the texture." << std::endl;
	glBindTexture(GL_TEXTURE_2D, textureID); //Make the texture the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	if (isAlpha) //(tex_img->format->BitsPerPixel==32)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImg);
    else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImg);
}