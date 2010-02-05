#ifndef _GL_APPLICATION_H_
#define _GL_APPLICATION_H_

#include <string>
#include <windows.h>
#include <list>
#include "GlWindow.h"
#include "KeyHandler.h"
#include "GlObject.h"

class GlApplication
{
public:
	GlApplication();
	virtual ~GlApplication();

	// Main program loop
	int Main( HINSTANCE hInstance , HINSTANCE prevInstance , LPSTR lpCmdLine , int nCmdShow );

	// Message Handler
	LRESULT MessageHandler( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

protected:
	// Draw the scene
	virtual void Draw();

	// Set up the gl window
	bool Init();

	virtual bool InitApp() { return true; }

	// Update all objects
	void Update();

	virtual void PerformUpdate();

	void SetResizeGlScene( bool setting );

	std::list< GlObject * > m_objectList;

	int m_lastTickCount;

	bool m_applicationRunning;

private:
	HINSTANCE hInstance; // Application Instance
	GlWindow m_window;
	KeyHandler m_keys;

	bool m_isActive;

	bool m_resizeGlScene;
};

#endif /* _GL_APPLICATION_H_ */