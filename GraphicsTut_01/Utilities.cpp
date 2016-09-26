#include "Utilities.h"

#include <random>


float getRandomNumb(float rangeStart, float rangeEnd)
{
	static std::random_device::result_type seed = std::random_device()();
	static std::mt19937 randomEngine(seed);

	std::uniform_real_distribution<float> randNumGen(rangeStart, rangeEnd);

	return randNumGen(randomEngine);

}