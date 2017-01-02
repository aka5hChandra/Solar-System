#ifndef TEXTURE_READER_H
#define TEXTURE_READER_H
#include <GL/glew.h>
#include "CTargaImage.h"
#include <iostream>
class TextureReader
{
public:
	void loadTexture2D(const char* textureFile,GLuint textureID);
void disableTexture2d();
};
#endif