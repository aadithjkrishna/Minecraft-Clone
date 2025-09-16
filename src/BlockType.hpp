#ifndef BLOCK_TYPE_HPP
#define BLOCK_TYPE_HPP

#include <cstdint>

enum FACES : uint8_t {
    FRONT,
    BACK,
    RIGHT,
    LEFT,
    TOP,
    BOTTOM
};

enum BLOCKS : uint8_t{
	AIR,
	GRASS,
	DIRT,
	STONE,
	IRON,
};

#endif