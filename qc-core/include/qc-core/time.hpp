#pragma once

#include <chrono>

#include <qc-core/core.hpp>

namespace qc
{
    //
    // Returns nanoseconds since epoch
    //
    nodisc s64 now();

    //
    // Simple clock usable for most timing-related needs
    // Period is the number of seconds per clock cycle
    // Frequency is how many cycles happen per seconds
    // Period = 1 / Frequency
    //
    class Clock
    {
      public:

        //
        // constructs clock with 1.0 sec period and 1.0 sec frequency
        //
        explicit Clock(f64 frequency = 1.0f);

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
        nodisc f64 age() const;

        //
        // the integral number or cycles since the clock started
        //
        nodisc u64 cycles() const;

        //
        // the fractional part of the current cycle
        //
        nodisc f64 time() const;

        //
        // gets/sets the period
        //
        nodisc f64 period() const;
        void period(f64 period);

        //
        // gets/sets the frequency
        //
        nodisc f64 frequency() const;
        void frequency(f64 frequency);

      private:

        std::chrono::steady_clock::time_point _start;
        f64 _period;
        f64 _frequency;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    finline s64 now()
    {
        return std::chrono::nanoseconds(std::chrono::steady_clock::now().time_since_epoch()).count();
    }

    finline Clock::Clock(const f64 frequency) :
        _start(),
        _period(1.0 / frequency),
        _frequency(frequency)
    {}

    finline void Clock::restart()
    {
        _start = std::chrono::steady_clock::now();
    }

    finline void Clock::restart(const s64 t)
    {
        _start = std::chrono::steady_clock::time_point(std::chrono::nanoseconds(t));
    }

    finline f64 Clock::age() const
    {
        return std::chrono::duration<f64>(std::chrono::steady_clock::now() - _start).count() * _frequency;
    }

    finline u64 Clock::cycles() const
    {
        return u64(age());
    }

    finline f64 Clock::time() const
    {
        const f64 a(age());
        return a - f64(s64(a));
    }

    finline f64 Clock::period() const
    {
        return _period;
    }

    finline void Clock::period(const f64 period)
    {
        _period = period;
        _frequency = 1.0 / period;
    }

    finline f64 Clock::frequency() const
    {
        return _frequency;
    }

    finline void Clock::frequency(const f64 frequency)
    {
        _frequency = frequency;
        _period = 1.0 / frequency;
    }
}
