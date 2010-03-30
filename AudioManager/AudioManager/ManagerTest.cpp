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
	std::cout << "---------------------------------------\n\n" <<std::endl;
	std::cout << "Input:\n" << std::endl;

	//make a new constructor that loads all of the files
	AudioManager *mySoundManager = new AudioManager();

	//set the listener properties
	mySoundManager->SetListenerValues();

	char key = 'z';
	while( key != 'p' )
	{
		key = getch();
		switch( key )
		{
		case 'q':
			mySoundManager->PlayALSource(Song1);
			break;
		case 'w':
			mySoundManager->StopALSource(Song1);
			break;
		case '1':
			mySoundManager->HoldALSource(Song1);
			break;
		case 'e':
			mySoundManager->PlayALSource(Song2);
			break;
		case 'r':
			mySoundManager->StopALSource(Song2);
			break;
		case '2':
			mySoundManager->HoldALSource(Song2);
			break;
		case 't':
			mySoundManager->PlayALSource(Song3);
			break;
		case 'y':
			mySoundManager->StopALSource(Song3);
			break;
		case '3':
			mySoundManager->HoldALSource(Song3);
			break;
		case 'a':
			mySoundManager->PlayALSource(PwrUp);
			break;
		case 's':
			mySoundManager->StopALSource(PwrUp);
			break;
		case '4':
			mySoundManager->HoldALSource(PwrUp);
			break;
		case 'd':
			mySoundManager->PlayALSource(ChckPt);
			break;
		case 'f':
			mySoundManager->StopALSource(ChckPt);
			break;
		case '5':
			mySoundManager->HoldALSource(ChckPt);
			break;
		case 'g':
			mySoundManager->PlayALSource(Coins);
			break;
		case 'h':
			mySoundManager->StopALSource(Coins);
			break;
		case '6':
			mySoundManager->HoldALSource(Coins);
			break;
		case 'z':
			mySoundManager->PlayALSource(HitBrick);
			break;
		case 'x':
			mySoundManager->StopALSource(HitBrick);
			break;
		case '7':
			mySoundManager->HoldALSource(HitBrick);
		case 'p':
			break;
		};
	}

}//end of main