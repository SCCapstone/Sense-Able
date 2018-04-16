#include "gtest/gtest.h"
#include "objectdetectthread.h"
#include "usernotifier.h"
#include "leddarthread.h"
#include "mainwindow.h"
#include "stdlib.h"

#include <QObject>
#include <dirent.h>
#define ARRAY_LEN( a )  (sizeof(a)/sizeof(a[0]))

//detect_wall(std::vector<float> distances, float measure_error, float flat_error)
// Using the following tutorial:
// https://www.ibm.com/developerworks/aix/library/au-googletestingframework.html



/****************************************
 * General format for writing unit tests:
 *
 *  TEST (NameOfFunction, NameOfTest) {
 *      // Do stuff to come up with data to test.
 *      continues even if a test fails
 *      EXPECT_EQ(EXPECTED_VALUE, function(args, ...));
 *
 *      stops the tests after 1 fails
 *      ASSERT_EQ(expected_value, function(args, ...));
 *
 *      for floating point comparisons
 *      EXPECT_FLOAT_EQ(expected_value, function(args,...)); up to 4 decimal precision
 *      EXPECT_DOUBLE_EQ(expected_value, function(args,...));
 *
 *      For higher precision
 *      EXPECT_NEAR(expected_value, function(args,...), absolute_range or tolerance);
 *
 *  }
 *
 *
***/

//temp test for testing that google test tests
TEST (testCase, testName) {
    int i = 6;
    int j = 3;
    int result = i*j;
    //EXPECT_EQUAL(expected value, result)
    EXPECT_EQ(18, result);
}


objectDetector detect;
LeddarStream stream;

TEST (DetectWallsTest, SimData) {
    // Get all pairs of files from the walls directory
    std::map<string, string> file_map;

    string wall_file = "../LeddarData/Walls";
    DIR* dir = opendir(wall_file.c_str());

    struct dirent * dp;
    while ((dp = readdir(dir)) != NULL) {
        string file_name = dp->d_name;

        int len = file_name.size();
//        std::cout << file_name << "  " << len << std::endl;

        if ( len > 3) {
            // Set file as map key, assume that a matching video exists for now.
            if (file_name.substr(len-3, len) == "ltl") {
                string file_mp4 = file_name.substr(0,len-3) + "mp4";

                std::cout << file_name << "  " << file_mp4 << std::endl;
                file_map.emplace(file_name, file_mp4);
            }
        }
    }
    map<string, string>::iterator it;
    for (it=file_map.begin(); it != file_map.end(); it++){
        QString qstr = QString::fromStdString(it->first);
        char* dumb = const_cast<char*>(qstr.toUtf8().constData());//it->first.c_str();

        if ( LeddarLoadRecord(stream.gHandle, dumb) == LD_SUCCESS) {

            // Read each line of the ltl file
            vector<float> dataPoints;
            unsigned int lCount;
            LdDetection lDetections[50];

            while (LeddarStepForward(stream.gHandle) != LD_END_OF_FILE) {
                lCount = LeddarGetDetectionCount( stream.gHandle );
                if ( lCount > ARRAY_LEN( lDetections ) )
                {
                    lCount = ARRAY_LEN( lDetections );
                }

               LeddarGetDetections( stream.gHandle, lDetections, ARRAY_LEN( lDetections ) );

                for( int i=0; i < lCount; i++ )
                {
                    cout << lDetections[i].mDistance << " ";
                    // TODO: Check that the segment corresponds to index. Can they be out of order?
                    dataPoints.push_back(lDetections[i].mDistance);
                }
                // Do test here
//                EXPECT_EQ(1, detect.detect_wall(dataPoints, .5, 100));

                dataPoints.erase(dataPoints.begin(), dataPoints.end());
            }
        }

    }

//    for (auto& x: file_map)
//       std::cout << " [" << x.first << ':' << x.second << ']';
//     std::cout << '\n';

}

