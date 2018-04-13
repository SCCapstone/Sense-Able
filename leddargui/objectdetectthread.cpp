/*********************************************************************
 * Class for detecting objects from a vector of points.
 *
 * Date last modified: 3 April 2018
 * Author: Jonathan Senn and Caleb Kisby
 *
 * Good way to visualize polynomials for curve fitting:
 * https://www.desmos.com/calculator/pfdwlq5qht
 *
***/

#include <vector>
#include <string>
#include <cmath>
#include <math.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include "objectdetectthread.h"

using namespace cv;



/*********************************************************************
 *********************************************************************
                           PUBLIC
 *********************************************************************
**********************************************************************/



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
 * The usual constructor.
 *
 * When initialized, we establish that this thread is not running, and
 * has not been stopped.  We also register the string type so that it
 * may be emitted via a signal.
***/
objectDetector::objectDetector()
{
//cout << "Entering objectDetector" << endl;
    qRegisterMetaType<string>("string");
    isstopped = false;
    isrunning = false;

    sig_dist = 25.0;
}


/*********************************************************************
 * JONBOI's CODE
 *
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
        projected.push_back(y);
//        std::cout << "THETA: " << theta << " SIN THETA: " << sin(theta_radians) << std::endl;
//        std::cout << "Value: " << distances.at(i) << " Projection: " << y << std::endl;

        // Increment theta for the next segment
        theta -= 2.8;
    }

    return projected;
}


// CALAAABS CODE
vector<float> objectDetector::xaxis_projection(vector<float> distances) {
cout << "Entering xaxis_projection" << endl;
    vector<float> projected;

    float theta = 90 + (2.8 * 0.5 * int(distances.size()));

    for (int i = 0; i < distances.size(); i++) {
        float theta_radians = theta * M_PI / 180;
        float x = distances.at(i) * cos(theta_radians);
        projected.push_back(x);

        theta -=2.8;
    }

    return projected;
}


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
vector<float> objectDetector::polynomial_fit(int polynom_degree, vector<float> points, vector<float> xvalues) {
    Mat XMAT;
    Mat YMAT;
    Mat XINV; // *Left* Inverse of X
    Mat XTRANS; // Transpose
    Mat COEFFS;

    float X[points.size()][polynom_degree + 1];
    float Y[points.size()][1];
    vector<float> coefficients;

    // First, we compute the matrix 'X' as given in the reference.
    for (int i = 0; i < points.size(); i++) {
        for (int k = 0; k < polynom_degree + 1; k++) {
            X[i][k] = pow(xvalues.at(i), k);
        }
    }

    // We then compute the matrix form of 'points' as matrix 'Y':
    for (int i = 0; i < points.size(); i++) {
        Y[i][0] = points.at(i);
    }

    // We then convert X and Y to OpenCV 'Mat' objects for easy calculation.
    XMAT = Mat(points.size(), polynom_degree + 1, CV_32F, X);
    YMAT = Mat(points.size(), 1, CV_32F, Y);

    // Next, we compute the *left* inverse XINV of matrix 'X', if it exists.
//    XINV = XMAT.inv(DECOMP_SVD);
    XTRANS = XMAT.t();
    XINV = (XTRANS * XMAT).inv();
    XINV = XINV * XTRANS;

    // Compute the product X*(y1, y2, y3, ..., yn) to obtain the vector
    // of coefficients (a0, a1, a2, ..., ak).
    COEFFS = XINV * YMAT;

    // Finally, we convert the coefficients (a1, a2, ..., an) back to a vector to return.
    for (int i = 0; i < COEFFS.rows; ++i) {
        coefficients.push_back(COEFFS.at<float>(i));
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
 * Note that we use the more general definition of R squared:
 * https://en.wikipedia.org/wiki/Coefficient_of_determination
 *
 * // TODO: Handle scaling error outside of this function, when performing
    // individual tests.  This is not the correct place for checking how
    // steep our curve is.
**/
float objectDetector::fit_quality(vector<float> coefficients, int polynom_degree, vector<float> points, vector<float> xvalues) {
    float r_squared = 0.0;
    float rss = 0.0; // Residual sum of squares
    float tss = 0.0; // Total sum of squares
    float mean = 0.0;

    // We compute the mean of the points.
    for (int i = 0; i < points.size(); i++) {
        mean += points.at(i);
    }
    mean = (float)(mean) / (float)(points.size());

    for (int i = 0; i < points.size(); i++) {
        // Take the difference between outcome and expected (using polynomial with 'coefficients').
        rss += std::pow(points.at(i) - apply_polynomial(coefficients, polynom_degree, xvalues.at(i)), 2);
        tss += std::pow(points.at(i) - mean, 2);
    }

    // Note that for non-linear fitting, sometimes the r_squared value can be negative!
    // How do we interpret this?
cout << "RSS: " << rss << "TSS " << tss << endl;

    r_squared = 1.0 - (float)(rss / tss);
cout << "R^2: " << r_squared << endl;
    return r_squared;
}


