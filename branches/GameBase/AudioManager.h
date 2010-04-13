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
	SL_SPECIAL = 11
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
	ALuint m_Song1Buff;			//first song buffer
	ALuint m_Song2Buff;			//second song buffer
	ALuint m_Song3Buff;			//third song buffer
	ALuint m_Song4Buff;			//fourth song buffer
	ALuint m_PowerupBuff;		//powerup buffer
	ALuint m_CheckpointBuff;	//checkpoint buffer
	ALuint m_CoinBuff;			//coin buffer
	ALuint m_HitBrickBuff;		//hit brick buffer
	ALuint m_DeathBuff;			//death buffer
	ALuint m_JumpBuff;			//jump buffer
	ALuint m_PowerdwnBuff;		//powerdown buffer
	ALuint m_SpecialBuff;		//special weapon buffer
	
	ALuint m_Song1Src;			//first song source
	ALuint m_Song2Src;			//second song source
	ALuint m_Song3Src;			//third song source
	ALuint m_Song4Src;			//fourth song source
	ALuint m_PowerupSrc;		//powerup source
	ALuint m_CheckpointSrc;		//checkpoint source
	ALuint m_CoinSrc;			//coin source 
	ALuint m_HitBrickSrc;		//hit brick source
	ALuint m_DeathSrc;			//death source
	ALuint m_JumpSrc;			//jump source
	ALuint m_PowerdwnSrc;		//powerdown source
	ALuint m_SpecialSrc;		//special weapon source

	ALfloat SourcePos[3];		//set the position of the source
	ALfloat SourceVel[3];		//set the velocity of the source
	ALfloat ListenerPos[3];		//set the position of the listener
	ALfloat ListenerVel[3];		//set the velocity of the listener
	ALfloat ListenerOri[6];		//set the orientation of the listener (right at us)
};//end of AudioManager.h

#endif /* _AUDIO_MANAGER_ */