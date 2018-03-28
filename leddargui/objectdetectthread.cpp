/*********************************************************************
 * Class for detecting objects from a vector of points.
 *
 * Date last modified: 8 December 2017
 * Author: Jonathan Senn
 * Modified by Caleb Kisby
***/

#include <vector>
#include <string>
#include <cmath>
#include <math.h>
#include <iostream>
#include "objectdetectthread.h"

/*********************************************************************
 * The usual constructor.
 *
 * When initialized, we establish that this thread is not running, and
 * has not been stopped.  We also register the string type so that it
 * may be emitted via a signal.
***/
objectDetector::objectDetector()
{
cout << "Entering objectDetector" << endl;
    qRegisterMetaType<string>("string");
    isstopped = false;
    isrunning = false;

    currentNotifier = UserNotifier();
}

/*********************************************************************
 * Function to detect different classes of obstacles.
 *
 * Currently we do this only for types of walls.  We take a 'float' 'vector'
 * of distances and pass them through a function for detecting walls.
 * The resulting 'detectCode' may be interpreted as follows:
 *
 * 1  - Flat wall detected (Currently the only implemented class)
 * 2  - Flat wall, at a left slant angle
 * 3  - Flat wall, at a right slant angle
 * 4  - Hallway
 * -1 - Nothing detected.
 *
 * We then emit that the obstacle was detected, and issue a notification sound.
 * If no obstacle was detected, we emit this as well, but play no
 * notification sound.
 *
 * When we close this function, we stop the thread for doing detections
 * so that it may be started later.
***/
void objectDetector::doDetect(vector<float> distances) {
cout << "Entering doDetect" << endl;
    int detectCode;
    float measure_err = .3;
    float flat_err = 100;
//    float sig_dist = 2;

    if (!isrunning || isstopped) return;

    bool close = false;
    for (unsigned i=0; i<distances.size(); i++) {
        if (distances.at(i) < sig_dist + .1 * sig_dist) {
            close = true;
        }
    }

    try{
        detectCode = detect_wall(yaxis_projection(distances), measure_err, flat_err);
    }
    catch (const std::exception& e){
        // TODO:: Change to log
        std::cout << e.what() << std::endl;
        detectCode = -1;
    }

//    float closest_point = 0;
//    for (int i = 0; i < distances.size(); i++) {
//        if (distances.at(i) > closest_point) {
//              closest_point = distances.at(i);
//        }
//    }

    if (detectCode == 1) {
        emit sendObjectDetected("Wall");
//        if ( closest_point - .5 < sig_dist ) {
        currentNotifier.playSound(0);
//        }
    } else if (detectCode == 2) {
        emit sendObjectDetected("Left Slant");
        currentNotifier.playSound(1);
    } else if (detectCode == 3) {
        emit sendObjectDetected("Right Slant");
        currentNotifier.playSound(2);
    } else if (detectCode == 4) {
        emit sendObjectDetected("Hallway");
        currentNotifier.playSound(3);
    } else if (detectCode == -1) {
        emit sendObjectDetected("NONE");
    } else {
        cout << "ERROR: detectCode has an invalid value." << endl;
    }

    StopDetect();
//cout << "Exiting doDetect" << endl;
}

