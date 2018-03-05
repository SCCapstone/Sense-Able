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
    soundFiles.push_back("../Sounds/owen_wilson.wav");
    soundFiles.push_back("../Sounds/hall_notification.wav");
    soundFiles.push_back("../Sounds/owen_wilson.wav");
    soundFiles.push_back("../Sounds/owen_wilson.wav");
    soundFiles.push_back("../Sounds/owen_wilson.wav");
    soundFiles.push_back("../Sounds/owen_wilson.wav");
    soundFiles.push_back("../Sounds/owen_wilson.wav");
    soundFiles.push_back("../Sounds/owen_wilson.wav");
   /* soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");*/
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
void UserNotifier::playSound(int index) {
    if(index < soundFiles.size() - 1) {
        QSound::play(QString::fromStdString(soundFiles.at(index)));
    }
    return;
}
