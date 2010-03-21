#include "GraphicLoaders.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "soil/SOIL.h"

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

#include <sstream>
bool GraphicLoaders::LoadTga( const std::wstring & fileName , TextureIdentifier & textureId )
{
	std::string convertedString;
	convertedString.assign( fileName.begin() , fileName.end() );
	return LoadTga( convertedString , textureId );
}

bool GraphicLoaders::LoadTga( const std::string & fileName , TextureIdentifier & textureId )
{
	if( ( textureId = SOIL_load_OGL_texture
	(
		fileName.c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y //| SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	) ) == 0 )
	{
		return false;
	}
	return true;
}