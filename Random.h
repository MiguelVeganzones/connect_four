#pragma once
#include <random>

class Random
{
public:

	static void init();

	static float randfloat();

	static int randint(int Min, int Max);

private:
	static std::mt19937 s_random_engine;
	static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
};