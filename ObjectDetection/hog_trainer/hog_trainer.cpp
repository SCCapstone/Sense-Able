/*
    Written by Jonathan Senn
    Lots of code copied or inspired by https://github.com/DaHoC/trainHOG/blob/master/main.cpp#L101


*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <typeinfo>
#include <sys/types.h>
#include <dirent.h>
using namespace std;

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include "opencv2/objdetect.hpp"
using namespace cv;
using namespace cv::ml;

#include "utilities.h"


// Base Project directory
static string projDir = "/home/elrondhubbard/Documents/ObjectDetection/";
// Directory containing Positive samples
static string posSampleDir = projDir + "data/stairs/samp_positive/";
// Directory containing Negative samples
static string negSampleDir = projDir + "data/stairs/samp_negative/";


static void getFilesInDirectory(string DirName, vector<string>& fileNames) {
  DIR* dirp = opendir(DirName.c_str());
  struct dirent * dp;
  while (( dp = readdir(dirp)) != NULL ) {
    // string str(dp->d_name);
    fileNames.push_back(dp->d_name);
  }
  closedir(dirp);
}


int main(int argc, char const *argv[])
{

  static std::vector<string> positiveTrainingImages;
  static std::vector<string> negativeTrainingImages;
  // static std::vector<string> validExtensions;
  // validExtensions.push_back("jpg");
  // validExtensions.push_back("png");

  getFilesInDirectory( posSampleDir, positiveTrainingImages);
  getFilesInDirectory( negSampleDir, negativeTrainingImages);
  // std::cout << to_string(positiveTrainingImages) << endl;

  for (int i=0; i<positiveTrainingImages.size(); i++){
    cout<< positiveTrainingImages.at(i) << endl;
  }
  for (int i=0; i<negativeTrainingImages.size(); i++){
    cout<< negativeTrainingImages.at(i) << endl;
  }
  // This is the HOG
  cv::HOGDescriptor hog(
    Size(64,128), //winSize
    Size(16,16), //blocksize
    Size(8,8), //blockStride,
    Size(8,8), //cellSize,
             9, //nbins,
              1, //derivAper,
             -1, //winSigma,
              0, //histogramNormType,
            0.2, //L2HysThresh,
              1,//gammal correction,
              64,//nlevels=64
              0);//Use unsigned gradients

  // Define the SVM
  Ptr<SVM> svm = SVM::create();
  svm-> setType(SVM::C_SVC);
  svm-> setTKernel(SVM::LINEAR);
  svm-> setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));

  /*
  * 1. Generate and Store feature vectors of Positive samples
      
  */
  for (unsigned int i=0; i<positiveTrainingImages.size(); i++) {

    //Get Image
    Mat img = imread(posSampleDir+positiveTrainingImages.at(i));

    //Is valid image?
    if (! img.data ) {
      cout << "Could not open the image " << positiveTrainingImages.at(i) << endl;
    }
    // Resize images and Compute HOG Feature
    else {

      resize(img, img, cv::Size(64,128));
      // cout << img.rows << "   " << img.cols << endl;
      cout << "Computing HOG for " << positiveTrainingImages.at(i) << endl;
      std::vector<float> descriptors;
      hog.compute(img, descriptors);
    }
    //Store
    // hog.compute()
  }
  /*
  * 2. Generate and store feature vectors of negative samples
  */

  return 0;
}