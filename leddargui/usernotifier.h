using namespace std;
#ifndef USERNOTIFIER_H
#define USERNOTIFIER_H

#include <vector>
#include <string>

class UserNotifier
{
public:
    UserNotifier();
    ~UserNotifier();

    void playSound(int index);
    vector<string> soundFiles;
    vector<string> voiceFiles;

private:

};

#endif // USERNOTIFIER_H
