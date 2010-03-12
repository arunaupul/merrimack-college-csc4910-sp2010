//Jonathan Caron @<caronjb@merrimack.edu>
//Software Engineering
//Prof. Zhang
//February 19, 2010
//--------------------------------------------------
//Audio Manager Prototype <AudioManager.cpp>
//-----------------------
//This will closely resemble in function what we
//we will be doing for the audio for our game. This
//prototype will allow for a looping background 
//sound, and several event driven sounds. This
//prototype will change as needed to reflect the
//actual implementation.
//--------------------------------------------------

//include files
#include "AudioManager.h"			//include appropriate header file
#include<al.h>						//used for openal
#include<alc.h>						//used for openal
#include<al\alut.h>					//used to cross platform openal
#include<conio.h>
#include<cstdlib>
#include<iostream>

/*constructor*/ 
AudioManager::AudioManager()
{
	memset( SourcePos , 0 , sizeof( ALfloat ) * 3 );
	memset( SourceVel , 0 , sizeof( ALfloat ) * 3 );
	memset( ListenerPos , 0 , sizeof( ALfloat ) * 3 );
	memset( ListenerVel , 0 , sizeof( ALfloat ) * 3 );
	memset( ListenerOri , 0 , sizeof( ALfloat ) * 6 );

	ListenerOri[2] = -1.0;
	ListenerOri[4] = 1.0;

}//end of constructor

/*deconstructor*/
AudioManager::~AudioManager()
{
}//end of deconstructor

/*Loads the AL data*/
ALboolean AudioManager::LoadALData()
{
	//variables to load into
	ALenum format;
	ALsizei size;
    ALvoid* data;
    ALsizei freq;
    ALboolean loop;

	//load the sound files into their buffers
	alGenBuffers(1, &songBuff);
	alGenBuffers(1, &jumpBuff);
	alGenBuffers(1, &altJumpBuff);

	//check for an error
	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	//grab the actual audio file and variables
	/*background sound*/
	alutLoadWAVFile("media/Footsteps.wav", &format, &data, &size, &freq, &loop);
	alBufferData(songBuff, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	/*jump 1 sound*/
	alutLoadWAVFile("media/wave1.wav", &format, &data, &size, &freq, &loop);
	alBufferData(jumpBuff, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	/*jump 2 sound*/
	alutLoadWAVFile("media/wave2.wav", &format, &data, &size, &freq, &loop);
	alBufferData(altJumpBuff, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	//create the sources
	alGenSources(1, &songSrc);
	alGenSources(1, &jumpSrc);
	alGenSources(1, &altJumpSrc);

	//do another error check
	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	//load the source with the buffers and give the variables
	alSourcei (songSrc, AL_BUFFER,   songBuff );		/*Background Song*/
    alSourcef (songSrc, AL_PITCH,    1.0f     );
    alSourcef (songSrc, AL_GAIN,     1.0f     );
    alSourcefv(songSrc, AL_POSITION, SourcePos);
    alSourcefv(songSrc, AL_VELOCITY, SourceVel);
    alSourcei (songSrc, AL_LOOPING,  AL_TRUE  );

	alSourcei (jumpSrc, AL_BUFFER,   jumpBuff );		/*Jump 1 Sound*/
    alSourcef (jumpSrc, AL_PITCH,    1.0f     );
    alSourcef (jumpSrc, AL_GAIN,     1.0f     );
    alSourcefv(jumpSrc, AL_POSITION, SourcePos);
    alSourcefv(jumpSrc, AL_VELOCITY, SourceVel);
    alSourcei (jumpSrc, AL_LOOPING,  loop  );

	alSourcei (altJumpSrc, AL_BUFFER,   altJumpBuff );		/*Jump 2 Sound*/
    alSourcef (altJumpSrc, AL_PITCH,    1.0f     );
    alSourcef (altJumpSrc, AL_GAIN,     1.0f     );
    alSourcefv(altJumpSrc, AL_POSITION, SourcePos);
    alSourcefv(altJumpSrc, AL_VELOCITY, SourceVel);
    alSourcei (altJumpSrc, AL_LOOPING,  loop  );

	//one last error check to make sure completion was succesful
	if (alGetError() == AL_NO_ERROR)
        return AL_TRUE;

    return AL_FALSE;
}//end of LoadALData

//SetListenerValues method
void AudioManager::SetListenerValues()
{
	alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
}//end of set listener values

//KillALData() method
void AudioManager::KillALData()
{
	/*Delete The Buffers*/
	alDeleteBuffers(1, &songBuff);
	alDeleteBuffers(1, &jumpBuff);
    alDeleteBuffers(1, &altJumpBuff);
	
	/*Delete The Sources*/
	alDeleteSources(1, &songSrc);
	alDeleteSources(1, &jumpSrc);
	alDeleteSources(1, &altJumpSrc);

    alutExit();						//exit
}//end of KillALData

//PlayALSource method
void AudioManager::PlayALSource(int num)
{
	//switch statement for which sound to play
	switch(num)
	{
	case BGROUND:
		alSourcePlay(songSrc);
		break;
	case JUMP1:
		alSourcePlay(jumpSrc);
		break;
	case JUMP2:
		alSourcePlay(altJumpSrc);
		break;
	};//end of switch statment
}//end of PlayALSource