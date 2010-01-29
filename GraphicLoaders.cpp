#include "GraphicLoaders.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

bool GraphicLoaders::LoadNewBitmap( const std::wstring & fileName , TextureIdentifier & textureId )
{
	HBITMAP hBMP;							// Bitmap Handler
	BITMAP BMP;								// Bitmap structure

	if( !( GetFileAttributes( fileName.c_str() ) != 0xFFFFFFFF ) )
	{
		return false;
	}

	glGenTextures( 1 , &textureId );		// Create the new texture
	hBMP = (HBITMAP) LoadImage( GetModuleHandle( NULL ) , fileName.c_str() , IMAGE_BITMAP , 0 , 0 , LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if( !hBMP )
	{
		return false;
	}

	GetObject( hBMP , sizeof( BMP ) , &BMP );

	glPixelStorei( GL_UNPACK_ALIGNMENT , 4 );

	glBindTexture( GL_TEXTURE_2D , textureId );
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D , 0 , 3 , BMP.bmWidth , BMP.bmHeight , 0 , GL_BGR_EXT , GL_UNSIGNED_BYTE , BMP.bmBits );

	DeleteObject( hBMP );
	return true;
}