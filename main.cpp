#include <windows.h>											// Windows header file

#include "GlApplication.h"

int WINAPI WinMain(	HINSTANCE hInstance , HINSTANCE prevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	int returnValue = -1;
	GlApplication * mainApp = new GlApplication();

	if( mainApp )
	{
		mainApp->Main( hInstance , prevInstance , lpCmdLine , nCmdShow );
		delete mainApp;
	}
	else
	{
		MessageBox( NULL , L"Error creating the application class." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
	}

	return returnValue;
}

LRESULT CALLBACK WindowProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	LONG user_data = GetWindowLong( hWnd , GWL_USERDATA );					// Load The Application Class Context
	if ( user_data )
	{	
		// Get The Application Class Context
		GlApplication * app = reinterpret_cast<GlApplication *>( user_data );
		return app->MessageHandler( hWnd , uMsg , wParam , lParam );	// Call Class Message Handler
	}
	else
	{
		if (uMsg == WM_CREATE)												// Evaluate Window Message
		{																	// Window Creation Message Received
			CREATESTRUCT * creation = reinterpret_cast<CREATESTRUCT *>( lParam );
			GlApplication * app = reinterpret_cast<GlApplication *>( creation->lpCreateParams );
			// Stash The Application Class  in the user data of the window
			SetWindowLong( hWnd , GWL_USERDATA , reinterpret_cast<LONG>( app ) );
			return 0;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);					// Pass Unhandled Messages To DefWindowProc
}