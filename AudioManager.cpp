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

	memset( m_zeroArray , 0 , sizeof( ALfloat ) * 3 );
}//end of constructor

/*Destructor Method*/
AudioManager::~AudioManager()
{
	/* Delete the buffers */
	for( int x = 0 ; x < SL_MAX_SOUND ; x++ )
	{
		alDeleteSources(1, &m_soundSrc[x]);
	}

	alutExit();
}//end of destructor

/*SetListenerValues Method*/
void AudioManager::SetListenerValues()
{
	ALfloat listenerOri[6] = { 0 , 0 , -1.0 , 0 , 1.0 , 0 };
	alListenerfv(AL_POSITION,    m_zeroArray);	//get the listener position
    alListenerfv(AL_VELOCITY,    m_zeroArray);	//get the listener velocity
    alListenerfv(AL_ORIENTATION, listenerOri);	//get the listener orientation
}//end of SetListenerValues

/*LoadSound Method*/
void AudioManager::LoadSound( SoundLookup loadSound , char * soundFilePath , bool isLoop )
{
	// Confirm the sound id is valid
	if( loadSound >= SL_MAX_SOUND )
	{
		return ;
	}
	//variable that each sound can take on
	ALenum format;					//format
	ALsizei size;					//size
    ALvoid* data;					//data
    ALsizei freq;					//freq
    ALboolean loop;					//loop **only one we will be modifying***

	// Load the sound into memory 
	alGenBuffers( 1 , &m_soundBuffers[loadSound] );
	alutLoadWAVFile( soundFilePath , &format , &data , &size , &freq , &loop );
	alBufferData( m_soundBuffers[loadSound] , format , data , size , freq );
	alutUnloadWAV( format , data , size , freq );

	// Unload existing sound
	alDeleteSources( 1 , &m_soundSrc[loadSound] );

	// Create and configure the sound 
	alGenSources( 1 , &m_soundSrc[loadSound] );
	alSourcei( m_soundSrc[loadSound] , AL_BUFFER , m_soundBuffers[loadSound] );
	alSourcef( m_soundSrc[loadSound] , AL_PITCH , 1.0f );
	alSourcef( m_soundSrc[loadSound] , AL_GAIN , 1.0f );
	alSourcefv( m_soundSrc[loadSound] , AL_POSITION , m_zeroArray );
	alSourcefv( m_soundSrc[loadSound] , AL_VELOCITY , m_zeroArray );
	alSourcei( m_soundSrc[loadSound] , AL_LOOPING , isLoop || loop );
	alDeleteBuffers( 1 , &m_soundBuffers[loadSound] );
}//end of LoadSound

/*PlayALSource Method*/ 
void AudioManager::PlayALSource(SoundLookup playSound)
{
	// Confirm the sound id is valid
	if( playSound >= SL_MAX_SOUND )
	{
		return ;
	}
	alSourcePlay( m_soundSrc[playSound] );
}//end of PlayALSource

/*StopALSource Method*/ 
void AudioManager::StopALSource(SoundLookup stopSound)
{
	// Confirm the sound id is valid
	if( stopSound >= SL_MAX_SOUND )
	{
		return ;
	}
	alSourceStop( m_soundSrc[stopSound] );
}//end of StopALSource

/*HoldALSource Method*/
void AudioManager::HoldALSource(SoundLookup holdSound)
{
	// Confirm the sound id is valid
	if( holdSound >= SL_MAX_SOUND )
	{
		return ;
	}
	alSourcePause( m_soundSrc[holdSound] );
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