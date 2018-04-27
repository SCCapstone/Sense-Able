/*********************************************************************
 * Class for playing notification sounds.
 *
 * Date last modified: 8 December 2017
 * Author: Austin Scampini, Caleb Kisby
***/

using namespace std;
#include "usernotifier.h"

#include <QSound>



/*********************************************************************
 *********************************************************************
                           PUBLIC
 *********************************************************************
**********************************************************************/



/*********************************************************************
 * The usual constructor.
 *
 * We store hardcoded sound filenames to a 'vector' 'soundFiles' to
 * be played back later.
***/
UserNotifier::UserNotifier() {

    soundsDirectory = "../media/sounds/";

    // Objects Map to the index of the vector via the integer defined in globalconstants.h

    // Populate vectors with default values
    defaultSoundFiles = {
        "short.wav",
        "long.wav",
        "short-long.wav",
        "long-short.wav",
        "short-short.wav",
        "short-short-long.wav",
        "long-short-short.wav",
        "blaster-firing.wav"
    };

    soundFiles = defaultSoundFiles;

    voiceFiles = {
        "Wall_Voice.wav",
        "Wall_Corner_Voice.wav",
        "Pillar_Voice.wav",
        "Trip_Hazard_Voice.wav",
        "Other_Voice.wav",
        "Stairs_Voice.wav",
        "Other_Voice.wav",
        "Other_Voice.wav"
    };

}


/********************************************************
 *************
 * The usual destructor.
 *
 ***/
UserNotifier::~UserNotifier() {
    return;
}


/*
 * Plays the sound stored at index
 */
/*********************************************************************
 * Function to play the sound given by the index.
 *
 * If the 'index' is valid, this function plays the sound stored in
 * the 'vector' 'soundFiles' at the given 'index'.
***/
void UserNotifier::playSound(int object) {

    if ( object != NONE && object < soundFiles.size() - 1) {

        if (fileType == SOUNDFILES) {
            QSound::play(QString::fromStdString(soundsDirectory + soundFiles.at(object)));
        }

        else { // fileType == VOICEFILES
            QSound::play(QString::fromStdString(soundsDirectory + voiceFiles.at(object)));

        }
    }
}


// End of file usernotifier.cpp

