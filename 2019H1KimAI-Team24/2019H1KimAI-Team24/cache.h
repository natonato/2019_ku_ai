#ifndef CACHE_H
#define CACHE_H

#define MAX_ENTRY 8388608				//8M
#include "common.h"
#include <cstdlib>


class Cache {
public:

	b64 *keyTable;
	byte *valTable;

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
	
	Cache() {
		keyTable = (b64*)calloc(MAX_ENTRY, sizeof(b64));
		valTable = (byte*)calloc(MAX_ENTRY, sizeof(byte));
	}
};

#endif