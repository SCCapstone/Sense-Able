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
 *  }
 *
 * Based on Caleby's 70% regression fit, a fit value of between 0.7 and 1.0 will
 * be considered successful.  For this purpose, use
 * EXPECT_NEAR(expected_value, actual_value, tolerance
 * with expected_value being in the middle at 0.85 and tolerance at 0.15
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

/***************************************
 * This is for testing function detectWall in objectdetectthread.cpp.
 * In order to do that, a simulated vector of distance will be created and
 * passed to the function.  The r squared value returned should be between
 * 0.7 and 1.0 to be considered a successful for wall and 0 for a non-wall
 * obstacle.
 *
 * Given the angles are known and walls are linear, use y = mx+b and
 * tan(theta) = y/x to set up the distance vectors.
 * X = b/(tan(theta)-m) and d = sqrt(x*x + y*y)
***/
TEST (DetectWallTest, FlatDistribution) {

    vector<float> distances;
    //theta is angle in degrees of the left most distance in vector
    //the angles are based on the sensor configuration
    //hypotenuse is the distance

    //sensors at 2.8 deg apart, the 90 degree is to center it
    float leftMostTheta = (90 + (2.8 * 0.5 * int(distances.size()-1)))*M_PI/180;
    float incriment = 2.8*M_PI/180; //incriment in radians
    float thetaRadians;
    //float random = 0.0; //simulate noise

    float x;
    float y;
    float m;
    float dTest;
    //bool poorCase = false;
    //for a procedurally generated case that is no good
    //ie: y ends up negative, which is impossible b/c of sensor configurations
    //    in the chosen orientation.
    //final verdict not necessary b/c the trig of the sensor angles ensures non negative y

    //flat 0 degree wall at 0 meters
    //scrapped to avoid divide by 0 problems
    //for (int i = 0; i < 16; i++) {
        //distances.push_back(0);
    //}

    EXPECT_NEAR(0.85, detect.detectWall(distances), 0.15);
    distances.clear();

    // Check for walls at 0 degree (slope is 0) at y 1 to 5 meters away from sensor
    for (int b=1; b < 6; b++) {
        //b is the y-intercept
        //using tan() = y/x, solve for hypotenuse and push it into distances

        for (int i = 0; i < 16; i++) {
            //random = (rand() % 6)/100; //adds between 0.00 to 0.05 m
            thetaRadians = (leftMostTheta-i*incriment);//update the angle
            x = b/tan(thetaRadians);
            //in this case, y = b for a horizontal line
            dTest = sqrt(pow(x,2) + pow(b,2));
            distances.push_back(dTest);
        }

        EXPECT_NEAR(0.85, detect.detectWall(distances), 0.15);
        distances.clear();
    }

    //slanted walls to the right and left / \
    //walls that are too slanted may be other obstacles
    //expect success when slope is between -0.75 and 0.75
    for(int b = 1; b < 6; b++) { //b for y-intercept

        for (int k=-10; k <= 10; k++) {
            //use m slope here;
            m = k/5; //ranges from -2.0 to 2.0 at incriments of 0.2

            for (int i = 0; i < 16; i++) {
                //random = (rand() % 6)/100;

                thetaRadians = leftMostTheta-i*incriment;
                x = b/(tan(thetaRadians)-m);
                y = m*x + b;
                dTest = sqrt(pow(x,2) + pow(y,2));
                distances.push_back(dTest);
             }

             if(m > 0.75 || m < -0.75){
                EXPECT_FLOAT_EQ(0.0, detect.detectWall((distances)));
             }
             else{
                EXPECT_NEAR(0.85, detect.detectWall(distances), 0.15);
             }
             distances.clear();

        }
    }

    vector<float> distances2;
    // Check variable length vectors
    for(int i=0; i<10; i++) {
        //set y to 1 aka wall 1 meter away
        thetaRadians = (leftMostTheta-i*incriment);//update the angle
        x = 1/tan(thetaRadians);
        //in this case, y = 1 for a horizontal line
        dTest = sqrt(pow(x,2) + 1);
        distances.push_back(dTest);
    }
    //less than 16 points
    EXPECT_NEAR(0.85, detect.detectWall(distances2), 0.15);

    for(int i = 10; i < 20; i++){
        //put a 10 more points in distance2
        thetaRadians = (leftMostTheta-i*incriment);//update the angle
        x = 1/tan(thetaRadians);
        dTest = sqrt(pow(x,2) + 1);
        distances.push_back(dTest);
    }
    //more than 16 points
    EXPECT_NEAR(0.85, detect.detectWall(distances2), 0.15);

}


TEST (DetectWallCorner, ParabolaCurveFitting) {
    vector<float> distances;
    //angle of the left most distance in vector
    //hypotenuse is the distance, we set y-projection however necessary, theta is set through hardware
    float leftMostTheta = (90 + (2.8 * 0.5 * int(distances.size()-1)))*M_PI/180;
    float incriment = 2.8*M_PI/180; //incriment in radians
    float thetaRadians;

    float x;
    float y;
    float m;
    float dTest;


    //n is which beam has the corner
    //n offset by 5 from each side to avoid being detected as slanted wall
    //simplest case is a 90 degree corner directly facing the sensor
    for(int n = 5; n < 11; n++){
        //b for y intercept of the first line
        //started at 3 to avoid being too close and mistake for a wall
        for(int b = 3; b < 6; b++){
            //use m for slope of the corner
            //it's m to the left of n and -1/m to the right of n to make the
            //2 lines perpendicular (90 degree)
            m = 1;
            //so y = x + b when x <=n
            //and y = -x + b when x > n

            //y = -x + b2
            //b2 = y + x at sensor n, y intercept of the 2nd line
            float b2 = m*(b/(tan(leftMostTheta-n*incriment)-m))+b
                    + b/(tan(leftMostTheta-n*incriment)-m);

            y = m*(b2/(tan(leftMostTheta-15*incriment)-m))+b2;

            for (int i = 0; i < 16; i++) {

                thetaRadians = leftMostTheta-i*incriment;//update the angle

                if(i <= n){
                    x = b/(tan(thetaRadians)-m);
                    y = m*x + b;
                }
                else if(i > n){
                    x = b/(tan(thetaRadians)+m);
                    y = -m*x + b2;
                }
                dTest = sqrt(pow(x,2) + pow(y,2));
                distances.push_back(dTest);
            }
            //Do the test

            EXPECT_NEAR(0.85, detect.detectCorner(distances),0.15);
            distances.clear();


        }
    }


    //detectCorner rejects too steep or too flat curves /\ or ~~ with a 0.0
    //for ease of testing right now, set corner directly in the middle between beam 7 and 8
    //to take advantage of symmetry
    for(int m = 5; m < 10; m++){

        for(int b = 10; y < 20; y++){

            for(int i = 0; i < 16; i++){

                thetaRadians = (leftMostTheta-i*incriment);//update the angle

                if(i < 8){
                    x = b/(tan(thetaRadians)-m);
                    y = m*x + b;
                }
                else{
                    x = b/(tan(thetaRadians)+m);
                    y = -m*x + b;
                }

                dTest = sqrt(pow(x,2) + pow(y,2));
                distances.push_back(dTest);
            }
            //test very steep corners, expect a float of 0.0
            EXPECT_FLOAT_EQ(0.0, detect.detectCorner(distances));
            distances.clear();
        }

    }

    //test for essentially a flat wall
    for (int b=1; b < 6; b++) {
        //b is the y-intercept

        for (int i = 0; i < 16; i++) {
            thetaRadians = (leftMostTheta-i*incriment);//update the angle
            x = b/tan(thetaRadians);
            //in this case, y = b for a horizontal line
            dTest = sqrt(pow(x,2) + pow(b,2));
            distances.push_back(dTest);
        }
        //expect 0.0 for not being a corner
        EXPECT_FLOAT_EQ(0.0, detect.detectCorner(distances));
        distances.clear();
    }
}

/*****************************
 * For testing the function polynomial_fit, which is key to this implementation
 * of recognizing specified obstacles
 *
 ***/
TEST (PolyFitTest, regression) {
    //polynomial_fit(int degree, vector<float> y, vector<float> x)
    //using all whole numbers to avoid rounding errors

    vector<float> x;
    vector<float> y;
    vector<float> expected;

    //linear polynomials y = mx + b;
    for(int b = 0; b < 6; b++){
        expected.push_back(b);
        for(int m = 0; m < 6; m++){
            expected.push_back(m);
            // i will be the x values
            for(int i = -10; i <= 10; i+=2) {
                x.push_back(i*1.0);
                y.push_back(i*m*1.0 + b);
            }
            //should consider comparing values individually
            //EXPECT_EQ(expected,detect.polynomial_fit(1,y,x));

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


