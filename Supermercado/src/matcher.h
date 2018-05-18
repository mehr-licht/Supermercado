/*
 * matcher.h
 *
 *  Created on: 13/05/2018
 *      Author: luis
 */

#ifndef SRC_MATCHER_H_
#define SRC_MATCHER_H_



#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>

#define INT_INFINITY std::numeric_limits<int>::max()

void pre_kmp(std::string pattern, std::vector<int> & prefix);
//int kmp(std::string text, std::string pattern);
bool kmpMatcher(std::string text, std::string pattern);
std::vector<int> numStringMatchingRoad(std::string filename,std::string toSearch);
std::vector<int> numStringMatching(std::string filename,std::string toSearch);
std::vector<int> numStringMatchingFreg(std::string filename,std::string toSearch);
int editDistance(std::string pattern, std::string text);
std::vector<float> numApproximateStringMatchingRoad(std::string filename, std::string toSearch);
std::vector<float> numApproximateStringMatching(std::string filename,std::string toSearch);
std::vector<float> numApproximateStringMatchingFreg(std::string filename,std::string toSearch);
bool notStreetName(std::string text);

#endif /* SRC_MATCHER_H_ */
