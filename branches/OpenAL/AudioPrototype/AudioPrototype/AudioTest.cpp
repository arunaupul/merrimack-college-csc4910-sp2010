//Jonathan Caron @<caronjb@merrimack.edu>
//Software Engineering
//Prof. Zhang
//February 26, 2010
//--------------------------------------------------
//Audio Manager Tester <AudioTest.cpp>
//-----------------------
// This is test cpp file to confirm that my class
// indeed functions the way i want it to. Ideally it
// should loop one sound, and should be able to play
// two sounds simultaneously based on keystrokes.
// This can be customized to fit the specifications
// of our program.
//--------------------------------------------------
/*include files <<<Dont know if openal ones are necessary>>*/
#include<al.h>						//used for openal
#include<alc.h>						//used for openal
#include<al\alut.h>					//used to cross platform openal

#include "AudioManager.h"
#include<conio.h>
#include<cstdlib>
#include<iostream>

//main function
int main(int argc, char *argv[])
{
	alutInit(&argc, argv);				//start up openal
    alGetError();						//check for an error

	//declare an audio Manager
	AudioManager * myManager = new AudioManager();

	myManager->LoadALData();			//load the AL data buffers
	myManager->SetListenerValues();		//set where the listener is listening

	ALubyte c = ' ';					//create the byte listening on the keyboard
	std::cout << "This is a proof of concept for the audio portion of our project.\n\nPress 's' to start the prototype.\nPress 'j' for a jump sound.\nPress 'a' for another jump sound.\nPress 'q' to quit\n" << std::endl;

	//this watches input and gives appropriate output sounds
	while(c != 'q')
	{
		c = getche();					//get the char from the keyboard

		//switch statement to see which char was pressed
		switch(c)
		{
		case 's':
			myManager->PlayALSource(0);
			std::cout << std::endl;
			break;
		case 'j':
			myManager->PlayALSource(1);
			std::cout << std::endl;
			break;
		case 'a':
			myManager->PlayALSource(2);
			std::cout << std::endl;
			break;
		};//end of switch statement
	}//end of while loop
	
	delete myManager;					//clean up the class after
	return 0;
}//end of main function

