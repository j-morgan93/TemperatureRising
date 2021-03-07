#ifndef LTIMER_H
#define LTIMER_H

//Using SDL and standard IO
#include <iostream>
#include "SDL.h"
#include <string>
#include <mutex>
#include <vector>
#include <thread>
#include <deque>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <condition_variable>

/* This MessageQueue is taken from the CPPND-Concurrent-Traffic-Simulation Project submission */
template <class T>
class MessageQueue
{
	public:

	//receives a message for either spawnmax or spawnfreq
	T receive();

	//sends a message for either spawnmax or spawnfreq
	void send(T &&msg);

	private:

	std::deque<T> queue_;
	std::condition_variable condition_;
	std::mutex mutex_;

};

//This is the timer class that tkaes care of timing thingssss
class LTimer
{
public:
    //Constructor of the Ltimer class
    LTimer();

    //Deconstructor of the LTimer class
    ~LTimer();

    //sends a message of when to spawn
    void spawnFrequency();

	//get max number of asteroids that can be spawned
	int getMax() {return max;}

	//get Quit flag
	bool getQuit() {return quit;}

	//set Quitflag
	void setQuit() {quit = true;}

	//simulate the spawncyclee
	void simulate();

	//Spawn phase signal type
	enum SpawnPhase {spawn, nospawn};

	//get current spawn phase
	SpawnPhase getCurrentPhase() {return currentPhase;}
	
private:

    //send a maximum number that can be on screen
    void spawnMax();

	//quit flag
	bool quit = false;

	//clock for timing when to change the game state
	std::chrono::time_point<std::chrono::high_resolution_clock> t1;

	MessageQueue<SpawnPhase> _spawnQueue;

    //this is the spawn signal
    SpawnPhase currentPhase;

    //this is the maximum number that can be spawned;
    int max;

	//in a seperate thread, start the timer; the level thread has access to this timer
	std::vector<std::thread> threads;
};

#endif