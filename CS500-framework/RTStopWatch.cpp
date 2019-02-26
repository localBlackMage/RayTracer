#include "stdafx.h"

RTStopWatch::RTStopWatch() :
    m_Start(std_clock::now())
{
    static_assert(std::chrono::steady_clock::is_steady, "Serious OS/C++ library issues. Steady clock is not steady");
}

RTStopWatch::RTStopWatch(const RTStopWatch& rhs) :
    m_Start(rhs.m_Start)
{

}

RTStopWatch& RTStopWatch::operator=(const RTStopWatch& rhs)
{
    m_Start = rhs.m_Start;
    return *this;
}

// Resets stop watch to start point
std_clock::time_point RTStopWatch::Reset()
{
    m_Start = std_clock::now();
    return m_Start;
}
