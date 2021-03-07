#ifndef LTIMER_H
#define LTIMER_H

//Using SDL and standard IO
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <condition_variable>


//This is the timer class that tkaes care of timing things and game state
class LTimer
{
public:
    //Constructor of the Ltimer class
    LTimer();

    //Deconstructor of the LTimer class
    ~LTimer();

	//get max number of asteroids that can be spawned
	int getMax() {return max;}

	//get Quit flag
	bool getQuit() {return quit;}

	//set Quitflag
	void setQuit() {quit = true;}

	//set score
	void setScore() {score++;}

	//get Score
	int getScore() {return score;}

	//simulate the spawncyclee
	void simulate();

private:

    //send a maximum number that can be on screen
    void spawnMax();

	//quit flag
	bool quit = false;

	//clock for timing when to change the game state
	std::chrono::time_point<std::chrono::high_resolution_clock> t1;

    //this is the maximum number that can be spawned;
    int max;

	//this is the score!
	int score;

	//in a seperate thread, start the timer; the level thread has access to this timer
	std::vector<std::thread> threads;
};

#endif