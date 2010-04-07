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

#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

//standard include files
#include<al.h>						//used for openal
#include<alc.h>						//used for openal
#include<al\alut.h>					//used to cross platform openal
#include<conio.h>
#include<cstdlib>
#include<iostream>


/**
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
	SL_HITBRICK = 7
}; //end enum


class AudioManager 
{

//public methods
public:
	/**
	 * SetListenerValues method that tells the listener
	 * where to listen from.
	 * @param None
	 * @return None
	 */
	void SetListenerValues();

	/**
	 * LoadSound method that loads a specific sound on demmand
	 * @param enum SoundLookup, bool isLoop
	 * @return none
	 */
	void LoadSound(SoundLookup loadSound, char * soundFilePath , bool isLoop);

	/**
	 * PlayALSource method that will play an imputted source
	 * @param enum
	 * @return None
	 */
	void PlayALSource(SoundLookup playSound);

	/**
	 * StopALSource method that will stop an imputted source
	 * @param enum
	 * @return None
	 */
	void StopALSource(SoundLookup stopSound);

	/**
	 * HoldALSource method that will hold a current sound state
	 * @param enum
	 * @return None
	 */
	void HoldALSource(SoundLookup holdSound);

	static AudioManager * Instance();

protected:
	/**
	 * Constructor that sets up all the components
	 * for the LoadSound method to work
	 * @param None
	 * @return None
	 */
	AudioManager();

	/**
	 * Destructor that unloads and detatches sounds from 
	 * their buffers.
	 * @param None
	 * @return None
	 */
	~AudioManager();
	AudioManager( const AudioManager & );
	AudioManager & operator=( const AudioManager & );
//private methods
private:
	static AudioManager * m_instance;
	/*Declare all the buffers and sources*/
	ALuint m_Song1Buff;			//first song buffer
	ALuint m_Song2Buff;			//second song buffer
	ALuint m_Song3Buff;			//third song buffer
	//ALuint m_Song4Buff;			//fourth song buffer
	ALuint m_PowerupBuff;		//powerup buffer
	ALuint m_CheckpointBuff;	//checkpoint buffer
	ALuint m_CoinBuff;			//coin buffer
	ALuint m_HitBrickBuff;		//hit brick buffer
	
	ALuint m_Song1Src;			//first song source
	ALuint m_Song2Src;			//second song source
	ALuint m_Song3Src;			//third song source
	//ALuint m_Song4Src;			//fourth song source
	ALuint m_PowerupSrc;		//powerup source
	ALuint m_CheckpointSrc;		//checkpoint source
	ALuint m_CoinSrc;			//coin source 
	ALuint m_HitBrickSrc;		//hit brick source

	ALfloat SourcePos[3];		//set the position of the source
	ALfloat SourceVel[3];		//set the velocity of the source
	ALfloat ListenerPos[3];		//set the position of the listener
	ALfloat ListenerVel[3];		//set the velocity of the listener
	ALfloat ListenerOri[6];		//set the orientation of the listener (right at us)
};//end of AudioManager.h

#endif /* _AUDIO_MANAGER_ */