//Based on Caleby's 70% regression fit, a fit value of between 0.7 and 1.0 will
//be considered successful
//use EXPECT_NEAR(expected_value, actual_value, tolerance)
//with expected being in the middle at 0.85 and tolerance at 0.15
TEST (DetectWallTest, FlatDistribution) {

    vector<float> distances;
    //angle of the left most distance in vector
    //hypotenuse is the distance, we set y however necessary, theta is given
    //d = y/sin(theta)
    float leftMostTheta = 90 + (2.8 * 0.5 * int(distances.size()));//sensors at 2.8 deg apart
    float thetaRadians = 0;
    float random = 0.0; //simulate noise

    // Check for walls at 0 degree at y (0 to 5) meters away from sensor
    for (int y=0; y < 6; y++) {
        for (int i = 0; i < 16; i++) {
            random = (rand() % 6)/100; //adds between 0.00 to 0.05 m
            thetaRadians = (leftMostTheta-2.8*i)*M_PI/180;//update the angle
            distances.push_back((y + random)/sin(thetaRadians));
        }

        EXPECT_NEAR(0.85, detect.detectWall(distances), 0.15);
        distances.clear();
    }

    //slanted walls to the right /
    for(int y = 0; y < 6; y++) { //y for distance of the left most point
        for (int m=0; m < 4; m++) { //use m for slope here; not too steep since the points go too far
            for (int i = 0; i < 16; i++) {
                //generate an int between 0 to 5 divided by 100
                random = (rand() % 6)/100;
                //adds between 0.00 to 0.05 m
                thetaRadians = (leftMostTheta-2.8*i)*M_PI/180;//update the angle
                distances.push_back((m*i*1.0 + y + random)/sin(thetaRadians));
            }

            EXPECT_NEAR(0.85, detect.detectWall(distances), 0.15);
            distances.clear();
        }
    }

    //slanted walls to the left \

    for(int y = 0; y < 6; y++) { //y for y-projected distance from the left most point
        for (int m=0; m < 4; m++) { //use m for slope here; not too steep since the points go too far
            for (int i = 15; i >= 0; i--) {
                //generate an int between 0 to 5 divided by 100
                random = (rand() % 6)/100;
                //adds between 0.00 to 0.05 m
                thetaRadians = (leftMostTheta-2.8*i)*M_PI/180;//update the angle
                distances.push_back((m*i*1.0 + y + random)/sin(thetaRadians));
            }

            EXPECT_NEAR(0.85, detect.detectWall(distances), 0.15);
            distances.clear();
        }
    }
    vector<float> distances2;
    // Check variable length vectors
    for(int i=0; i<10; i++) {
        //set y to 1 aka wall 1 meter away
        thetaRadians = (leftMostTheta-2.8*i)*M_PI/180;//update the angle
        distances.push_back(1.0/sin(thetaRadians));
    }
    //less than 16 points
    EXPECT_NEAR(0.85, detect.detectWall(distances2), 0.15);

    for(int i = 11; i < 20; i++){
        //put a 10 more points in distance2
        thetaRadians = (leftMostTheta-2.8*i)*M_PI/180;//update the angle
        distances.push_back(1.0/sin(thetaRadians));
    }
    //more than 16 points
    EXPECT_NEAR(0.85, detect.detectWall(distances2), 0.15);

}


