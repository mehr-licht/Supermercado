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

/**
 *
 */
void pre_kmp(std::string pattern, std::vector<int> & prefix);

/**
 *
 */
bool kmpMatcher(std::string text, std::string pattern);

/**
 *
 */
std::vector<int> numStringMatchingRoad(std::string filename,
		std::string toSearch);

/**
 *
 */
 std::vector<int> numStringMatching(std::string filename, std::string toSearch);

/**
 *
 */
 std::vector<int> numStringMatchingFreg(std::string filename,
		std::string toSearch);

/**
 *
 */
int editDistance(std::string pattern, std::string text);

/**
 *
 */
std::vector<float> numApproximateStringMatchingRoad(std::string filename,
		std::string toSearch);

/**
 *
 */std::vector<float> numApproximateStringMatching(std::string filename,
		std::string toSearch);

/**
 *
 */
std::vector<float> numApproximateStringMatchingFreg(std::string filename,
		std::string toSearch);

/**
 * checks if text is a word not to be matched because it appers very often
 * @param text to be investigated
 * @return true if it is one of those words and false otherwise
 */
bool notStreetName(std::string text);

/**
 * checks if text has only one word
 * @param text to be investigated
 * @return true if it has only one word and false otherwise
 */
bool onlyOneWord(std::string text);

#endif /* SRC_MATCHER_H_ */
