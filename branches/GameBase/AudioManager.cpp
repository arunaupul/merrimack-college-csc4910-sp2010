/**
 * @file
 * @author	Jon Caron <caronj88@gmail.com>
 * @version 1.0
 *
 * This is the AudioManager class for the SuperEastGate.
 * The functions this class performs are; looping background
 * sounds, gameplay sounds based on action, pausing sounds,
 * stopping sounds, and possibly loading sounds on demmand.
 *
 */

//include files
#include "AudioManager.h"			//include appropriate header file
#include<al.h>						//used for openal
#include<alc.h>						//used for openal
#include<al\alut.h>					//used to cross platform openal
#include<conio.h>
#include<cstdlib>
#include<iostream>

/*Constructor Method*/
AudioManager::AudioManager()
{
	int refZero = 0;				//used in the init method
	char * refArgv = "";			//used in the init method
	alutInit(&refZero, &refArgv);	//initialize opeanAL
	alGetError();					//check for initialization error

	memset( SourcePos , 0 , sizeof( ALfloat ) * 3 );
	memset( SourceVel , 0 , sizeof( ALfloat ) * 3 );
	memset( ListenerPos , 0 , sizeof( ALfloat ) * 3 );
	memset( ListenerVel , 0 , sizeof( ALfloat ) * 3 );
	memset( ListenerOri , 0 , sizeof( ALfloat ) * 6 );

	ListenerOri[2] = -1.0;			//sets a specific array value
	ListenerOri[4] = 1.0;			//sets a specific array value
}//end of constructor

/*Destructor Method*/
AudioManager::~AudioManager()
{
	/* Delete the buffers */
	alDeleteBuffers(1, &m_Song1Buff);		//deleting song 1 buffer
	alDeleteBuffers(1, &m_Song2Buff);		//deleting song 2 buffer
	alDeleteBuffers(1, &m_Song3Buff);		//deleting song 3 buffer
	alDeleteBuffers(1, &m_Song4Buff);		//deleting song 4 buffer
	alDeleteBuffers(1, &m_PowerupBuff);		//deleting powerup buffer
	alDeleteBuffers(1, &m_CheckpointBuff);	//deleting checkpoint buffer
	alDeleteBuffers(1, &m_CoinBuff);		//deleting coin buffer
	alDeleteBuffers(1, &m_HitBrickBuff);	//deleting hit brick buffer
	alDeleteBuffers(1, &m_DeathBuff);		//deleting death buffer
	alDeleteBuffers(1, &m_JumpBuff);		//deleting jump buffer
	alDeleteBuffers(1, &m_PowerdwnBuff);	//deleting powerdown buffer
	alDeleteBuffers(1, &m_SpecialBuff);		//deleting special buffer



	/* Delete the sources */
	alDeleteSources(1, &m_Song1Src);		//deleting song 1 source
	alDeleteSources(1, &m_Song2Src);		//deleting song 2 source
	alDeleteSources(1, &m_Song3Src);		//deleting song 3 source
	alDeleteSources(1, &m_Song4Src);		//deleting song 4 source
	alDeleteSources(1, &m_PowerupSrc);		//deleting powerup source
	alDeleteSources(1, &m_CheckpointSrc);	//deleting checkpoint source
	alDeleteSources(1, &m_CoinSrc);			//deleting coin source
	alDeleteSources(1, &m_HitBrickSrc);		//deleting hit brick source
	alDeleteSources(1, &m_DeathSrc);		//deleting death source
	alDeleteSources(1, &m_JumpSrc);			//deleting jump source
	alDeleteSources(1, &m_PowerdwnSrc);		//deleting powerdown source
	alDeleteSources(1, &m_SpecialSrc);		//deleting special source

	alutExit();
}//end of destructor

/*SetListenerValues Method*/
void AudioManager::SetListenerValues()
{
	alListenerfv(AL_POSITION,    ListenerPos);	//get the listener position
    alListenerfv(AL_VELOCITY,    ListenerVel);	//get the listener velocity
    alListenerfv(AL_ORIENTATION, ListenerOri);	//get the listener orientation
}//end of SetListenerValues

