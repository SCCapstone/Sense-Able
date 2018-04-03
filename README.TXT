Sense-Able Prototype:
	  
	  For assistance, please email Jonathan Senn at js5@email.sc.edu.

________________________
CONTENTS
________________________
1. SYSTEM REQUIREMENTS
2. BUILDING AND RUNNING
3. TESTING

________________________
1. SYSTEM REQUIREMENTS
________________________

  Linux - Ubuntu 16.03 LTS
  Architecture - 64 bit


  Make sure your system has all recent updates!
    sudo apt update


  Install QtSerialPort
    sudo apt install libqt5serialport5-dev


________________________
2. BUILDING AND RUNNING
________________________

  Download and unpack the latest release:
    https://github.com/SCCapstone/Sense-Able/releases
    tar -zxvf sense-able-release.tar.gz


  Run our execution script:
    cd Release/build_deploy/
    sudo ./runSenseAbleGui


________________________
3. TESTING
________________________
In order to run tests, just run the ./leddargui executable in the
build-leddargui-Desktop-Debug/ debug directory.

We give an overview of how one should make their own tests:

_________________
UNIT TESTING:
_________________
We use the googletest testing framework.

In order to test a function, use the following template (within the
unittestsuite.cpp file):

TEST (TestCase, TestName) {
	EXPECT_EQ(expected_value, function(args...))
}
_________________
BEHAVIOR TESTING:
_________________
We use the QTest testing framework to simulate clicks and keypresses
on the gui.

In order to test a behavior, use the following template (within the
QtBehaviorTestSuite.cpp file):

void QtBehaviorTestSuite::testName() {
	MainWindow window;
	
	QSignalSpy spy(&window, SIGNAL(nameOfSignalToTest()));
	QWidget widget = window.findChild<WidgetType>("name of widget");
	
	// Simulate use of the widget here
	
	// We should make this a separate function; less typing:
	cout << "testStreamButtonClicked:  ";
    if (spy.count() == 1) {
        cout << "SUCCESS";
    } else {
        cout << "FAILURE";
    }
    cout << endl;

}

This function sets up a spy to track whether the given signal emits.
We then get the widget on the screen to do something to, and simulate
that widget (i.e. do a keypress or a mouse click, etc.).  See the
QTest documentation on how to simulate a widget.  Finally, we output
whether the simulation was actually performed ("SUCCESS") or not
("FAILURE").
