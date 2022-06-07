#pragma once
#include "TTable.h"

class THashTable : public TTable {
protected:
	int HashFunc(TKey key)  {
		return key;
	}
};