/*LoadSound Method*/
void AudioManager::LoadSound(SoundLookup loadSound, char * soundFilePath , bool isLoop)
{
	//variable that each sound can take on
	ALenum format;					//format
	ALsizei size;					//size
    ALvoid* data;					//data
    ALsizei freq;					//freq
    ALboolean loop;					//loop **only one we will be modifying***

	//switch statement to find out which song to load
	switch(loadSound)
	{
	case SL_SONG1:
		alGenBuffers(1, &m_Song1Buff);		//attatching song 1 buffer
		alGetError();
		/*background sound 1*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_Song1Buff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_Song1Src);			//song 1 source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_Song1Src, AL_BUFFER,   m_Song1Buff );		/*Song 1*/
			alSourcef (m_Song1Src, AL_PITCH,    1.0f     );
			alSourcef (m_Song1Src, AL_GAIN,     1.0f     );
			alSourcefv(m_Song1Src, AL_POSITION, SourcePos);
			alSourcefv(m_Song1Src, AL_VELOCITY, SourceVel);
			alSourcei (m_Song1Src, AL_LOOPING,  AL_TRUE  );
		}//end of loop check
		else
		{
			alSourcei (m_Song1Src, AL_BUFFER,   m_Song1Buff );		/*Song 1*/
			alSourcef (m_Song1Src, AL_PITCH,    1.0f     );
			alSourcef (m_Song1Src, AL_GAIN,     1.0f     );
			alSourcefv(m_Song1Src, AL_POSITION, SourcePos);
			alSourcefv(m_Song1Src, AL_VELOCITY, SourceVel);
			alSourcei (m_Song1Src, AL_LOOPING,  loop  );
		}//end of loop check
		alGetError();
		break;
	case SL_SONG2:
		alGenBuffers(1, &m_Song2Buff);		//attatching song 2 buffer
		alGetError();
		/*background sound 2*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_Song2Buff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_Song2Src);			//song 2 source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_Song2Src, AL_BUFFER,   m_Song2Buff );		/*Song 2*/
			alSourcef (m_Song2Src, AL_PITCH,    1.0f     );
			alSourcef (m_Song2Src, AL_GAIN,     1.0f     );
			alSourcefv(m_Song2Src, AL_POSITION, SourcePos);
			alSourcefv(m_Song2Src, AL_VELOCITY, SourceVel);
			alSourcei (m_Song2Src, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_Song2Src, AL_BUFFER,   m_Song2Buff );		/*Song 2*/
			alSourcef (m_Song2Src, AL_PITCH,    1.0f     );
			alSourcef (m_Song2Src, AL_GAIN,     1.0f     );
			alSourcefv(m_Song2Src, AL_POSITION, SourcePos);
			alSourcefv(m_Song2Src, AL_VELOCITY, SourceVel);
			alSourcei (m_Song2Src, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	case SL_SONG3:
		alGenBuffers(1, &m_Song3Buff);		//attatching song 3 buffer
		alGetError();
		/*background sound 3*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_Song3Buff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_Song3Src);			//song 3 source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_Song3Src, AL_BUFFER,   m_Song3Buff );		/*Song 3*/
			alSourcef (m_Song3Src, AL_PITCH,    1.0f     );
			alSourcef (m_Song3Src, AL_GAIN,     1.0f     );
			alSourcefv(m_Song3Src, AL_POSITION, SourcePos);
			alSourcefv(m_Song3Src, AL_VELOCITY, SourceVel);
			alSourcei (m_Song3Src, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_Song3Src, AL_BUFFER,   m_Song3Buff );		/*Song 3*/
			alSourcef (m_Song3Src, AL_PITCH,    1.0f     );
			alSourcef (m_Song3Src, AL_GAIN,     1.0f     );
			alSourcefv(m_Song3Src, AL_POSITION, SourcePos);
			alSourcefv(m_Song3Src, AL_VELOCITY, SourceVel);
			alSourcei (m_Song3Src, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	case SL_SONG4:
		alGenBuffers(1, &m_Song4Buff);		//attatching song 4 buffer
		alGetError();
		/*background sound 4*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_Song4Buff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_Song4Src);			//song 4 source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_Song4Src, AL_BUFFER,   m_Song4Buff );		/*Song 4*/
			alSourcef (m_Song4Src, AL_PITCH,    1.0f     );
			alSourcef (m_Song4Src, AL_GAIN,     1.0f     );
			alSourcefv(m_Song4Src, AL_POSITION, SourcePos);
			alSourcefv(m_Song4Src, AL_VELOCITY, SourceVel);
			alSourcei (m_Song4Src, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_Song4Src, AL_BUFFER,   m_Song4Buff );		/*Song 4*/
			alSourcef (m_Song4Src, AL_PITCH,    1.0f     );
			alSourcef (m_Song4Src, AL_GAIN,     1.0f     );
			alSourcefv(m_Song4Src, AL_POSITION, SourcePos);
			alSourcefv(m_Song4Src, AL_VELOCITY, SourceVel);
			alSourcei (m_Song4Src, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	case SL_PWRUP:
		alGenBuffers(1, &m_PowerupBuff);	//attatching powerup buffer
		alGetError();
		/*powerup sound*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_PowerupBuff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_PowerupSrc);			//powerup source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_PowerupSrc, AL_BUFFER,   m_PowerupBuff );		/*powerup*/
			alSourcef (m_PowerupSrc, AL_PITCH,    1.0f     );
			alSourcef (m_PowerupSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_PowerupSrc, AL_POSITION, SourcePos);
			alSourcefv(m_PowerupSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_PowerupSrc, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_PowerupSrc, AL_BUFFER,   m_PowerupBuff );		/*powerup*/
			alSourcef (m_PowerupSrc, AL_PITCH,    1.0f     );
			alSourcef (m_PowerupSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_PowerupSrc, AL_POSITION, SourcePos);
			alSourcefv(m_PowerupSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_PowerupSrc, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	case SL_CHCKPT:
		alGenBuffers(1, &m_CheckpointBuff);	//attatching checkpoint buffer
		alGetError();
		/*checkpoint sound*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_CheckpointBuff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_CheckpointSrc);		//checkpoint source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_CheckpointSrc, AL_BUFFER,   m_CheckpointBuff );	/*checkpoint*/
			alSourcef (m_CheckpointSrc, AL_PITCH,    1.0f     );
			alSourcef (m_CheckpointSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_CheckpointSrc, AL_POSITION, SourcePos);
			alSourcefv(m_CheckpointSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_CheckpointSrc, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_CheckpointSrc, AL_BUFFER,   m_CheckpointBuff );	/*checkpoint*/
			alSourcef (m_CheckpointSrc, AL_PITCH,    1.0f     );
			alSourcef (m_CheckpointSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_CheckpointSrc, AL_POSITION, SourcePos);
			alSourcefv(m_CheckpointSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_CheckpointSrc, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	case SL_COINS:
		alGenBuffers(1, &m_CoinBuff);		//attatching coin buffer
		alGetError();
		/*coin sound*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_CoinBuff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_CoinSrc);			//coin source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_CoinSrc, AL_BUFFER,   m_CoinBuff );		/*coin*/
			alSourcef (m_CoinSrc, AL_PITCH,    1.0f     );
			alSourcef (m_CoinSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_CoinSrc, AL_POSITION, SourcePos);
			alSourcefv(m_CoinSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_CoinSrc, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_CoinSrc, AL_BUFFER,   m_CoinBuff );		/*coin*/
			alSourcef (m_CoinSrc, AL_PITCH,    1.0f     );
			alSourcef (m_CoinSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_CoinSrc, AL_POSITION, SourcePos);
			alSourcefv(m_CoinSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_CoinSrc, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	case SL_HITBRICK:
		alGenBuffers(1, &m_HitBrickBuff);	//attatching hit brick buffer
		alGetError();
		/*hit brick sound*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_HitBrickBuff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_HitBrickSrc);		//hit brick source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_HitBrickSrc, AL_BUFFER,   m_HitBrickBuff );		/*hit brick*/
			alSourcef (m_HitBrickSrc, AL_PITCH,    1.0f     );
			alSourcef (m_HitBrickSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_HitBrickSrc, AL_POSITION, SourcePos);
			alSourcefv(m_HitBrickSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_HitBrickSrc, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_HitBrickSrc, AL_BUFFER,   m_HitBrickBuff );		/*hit brick*/
			alSourcef (m_HitBrickSrc, AL_PITCH,    1.0f     );
			alSourcef (m_HitBrickSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_HitBrickSrc, AL_POSITION, SourcePos);
			alSourcefv(m_HitBrickSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_HitBrickSrc, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	case SL_DEATH:
		alGenBuffers(1, &m_DeathBuff);		//attatching death buffer
		alGetError();
		/*Death sound*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_DeathBuff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_DeathSrc);			//Death source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_DeathSrc, AL_BUFFER,   m_DeathBuff );		/*Death Sound*/
			alSourcef (m_DeathSrc, AL_PITCH,    1.0f     );
			alSourcef (m_DeathSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_DeathSrc, AL_POSITION, SourcePos);
			alSourcefv(m_DeathSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_DeathSrc, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_DeathSrc, AL_BUFFER,   m_DeathBuff );		/*Death Sound*/
			alSourcef (m_DeathSrc, AL_PITCH,    1.0f     );
			alSourcef (m_DeathSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_DeathSrc, AL_POSITION, SourcePos);
			alSourcefv(m_DeathSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_DeathSrc, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	case SL_JUMP:
		alGenBuffers(1, &m_JumpBuff);		//attatching Jump buffer
		alGetError();
		/*Jump sound*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_JumpBuff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_JumpSrc);			//Jump source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_JumpSrc, AL_BUFFER,   m_JumpBuff );		/*Jump Sound*/
			alSourcef (m_JumpSrc, AL_PITCH,    1.0f     );
			alSourcef (m_JumpSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_JumpSrc, AL_POSITION, SourcePos);
			alSourcefv(m_JumpSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_JumpSrc, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_JumpSrc, AL_BUFFER,   m_JumpBuff );		/*Jump Sound*/
			alSourcef (m_JumpSrc, AL_PITCH,    1.0f     );
			alSourcef (m_JumpSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_JumpSrc, AL_POSITION, SourcePos);
			alSourcefv(m_JumpSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_JumpSrc, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	case SL_PWRDOWN:
		alGenBuffers(1, &m_PowerdwnBuff);		//attatching Powerdown buffer
		alGetError();
		/*Powerdown sound*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_PowerdwnBuff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_PowerdwnSrc);			//Powerdown source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_PowerdwnSrc, AL_BUFFER,   m_PowerdwnBuff );		/*Powerdown Sound*/
			alSourcef (m_PowerdwnSrc, AL_PITCH,    1.0f     );
			alSourcef (m_PowerdwnSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_PowerdwnSrc, AL_POSITION, SourcePos);
			alSourcefv(m_PowerdwnSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_PowerdwnSrc, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_PowerdwnSrc, AL_BUFFER,   m_PowerdwnBuff );		/*Powerdown Sound*/
			alSourcef (m_PowerdwnSrc, AL_PITCH,    1.0f     );
			alSourcef (m_PowerdwnSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_PowerdwnSrc, AL_POSITION, SourcePos);
			alSourcefv(m_PowerdwnSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_PowerdwnSrc, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	case SL_SPECIAL:
		alGenBuffers(1, &m_SpecialBuff);		//attatching Special buffer
		alGetError();
		/*Special sound*/
		alutLoadWAVFile(soundFilePath, &format, &data, &size, &freq, &loop);
		alBufferData(m_SpecialBuff, format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);
		alGenSources(1, &m_SpecialSrc);			//Special source
		alGetError();
		if(isLoop == true)
		{
			alSourcei (m_SpecialSrc, AL_BUFFER,   m_SpecialBuff );		/*Special Sound*/
			alSourcef (m_SpecialSrc, AL_PITCH,    1.0f     );
			alSourcef (m_SpecialSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_SpecialSrc, AL_POSITION, SourcePos);
			alSourcefv(m_SpecialSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_SpecialSrc, AL_LOOPING,  AL_TRUE  );
		}//end of if
		else
		{
			alSourcei (m_SpecialSrc, AL_BUFFER,   m_SpecialBuff );		/*Special Sound*/
			alSourcef (m_SpecialSrc, AL_PITCH,    1.0f     );
			alSourcef (m_SpecialSrc, AL_GAIN,     1.0f     );
			alSourcefv(m_SpecialSrc, AL_POSITION, SourcePos);
			alSourcefv(m_SpecialSrc, AL_VELOCITY, SourceVel);
			alSourcei (m_SpecialSrc, AL_LOOPING,  loop  );
		}//end of else
		alGetError();
		break;
	};//end of switch
}//end of LoadSound

/*PlayALSource Method*/ 
void AudioManager::PlayALSource(SoundLookup playSound)
{
	//switch statement to figure out which song to play
	switch(playSound)
	{
	case SL_SONG1:
		alSourcePlay(m_Song1Src);
		break;
	case SL_SONG2:
		alSourcePlay(m_Song2Src);
		break;
	case SL_SONG3:
		alSourcePlay(m_Song3Src);
		break;
	case SL_SONG4:
		alSourcePlay(m_Song4Src);
		break;
	case SL_PWRUP:
		alSourcePlay(m_PowerupSrc);
		break;
	case SL_CHCKPT:
		alSourcePlay(m_CheckpointSrc);
		break;
	case SL_COINS:
		alSourcePlay(m_CoinSrc);
		break;
	case SL_HITBRICK:
		alSourcePlay(m_HitBrickSrc);
		break;
	case SL_DEATH:
		alSourcePlay(m_DeathSrc);
		break;
	case SL_JUMP:
		alSourcePlay(m_JumpSrc);
		break;
	case SL_PWRDOWN:
		alSourcePlay(m_PowerdwnSrc);
		break;
	case SL_SPECIAL:
		alSourcePlay(m_SpecialSrc);
		break;
	};//end of swich statement
}//end of PlayALSource

/*StopALSource Method*/ 
void AudioManager::StopALSource(SoundLookup stopSound)
{
	//switch statement to figure out which song to stop
	switch(stopSound)
	{
	case SL_SONG1:
		alSourceStop(m_Song1Src);
		break;
	case SL_SONG2:
		alSourceStop(m_Song2Src);
		break;
	case SL_SONG3:
		alSourceStop(m_Song3Src);
		break;
	case SL_SONG4:
		alSourceStop(m_Song4Src);
		break;
	case SL_PWRUP:
		alSourceStop(m_PowerupSrc);
		break;
	case SL_CHCKPT:
		alSourceStop(m_CheckpointSrc);
		break;
	case SL_COINS:
		alSourceStop(m_CoinSrc);
		break;
	case SL_HITBRICK:
		alSourceStop(m_HitBrickSrc);
		break;
	case SL_DEATH:
		alSourceStop(m_DeathSrc);
		break;
	case SL_JUMP:
		alSourceStop(m_JumpSrc);
		break;
	case SL_PWRDOWN:
		alSourceStop(m_PowerdwnSrc);
		break;
	case SL_SPECIAL:
		alSourceStop(m_SpecialSrc);
		break;
	};//end of swich statement
}//end of StopALSource

/*HoldALSource Method*/
void AudioManager::HoldALSource(SoundLookup holdSound)
{
	//switch statement to figure out which song to hold
	switch(holdSound)
	{
	case SL_SONG1:
		alSourcePause(m_Song1Src);
		break;
	case SL_SONG2:
		alSourcePause(m_Song2Src);
		break;
	case SL_SONG3:
		alSourcePause(m_Song3Src);
		break;
	case SL_SONG4:
		alSourcePause(m_Song4Src);
		break;
	case SL_PWRUP:
		alSourcePause(m_PowerupSrc);
		break;
	case SL_CHCKPT:
		alSourcePause(m_CheckpointSrc);
		break;
	case SL_COINS:
		alSourcePause(m_CoinSrc);
		break;
	case SL_HITBRICK:
		alSourcePause(m_HitBrickSrc);
		break;
	case SL_DEATH:
		alSourcePause(m_DeathSrc);
		break;
	case SL_JUMP:
		alSourcePause(m_JumpSrc);
		break;
	case SL_PWRDOWN:
		alSourcePause(m_PowerdwnSrc);
		break;
	case SL_SPECIAL:
		alSourcePause(m_SpecialSrc);
		break;
	};//end of swich statement
}//end of HoldALSource

AudioManager * AudioManager::m_instance = 0;

AudioManager * AudioManager::Instance()
{
	if( !m_instance )
	{
		m_instance = new AudioManager();
		m_instance->SetListenerValues();
	}
	return m_instance;
}