TEST (DetectWallCorner, ParabolaCurveFitting) {
    vector<float> distances;
    //angle of the left most distance in vector
    //hypotenuse is the distance, we set y-projection however necessary, theta is set through hardware
    //d = y/sin(theta)
    float leftMostTheta = 90 + (2.8 * 0.5 * int(distances.size()));//sensors at 2.8 deg apart
    float thetaRadians = 0;
    //float random = 0.0; //simulate noise


    //simplest case is a 90 degree corner directly facing the sensor
    //k is which beam has the corner
    //k offset by 3 from each side to avoid being detected as slanted wall

    for(int k = 3; k < 13; k++){
        //y for y-axis projection or how far straight up the left most point is
        //started at 2 to avoid being too close and mistake for a wall
        for(int y = 2; y < 6; y++){
            //use m for slope of the corner
            //it's m to the left of k and -1/m to the right of k to make the
            //2 lines perpendicular (90%)
            //made m not too steep at either 1 and 2 y meters for every meter increase in x
            for (int m=1; m < 3; m++) {

                float y_proj = y;//temp variable to track where project y distance is from sensor

                for (int i = 0; i < 16; i++) {
                    thetaRadians = (leftMostTheta-2.8*i)*M_PI/180;//update the angle

                    //generate an int between 0 to 5 and divided by 100
                    //random = (rand() % 6)/100;

                    //corner left of sensor
                    if(k < 8){
                        if(i <= k){
                            //positive slope of m, going up until k
                            y_proj += m*i*1.0;
                        }
                        else{
                            //negative slope -1/m, offset by k
                            y_proj += -1.0/m*(i-k);
                        }
                    }
                    //corner right of sensor
                    if(k >= 8){
                        if(i <= k){
                            //positive slope of 1/m, going up until k
                            y_proj += 1.0/m*i;
                        }
                        else{
                            //negative slope -m, offset by k
                            y_proj += -m*(i-k)*1.0;
                        }
                    }
                    distances.push_back(y_proj/sin(thetaRadians));
                }
                //Do the test
                EXPECT_NEAR(0.85, detect.detectCorner(distances),0.15);
                distances.clear();
            }
        }
    }


    //detectCorner rejects too steep or too flat curves /\ or ~~ with a 0.0
    //for ease of testing right now, set corner k directly in the middle between beam 7 and 8
    for(int m = 3; m < 10; m++){
        //
        int k = 8; //corner is at around 8
        for(int y = 2; y < 6; y++){

            float y_proj = 0.0;

            for(int i = 0; i < 16; i++){
                if(i < k){

                    //positive slope of m, going up until k
                    y_proj += m*i*1.0;
                }
                else{
                //negative slope -m, offset by k
                    y_proj += -m*(i-k)*1.0;

                }
                thetaRadians = (leftMostTheta-2.8*i)*M_PI/180;//update the angle
                distances.push_back(y_proj/sin(thetaRadians));
            }
            //test very steep corners, expect a float of 0.0
            EXPECT_FLOAT_EQ(0.0, detect.detectCorner(distances));
            distances.clear();
        }

    }

    for(int m = 3; m < 10; m++){
        //
        int k = 8; //corner is at around 8
        for(int y = 2; y < 6; y++){

            float y_proj = 0.0;

            for(int i = 0; i < 16; i++){
                if(i < k){

                    //positive slope of 1/m, going up until k
                    y_proj += 1.0/m*i;
                }
                else{
                //negative slope -1/m, offset by k
                    y_proj += -1.0/m*(i-k);

                }
                thetaRadians = (leftMostTheta-2.8*i)*M_PI/180;//update the angle
                distances.push_back(y_proj/sin(thetaRadians));
            }
            //test very flat corners, expect a float of 0.0
            EXPECT_FLOAT_EQ(0.0, detect.detectCorner(distances));
            distances.clear();
        }

    }
}

/*
 UserNotifier notifier;
/

/*
TEST (UserNotifyTest, SoundCheck) {

    for (int i=1; i<9; i++){
        std::cout << "Playing sound file: " << notifier.soundFiles.at(i-1) << endl;
//        notifier.playSound(i);
    }

}
*/

// I for one take by faith that Google's code always works. ;)

/** Functions to Test:
*   DetectWall
*   DetectCorner
*
*   Not yet implemented
*   DetectPillar
*   DetectTripHazard
*
*
*
*    FlatDistribution:
*        - All 0's
*        - More points
*        - Less points
*        - Angles (grid search)
*        - Noisey Angles (grid search)
*
**/


