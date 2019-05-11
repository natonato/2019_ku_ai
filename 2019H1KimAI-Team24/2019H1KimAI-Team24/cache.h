#ifndef CACHE_H
#define CACHE_H

#include "common.h"
#include <cstdlib>
#include <vector>

class Cache {
	static constexpr int SIZE = 0x800000 + 9;
public:

	std::vector<unsigned int> keyTable;
	std::vector<byte> valTable;

	unsigned int index(b64 key) {
		return key % SIZE;
	}

	int getValue(b64 key) {
		unsigned int idx = index(key);
		return (keyTable[idx] == (unsigned int)key) ? valTable[idx] : 0;
	}

	void putValue(b64 key, byte val) {
		unsigned int idx = index(key);
		keyTable[idx] = index(key);
		valTable[idx] = val;
	}
	
	Cache() : keyTable(SIZE), valTable(SIZE) {}
};

#endif