#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "TestApp.h"
#include "soil/SOIL.h"

TestApp::TestApp():
m_textureId(0)
{
}

TestApp::~TestApp()
{
}

bool TestApp::InitApp() 
{ 
	glEnable(GL_TEXTURE_2D);
	//GraphicLoaders::LoadNewBitmap( L"dude.bmp" , m_textureId );
	m_textureId = SOIL_load_OGL_texture
	(
		"dude.tga",
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y //| SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glColor4f(1.0f,1.0f,1.0f,0.5f);			// Full Brightness, 50% Alpha ( NEW )
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return true; 
}

void TestApp::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix									// Finished Drawing The Triangle
	glBindTexture( GL_TEXTURE_2D , m_textureId );
	glEnable(GL_BLEND); 
	glDisable(GL_DEPTH_TEST);
	glTranslatef(0.0f,0.0f,-6.0f);						// Move Right 3 Units
	glBegin(GL_QUADS);									// Draw A Quad
		glTexCoord2d( 0 , 1 );
		glVertex3f(-1.0f, 1.5f, 0.0f);					// Top Left
		glTexCoord2d( 1 , 1 );
		glVertex3f( 1.0f, 1.5f, 0.0f);					// Top Right
		glTexCoord2d( 1 , 0 );
		glVertex3f( 1.0f,-1.5f, 0.0f);					// Bottom Right
		glTexCoord2d( 0 , 0 );
		glVertex3f(-1.0f,-1.5f, 0.0f);					// Bottom Left
	glEnd();
/*	glEnable(GL_DEPTH_TEST); 
	glDisable(GL_BLEND);
	glTranslatef(0.0f,0.0f,-7.0f);						// Move Right 3 Units
	glBegin(GL_QUADS);									// Draw A Quad
		glVertex3f(-4.0f, 6.0f, 0.0f);					// Top Left
		glVertex3f( 4.0f, 6.0f, 0.0f);					// Top Right
		glVertex3f( 4.0f,-6.0f, 0.0f);					// Bottom Right
		glVertex3f(-4.0f,-6.0f, 0.0f);					// Bottom Left
	glEnd();*/
}