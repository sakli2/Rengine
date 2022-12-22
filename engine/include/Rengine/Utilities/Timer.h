#include "pch.h"

namespace RENGINE
{
    class Timer
    {
    public:
        Timer(bool startTimer = true)
        {
            if(startTimer)
                start();
        }
        ~Timer()
        {
            if(!stopped)
                stop();
        }
        void start()
        {
            m_StartTimePoint = std::chrono::high_resolution_clock::now();   
        }
        void stop()
        {
            stopped = true;

            auto endTimePoint = std::chrono::high_resolution_clock::now();

            auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_StartTimePoint).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(endTimePoint).time_since_epoch().count();
            
            auto duration = end - start;
            double us = duration  * 0.000001;

            LOG::info("[TIMER]" + std::to_string(duration) + "ns(" + std::to_string(us) + "ms)" );
        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
        bool stopped = false;
    };

}
