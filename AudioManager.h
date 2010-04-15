/**
 * @file AudioManager.h
 * @author	Jon Caron <caronj88@gmail.com>
 * @version 1.0
 *
 * Contains all relivant classes and enums for playing audio
 *
 */

#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include<al.h>						//used for openal
#include<alc.h>						//used for openal
#include<al\alut.h>					//used to cross platform openal
#include<conio.h>
#include<cstdlib>
#include<iostream>


/**
* @enum SoundLookup
* enum to use to play the appropriate sound
*/
enum SoundLookup{
	SL_SONG1 = 0,
	SL_SONG2 = 1,
	SL_SONG3 = 2,
	SL_SONG4 = 3,
	SL_PWRUP = 4,
	SL_CHCKPT = 5,
	SL_COINS = 6,
	SL_HITBRICK = 7,
	SL_DEATH = 8,
	SL_JUMP = 9,
	SL_PWRDOWN = 10,
	SL_SPECIAL = 11,
	SL_MAX_SOUND
}; //end enum


/**
 * @class AudioManager
 * @brief Singeton Object to play and pause sounds
 *
 * This is the AudioManager class for the SuperEastGate.
 * The functions this class performs are; looping background
 * sounds, gameplay sounds based on action, pausing sounds,
 * stopping sounds, and possibly loading sounds on demmand.
 */
class AudioManager 
{
public:
	/**
	 * SetListenerValues method that tells the listener
	 * where to listen from.
	 */
	void SetListenerValues();

	/**
	 * LoadSound method that loads a specific sound on demmand
	 * @param loadSound Sound ID for the buffer to load
	 * @param soundFilePath Path to the wav file to load
	 * @param isLoop Should the sound loop once started
	 */
	void LoadSound(SoundLookup loadSound, char * soundFilePath , bool isLoop);

	/**
	 * PlayALSource method that will play an imputted source
	 * @param playSound Sound ID for the buffer to play
	 */
	void PlayALSource(SoundLookup playSound);

	/**
	 * StopALSource method that will stop an imputted source
	 * @param stopSound Sound ID for the buffer to stop
	 */
	void StopALSource(SoundLookup stopSound);

	/**
	 * HoldALSource method that will hold a current sound state
	 * @param holdSound Sound ID for the buffer to pause
	 */
	void HoldALSource(SoundLookup holdSound);

	/**
	 * Method to obtain the instance of this singleton object
	 * @return The singleton instance of the AudioManager
	 */
	static AudioManager * Instance();

protected:
	/**
	 * Constructor that sets up all the components
	 * for the LoadSound method to work
	 */
	AudioManager();

	/**
	 * Destructor that unloads and detatches sounds from 
	 * their buffers.
	 */
	~AudioManager();
	AudioManager( const AudioManager & );
	AudioManager & operator=( const AudioManager & );

private:
	static AudioManager * m_instance;
	/*Declare all the buffers and sources*/
	ALuint m_soundBuffers[SL_MAX_SOUND];
	ALuint m_soundSrc[SL_MAX_SOUND];

	ALfloat m_zeroArray[3];
};//end of AudioManager.h

#endif /* _AUDIO_MANAGER_ */