#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
#include "readBMP.h"

bool readBmp(const char *infilename, int &PixmapHeight, int&PixmapWidth, unsigned char *&pixels )	/* I - File to load */
{

	BITMAPFILEHEADER bmheader;
    int i;
	ifstream fp( infilename, ios::binary);

 	if ( !fp )
	{
		cerr << "cannot open file\n";
	    return false;
	}

	fp.read( reinterpret_cast<char *>(&bmheader), sizeof(BITMAPFILEHEADER));
	if ( fp.gcount() != sizeof(BITMAPFILEHEADER) )
	{

		fp.close();
		return false;
	}

	if ( bmheader.bfType != 'MB')	// Microsoft Only feature
	{
		cout << "Unsuccessful read of bfType\n";
		fp.close();
		return false;
	}

	int infosize = bmheader.bfOffBits - sizeof( BITMAPFILEHEADER ); //_bmpheader.bfOffBits
	int calc = bmheader.bfSize - bmheader.bfOffBits;            // temp value for texture size

	BITMAPINFO *bminfo;

	if (( bminfo = reinterpret_cast<BITMAPINFO *>(new char[ infosize ])) == NULL)
	{
		cout << "Not enough memory for bitmap info\n";
		fp.close();
		return false;
	}
	fp.read( reinterpret_cast<char *>(bminfo), infosize );

	if ( fp.gcount() != infosize )
	{
	    delete [] bminfo;	
	    fp.close();
		return false;
	}

 
	PixmapHeight = bminfo->bmiHeader.biHeight;
	PixmapWidth = bminfo->bmiHeader.biWidth;

	switch( bminfo->bmiHeader.biBitCount ) {
	case 24:
		break;
	default:
		cout << "Cannot read this bitCount\n";
		delete [] bminfo;
		fp.close();
		return false;
	}

	// Handle compression 
	switch( bminfo->bmiHeader.biCompression )
	{
	case BI_RGB:
		break;
	default:	  //printf("BI_JPEG");
		cout << " Cannot handle this compression\n";
		delete [] bminfo;
		fp.close();
		return false;
	}

	int texturesize;
    if (( texturesize = bminfo->bmiHeader.biSizeImage) == 0)
		texturesize = calc;


 	if ( ( pixels = new GLubyte[texturesize] ) == NULL)
	{
	    delete [] bminfo;
		bminfo = 0;
		fp.close();
		return false;
	}

	cout << "reading " << texturesize << " pixels\n";
	fp.read( reinterpret_cast<char *>(pixels), texturesize );
	if (fp.gcount() != texturesize)
	{
		delete [] bminfo;
	    delete [] pixels;
		bminfo = 0;
		pixels = 0;
		return false;
	 }	
	
    fp.close();
	
	return true;
}
