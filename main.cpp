/*
 *************************
 **   Ryan Fleming      **
 **   Main              **
 **   Jan 27, 2010      **
 **         ,,,         **
 **        (0 0)        **
 **  ---ooO-(_)-Ooo---  **
 *************************
 * Version 1
 *
 * Main function for the app
 */

#include <windows.h>											// Windows header file
#include "GameTest.h"

int WINAPI WinMain(	HINSTANCE hInstance , HINSTANCE prevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	int returnValue = -1;
	GameTest * mainApp = new GameTest();

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