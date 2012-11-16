#pragma once

class Texture
{
public:
	Color c;
	int width;
	int height;
	GLubyte *textureImg; 
	GLuint textureID;

	Texture();
	Texture(GLuint newTextureID, int newWidth, int newHeight, GLubyte *newImage,Color newColor);
	~Texture(void);
	void applyTexture();
	void genMipMapTexture(bool isAlpha);
};
