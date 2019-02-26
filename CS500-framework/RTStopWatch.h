#pragma once
#include <chrono>

using std_clock         = std::chrono::steady_clock;
using std_microseconds  = std::chrono::microseconds;
using std_milliseconds  = std::chrono::milliseconds;
using std_seconds       = std::chrono::seconds;

class RTStopWatch
{

public:

                            RTStopWatch();
                            RTStopWatch(const RTStopWatch&);
                            RTStopWatch& operator=(const RTStopWatch& rhs);
                            ~RTStopWatch() = default;

    // Return the elapsed microseconds since start
    inline uint64           ElapsedInUs() const;

    // Return the elapsed milliseconds since start
    inline uint64           ElapsedInMs() const;

    // Return the elapsed seconds since start
    inline uint64           ElapsedInSec() const;

    std_clock::time_point   Reset();

private:
    std_clock::time_point   m_Start;

};

//////////////////////////////////////////////////////////////////////////

inline uint64 RTStopWatch::ElapsedInUs() const
{
    return std::chrono::duration_cast<std_microseconds>(std_clock::now() - m_Start).count();
}
// Return the elapsed milliseconds since start
inline uint64 RTStopWatch::ElapsedInMs() const
{
    return std::chrono::duration_cast<std_milliseconds>(std_clock::now() - m_Start).count();
}
// Return the elapsed seconds since start
inline uint64 RTStopWatch::ElapsedInSec() const
{
    return std::chrono::duration_cast<std_seconds>(std_clock::now() - m_Start).count();
}