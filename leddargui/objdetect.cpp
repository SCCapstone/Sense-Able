#include "objdetect.h"

objectDetector::objectDetector()
{

}

void objectDetector::objDetect(int i)
{
    //this is a slot

    //signal passes integer i
    int j = i;
    emit(objNotify(j));
}
void objectDetector::DetectObject(vector<float> distances, float sig_dist)
{
    //also a slot
}

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
