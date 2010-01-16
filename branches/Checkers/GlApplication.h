#ifndef _GL_APPLICATION_H_
#define _GL_APPLICATION_H_

#include <string>
#include <windows.h>
#include <list>
#include "GlWindow.h"
#include "KeyHandler.h"
#include "GamePiece.h"
#include "BoardSquare.h"

// 8 X 8 Board
#define NUM_BOARD_SQUARES	64
#define NUM_ROWS			8
#define NUM_COLUMNS			8

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

	void AttemptMove( int pos );

private:
	HINSTANCE hInstance; // Application Instance
	GlWindow m_window;
	KeyHandler m_keys;

	bool m_isActive;
	bool m_applicationRunning;

	BoardSquare * m_board[NUM_BOARD_SQUARES];

	BoardSquare * m_selectedSpace;

	int m_lastTickCount;

	int m_playerNumbersTurn;
};

#endif /* _GL_APPLICATION_H_ */