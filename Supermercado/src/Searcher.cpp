///*
// * Searcher.cpp
// *
// *  Created on: 14/05/2018
// *      Author: luis
// */
//
//
//
//#include "Searcher.h"
//
//
//#define ROADFILE_ "roads.txt"
//#define EDGEFILE_ "edges.txt"
//#define SUPERFILE "supermarkets.txt"
//
//using namespace std;
//
//Searcher::Searcher() {
//	// TODO Auto-generated constructor stub
//
//}
//
//Searcher::~Searcher() {
//	// TODO Auto-generated destructor stub
//}
//
//vector<string> Searcher::GetAllRouteIds(ifstream& filein, string routeName)
//{
//	vector<string> routeIds;
//
//	while(!filein.eof())
//	{
//		string routeFileLine;
//		getline(filein, routeFileLine);
//
//		if(kmpMatcher(routeFileLine, routeName))
//		{
//			string s;
//			stringstream ssLine(routeFileLine);
//			getline(ssLine, s, ';');
//			routeIds.push_back(s);
//		}
//	}
//
//	return routeIds;
//}
//
//vector<string> Searcher::GetAllVertIdsFromEdge(ifstream& filein, vector<string> edgeIds)
//{
//	vector<string> vertIds;
//	vector<string>::iterator beg = edgeIds.begin(), end = edgeIds.end();
//	for(; beg != end; beg++)
//	{
//		filein.clear();
//		filein.seekg(0, ios::beg);
//		//Get route 1 vertices from edge file
//		while(!filein.eof())
//		{
//			string inLine;
//			getline(filein, inLine);
//			if(kmpMatcher(inLine, *beg) )
//			{
//				string s;
//				stringstream ss(inLine);
//				//Remove 1st line component as it is the edge ID.
//				getline(ss, s, ';');
//				getline(ss, s, ';');
//				if(find(vertIds.begin(), vertIds.end(), s) == vertIds.end())
//				{
//					vertIds.push_back(s);
//				}
//				getline(ss, s, ';');
//				if(find(vertIds.begin(), vertIds.end(), s) == vertIds.end())
//				{
//					vertIds.push_back(s);
//				}
//			}
//		}
//	}
//
//	return vertIds;
//}
//
//vector<string> Searcher::GetAllCommonVertIds(vector<string> vert1Ids, vector<string> vert2Ids)
//{
//	vector<string> commonVerts;
//	vector<string>::iterator beg1 = vert1Ids.begin(), end1 = vert1Ids.end();
//	while(beg1 != end1)
//	{
//		vector<string>::iterator beg2 = vert2Ids.begin(), end2 = vert2Ids.end();
//		for(; beg2 != end2; beg2++)
//		{
//			if(beg1->compare(*beg2) == 0)
//			{
//				cout << *beg1 << endl;
//				commonVerts.push_back(*beg1);
//			}
//		}
//		beg1++;
//	}
//	return commonVerts;
//}
//
//void Searcher::PrintAllCommonSupermarkets(vector<string> commonVertIds)
//{
//
//	ifstream infile(SUPERFILE);
//	if(!infile.is_open())
//	{
//		cout << "Could not open supermarket file.";
//		return;
//	}
//
//	bool foundSm = false;
//	for(unsigned int i=0;i<commonVertIds.size(); i++)
//	{
//		while(!infile.eof())
//		{
//			string fileLine;
//			getline(infile, fileLine);
//			if(kmpMatcher(fileLine, commonVertIds.at(i)) )
//			{
//				stringstream ss(fileLine);
//				string supermarketName;
//				getline(ss, supermarketName, ';');
//				getline(ss, supermarketName, ';');
//				cout << "Supermarket found in cross: " + supermarketName << endl;
//				foundSm = true;
//			}
//		}
//		infile.clear();
//		infile.seekg(0, ios::beg);
//	}
//
//	if(!foundSm)
//	{
//		cout << "No supermarkets found.";
//	}
//
//	Menu* sd = new Menu();
//		return;//sd->goBack(5);
//}
//
//vector<string> Searcher::GetAproxRoutesFromPattern(string roadName)
//{
//	ifstream fich(ROADFILE_);
//	/*if (!fich)
//	{ cout << "Erro a abrir ficheiro de leitura\n"; return 0; }*/
//
//	string line, word1;
//	int num=0, nwords=0;
//	vector<string> routeIds;
//	float minVal = 9999;
//	string minValRouteName;
//	while(getline(fich,line)) {
//		num=0;
//		nwords=0;
//		stringstream linestream(line);
//		string routeId;
//		getline(linestream, routeId,';');
//		string routeName;
//		getline(linestream, routeName,';');
//		stringstream s1(routeName);
//		while (!s1.eof()) {
//			s1 >> word1;
//			transform(roadName.begin(), roadName.end(), roadName.begin(), ::tolower);
//			transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
//			num += editDistance(roadName, word1);
//			nwords++;
//		}
//		float res=(float)num/nwords;
//		if(res < minVal && !routeName.empty())
//		{
//			cout << "New route: " << routeName << endl;
//			minVal = res;
//			minValRouteName = routeName;
//			routeIds.clear();
//			routeIds.push_back(routeId);
//		}
//		else if(minValRouteName.compare(routeName) == 0)
//		{
//			routeIds.push_back(routeId);
//		}
//	}
//	fich.close();
//
//	return routeIds;
//}
//
//void Searcher::SearchForSupermarketInRoutes(string route1, string route2)
//{
//	//Open file stream
//	string filename = ROADFILE_;
//	ifstream infile(filename.c_str());
//
//	if(!infile.is_open())
//	{
//		cout << "Could not open roads file.";
//		return;
//	}
//	//Still needs to test whether or not both route names are equal.
//
//	//Search for both routes names and gets their ids
//	vector<string> route1EdgeIds = this->GetAllRouteIds(infile, route1);
//	//resets ifstream to begining and clears all flags set from navigating the file
//	infile.clear();
//	infile.seekg(0, ios::beg);
//	vector<string> route2EdgeIds = this->GetAllRouteIds(infile, route2);
//	infile.close();
//	if(route1EdgeIds.size() == 0 || route2EdgeIds.size() == 0)
//	{
//		cout << "One or more of the route names were not found.";
//		return;
//	}
//
//	//Try and open edges file
//	infile.open(EDGEFILE_);
//
//	if(!infile.is_open())
//	{
//		cout << "Could not open edges file.";
//		return;
//	}
//
//	//Check every id from route 1 for comparison with route 2
//	vector<string> route1Vert = this->GetAllVertIdsFromEdge(infile, route1EdgeIds);
//	infile.clear();
//	infile.seekg(0, ios::beg);
//	vector<string> route2Vert = this->GetAllVertIdsFromEdge(infile, route2EdgeIds);
//	infile.close();
//	vector<string> commonVertIds = this->GetAllCommonVertIds(route1Vert, route2Vert);
//	if(commonVertIds.size() == 0)
//	{
//		cout << "No cross between both routes has been found.";
//		return;
//	}
//
//	this->PrintAllCommonSupermarkets(commonVertIds);
//}
//
//void Searcher::SearchForSupermarketInRoutesAprox(string route1, string route2)
//{
//	//These hold all ids and route names.
//	vector<string> route1AproxIds = this->GetAproxRoutesFromPattern(route1), route2AproxIds = this->GetAproxRoutesFromPattern(route2);
//	if(route1AproxIds.size() == 0 || route2AproxIds.size() == 0)
//	{
//		cout << "One or more of the route names was not found.";
//		return;
//	}
//
//	//Check if there are any equal ids in both vectors and remove from first vector.
//	/*
//	vector<string> route1AproxIdsUnique;
//	vector<string>::iterator beg1, end1 = route1AproxIds.end(), beg2 = route2AproxIds.begin(), end2 = route2AproxIds.end();
//
//	for(beg1 = route1AproxIds.begin(); beg1 != end1; beg1++)
//	{
//		if(find(beg2, end2, *beg1) == end2)
//		{
//			route1AproxIdsUnique.push_back(*beg1);
//		}
//	}
//
//	if(route1AproxIdsUnique.size() == 0)
//	{
//		cout << "Both route names led to the same set of results.";
//		return;
//	}*/
//
//	//Check every id from route 1 for comparison with route 2
//	ifstream infile(EDGEFILE_);
//
//	if(!infile.is_open())
//	{
//		cout << "Could not open edges file.";
//		return;
//	}
//
//	vector<string> route1Vert = this->GetAllVertIdsFromEdge(infile, route1AproxIds);
//	infile.clear();
//	infile.seekg(0, ios::beg);
//	vector<string> route2Vert = this->GetAllVertIdsFromEdge(infile, route2AproxIds);
//	infile.close();
//	vector<string> commonVertIds = this->GetAllCommonVertIds(route1Vert, route2Vert);
//	if(commonVertIds.size() == 0)
//	{
//		cout << "No cross between both routes has been found.";
//		return;
//	}
//
//	this->PrintAllCommonSupermarkets(commonVertIds);
//
//}
//
