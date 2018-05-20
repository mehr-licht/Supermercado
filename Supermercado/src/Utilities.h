
#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <time.h>//getMilliSpan
#include <sys/timeb.h>//getMilliSpan
#include <algorithm>
#include "Road.h"
#include "Supermarket.h"
/**
 * get milliseconds
 * @return milliseconds
 */
long long GetMilliCount();

/**
 * get time elapsed between nTimeStart and now
 * @param nTimeStart time stamp of the beginning
 * @return milliseconds elapsed since nTimeStart
 */
long long GetMilliSpan(long long nTimeStart) ;

/**
 * measure the greatness of a number
 * @param number
 * @return greatness of the number
 */
int greatness(int number) ;

/**
 * function to sort the vector of pairs
 * @param pair first of one element
 * @param pair first of another element
 */
bool sortPair (const std::pair<float,Road*> &a,const std::pair<float,Road*> &b);

/**
 * function to sort the vector of pairs
 * @param pair first of one element
 * @param pair first of another element
 */
bool sortPairS (const std::pair<float, Supermarket *> &a,const std::pair<float, Supermarket *> &b);

#endif /* UTILITIES_H_ */
