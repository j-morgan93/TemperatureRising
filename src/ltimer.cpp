#include "ltimer.h"

LTimer::LTimer()
{
    score = 0;
    max = 0;
    t1 = std::chrono::high_resolution_clock::now();

}

/* This is sourced from the CPPND-Concurrent-Traffic-Simulation Project submission */
// This frequncy is dependant upon game time, too
// Execute the virtual function for deciding how many bodies can be spawned.
void LTimer::simulate()
{
    threads.emplace_back(std::thread (&LTimer::spawnMax, this));
}


//This changes the number of maximum asteroids that can be on the screen at any one time!
void LTimer::spawnMax()
{
       
    while (true)
    {
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();

        //std::cout << quit << std::endl;
        if (quit == true)
        {
            return;
        }
        else
        {
            //std::cout << "duration" << duration <<std::endl;
            if (duration < 7)
            {
                max = 0;
                //std::cout << "Level UP!: " << max << std::endl;
            }
            else if (duration >=7 && duration < 20)
            {
                max = 1;
                //std::cout << "Level UP!: " << max << std::endl;
            }
            else if (duration >=20 && duration < 0)
            {
                max = 2;
                //std::cout << "Level UP!: " << max << std::endl;
            }
            else if (duration >=0 && duration < 60)
            {
                max = 4;
                //std::cout << "Level UP!: " << max << std::endl;
            }
            else {
                max = 8;
                //std::cout << "Level UP!: " << max << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
                
    }
    return;
}

LTimer::~LTimer()
{
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });

}