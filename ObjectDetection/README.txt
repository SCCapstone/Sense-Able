
Required software: 
  OpenCV Libraries + contrib modules - https://docs.opencv.org/trunk/d7/d9f/tutorial_linux_install.html

Instructions to run:
  From ObjectDetection/hog_trainer:
    cmake .
    make
    ./hog_script.sh 


train_HOG.cpp: 
  Executable that will test or train a Hog+SVM object detector given some 
  training set. 

hog_script:
  Passes all required arguments to HogTrainer
  Detector object is saved to the file "my_dector.yml" 
