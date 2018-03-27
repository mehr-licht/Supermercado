/*
 * functions.h
 *
 *  Created on: 27/03/2018
 *      Author: up201607946
 */
#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include "Supermarket.h"
#include "Client.h"
#include <vector>
#include <queue>
#include <stack>
#include "Graph.h"
#include "Node.h"
#include "map.h"

void assignSupers();
bool Visited(unsigned int ordem, vector<Client> clients);
void toAndFrom();
int GetMilliCount();
int GetMilliSpan(int nTimeStart);
std::string floatToString(float i);
std::string intToString(int i);
std::string doubleToString(double i);


#endif
