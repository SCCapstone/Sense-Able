/*********************************************************************
 * Class for detecting objects from a vector of points.
 *
 * Date last modified: 3 April 2018
 * Author: Jonathan Senn and Caleb Kisby
 *
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

//    obstacleTypes.push_back("Wall");
//    obstacleTypes.push_back("Wall Corner");
//    obstacleTypes.push_back("Pillar");
//    obstacleTypes.push_back("Trip Hazard");
//    obstacleTypes.push_back("Unidentified Obstacle");
//    obstacleTypes.push_back("None");
}

void objectDetector::doDetect(vector<float> distances) {
cout << "Entering doDetect" << endl;
    map<int, float> obstacle_fits;
    int obstacle_type = NONE;
    int running_fit = 0;

    if (!isrunning || isstopped) return;

    // Check if there are any obstacles within range, whatsoever.
    bool close = false;
    for (int i = 0; i < distances.size(); i++) {
        if (distances.at(i) < sig_dist + .1 * sig_dist) {
            close = true;
        }
    }

    if (close) {
        // There is an obstacle in range.  We need to identify it.

        // Compute each obstacle fit value.
        obstacle_fits.emplace(WALL, detectWall(distances));
        obstacle_fits.emplace(WALL_CORNER, detectCorner(distances));
        obstacle_fits.emplace(PILLAR, detectPillar(distances));
        obstacle_fits.emplace(TRIP_HAZARD, detectTripHazard(distances));
        obstacle_fits.emplace(UNIDENTIFIED_OBSTACLE, 0.0);
        obstacle_fits.emplace(NONE, -1.0);

        // Determine the obstacle type with the maximum fit value.
        for (map<int, float>::iterator it = obstacle_fits.begin();
             it != obstacle_fits.end(); ++it) {

            if (it->second >= running_fit) {
                obstacle_type = it->first;
            }
        }

    } else {
        // There is no obstacle in range.
        obstacle_type = NONE;
    }

    emit emitDetectedObject(obstacle_type);

    StopDetect();
//cout << "Exiting doDetect" << endl;
}

float objectDetector::detectWall(vector<float> distances) {
    vector<float> coefficients;
    float fit;

    // Fit a linear curve y = a1 * x + a0 to the distances.
    coefficients = polynomial_fit(1, distances);
    fit = fit_quality(coefficients, 1, distances);

    // TODO: If the linear curve is too steep, we want to return '0' to
    // indicate that the wall is not detected!  This should be handled here.

    // Essentially, we just check if the slope exceeds a certain error around our
    // expected slope.
    // Jonathan's old, helpful code, for just linear curves:

    // If any of the segments exceed tolerated measurement error -
    // A wall is not considered to exist across the field of vision
/*    bool wall = true;
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
*/

    return fit;
}

float objectDetector::detectCorner(vector<float> distances) {
    vector<float> coefficients;
    float fit;

    // Fit a degree 2 parabola to the distances.
    coefficients = polynomial_fit(2, distances);
    fit = fit_quality(coefficients, 2, distances);

    // TODO: If the parabola is too steep, or not sharp enough, we want to
    // return '0' to indicate that no parabola is detected!  This should
    // be handled here.

    return 0.0;
}

float objectDetector::detectPillar(vector<float> distances) {
    return 0.0;
}

float objectDetector::detectTripHazard(vector<float> distances) {
    return 0.0;
}

float apply_polynomial(vector<float> coefficients, int degree, float x_value) {
    float result = 0;

    for (int i = 0; i < degree; i++) {
        result += coefficients.at(i) * x_value;
    }

    return result;
}

/**************** HERE BE DRAGONS ****************/
/*___________________________________________________
@@@@@@@@@@@@@@@@@@@@@**^^""~~~"^@@^*@*@@**@@@@@@@@@
@@@@@@@@@@@@@*^^'"~   , - ' '; ,@@b. '  -e@@@@@@@@@
@@@@@@@@*^"~      . '     . ' ,@@@@(  e@*@@@@@@@@@@
@@@@@^~         .       .   ' @@@@@@, ~^@@@@@@@@@@@
@@@~ ,e**@@*e,  ,e**e, .    ' '@@@@@@e,  "*@@@@@'^@
@',e@@@@@@@@@@ e@@@@@@       ' '*@@@@@@    @@@'   0
@@@@@@@@@@@@@@@@@@@@@',e,     ;  ~^*^'    ;^~   ' 0
@@@@@@@@@@@@@@@^""^@@e@@@   .'           ,'   .'  @
@@@@@@@@@@@@@@'    '@@@@@ '         ,  ,e'  .    ;@
@@@@@@@@@@@@@' ,&&,  ^@*'     ,  .  i^"@e, ,e@e  @@
@@@@@@@@@@@@' ,@@@@,          ;  ,& !,,@@@e@@@@ e@@
@@@@@,~*@@*' ,@@@@@@e,   ',   e^~^@,   ~'@@@@@@,@@@
@@@@@@, ~" ,e@@@@@@@@@*e*@*  ,@e  @@""@e,,@@@@@@@@@
@@@@@@@@ee@@@@@@@@@@@@@@@" ,e@' ,e@' e@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@" ,@" ,e@@e,,@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@~ ,@@@,,0@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@,,@@@@@@@@@@@@@@@@@@@@@@@@@
"""""""""""""""""""""""""""""""""""""""""""""""""""
                 TREAD CAREFULLY.
*/

