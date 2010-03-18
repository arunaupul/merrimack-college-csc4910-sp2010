#include "BackGroundManager.h"
#include "GraphicLoaders.h"
#include <windows.h>
#include <gl\gl.h>

BackGroundManager::BackGroundManager( const std::wstring & backgroundPath , double screenWidth , double screenHeight , double backgroundCameraPercent )
:	m_background( 0 ),
	m_screenWidth( screenWidth ),
	m_screenHeight( screenHeight ),
	m_cameraPercent( backgroundCameraPercent )
{
	GraphicLoaders::LoadNewBitmap( backgroundPath , m_background );
}

BackGroundManager::~BackGroundManager()
{
}

void BackGroundManager::Draw( double xOffset )
{
	double start = xOffset / ( m_screenWidth / m_cameraPercent );
	glColor3d( 1.0 , 1.0 , 1.0 );
	glBindTexture( GL_TEXTURE_2D , m_background );
	glBegin( GL_POLYGON );
		glTexCoord2d( start , 1.0 );
		glVertex3d( 0 , m_screenHeight , 0 );
		glTexCoord2d( start + m_cameraPercent , 1.0 );
		glVertex3d( m_screenWidth , m_screenHeight , 0 );
		glTexCoord2d( start + m_cameraPercent , 0.0 );
		glVertex3d( m_screenWidth , 0 , 0 );
		glTexCoord2d( start , 0.0 );
		glVertex3d( 0 , 0 , 0 );
	glEnd();
}