/*********************************************************************
 * Function to detect classes of flat walls.
 *
 * This function takes a 'float' 'vector' of distances, along with tolerance
 * 'measure_error' and 'flat_error', and determines whether a wall or hallway
 * is present.
 *
 * Input:
 *   distances - The distances 'vector' given
 *   measure_error - A parameter for tolerance - deviation of individual measurements to the mean
 *   flat_error - A parameter for tolerance - deviation of slope
 *
 * Returns:
 *  -1 if invalid input
 *   0 if no wall
 *   1 if a flat wall is detected
 *   2 if a left slant (/) wall detected
 *   3 if a right slant (\) wall detected
 *   4 if a hallway (/\) detected
 *
 * Note to self:
 * y = a + bx
 * a = My - b(Mx)
 * b = r * (sdy/sdx)
 *
***/
int objectDetector::detect_wall(std::vector<float> distances, float measure_error, float flat_error) {
  std::cout << "Entering detect_wall" << std::endl;

  if (distances.size() != 16) {
      return -1;
  }

  int n = 0;    // Size of distances
  float sumx = 0; // sum of x
  float sumy = 0; // sum of y
  float ssy = 0; // Sum of squared difference of x - ux
  float ssx = 0; // sum of squared differnce of y - uy
  float mx, my, sdx, sdy; // mean x/y, standard deviation x/y


  // Calculate Mean
  for (unsigned int i = 0; i < distances.size(); i++) {
    sumx += int(i);
    sumy += distances.at(i);
    n += 1;
  }
  mx = sumx / n;
  my = sumy / n;

  // Calculate Standard Deviation for X's and Y's
  for (unsigned int i = 0; i < distances.size(); i++) {
    ssy += std::pow(distances.at(i) - my, 2);
    ssx += std::pow(int(i) - mx, 2);
  }
  sdy = std::sqrt(ssy/n);
  sdx = std::sqrt(ssx/n);

//  std::cout << "sdy" << sdy << std::endl;
//  std::cout << "sdx" << sdx << std::endl;

  // Calculate R - sum(xy)/ swrt(sum(x^2) * sum(y^2))
  // Calculate Covariance
  float r, intercept, slope; // R value
  float sumxy = 0; // sum of all x*y
  float sumxx = 0; // sum of all x*x
  float sumyy = 0; // sum of all y*y


  for (unsigned int i = 0; i < distances.size(); i++) {
    sumxy += int(i) * distances.at(i);
    sumxx += std::pow(int(i), 2);
    sumyy += std::pow(distances.at(i), 2);
  }

  r = sumxy / sqrt(sumxx*sumyy);

  // Calculate slope and intercept
  slope = r * (sdy/sdx);
  // TODO: This assumes even number of beams
  intercept = (distances.at( n/2 - 1) + distances.at( n/2 )) / 2;
//  std::cout << "SLope " << slope << "  Intercept: " << intercept << std::endl;
//  std::cout << "MEANX, MEANY " << mx << " " << my << std::endl;

  // If any of the segments exceed tolerated measurement error -
  // A wall is not considered to exist across the field of vision
  bool wall = true;
  for ( unsigned int i = 0; i < distances.size(); i++ ){
    float errori = std::abs( (slope*int(i) + intercept) - distances.at(i) );
    if ( errori > measure_error )  {
//       std::cout << "error: " << (slope*int(i)+intercept) - distances.at(i) << std::endl;
//       std::cout << "Distance: " << distances.at(i) << std::endl;
//       std::cout << "Slope: " << slope << std::endl;
//       std::cout << "Intercept: " << intercept << std::endl;
      wall = false;
    }
  }

  // If a wall exists, check if flat, left slant, or right slant
  if (wall) {
    // flat wall
    if (std::abs(slope) < flat_error) {
      return 1;
    }
    //left slant (/)
    else if (slope > 0) {
      return 2;
    }
    //right slant (\)
    else { // b < 0
      return 3;
    }
  }
  // Check left and right fields of vision for hall way
  // TODO: EXPAND CASES TO CHECK FOR LEFT/RIGHT OBSTRUCTION
  else if (distances.size() == 16) {
    std::vector<float> left_v(distances.begin(), distances.begin() + 8);
    std::vector<float> right_v(distances.end() - 8, distances.end());

    int left_wall = detect_wall(left_v, measure_error, flat_error);
    int right_wall = detect_wall(right_v, measure_error, flat_error);

    if ((left_wall == 2) && (right_wall == 3)) {
      return 4;
    }
  }
  // No Wall
  return -1;
}

float apply_polynomial(float coefficients[], int degree, float x_value) {
    float result = 0;

    for (int i = 0; i < degree; i++) {
        result += coefficients[i] * x_value;
    }

    return result;
}

