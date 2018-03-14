#include "gtest/gtest.h"
#include "objectdetectthread.h"
#include "usernotifier.h"
#include "leddarthread.h"
#include "mainwindow.h"

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
                EXPECT_EQ(1, detect.detect_wall(dataPoints, .5, 100));

                dataPoints.erase(dataPoints.begin(), dataPoints.end());
            }
        }

    }

//    for (auto& x: file_map)
//       std::cout << " [" << x.first << ':' << x.second << ']';
//     std::cout << '\n';

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

UserNotifier notifier;

TEST (UserNotifyTest, SoundCheck) {

    for (int i=1; i<9; i++){
        std::cout << "Playing sound file: " << notifier.soundFiles.at(i-1) << endl;
//        notifier.playSound(i);
    }

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


