#pragma once



#include <chrono>

#include "Core.hpp"



namespace qmu {



double now();



class Clock {

    private:

    std::chrono::high_resolution_clock::time_point m_start;
    double m_period;
    double m_frequency;

    public:

    Clock();

    void restart();

    double age() const;
    
    double time() const;

    nat cycles() const;

    void recycle();

    void decycle();

    double period() const;
    void period(double period);

    double frequency() const;
    void frequency(double frequency);

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

double Clock::age() const {
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - m_start).count() * m_frequency;
}

double Clock::time() const {
    return fract(age());
}

nat Clock::cycles() const {
    return static_cast<nat>(age());
}

void Clock::recycle() {
    m_start += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::duration<double>(cycles() * m_period));
}

void Clock::decycle() {
    if (cycles() > 0) {
        m_start += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::duration<double>(m_period));
    }
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