/*********************************************************************
 * Function to compute the best fit polynomial for a set of points.
 *
 * This calculation follows closely the following:
 * http://mathworld.wolfram.com/LeastSquaresFittingPolynomial.html
 * http://mathworld.wolfram.com/LeastSquaresFitting.html
 *
 * Please refer to that page if you enjoy confusing yourself with
 * a maze of intimidating math. -Caleb
 *
 *
 *
 * General strategy for coming up with a polynomial to fit:
 *
 * Take the non-polynomial function f(x) that you wish to approximate
 * with a polynomial, and compute its Fourier series via
 * http://www.wolframalpha.com/input/?i=fourier+polynomial+for+cos(x)
 *
 * The resulting polynomial F(x) is of degree 'n'.  Use this 'polynomial_fit'
 * function to construct a polynomial of best fit p(x) = an*x^n + ... + a0.
 * We can then use F(x) as an error range: If p(x) is too far from F(x), then
 * even though it has a well-fit polynomial of degree n, this polynomial is
 * not scaled correctly.  We can handle this error individually for each
 * new obstacle.
**/
vector<float> objectDetector::polynomial_fit(int polynom_degree, vector<float> points) {
    float X[points.size()][polynom_degree + 1];
    float T[polynom_degree + 1][points.size()];
    vector<float> coefficients;

    // First, we compute the matrix 'X' as given in the reference.
    for (int i = 0; i < points.size(); i++) {
        for (int k = 0; k < polynom_degree + 1; k++) {
            // xi happens to be just 'i' in this case.
            X[i][k] = pow(i, k);
        }
    }

    // Next, we compute the transpose 'T' of matrix 'X', as discussed
    // in the reference.
    for (int i = 0; i < points.size(); i++) {
        for (int k = 0; k < polynom_degree + 1; k++) {
            T[k][i] = X[i][k];
        }
    }/* TODO TODO TODO
Jinyu pointed out that this step is wrong!  We need to compute the *inverse* of X!
Credit Jinyu for helping with this function.
*/

    // Finally, we take the product X*(y1, y2, y3, ..., yn) to obtain
    // the vector of coefficients (a0, a1, a2, ..., ak).
    int dotproduct;
    for (int k = 0; k < polynom_degree + 1; k++) {
        dotproduct = 0;

        for (int i = 0; i < points.size(); i++) {
            dotproduct += T[k][i] * points.at(i);
        }

        coefficients.push_back(dotproduct);
    }

    return coefficients;
}

/*********************************************************************
 * Function to compute the r squared fit value of a *polynomial*
 * curve on a set of points.
 *
 * Reference:
 * http://mathworld.wolfram.com/LeastSquaresFittingPolynomial.html
 * http://mathworld.wolfram.com/CorrelationCoefficient.html
 *
 * // TODO: Handle scaling error outside of this function, when performing
    // individual tests.  This is not the correct place for checking how
    // steep our curve is.
**/
float objectDetector::fit_quality(vector<float> coefficients, int polynom_degree, vector<float> points) {
    int r = 0;
    for (int i = 0; i < points.size(); i++) {
        // Take the difference between outcome and expected (using polynomial with 'coefficients').
        r += std::pow(points.at(i) - apply_polynomial(coefficients, polynom_degree, i), 2);
    }
    r = sqrt(r);

    return r;
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
void objectDetector::StartDetect(int index, vector<float> dataPoints, bool aOrientation) {
cout << "Entering StartDetect" << endl;
    if (isrunning) return;
    isstopped = false;
    isrunning = true;
    emit running();
    doDetect(dataPoints);
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
cout << "Exiting StopDetect" << endl;
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
