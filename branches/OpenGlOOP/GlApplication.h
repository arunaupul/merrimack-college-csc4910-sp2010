#ifndef _GL_APPLICATION_H_
#define _GL_APPLICATION_H_

#include <string>
#include <windows.h>
#include "GlWindow.h"
#include "KeyHandler.h"

class GlApplication
{
public:
	GlApplication();
	~GlApplication();

	// Main program loop
	int Main( HINSTANCE hInstance , HINSTANCE prevInstance , LPSTR lpCmdLine , int nCmdShow );

	// Message Handler
	LRESULT MessageHandler( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

	// Draw the scene
	void Draw();

protected:
	bool Init();

private:
	HINSTANCE hInstance; // Application Instance
	GlWindow m_window;
	KeyHandler m_keys;

	bool m_isActive;
	bool m_applicationRunning;
};

#endif /* _GL_APPLICATION_H_ */