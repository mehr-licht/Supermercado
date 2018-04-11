
#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <time.h>//getMilliSpan
#include <sys/timeb.h>//getMilliSpan

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

#endif /* UTILITIES_H_ */