/*********************************************************************
 * Function to do wall detection.
 *
 * This function determines if the given 'distances' are best fit
 * by a flat wall.  First, since the LIDAR distances are separated
 * by an angle, we project the distances onto the y-axis and the x-axis
 * to get our 'yvalues' and 'xvalues' for curve fitting.
 *
 * We then fit a linear curve y = a1*x + a0 to the distances.  This
 * is because a flat wall is best given by a straight line.  We also
 * obtain the fit quality 'fit' (i.e. the r squared value) of this fit.
 *
 * Finally, if the slope is too steep (in either direction), then we
 * decide that a wall does not fit at all, and reject the fit value.
 *
 * We return the quality of the fit.
 *
 * Parameters:
 *  distances - The 'vector' of distance points coming in.
 *
 * Returns:
 *  fit - The fit quality of the linear curve on the distances
 *  0.0 - Indicates that the curve does not fit at all.
 *
 ********************************************************************
***/

float objectDetector::detectWall(vector<float> distances) {
    vector<float> coefficients;
    vector<float> xvalues;
    vector<float> yvalues;
    float fit = 0.0;

    xvalues = xaxis_projection(distances);
    yvalues = yaxis_projection(distances);

    // Fit a linear curve y = a1 * x + a0 to the distances.
    coefficients = polynomial_fit(1, yvalues, xvalues);
    fit = fit_quality(coefficients, 1, yvalues, xvalues);

/*
cout << "WALL DETECT FIT: " << fit << endl;

    for (int i = 0; i < coefficients.size(); i++) {
        cout << "WALL DETECT COEFFICIENTS: " << coefficients.at(i) << " ";
    }
    cout << endl << endl;
*/

    // If the slope is too steep in either direction, then a wall is
    // not a good fit.
    if (coefficients.at(1) > 0.75 ||
        coefficients.at(1) < -0.75) {

        return 0.0;
    }

    return fit;
}


