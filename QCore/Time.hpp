#pragma once



#include <chrono>

#include "Core.hpp"



namespace qc {



// nanoseconds since epoch
s64 now();



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
    Clock(float frequency = 1.0f);

    // the clock starts now
    void restart();
    // the clock starts at the given time in nanoseconds since epoch
    void restart(s64 t);

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
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



s64 now() {
    return std::chrono::nanoseconds(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}



Clock::Clock(float frequency) :
    m_start(),
    m_period(1.0f / frequency),
    m_frequency(frequency)
{}

void Clock::restart() {
    m_start = std::chrono::high_resolution_clock::now();
}

void Clock::restart(s64 t) {
    m_start = std::chrono::high_resolution_clock::time_point(std::chrono::nanoseconds(t));
}

double Clock::age() const {
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - m_start).count() * m_frequency;
}

nat Clock::cycles() const {
    return nat(age());
}

double Clock::time() const {
    double a(age());
    return a - nat(a);
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