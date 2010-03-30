//Jonathan Caron
//Software Engineering
//Prof. Zhang
//March 29, 2010
//This is a test of the audio manager

#include "AudioManager.h"
#include<iostream>		//for input and output
#include<cstdlib>
#include<conio.h>
#include<iostream>

int main(int argc, char *argv[])
{
	std::cout << "This is a test for all aspects of every sound written\nPlease read the key below to use\n" << std::endl;
	std::cout << "Song 1:		q = play, w = stop, 1 = pause\n" << std::endl;
	std::cout << "Song 2:		e = play, r = stop, 2 = pause\n" << std::endl;
	std::cout << "Song 3:		t = play, y = stop, 3 = pause\n" << std::endl;
	std::cout << "Mushroom:	a = play, s = stop, 4 = pause\n" << std::endl;
	std::cout << "CheckPt:	d = play, f = stop, 5 = pause\n" << std::endl;
	std::cout << "Coin:		g = play, h = stop, 6 = pause\n" << std::endl;
	std::cout << "HitBrick:	z = play, x = stop, 7 = pause\n" << std::endl;
	std::cout << "QUIT:		p\n" << std::endl;
	std::cout << "---------------------------------------\n\n" <<std::endl;
	std::cout << "Input:\n" << std::endl;

	//make a new constructor that loads all of the files
	AudioManager *mySoundManager = new AudioManager();

	//load three files
	mySoundManager->LoadSound(SL_SONG1, true);
	mySoundManager->LoadSound(SL_SONG2, true);
	mySoundManager->LoadSound(SL_SONG3, true);
	mySoundManager->LoadSound(SL_PWRUP, false);
	mySoundManager->LoadSound(SL_CHCKPT, false);
	mySoundManager->LoadSound(SL_COINS, false);
	mySoundManager->LoadSound(SL_HITBRICK, false);
	

	//set the listener properties
	mySoundManager->SetListenerValues();


	char key = 'z';
	while( key != 'p' )
	{
		key = getch();
		switch( key )
		{
		case 'q':
			mySoundManager->PlayALSource(SL_SONG1);
			break;
		case 'w':
			mySoundManager->StopALSource(SL_SONG1);
			break;
		case '1':
			mySoundManager->HoldALSource(SL_SONG1);
			break;
		case 'e':
			mySoundManager->PlayALSource(SL_SONG2);
			break;
		case 'r':
			mySoundManager->StopALSource(SL_SONG2);
			break;
		case '2':
			mySoundManager->HoldALSource(SL_SONG2);
			break;
		case 't':
			mySoundManager->PlayALSource(SL_SONG3);
			break;
		case 'y':
			mySoundManager->StopALSource(SL_SONG3);
			break;
		case '3':
			mySoundManager->HoldALSource(SL_SONG3);
			break;
		case 'a':
			mySoundManager->PlayALSource(SL_PWRUP);
			break;
		case 's':
			mySoundManager->StopALSource(SL_PWRUP);
			break;
		case '4':
			mySoundManager->HoldALSource(SL_PWRUP);
			break;
		case 'd':
			mySoundManager->PlayALSource(SL_CHCKPT);
			break;
		case 'f':
			mySoundManager->StopALSource(SL_CHCKPT);
			break;
		case '5':
			mySoundManager->HoldALSource(SL_CHCKPT);
			break;
		case 'g':
			mySoundManager->PlayALSource(SL_COINS);
			break;
		case 'h':
			mySoundManager->StopALSource(SL_COINS);
			break;
		case '6':
			mySoundManager->HoldALSource(SL_COINS);
			break;
		case 'z':
			mySoundManager->PlayALSource(SL_HITBRICK);
			break;
		case 'x':
			mySoundManager->StopALSource(SL_HITBRICK);
			break;
		case '7':
			mySoundManager->HoldALSource(SL_HITBRICK);
		case 'p':
			break;
		};
	}

}//end of main