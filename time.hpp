#pragma once

#include <chrono>

#include "core.hpp"

namespace qc::core {

    //
    // Returns nanoseconds since epoch
    //
    s64 now();

    //
    // Simple clock usable for most timing-related needs
    // Period is the number of seconds per clock cycle
    // Frequency is how many cycles happen per seconds
    // Period = 1 / Frequency
    //
    class Clock {

        private:

        std::chrono::high_resolution_clock::time_point _start;
        double _period;
        double _frequency;

        public:

        //
        // constructs clock with 1.0 sec period and 1.0 sec frequency
        //
        Clock(float frequency = 1.0f);

        //
        // ...
        // the clock starts now
        //
        void restart();
        // the clock starts at the given time in nanoseconds since epoch
        void restart(s64 t);

        //
        // the fractional number of cycles since the clock started
        //
        double age() const;

        //
        // the integral number or cycles since the clock started
        //
        nat cycles() const;

        //
        // the fractional part of the current cycle
        //
        double time() const;

        //
        // gets/sets the period
        //
        double period() const;
        void period(double period);

        //
        // gets/sets the frequency
        //
        double frequency() const;
        void frequency(double frequency);

    };

}

// INLINE IMPLEMENTATION ///////////////////////////////////////////////////////////////////////////////////////////////

namespace qc::core {

    inline s64 now() {
        return std::chrono::nanoseconds(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    inline Clock::Clock(float frequency) :
        _start(),
        _period(1.0f / frequency),
        _frequency(frequency)
    {}

    inline void Clock::restart() {
        _start = std::chrono::high_resolution_clock::now();
    }

    inline void Clock::restart(s64 t) {
        _start = std::chrono::high_resolution_clock::time_point(std::chrono::nanoseconds(t));
    }

    inline double Clock::age() const {
        return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - _start).count() * _frequency;
    }

    inline nat Clock::cycles() const {
        return nat(age());
    }

    inline double Clock::time() const {
        double a(age());
        return a - nat(a);
    }

    inline double Clock::period() const {
        return _period;
    }

    inline void Clock::period(double period) {
        _period = period;
        _frequency = 1.0 / period;
    }

    inline double Clock::frequency() const {
        return _frequency;
    }

    inline void Clock::frequency(double frequency) {
        _frequency = frequency;
        _period = 1.0 / frequency;
    }

}
