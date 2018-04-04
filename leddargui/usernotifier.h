using namespace std;
#ifndef USERNOTIFIER_H
#define USERNOTIFIER_H

#include <vector>
#include <string>
#include "globalconstants.h"

class UserNotifier
{
public:
    UserNotifier();
    ~UserNotifier();

    void playSound(int index);

    bool fileType = SOUNDFILES;

    vector<string> soundFiles;
    vector<string> voiceFiles;
    vector<string> defaultSoundFiles;

};

#endif // USERNOTIFIER_H
