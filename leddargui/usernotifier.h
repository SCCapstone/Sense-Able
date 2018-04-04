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

    void playSound(string object);

    bool fileType = SOUNDFILES;

    map<string, string> soundFiles;
    map<string, string> voiceFiles;

private:

};

#endif // USERNOTIFIER_H
