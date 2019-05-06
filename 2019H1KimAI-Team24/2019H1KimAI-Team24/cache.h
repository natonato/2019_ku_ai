#ifndef CACHE_H
#define CACHE_H

#define MAX_ENTRY 0x800000				//8M
#include "common.h"
#include <cstdlib>
#include <vector>


class Cache {
public:

	std::vector<b64> keyTable;
	std::vector<byte> valTable;

	unsigned int index(b64 key) {
		return key % MAX_ENTRY;
	}

	int getValue(b64 key) {
		unsigned int idx = index(key);
		if (keyTable[idx] == key) {
			return valTable[idx];
		}
		return 0;
	}

	void putValue(b64 key, byte val) {
		unsigned int idx = index(key);
		keyTable[idx] = key;
		valTable[idx] = val;
	}
	
	Cache() : keyTable(MAX_ENTRY), valTable(MAX_ENTRY) {}
};

#endif