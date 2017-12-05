using namespace std;
#include "usernotifier.h"

#include <QSound>


/*
 * Constructor. Stores hardcoded sound filenames to an array
 */
UserNotifier::UserNotifier() {
    soundFiles.push_back("Sounds/blaster-firing.wav");
    soundFiles.push_back("hall_notification.wav");
    soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");
}

UserNotifier::~UserNotifier() {
    return;
}

/*
 * Plays the sound stored at index
 */
void UserNotifier::playSound(int index) {
    QSound::play(QString::fromStdString(soundFiles.at(index)));
    return;
}
