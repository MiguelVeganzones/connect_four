#pragma once
#include <chrono>
#include <iostream>

class stopwatch
{
public:
    stopwatch()
    {
        s_start = std::chrono::steady_clock::now();
    }

    ~stopwatch()
    {
        s_end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::micro> duration = s_end - s_start;
        std::cout << "Process took " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()
            << "ms, (" << duration.count() << "us)\n";
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> s_start, s_end;
};

/*

time a function :

auto t0 = std::chrono::steady_clock::now();
f();
auto t1 = std::chrono::steady_clock::now();
// std::cout << nanoseconds{t-t0}.count << "ns\";
// std::cout << std::chrono::duration<double>{t1-t0}.count(); // print in floating point seconds
// std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count;



*/