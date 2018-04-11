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
 * The usual constructor.
 *
 * We store hardcoded sound filenames to a 'vector' 'soundFiles' to
 * be played back later.
***/
UserNotifier::UserNotifier() {

    // Objects Map to the index of the vector via the integer defined in globalconstants.h

    // Populate vectors with default values
    defaultSoundFiles = {
        "../Sounds/short.wav",
        "../Sounds/long.wav",
        "../Sounds/short-long.wav",
        "../Sounds/long-short.wav",
        "../Sounds/short-short.wav",
        "../Sounds/short-short-long.wav",
        "../Sounds/long-short-short.wav",
        "../Sounds/blaster-firing.wav"
    };

    soundFiles = defaultSoundFiles;

    voiceFiles = {
        "../Sounds/Wall_Voice.wav",
        "../Sounds/Wall_Corner_Voice.wav",
        "../Sounds/Pillar_Voice.wav",
        "../Sounds/Trip_Hazard_Voice.wav",
        "../Sounds/Other_Voice.wav",
        "../Sounds/Stairs_Voice.wav",
        "../Sounds/Other_Voice.wav",
        "../Sounds/Other_Voice.wav"
    };

}

/********************************************************
*************
 * The usual destructor.
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
            QSound::play(QString::fromStdString(soundFiles.at(object)));
        }

        else { // fileType == VOICEFILES
            QSound::play(QString::fromStdString(voiceFiles.at(object)));

        }
    }
}
