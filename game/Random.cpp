#include "Random.h"
std::random_device Random::rnd;
std::mt19937 Random::mt(rnd());
Random::Random()
{
	offset = 0;
}

Random::~Random()
{
}

int Random::Generate(int min, int max)
{
	if (min < 0) {
		offset = min;
		std::uniform_int_distribution<> rn(0, max - offset);
		return rn(mt) + offset;
	}
	else {
		std::uniform_int_distribution<> rn(min, max);
		return rn(mt);
	}
}