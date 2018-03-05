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
    soundFiles.push_back("../Sounds/beep-01.wav");
    soundFiles.push_back("../Sounds/beep-02.wav");
    soundFiles.push_back("../Sounds/beep-03.wav");
    soundFiles.push_back("../Sounds/beep-04.wav");
    soundFiles.push_back("../Sounds/beep-05.wav");
    soundFiles.push_back("../Sounds/beep-06.wav");
    soundFiles.push_back("../Sounds/beep-07.wav");
    soundFiles.push_back("../Sounds/beep-08.wav");
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
