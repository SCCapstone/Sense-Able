#include "gtest/gtest.h"
#include "objectdetectthread.h"
#include "mainwindow.h"

//detect_wall(std::vector<float> distances, float measure_error, float flat_error)
// Using the following tutorial:
// https://www.ibm.com/developerworks/aix/library/au-googletestingframework.html



objectDetector detect;

/****************************************
 * General format for writing unit tests:
 *
 *  TEST (NameOfFunction, NameOfTest) {
 *      // Do stuff to come up with data to test.
 *
 *      EXPECT_EQ(EXPECTED_VALUE, function(args, ...));
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
TEST (DetectWallTest, FlatDistribution) {

    vector<float> distances;

    // Check all 0's and simple cases
    for (int j=0; j < 9; j++) {
        for (int i = 0; i < 16; i++) {
            distances.push_back(1.0 * j);
        }
        EXPECT_EQ(1, detect.detect_wall(distances, 0.75, 100));
        distances.clear();
    }
//    std::cout << "gey";
//    vector<float> distances2;
//    // Check variable length vectors
//    for (int i=0; i<3; ) {
//        distances2.push_back(0);
//    }
////    std::cout << distances.at(.5) << std::endl;
//    EXPECT_EQ(1, detect.detect_wall(distances2, 0.75, 100));
}


// I for one take by faith that Google's code always works. ;)

/** Functions to Test:
*
*    FlatDistribution:
*        - All 0's
*        - More points
*        - Less points
*        - Angles (grid search)
*        - Noisey Angles (grid search)
*
**/


