#pragma once



#include <chrono>

#include "Core.hpp"



namespace qcu {



// seconds since epoch
double now();



// Simple clock usable for most timing-related needs
// Period is the number of seconds per clock cycle
// Frequency is how many cycles happen per seconds
// Period = 1 / Frequency
class Clock {

    private:

    std::chrono::high_resolution_clock::time_point m_start;
    double m_period;
    double m_frequency;

    public:

    // constructs clock with 1.0 sec period and 1.0 sec frequency
    Clock();

    // the clock starts now
    void restart();
    // the clock starts at the given time in seconds since epoch
    void restart(double t);

    // the fractional number of cycles since the clock started
    double age() const;

    // the integral number or cycles since the clock started
    nat cycles() const;
    
    // the fractional part of the current cycle
    double time() const;

    // get the period
    double period() const;
    // set the period
    void period(double period);

    // get the frequency
    double frequency() const;
    // set the frequency
    void frequency(double frequency);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENdoubleAdoubleION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



double now() {
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}



Clock::Clock() :
    m_start(),
    m_period(1.0),
    m_frequency(1.0)
{}

void Clock::restart() {
    m_start = std::chrono::high_resolution_clock::now();
}

void Clock::restart(double t) {
    m_start = std::chrono::high_resolution_clock::time_point(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(1.0)));
}

double Clock::age() const {
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - m_start).count() * m_frequency;
}

nat Clock::cycles() const {
    return nat(age());
}

double Clock::time() const {
    return fract(age());
}

double Clock::period() const {
    return m_period;
}

void Clock::period(double period) {
    m_period = period;
    m_frequency = 1.0 / period;
}

double Clock::frequency() const {
    return m_frequency;
}

void Clock::frequency(double frequency) {
    m_frequency = frequency;
    m_period = 1.0 / frequency;
}



}