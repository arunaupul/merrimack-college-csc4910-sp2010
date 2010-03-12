//Jonathan Caron @<caronjb@merrimack.edu>
//Software Engineering
//Prof. Zhang
//February 19, 2010
//--------------------------------------------------
//Audio Manager Prototype <AudioManager.h>
//-----------------------
//This will closely resemble in function what we
//we will be doing for the audio for our game. This
//prototype will allow for a looping background 
//sound, and several event driven sounds. This
//prototype will change as needed to reflect the
//actual implementation.
//****NEED to figure out how to work in killALData
//****NEED to include stop and pause methods for sounds
//--------------------------------------------------

#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

//standard include files
#include<al.h>						//used for openal
#include<alc.h>						//used for openal
#include<al\alut.h>					//used to cross platform openal
#include<conio.h>
#include<cstdlib>
#include<iostream>

class AudioManager
{
//public methods
public:
	AudioManager();				//constructor
	~AudioManager();			//destructor
	ALboolean LoadALData();		//loads all the buffers and sources
	void SetListenerValues();	//sets values already given to the listener
	void KillALData();			//frees up memory used by buffers and sources
	void PlayALSource(int num);
private:
	/*Declare Buffers and Sources*/ 
	ALuint songBuff;					//background music buffer
	ALuint jumpBuff;					//gamedude jump buffer
	ALuint altJumpBuff;					//alternate jump sound buffer
	ALuint songSrc;						//background music source
	ALuint jumpSrc;						//gamedude jump source
	ALuint altJumpSrc;					//alternate jump sound source
	
	ALfloat SourcePos[3];
	ALfloat SourceVel[3];	//set the velocity of the source
	ALfloat ListenerPos[3];	//set the position of the listener
	ALfloat ListenerVel[3];	//set the velocity of the listener
	ALfloat ListenerOri[6];	//set the orientation of the listener (right at us)
};//end of AudioManager Class


#define BGROUND		0
#define JUMP1		1
#define JUMP2		2

#endif /* _AUDIO_MANAGER_H_ */