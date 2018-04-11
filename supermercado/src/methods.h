/*
 * methods.h
 *
 *  Created on: 26/03/2018
 *      Author: luis
 */

#ifndef SRC_METHODS_H_
#define SRC_METHODS_H_
#include "map.h"
void allFromOne(map* obj,int from,int to);

void eachFromSelf(map* obj);
void fromTo(map* obj,int from,int to);
void optimal(map* obj);

void runAllMethods(map* obj,int from,int to);


#endif /* SRC_METHODS_H_ */
