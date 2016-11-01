#include "Utilities.h"

#include <random>


float getRandomNumb(float min, float max)
{
	static std::random_device::result_type seed = std::random_device()();
	static std::mt19937 randomEngine(seed);


	std::uniform_real_distribution<float> randNumGen(min, max);
	
	return randNumGen(randomEngine);

}


int getRandomNumb(int min, int max)
{
	static std::random_device::result_type seed = std::random_device()();
	static std::mt19937 randomEngine(seed);


	std::uniform_int_distribution<int> randNumGen(min, max);

	return randNumGen(randomEngine);

}