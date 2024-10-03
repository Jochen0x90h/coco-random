#pragma once


namespace coco {

/**
 * Hardware random number generator interface (comparable to /dev/random) that generates random 32 bit values
 * that can be used as seed for pseudo random number renerators.
*/
class Random {
public:

	virtual ~Random() {}

	/**
	 * Draw random values
	 * Blocks execution, therefore should be used only to initialize the seed of a pseudo random number generator
	 */
	virtual void draw(void *data, int size) = 0;
};

} // namespace coco
