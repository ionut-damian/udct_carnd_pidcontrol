# PID Controller

This project implements a PID controller in C++ to maneuver the vehicle around the lake track. Fore more details on the implementation, please check the file writeup.md

---

## Compiling the Code

The program can be built both with cmake/gcc and with Visual Studio. In both cases, the stand-alone simulator aslo needs to be downloaded. You can download it from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

### Cmake and GCC

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

Basic Build Instructions:

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

### Visual Studio

For setting up the environment for Visual Studio under Windows, follow these steps (credits go to [fkeidel](https://github.com/fkeidel/CarND-Term2-ide-profile-VisualStudio/blob/master/VisualStudio/README.md)):

1. Install cmake
    * Download and run windows installer (see https://cmake.org/download/)

2. Install make
    * Download setup from   http://gnuwin32.sourceforge.net/packages/make.htm
    * Select 'Complete package, except sources - Setup'
    * Run downloaded setup

3. Clone and install vcpkg
    * The install script used in the next step will asume that you installed vckpgk in c:\\vcpkg. You can choose another location, but then you have to adapt VcPkgDir in line 13 in install-windows.bat
    * cd c:\\
    * git clone https://github.com/Microsoft/vcpkg.git
    * cd vcpkg
    * call bootstrap-vcpkg.bat

4. Adapt and call the install script for windows
    * cd to directory ide_profiles\\VisualStudio
    * Open install-windows.bat and adjust lines 5 to 7 to the   settings you will use when building your Visual Studio project    (platform, toolset, buildtype)
    * You could also pass these settings as command line arguments  to install-windows.bat
    * If you have more than one toolset installed, comment line 14  and uncomment line 15
    * call install-windows.bat
    * the install scipt will
        * set the build parameters for the libraries to install     (platform, toolset, buildtype)
        * use vcpkg to download, build and install uWebSockets
            * it will download the latest version of uWebSockets

5. Open solution and adapt toolset settings
    * Open Localisation.sln
    * Open project properties
    * Adapt target platform version and platform toolset (use the   same setting that you used in the install script)

6. Build project in Visual Studio
    * Build the project for the platform and buildtype you used in the install script