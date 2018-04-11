#ifndef MENU_H_
#define MENU_H_

#include "Road.h"
#include "Graph.h"
#include "Node.h"
#include "RoadConnection.h"
#include "Supermarket.h"
#include "Client.h"
#include "connection.h"
#include "graphviewer.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include <string>
#include "Truck.h"
#include <unistd.h>
#include "Graph.h"
#include "Files.h"
#include "Utilities.h"//getMilliSpan
#include <stack>
#include <limits>
#include "edgetype.h"

#define IMGEXT ".png"

#define DBL_MAX std::numeric_limits<double>::max();

class Menu {
private:
	GraphViewer *gv;
	Graph<long long> graph;
	vector<Road*> roads;
	vector<RoadConnection*> connections;
	vector<Node*> nodes;
	vector<Supermarket*> supermarkets;
	vector<Client*> clients;
	vector<Truck*> trucks;
	static long long last_id;

	bool statsShown;

	struct methodData {
		int totalNodes;
		double totalWeight;
		long long totalMillis;
		vector<vector<long long> > routes;
	};

	struct methodStruct {
		struct methodData biMethod;
		struct methodData dOdMethod;
		struct methodData fwMethod;
	};

	methodStruct compareStruct;
public:

	/**
	 * creates the clients needed
	 * @param number of clientes needed
	 */
	void createClients(int clientes);

	/**
	 * Supermarket Delivery default constructor.
	 */
	Menu();

	/**
	 * Method to load graph from files.
	 */
	void loadFiles(int numNodes);

	/**
	 * Method to view graph in GraphViewer.
	 */
	void viewGraph(bool toSupermarket, long long idtruck,
			vector<long long> route);

	/**
	 * Method to return all nodes within certain stops, calculating the best path according to FloydWarshall's algorithm.
	 * @return Best route.
	 */
	vector<long long> getFW(long long SupermarketNode, vector<long long> stops,
			long long endNode, double &total);
	/**
	 * Dijkstra of Dijkstras method
	 * @param total to return the route total meters
	 * @param toPrint true implies printing the routes
	 */
	void DoD(double &total, bool toPrint);

	/**
	 * Floyd-Warshall method
	 * @param total to return the route total meters
	 * @param toPrint true implies printing the routes
	 */
	void fw(double &total, bool toPrint);

	/**
	 * Our bidireccional method
	 * @param total to return the route total meters
	 * @param toPrint true implies printing the routes
	 */
	void bi(double &total, bool toPrint);

	/**
	 * Compares between the 3 methods presented and says which is faster (and times of all 3), which has less nodes
	 * in the sum of all routes (and the number of nodes of all 3) and which is less long in meters ((and meters of all 3)
	 *
	 */
	void compareMethods();

	/**
	 * prints each calculated route for the supermarket and truck provided
	 * @param completeRoute the route to be printed
	 * @param s the supermarket
	 * @param t the truck
	 */
	void printRoute(vector<long long> & completeRoute, int s, int t);

	/**
	 * Method to return all nodes within certain stops, calculating the best path according to applying dijkstra after dijkstra.
	 * @return Best route.
	 */
	vector<long long> dijkstraOfDijkstras(long long firstNode,
			vector<long long> stops, long long endNode, double &total);

	/**
	 * verifies if the Graph is dense or sparse, highly connected or not and complete or not
	 */
	void getGraphStats();

	/**
	 * Calculate distance from one node to another.
	 * @param x1
	 * @param y1
	 * @param x2
	 * @param y2
	 * @return Distance in double.
	 */
	double euclideanDist(double x1, double y1, double x2, double y2);

	/**
	 * Main menu interface.
	 */
	void menu();

	/**
	 * Get route in console.
	 */
	void textRoute();

	/**
	 * call the functions to assign supermarkets and truck to clients
	 * @ param supers how many supermarkets
	 * @ param trucks how many trucks
	 */
	void assignClients(int supers, int camioes);

	/**
	 *assigns supermarkets  to clients
	 * @ param supers how many supermarkets
	 *
	 */
	void assignClientToSuper(int supers);

	/**
	 *assigns trucks  to clients
	 * @ param trucks how many trucks
	 *
	 */
	void assignClientToTruck(int trucks);

	/**
	 *verifies if given id corresponds to a Supermarket
	 * @parm idNo id number
	 */
	bool isSupermarket(int idNo);

	/**
	 *verifies if given id corresponds to a Client
	 * @parm idNo id number
	 */
	bool isClient(int idNo);

	/**
	 * returns the number of clients assigned to each supermarket
	 * @param super number of the supermarket
	 *@return number of clients of the supermarket given
	 */
	int numberOfClientsOfSupermarket(int super);

	/**
	 * menu to choose which method to be calculated to show the route in the graphviewer
	 */
	void gvRoute();

	/**
	 * Get route obtained with Floyd-Warshall algorithm in graphviewer.
	 */
	void gvRouteFW();

	/**
	 * Get route obtained with bidireccional algorithm in graphviewer.
	 */
	void gvRouteBi();

	/**
	 * Get route obtained with Dijkstra of Dijkstras algorithm in graphviewer.
	 */
	void gvRouteDoD();
}
;

#endif /* MENU_H_ */
