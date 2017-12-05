#include <vector>
#include <string>
#include <cmath>
#include <math.h>
#include <iostream>
#include "objdetect.h"

objectDetector::objectDetector()
{
    qRegisterMetaType<string>("string");
}
/*
void objectDetector::objDetect(int i)
{
    //this is a slot

    //signal passes integer j
    int j = i;
    emit(objNotify(j));
}
*/
void objectDetector::processDataPoints(int index, vector<float> dataPoints) {
cout << "LeddarStream->objectDetector signal /slot works!" << endl;
    detectObject(dataPoints);
}

void objectDetector::detectObject(vector<float> distances)
{
cout << "Entering objectDetector" << endl;
    UserNotifier notifier = UserNotifier();
    int detectCode;

    detectCode = detect_wall((distances), 0.1, 0.2);

    if (detectCode == 1) {
        emit sendObjectDetected("Flat Wall");
        notifier.playSound(0);
    } else if (detectCode == 2) {
        emit sendObjectDetected("Left Slant");
        notifier.playSound(1);
    } else if (detectCode == 3) {
        emit sendObjectDetected("Right Slant");
        notifier.playSound(2);
    } else if (detectCode == 4) {
        emit sendObjectDetected("Hallway");
        notifier.playSound(3);
    } else if (detectCode == -1) {
        emit sendObjectDetected("NONE");
    } else {
        cout << "ERROR: detectCode has an invalid value." << endl;
    }

    return;
}

// static float standard_deviation(std::vector<float> xs, std::vector<float> ys);
// static int detect_wall(std::vector<float> v);

/*
* Takes a vector of floats and determines wether a wall or hallway is present
* -1 -> Wall not detected
*  1 -> Flat wall detected
*  2 -> Left slant (/) Wall detected
*  3 -> Right slant (\) wall detected
*  4 -> Hallway (/\) detected
*
* y = a + bx
* a = My - b(Mx)
* b = r (sdy/sdx)
*/
int objectDetector::detect_wall(std::vector<float> v, float measure_error, float flat_error) {

  // Calculate Equation for line of best fit
  int n;
  float sumx, sumy, mx, my, sdx, sdy;

  // Calculate Mean
  for (unsigned int i=0; i<v.size(); i++) {
    sumx += int(i);
    sumy += v.at(i);
    n += 1;
  }

  mx = sumx / n;
  my = sumy / n;

  // Calculate Standard Deviation for X's and Y's
  float ssy, ssx;

  for (unsigned int i=0; i<v.size(); i++) {
    ssy += std::pow(v.at(i) - my, 2);
    ssx += std::pow(int(i) - mx, 2);
  }

  sdy = std::sqrt(ssy/n);
  sdx = std::sqrt(ssx/n);

  std::cout << sdy << std::endl;
  std::cout << sdx << std::endl;

  // Calculate R - sum(xy)/ swrt(sum(x^2) * sum(y^2))

  float sumxy, sumxx, sumyy, r, a, b;

  for (unsigned int i=0; i<v.size(); i++) {
    sumxy += int(i) * v.at(i);
    sumxx += std::pow(int(i), 2);
    sumyy += std::pow(v.at(i), 2);
  }

  r = sumxy / sqrt(sumxx*sumyy);

  b = r * (sdy/sdx);
  a = my - b*mx;
  std::cout << b << " " << a << std::endl;
  std::cout << "MEANX, MEANY " << mx << " " << my << std::endl;
  // std::cout << << std::endl;
  // std::cout << << std::endl;
  // std::cout << << std::endl;
  // std::cout << << std::endl;
  // If any of the segments exceed tolerated measurement error -
  // A wall is not considered to exist across the field of vision
  bool wall = true;
  for ( unsigned int i=0; i<v.size(); i++ ){
    if ( std::abs( (b*int(i)+a) - v.at(i) ) > measure_error )  {
      // std::cout << (b*int(i)+a) - v.at(i) << std::endl;
      wall = false;
    }
  }

  // If a wall exists, check if flat, left slant, or right slant
  if (wall) {
    // flat wall
    if (std::abs(b) < flat_error) {
      return 1;
    }
    //left slant (/)
    else if (b > 0) {
      return 2;
    }
    //right slant (\)
    else { // b < 0
      return 3;
    }
  }
  // Check left and right fields of vision for hall way
  // TODO: EXPAND CASES TO CHECK FOR LEFT/RIGHT OBSTRUCTION
  else if (v.size() == 16) {
    std::vector<float> left_v(v.begin(), v.begin() + 8);
    std::vector<float> right_v(v.end() - 8, v.end());

    int left_wall = detect_wall(left_v, measure_error, flat_error);
    int right_wall = detect_wall(right_v, measure_error, flat_error);

    if ((left_wall == 2) && (right_wall == 3)) {
      return 4;
    }
  }
  // No Wall
  return -1;
}
/* Function projects onto the y-axis
 *
 *
*/
vector<float> objectDetector::yaxis_projection(vector<float> distances){
    vector<float> projected;
    // Theta is the angle between the x-axis and the right most segment.
    // The angle between segments is 2.8 degrees
    float theta = 90 - (2.8 * .5 * int(distances.size()) );

    for (int i=int(distances.size())-1; i>-1; i-- )
    {
        float y = distances.at(i) * sin(theta);
        projected.insert(projected.begin(), y);

        // Increment theta for the next segment
        theta += 2.8;
    }

    return projected;
}
