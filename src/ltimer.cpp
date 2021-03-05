#include "ltimer.h"

template <typename T>
T MessageQueue<T>::receive()
{

}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{

}

LTimer::LTimer()
{
    //start the timer upon declaration;
    auto t1 = std::chrono::high_resolution_clock::now();
    max = 1;
    std::cout << " Timer Started!: "  << std::endl;
    threads.emplace_back(std::thread(&LTimer::spawnFrequency,this));

}

/* This is sourced from the CPPND-Concurrent-Traffic-Simulation Project submission */
//This frequncy is dependant upon game time, too
void LTimer::spawnFrequency()
{
    int countdown = 10 - max;
    auto randnum = rand() % countdown;
    auto t1 = std::chrono::high_resolution_clock::now();

    while (true)
    {
        auto t2 = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() >= randnum)
        {
            
            std::this_thread::sleep_for(std::chrono::seconds(randnum));
            std::cout << "Randnum!: " << randnum << std::endl;

            //_spawnQueue.send(std::move(currentPhase));
        }
    }
}

void LTimer::spawnMax()
{

}

LTimer::~LTimer()
{
        // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}