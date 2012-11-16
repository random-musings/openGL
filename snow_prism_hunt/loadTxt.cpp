#include "stdafx.h"
void freetexture (GLuint texture) {
    glDeleteTextures( 1, &texture );
}

GLuint loadtextures (const char *filename, float width, float height) {
  GLuint texture;

  unsigned char *data;
  FILE *file;

  file = fopen( filename, "rb" );
  if ( file == NULL ) return 0;

  data = (unsigned char *)malloc( width * height * 3 );
  fread( data, width * height * 3, 1, file );

  fclose( file );
  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D,3,GL_RGBA8,width,height,0,GL_BGR,GL_UNSIGNED_BYTE,data);
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
  // glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
   glEnable(GL_TEXTURE_2D);

 //    glGenTextures(1, &texture);
 //  glBindTexture(GL_TEXTURE_2D, texture);
 //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
 //  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 
 //  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
  data = NULL;

  return texture;
}