/*********************************************************************
 * Function to do wall corner detection.
 *
 * This function determines if the given 'distances' are best fit
 * by a wall corner.  First, since the LIDAR distances are separated
 * by an angle, we project the distances onto the y-axis and the x-axis
 * to get our 'yvalues' and 'xvalues' for curve fitting.
 *
 * We then fit a quadratic y = a0 + a1x + a2x^2 to the distances.  This
 * is because a wall corner, although rigid and pointed, can be adequately
 * modeled as a sharp quadratic curve, pointed downward.  We also
 * obtain the fit quality 'fit' (i.e. the r squared value) of this fit.
 *
 * If the quadratic happens to be linear (i.e. the a2 coefficient is 0),
 * or points upward (the a2 coefficient is negative),
 * then it does not model a wall corner, so we reject the fit value.
 *
 * Finally, if the quadratic is too flat, or not sharp enough,
 * then we determine that it is not a wall corner at all, and reject the fit value.
 *
 * We return the quality of the fit.
 *
 * Parameters:
 *  distances - The 'vector' of distance points coming in.
 *
 * Returns:
 *  fit - The fit quality of the quadratic curve on the distances
 *  0.0 - Indicates that the curve does not fit at all.
 *
 ********************************************************************
 * TODO: Corner detection is a little bit finicky (i.e. it rarely decides
 * that the obstacle is a wall corner).  Play around with
 * the flatness and sharpness numbers, perhaps, until desired
 * nonfinickyness.
 *
 * You can play around with such numbers with the following useful website:
 * https://www.desmos.com/calculator/pfdwlq5qht
***/
float objectDetector::detectCorner(vector<float> distances) {
    vector<float> coefficients;
    vector<float> yvalues;
    vector<float> xvalues;
    float fit;

    xvalues = xaxis_projection(distances);
    yvalues = yaxis_projection(distances);

    // Fit a degree 2 parabola to the distances.
    coefficients = polynomial_fit(2, yvalues, xvalues);
    fit = fit_quality(coefficients, 2, yvalues, xvalues);
/*
    cout << "CORNER FIT: " << fit << endl;

        for (int i = 0; i < coefficients.size(); i++) {
            cout << "CORNER COEFFICIENTS: " << coefficients.at(i) << " ";
        }
        cout << endl << endl;
*/
    // If the best fit degree parabola is actually a degree 1 parabola,
    // or points up, reject.
    if (coefficients.at(coefficients.size() - 1) >= 0) {
        return 0.0;

    // If the parabola is too flat, or not sharp enough, then a wall corner
    // is not a good fit.  Reject.
    } else if (coefficients.at(coefficients.size() - 1) > -0.1 ||
               coefficients.at(coefficients.size() - 1) < -1) {
        return 0.0;
    }

    return fit;
}


/*********************************************************************
 * Function to do pillar detection.
 *
***/
float objectDetector::detectPillar(vector<float> distances) {
    return 0.0;
}


/*********************************************************************
 * Function to do trip hazard detection.
 *
***/
float objectDetector::detectTripHazard(vector<float> distances) {
    return 0.0;
}


/*********************************************************************
 * Slot to start this thread.
 *
 * We establish that this thread has started running, is not stopped,
 * emit that this thread has started running, and then begin detecting
 * objects among the 'dataPoints' caught by the slot.
***/
void objectDetector::StartDetect(int index, vector<float> dataPoints, bool aOrientation) {
//cout << "Entering StartDetect" << endl;
    if (isrunning) return;
    isstopped = false;
    isrunning = true;
    emit running();
    doDetect(dataPoints, aOrientation);
//cout << "Exiting StartDetect" << endl;
}


/*********************************************************************
 * Slot to stop this thread.
 *
 * We establish that this thread has stopped running, it is not running,
 * and emit that this thread has stopped.
***/
void objectDetector::StopDetect() {
//cout << "Entering StopDetect" << endl;
    if (!isrunning || isstopped) return;

    isstopped = true;
    isrunning = false;
    emit stopped();
//cout << "Exiting StopDetect" << endl;
}


/**********************************************************************
 * Slot to change the signal distance
 *
 * Overwrite whatever the previous signal distance
***/
void objectDetector::SetSignalDist(float new_dist) {
//cout << "Entering SetsignalDist" << endl;
    sig_dist = new_dist;
}



/*********************************************************************
 *********************************************************************
                           PRIVATE
 *********************************************************************
**********************************************************************/



