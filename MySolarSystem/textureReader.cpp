#include "textureReader.h"


void TextureReader::loadTexture2D(const char* textureFile,GLuint textureID)
{ 
    glBindTexture(GL_TEXTURE_2D, textureID);

	CTargaImage	*textureOne = new CTargaImage;
		if (!textureOne->Load(textureFile))
		{
		std::cout<<"Loading texture "<<textureFile<<" failed"<<std::endl;
		exit(0);
		}
		
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureOne->GetWidth(), textureOne->GetHeight(),
				 0, GL_RGB, GL_UNSIGNED_BYTE, textureOne->GetImage());

}

void TextureReader::disableTexture2d()
{
	glDisable(GL_TEXTURE_2D);


}