/*
 * Searcher.h
 *
 *  Created on: 14/05/2018
 *      Author: luis
 */

#ifndef SRC_SEARCHER_H_
#define SRC_SEARCHER_H_

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "matcher.h"
#include "Menu.h"
#include "Files.h"


class Searcher {
private:
	std::vector<std::string> GetAllRouteIds(std::ifstream& filein, std::string routeName);
	std::vector<std::string> GetAllVertIdsFromEdge(std::ifstream& filein, std::vector<std::string> edgeIds);
	std::vector<std::string> GetAllCommonVertIds(std::vector<std::string> vert1Ids, std::vector<std::string> vert2Ids);
	void PrintAllCommonSupermarkets(std::vector<std::string> commonVertIds);
	std::vector<std::string> GetAproxRoutesFromPattern(string toSearch);

public:
	Searcher();
	virtual ~Searcher();

	void SearchForSupermarketInRoutes(std::string route1, std::string route2);
	void SearchForSupermarketInRoutesAprox(std::string route1, std::string route2);
};



#endif /* SRC_SEARCHER_H_ */
