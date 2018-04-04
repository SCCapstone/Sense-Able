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

    soundFiles.emplace(WALL, "../Sounds/short.wav");
    soundFiles.emplace(WALL_CORNER, "../Sounds/short.wav");
    soundFiles.emplace(PILLAR, "../Sounds/long.wav");
    soundFiles.emplace(TRIP_HAZARD, "../Sounds/short-long.wav");
    soundFiles.emplace(UNIDENTIFIED_OBSTACLE, "../Sounds/long-short.wav");

    voiceFiles.emplace(WALL, "../Sounds/blaster-firing.wav");
    voiceFiles.emplace(WALL_CORNER, "../Sounds/blaster-firing.wav");
    voiceFiles.emplace(PILLAR, "../Sounds/blaster-firing.wav");
    voiceFiles.emplace(TRIP_HAZARD, "../Sounds/blaster-firing.wav");
    voiceFiles.emplace(UNIDENTIFIED_OBSTACLE, "../Sounds/blaster-firing.wav");
//    soundFiles.push_back("../Sounds/short-short.wav");
//    soundFiles.push_back("../Sounds/short-short-long.wav");
//    soundFiles.push_back("../Sounds/long-short-short.wav");
//    soundFiles.push_back("../Sounds/blaster-firing.wav");


}

/*********************************************************************
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
void UserNotifier::playSound(string object) {
    if (fileType == SOUNDFILES) {
        if( soundFiles.size() - 1) {
            QSound::play(QString::fromStdString(soundFiles.at(object)));
        }
    }
    else if ( fileType == VOICEFILES) {
        if(index < soundFiles.size() - 1) {
            QSound::play(QString::fromStdString(voiceFiles.at(object)));
        }
    }

    return;
}
