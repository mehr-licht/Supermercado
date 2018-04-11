
#ifndef FILES_H_
#define FILES_H_

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Road.h"
#include "Truck.h"
#include "Node.h"
#include "RoadConnection.h"
#include "Supermarket.h"
#include "Client.h"
#include <unistd.h>

#define TXTEXT ".txt"
#define NODEFILE "nodes"
#define ROADFILE "roads"
#define EDGEFILE "edges"

class Files {
public:
	/**
	 * Load nodes file.
	 * @return Nodes vector.
	 */
	vector <Node*> loadNodes(int numNodes);

	/**
	 * Load roads file.
	 * @return Roads vector.
	 */
	vector <Road*> loadRoads(int numNodes);

	/**
	 * Load connections file.
	 * @return Connections vector.
	 */
	vector <RoadConnection*> loadConnections(int numNodes);

	/**
	 * Load predefined supermarket file.
	 * @return	Supermarkets vector.
	 */
	vector <Supermarket*> loadSupermarkets();

	/**
	 * Load predefined clients file.
	 * @return	clients vector.
	 */
	vector <Client*> loadClients();

	/**
	 * Load predifined truck file.
	 * @param clients
	 * @return	trucks vector.
	 */
	vector <Truck*> loadTruck(vector <Client*> clients);
};




#endif /* FILES_H_ */
