# CPPND: Capstone Game - F-d Up!

This is the README for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
The code for this game was heavily sourced from the tutorials and examples given by LazyFoo (https://lazyfoo.net/tutorials/SDL/index.php)

This game - F'd Up! - is a key-board interactive space game in which you control a tiny capsule as it descends into the atmosphere of a planet! On the way, you encounter an increasingly dense atmosphere that is riddles with debris that you must navigate to succesfully land on the planet! The temperature of the spacecraft must be kept below 250 F, or else you'll destroy the precious cargo within.

## The Class Structure is:
* main: game loop of instantiation, movement, updating the logic, and rendering
* controller: handles the arrow key to modify the dot class
* dot: both the asteroids and the spacecraft are dot-type objects
* ltexture: texture-handling
* ltimer: game-timers and game-state variables ar held within this object
* renderer: the game window, rending, and collision are contained within this class

- the asteroid.bmp and m2020_1.bmp are custom files that are loaded into memory and rendered for each object of dot-class. The path fors this files is given as `/home/workspace/TemperatureRising/TemperatureRising/src/asteroid.bmp`

## Project Rubric Satisfaction - 5 minimum needed.
1. The game makes use of 5 distinct classes, as denoted above.
2. The project reads data from an external file using:
```c++
bool loadFromFile( std::string path, SDL_Renderer *gRenderer );
```
3. The project accepts input from a user as part of the necessary operation of the program by setting:
```c++
void Controller::handleEvent( SDL_Event& e, Dot &dot )
```
4. The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
5. All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.
6. Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions. They use get() and set() member functions as needed.
7. At least two variables are defined as references, or two functions use pass-by-reference in the project code. Some examples are listed below:
```c++
bool Renderer::CheckCollision(Dot &a, Dot &b)
bool Renderer::loadMedia(std::string path,LTexture &gDotTexture)
```
8. At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor. Two such example destructors are called out below, either for thread synchronization before game-exit, or for loading new textures.
```c++
LTimer::~LTimer()
LTexture::~LTexture()
```
9. The project uses multiple threads in the execution. A virtual function is used in LTimer to independantly run
```c++
void LTimer::simulate()
{
    threads.emplace_back(std::thread (&LTimer::spawnMax, this));
}
```

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL_Image libraries:
  * Linux: Aside from habing SDL installed, you need to make sure you have libsdl2-image-dev installed on your machine, recommended using `sudo apt-get install libsdl2-image-dev`.
  * Windows: you can follow the tutorials found on Lazy Foo's website: (https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/windows/msvc2019/index.php)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./F_d_UP`.