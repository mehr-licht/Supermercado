
#include "Utilities.h"
#include <algorithm>    //sort
#include <vector>

long long GetMilliCount() {
	timeb tb;
	ftime(&tb);
	long long nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

long long GetMilliSpan(long long nTimeStart) {
	long long nSpan = GetMilliCount() - nTimeStart;
	if (nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}

int greatness(int number) {
	int n = number;
	int great = 0;

	while (n >= 10) {
		n /= 10;
		great++;
	}
	return great;
}


bool sortPair (const std::pair<float,Road*> &a,const std::pair<float,Road*> &b)
{
       return a.first<b.first;
}

bool sortPairS (const std::pair<float, Supermarket *> &a,const std::pair<float, Supermarket *> &b)
{
       return a.first<b.first;
}