/*********************************************************************
 * Function to do obstacle detection.
 *
 * This function determines whether there is a recognizable obstacle
 * within range in the set of 'distances', and if so, emits that detected obstacle.
 *
 * First, we check if there are any obstacles in range.  If we are 'close' to
 * such an obstacle, then we compute the (r squared) fit values for each
 * possible obstacle type.  Possible obstacle types are determined by the
 * orientation 'aOrientation' of the Leddar sensor.  We consider the detected
 * obstacle to be that with the highest (i.e. closest to 1) r squared value.
 *
 * Note that if none of the obstacles have a higher fit value than the
 * FIT_THRESHOLD, then we emit UNIDENTIFIED_OBSTACLE.
 *
 * Parameters:
 *  distances - The 'vector' of distance points coming in
 *  aOrientation - The orientation of the Leddar sensor.
 *
 * Returns: None
 *
 * Emits:
 *  obstacleType - The type of obstacle detected.  Possible values are:
 *   NONE - If no obstacle is within range
 *
 *   UNIDENTIFIED_OBSTACLE - If an obstacle is within range, but all obstacle
 *    types fail to have fit values within the FIT_THRESHOLD.
 *
 *   WALL - If a wall has been detected
 *   WALL_CORNER - If a wall corner has been detected (horizontal orientation)
 *   PILLAR - If a pillar has been detected (horizontal orientation)
 *   TRIP_HAZARD - If a trip hazard has been detected (vertical orientation)
 *
 ********************************************************************
 * TODO: Austin suggested determining 'close' by taking the *average* of the
 *   'distances' and comparing that against our 'sig_dist'
 *
 * TODO: Implement PILLAR detection
 * TODO: Implement TRIP_HAZARD detection
 *
***/
void objectDetector::doDetect(vector<float> distances, bool aOrientation) {
//cout << "Entering doDetect" << endl;
    map<int, float> obstacle_fits;
    int obstacle_type = NONE;
    float running_fit = 0.0;

    if (!isrunning || isstopped) return;

    // Check if there are any obstacles within range, whatsoever.
    bool close = false;
    for (int i = 0; i < distances.size(); i++) {
        if (distances.at(i) < sig_dist + .1 * sig_dist) {
            close = true;
        }
    }

    // There is an obstacle in range.  We need to identify it.
    if (close) {

        // Compute each obstacle fit value for the chosen orientation.
        if (aOrientation == HORIZONTAL) {
            obstacle_fits.emplace(WALL, detectWall(distances));
            obstacle_fits.emplace(WALL_CORNER, detectCorner(distances));
            obstacle_fits.emplace(PILLAR, detectPillar(distances));
            obstacle_fits.emplace(UNIDENTIFIED_OBSTACLE, FIT_THRESHOLD);

        } else if (aOrientation == VERTICAL) {
            obstacle_fits.emplace(WALL, detectWall(distances));
            obstacle_fits.emplace(TRIP_HAZARD, detectTripHazard(distances));
            obstacle_fits.emplace(UNIDENTIFIED_OBSTACLE, FIT_THRESHOLD);
        } else {
            cout << "ERROR: Orientation hasn't been set." << endl;
            return;
        }

        // Determine the obstacle type with the maximum fit value.
        running_fit = 0;
        for (map<int, float>::iterator it = obstacle_fits.begin();
             it != obstacle_fits.end(); ++it) {

            if (it->second >= running_fit) {
                obstacle_type = it->first;
                running_fit = it->second;
            }
        }

    } else {
        // There is no obstacle in range.
        obstacle_type = NONE;
    }

    // Emit the detected obstacle!
    emit emitDetectedObject(obstacle_type);

    StopDetect();
//cout << "Exiting doDetect" << endl;
}


/*********************************************************************
 * Function to plug in a value into a polynomial.
 *
 * This function plugs in the given 'x_value' to the polynomial of degree
 * 'degree' with the given 'coefficients'.  This is done straightforwardly,
 * as the sum:
 *
 *   a0 + a1x + a2x^2 + ... + adx^d,
 *
 * Where d='degree', 'coefficients'= <a0, a1, ..., ad>, and x='x_value'.
 *
 * Parameters:
 *  coefficients - The coefficients that determine the polynomial
 *  degree - The degree of the polynomial
 *  x_value - The x value to apply
 *
 * Returns:
 *  result - The result of plugging the 'x_value' into the polynomial.
***/
float objectDetector::apply_polynomial(vector<float> coefficients, int degree, float x_value) {
    float result = 0;

    for (int i = 0; i <= degree; i++) {
        result += coefficients.at(i) * std::pow(x_value, i);
    }

    return result;
}


// End of file objectdetectthread.cpp



