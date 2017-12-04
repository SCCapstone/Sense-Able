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

private:
    vector<string> soundFiles;
};

#endif // USERNOTIFIER_H
