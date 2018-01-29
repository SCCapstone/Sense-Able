#include "gtest/gtest.h"
#include "objdetect.h"

//detect_wall(std::vector<float> distances, float measure_error, float flat_error)
// Using the following tutorial:
// https://www.ibm.com/developerworks/aix/library/au-googletestingframework.html


vector<float> distances;

for (i = 0; i < 16; i++) {
    distances.push_back(1.0);
}

TEST (DetectWallTest, FlatDistribution) {
    EXPECT_EQ(1, detect_wall(distances, 0.75, 100));
}
