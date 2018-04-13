#ifndef GLOBALCONSTANTS_H
#define GLOBALCONSTANTS_H

using namespace std;

#include <string>

const static bool VERTICAL = true;
const static bool HORIZONTAL = false;

const static bool SOUNDFILES = true;
const static bool VOICEFILES = false;


/*********************************************************************
* Identifiable objects are defined here. If a new object is detected,
* define it here, add it to usernotifier, objectdetector, and.
*
***/
//const static string WALL = "WALL";
//const static string WALL_CORNER = "WALL_CORNER";
//const static string PILLAR = "PILLAR";
//const static string TRIP_HAZARD = "TRIP_HAZARD";
//const static string UNIDENTIFIED_OBSTACLE = "UNIDENTIFIED_OBSTACLE";
//const static string NONE = "NONE";

const static int NONE = -1;
const static int WALL = 0;
const static int WALL_CORNER = 1;
const static int PILLAR = 2;
const static int TRIP_HAZARD = 3;
const static int UNIDENTIFIED_OBSTACLE = 4;

const static int FIT_THRESHOLD = 0.70;

const static string OBJECT_MAP[] = {
    "Wall",
    "Wall Corner",
    "Pillar",
    "Trip Hazard",
    "Unidentified Obstacle",
};

#endif // GLOBALCONSTANTS_H
