#ifndef _GL_APPLICATION_H_
#define _GL_APPLICATION_H_

#include <string>
#include <windows.h>
#include <list>
#include "GlWindow.h"
#include "KeyHandler.h"
#include "GlCircle.h"

class GlApplication
{
public:
	GlApplication();
	~GlApplication();

	// Main program loop
	int Main( HINSTANCE hInstance , HINSTANCE prevInstance , LPSTR lpCmdLine , int nCmdShow );

	// Message Handler
	LRESULT MessageHandler( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );


	Point GetPointAtCursor( LPARAM lParam );

protected:
	// Draw the scene
	void Draw();

	// Set up the gl window
	bool Init();

	// Update all object
	void Update();

private:
	HINSTANCE hInstance; // Application Instance
	GlWindow m_window;
	KeyHandler m_keys;

	bool m_isActive;
	bool m_applicationRunning;

	std::list<GlCircle *> m_drawList;
	RgbaColor m_color;
	double m_circleSize;

	int m_lastTickCount;
};

#endif /* _GL_APPLICATION_H_ */