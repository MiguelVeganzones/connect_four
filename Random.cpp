//To use in various threads, uncoment mutex to use the same instance of mt19937 
//I think initialicing random::init once per thread does not work

#include "Random.h"
#include <mutex>
#include <chrono>

std::mt19937  Random::s_random_engine;
std::uniform_int_distribution<std::mt19937::result_type> Random::s_distribution;

std::mutex mu_randint;
std::mutex mu_randfloat;

void Random::init()
{
    s_random_engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

float Random::randfloat()
{
    mu_randfloat.lock();
    float f = (float)s_distribution(Random::s_random_engine) / (float)std::numeric_limits<uint32_t>::max();
    mu_randfloat.unlock();
    return f;
    //return (float)s_distribution(Random::s_random_engine) / (float)std::numeric_limits<uint32_t>::max();
}

int Random::randint(int Min, int Max)
{
    std::uniform_int_distribution<int> U(Min, Max);
    mu_randint.lock();
    int n = U(Random::s_random_engine);
    mu_randint.unlock();
    return n;
    //std::uniform_int_distribution<int> U(Min, Max);
    //return U(Random::s_random_engine);
}