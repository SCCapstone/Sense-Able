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
    https://docs.opencv.org/trunk/d7/d9f/tutorial_linux_install.html
  
  Note: This is a big install!

  qt5
    Install Tutorial:
    https://wiki.qt.io/Install_Qt_5_on_ubuntu
  
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

