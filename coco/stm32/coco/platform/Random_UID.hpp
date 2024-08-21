#pragma once

#include <coco/Random.hpp>


namespace coco {

/**
	Blocking implementation of a random number generator using the unique identifier.
	Recommended is to only obtain a seed for a pseudo random number generator.

	Resources:
		UID: 96-bit unique ID
*/
class Random_UID : public Random {
public:
	~Random_UID() override;

	void draw(void *data, int size) override;

protected:
	int x = 0;
};

} // namespace coco
