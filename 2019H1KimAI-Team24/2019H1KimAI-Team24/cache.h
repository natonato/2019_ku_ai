#ifndef CACHE_H
#define CACHE_H

#define MAX_ENTRY 8388608				//8M
#include "common.h"
#include <cstdlib>

struct node {
	byte value;
	b64 key;
};

class Cache {
public:

	node *table;

	unsigned int index(b64 key) {
		return key % MAX_ENTRY;
	}

	int getValue(b64 key) {
		unsigned int idx = index(key);
		if (table[idx].key == key) {
			return table[idx].value;
		}
		return 0;
	}

	void putValue(b64 key, byte val) {
		unsigned int idx = index(key);
		table[idx].key = key;
		table[idx].value = val;
	}
	
	Cache() {
		table = (node*)calloc(MAX_ENTRY, sizeof(node));
	}
};

#endif