/*********************************************************************
 * Function to fit a polynomial onto a set of points.
 *
 * TODO: INSTEAD OF INPUTTING A FUNCTION, WE NOW INPUT A 'polynom_degree'!
 *
 * This function performs general curve fitting for polynomials.  We
 * construct the best possible fit of a polynomial 'f(x)' onto a set of
 * points 'points'.
 *
 * Normally, we return the 'correlation coefficient' 'r^2', which
 * represents the quality of the fit (i.e. whether the curve fits
 * well).  If the fit is well out of some 'scaling error',
 * then we return -1 to indicate that there is no fit at all.
 *
 * For any polynomial f(x) = c_n x^n + ... + c_0, the 'scaling error'
 * indicates how lenient we are about the scaling constant 'c_n'.
 * e.g. If f(x) is linear, the scaling error indicates the range of slope of f(x)
 * that we are willing to tolerate.
 * e.g. if f(x) = x^2, the scaling error indicates the steepness of f(x) that we are
 * willing to tolerate.
 *
***/
float polynomial_fit(int polynom_degree, vector<float> points, float scaling_error) {

    int N = points.size();    // Number of distance points
    float sumx = 0; // sum of x
    float sumy = 0; // sum of y
    float ssy = 0; // Sum of squared difference of x - ux
    float ssx = 0; // sum of squared differnce of y - uy
    float mx, my, sdx, sdy; // mean x/y, standard deviation x/y

    float r, intercept, slope; // r value
    float sumxy = 0; // sum of all x*y
    float sumxx = 0; // sum of all x*x
    float sumyy = 0; // sum of all y*y

/*************************** HERE BE DRAGONS ***************************************/
/* PLAN:
 *
 * Generalize this code for general polynomials.
 *
 * Compute the polynomial using the Matrix bit (rather than the linear standard deviation bit).
 * Then compute the r^2 value.
 * Return the r^2 value, unless the scaling value exceeds the scaling error.
 *
 * Reference:
 * http://mathworld.wolfram.com/LeastSquaresFittingPolynomial.html
 * http://mathworld.wolfram.com/LeastSquaresFitting.html
 * http://mathworld.wolfram.com/CorrelationCoefficient.html
 *
 * Compute Fourier Transforms ahead of time in order to get a signature for *any*
 * reasonable function f(x) (i.e. non-polynomials).
 * http://www.wolframalpha.com/input/?i=fourier+polynomial+for+cos(x)
 *
*/

    /***************** COMPUTE OUR POLYNOMIAL ******************/
    // This calculation follows closely the following:
    // http://mathworld.wolfram.com/LeastSquaresFittingPolynomial.html
    //
    // Please refer to that page if you are confused and you would
    // like to be even more confused. ;)

    float X[16][polynom_degree];
    float T[polynom_degree][16];
    float coefficients[polynom_degree];

    // First, we compute the matrix 'X' as given in the reference.
    for (int i = 0; i < 16; i++) {
        for (int k = 0; k < polynom_degree; k++) {
            // xi happens to be just 'i' in this case.
            X[i][k] = pow(i, k);
        }
    }

    // Next, we compute the transpose 'T' of matrix 'X', as discussed
    // in the reference.
    for (int i = 0; i < 16; i++) {
        for (int k = 0; k < polynom_degree; k++) {
            T[k][i] = X[i][k];
        }
    }

    // Finally, we take the product X*(y1, y2, y3, ..., yn) to obtain
    // the vector of coefficients (a0, a1, a2, ..., ak).
    int dotproduct;
    for (int k = 0; k < polynom_degree; k++) {
        dotproduct = 0;

        for (int i = 0; i < 16; i++) {
            dotproduct += T[k][i] * points.at(i);
        }

        coefficients[k] = dotproduct;
    }

    /***************** COMPUTE FIT QUALITY r ******************/
    r = 0;

    for (int i = 0; i < 16; i++) {
        // Take the difference between outcome and expected (using polynomial f(x)).
        r += std::pow(points.at(i) - apply_polynomial(coefficients, polynom_degree, i), 2);
    }

    r = sqrt(r);

    // TODO: Handle scaling error outside of this function, when performing
    // individual tests.  This is not the correct place for checking how
    // steep our curve is.
}

/*********************************************************************
 * Function to project each distance onto the y-axis.
 *
 * This function projects each point of a 'float' 'vector' of distances
 * onto the y-axis and returns the 'projected' points as a vector.
 *
 * Input:
 *   distances - the 'vector' points to be projected
 *
 * Returns:
 *   projected - the points projected onto the y-axis.
***/
vector<float> objectDetector::yaxis_projection(vector<float> distances){
cout << "Entering yaxis_projection" << endl;
    vector<float> projected;
    // Theta is the angle between the x-axis and the right most segment.
    // The angle between segments is 2.8 degrees
    float theta = 90 + (2.8 * .5 * int(distances.size()) );

    for ( int i=0; i<int(distances.size()); i++)
    {
        float theta_radians = theta*M_PI/180;
        float y = distances.at(i) * sin(theta_radians);
        projected.insert(projected.begin(), y);
//        std::cout << "THETA: " << theta << " SIN THETA: " << sin(theta_radians) << std::endl;
//        std::cout << "Value: " << distances.at(i) << " Projection: " << y << std::endl;

        // Increment theta for the next segment
        theta -= 2.8;
    }

    return projected;
}

/*********************************************************************
 * Slot to start this thread.
 *
 * We establish that this thread has started running, is not stopped,
 * emit that this thread has started running, and then begin detecting
 * objects among the 'dataPoints' caught by the slot.
***/
void objectDetector::StartDetect(int index, vector<float> dataPoints) {
cout << "Entering StartDetect" << endl;
    if (isrunning) return;
    isstopped = false;
    isrunning = true;
    emit running();
    doDetect(dataPoints);
}

void objectDetector::getCurrentNotifier(vector<string> someOrderedSounds) {
    this->currentNotifier.soundFiles = someOrderedSounds;
//    this->currentNotifier = someNotifier;

    for (int i = 0; i < 8; i++) {
        cout << "i=" << i << "AFTER SIGNAL, ASSIGN: " << currentNotifier.soundFiles.at(i) << endl;
    }
}

/*********************************************************************
 * Slot to stop this thread.
 *
 * We establish that this thread has stopped running, it is not running,
 * and emit that this thread has stopped.
***/
void objectDetector::StopDetect() {
cout << "Entering StopDetect" << endl;
    if (!isrunning || isstopped) return;

    isstopped = true;
    isrunning = false;
    emit stopped();
}

/**********************************************************************
 * Slot to change the signal distance
 *
 * Overwrite whatever the previous signal distance
***/
void objectDetector::SetSignalDist(float new_dist) {
cout << "Entering SetsignalDist" << endl;
    sig_dist = new_dist;
}
