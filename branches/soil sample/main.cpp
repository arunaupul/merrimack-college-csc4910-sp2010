#include <windows.h>											// Windows header file

#include "TestApp.h"

int WINAPI WinMain(	HINSTANCE hInstance , HINSTANCE prevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	int returnValue = -1;
	TestApp * mainApp = new TestApp();

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