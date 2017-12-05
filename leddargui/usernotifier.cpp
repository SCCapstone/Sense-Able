using namespace std;
#include "usernotifier.h"

#include <QSound>

UserNotifier::UserNotifier() {
    soundFiles.push_back("Sounds/blaster-firing.wav");
    soundFiles.push_back("Sounds/hall_notification.wav");
   /* soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");
    soundFiles.push_back("");*/
}

UserNotifier::~UserNotifier() {
    return;
}

void UserNotifier::playSound(int index) {
    if(index < soundFiles.size() - 1) {
        QSound::play(QString::fromStdString(soundFiles.at(index)));
    }
    return;
}
