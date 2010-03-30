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
	Song1 = 0,
	Song2 = 1,
	Song3 = 2,
	Song4 = 3,
	PwrUp = 4,
	ChckPt = 5,
	Coins = 6,
	HitBrick = 7
}; //end enum


class AudioManager 
{

//public methods
public:
	/**
	 * Constructor that loads all of the sounds and
	 * attatches them to the specified sources.
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

	/**
	 * SetListenerValues method that tells the listener
	 * where to listen from.
	 * @param None
	 * @return None
	 */
	void SetListenerValues();

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

//private methods
private:
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