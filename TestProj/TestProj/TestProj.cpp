//Jonathan Caron @<caronj88@gmail.com>
//Software Engineering
//Prof. Zhang
//February 07, 2010
//-------------------------------------------------------------
//Basic Example
//---------------
//This will demonstrate how to loop a sound continuously.
//This applies to our project because we will be having
//background music playing continuously as our character plays
//a level. This code is based on lesson 1-2 on the devmaster
//website.
//-------------------------------------------------------------

//include files
#include<al.h>						//used for openal
#include<alc.h>						//used for openal
#include<al\alut.h>					//used to cross platform openal
#include<conio.h>
#include<cstdlib>
#include<iostream>

ALuint MyBuffer;					//declare buffers
ALuint MySource;					//declare source

//Set the source position to be right here
ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

//set the velocity of the source
ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };

//set the position of the listener
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

//set the velocity of the listener
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

//set the orientation of the listener (right at us)
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

//method to load the AL data that we will be using
ALboolean LoadALData()
{
	//variables to load into
	ALenum format;
	ALsizei size;
    ALvoid* data;
    ALsizei freq;
    ALboolean loop;

	//load the sound file into the buffer
	alGenBuffers(1, &MyBuffer);

	//check for an error
	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;
	
	//grab the actual audio file and variables
	alutLoadWAVFile("media/Footsteps.wav", &format, &data, &size, &freq, &loop);
	alBufferData(MyBuffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	//time to bind the buffer to the source
	alGenSources(1, &MySource);

	//do another error check
	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	//tell the source what buffer and variables to get
	alSourcei (MySource, AL_BUFFER,   MyBuffer );
    alSourcef (MySource, AL_PITCH,    1.0f     );
    alSourcef (MySource, AL_GAIN,     1.0f     );
    alSourcefv(MySource, AL_POSITION, SourcePos);
    alSourcefv(MySource, AL_VELOCITY, SourceVel);
    alSourcei (MySource, AL_LOOPING,  AL_TRUE  );

	//one last error check to make sure completion was succesful
	if (alGetError() == AL_NO_ERROR)
        return AL_TRUE;

    return AL_FALSE;

}//end of LoadALData

//this function updates the listener properties
void SetListenerValues()
{
	alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
}//end of SetListenerValues

//this releases all the memory and audio devices that our program is using
void KillALData()
{
    alDeleteBuffers(1, &MyBuffer);
    alDeleteSources(1, &MySource);
    alutExit();
}//end of KillALData

//main function
int main(int argc, char *argv[])
{
	alutInit(&argc, argv);				//start up openal
    alGetError();						//check for an error

	if (LoadALData() == AL_FALSE)
        return -1;

    SetListenerValues();				//set the values to what we specified above

    // Setup an exit procedure.
    atexit(KillALData);

	 ALubyte c = ' ';

	 std::cout << "This is a loop test.\nPlease press 'p' to play sound\nPlease press 's' to stop the sound\nPlease press 'h' to hold the sound.\nPlease press 'q' to quit.\n" << std::endl;

	 //while loop to check for char "q"
    while (c != 'q')
    {
        c = getche();

		//statement to see if specific keys are pressed
        switch (c)
        {
            // Pressing 'p' will begin playing the sample.
            case 'p': alSourcePlay(MySource); break;

            // Pressing 's' will stop the sample from playing.
            case 's': alSourceStop(MySource); break;

            // Pressing 'h' will pause (hold) the sample.
            case 'h': alSourcePause(MySource); break;
        };//end switch
    }//end while loop

    return 0;

}//end main
