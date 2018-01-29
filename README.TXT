Sense-Able Prototype:

WARNING!  THE BINARY WILL NOT RUN WITHOUT INSTALLING THE SYSTEM
          REQUIREMENTS OUTLINED BELOW!  PLEASE INSTALL THESE
          REQUIREMENTS!
	  
	  For assistance, please email Jonathan Senn at js5@email.sc.edu.

SYSTEM REQUIREMENTS
___________________

  Make sure your system has all recent updates!
    sudo apt-get update

  opencv + contrib modules 
    Install Tutorial: 
    https://docs.opencv.org/trunk/d7/d9f/tutorial_linux_install.html:
      
      [compiler] sudo apt-get install build-essential
      [required] sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
      [optional] sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev

      Download the latest OpenCV 3 release:
        https://opencv.org/releases.html

      cd ~/opencv
      mkdir build
      cd build
      cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..

      make -j7 # runs 7 jobs in parallel

      sudo make install

  
  Note: This is a big install!

  qt5
    Install Tutorial:
    https://wiki.qt.io/Install_Qt_5_on_ubuntu
    sudo apt-get install qtmultimedia5-dev
  
  libusb
    Using apt-get on Ubuntu:
    sudo apt-get install libusb-1.0-0-dev
  
  libxml2
    Using apt-get on Ubuntu:
    sudo apt-get install libxml2
  
  gcc 4.8
    sudo apt-get install gcc

To make and run :
____________________
  
  In Sense-Able/build-leddargui-Desktop-Release/
    Run the following in bash:
    
    make
    ./leddargui

Make sure, of course, that the 'leddargui' binary isn't already
in the directory.  If you cloned this repository, 'leddargui' will
already be built.  Just remove it and rebuild if you prefer.

