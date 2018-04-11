#include "Files.h"
#include <algorithm>    //sort
#include <vector>
#include <string>
#include <iostream>

vector<Client> invertedClients;

vector<Node*> Files::loadNodes(int numNodes) {
	vector<Node*> nodes;

	std::stringstream sstm;
	sstm << NODEFILE << numNodes << TXTEXT;
	string filename = sstm.str();
	if (numNodes==0)	 filename = "nodes.txt";
	string line;
	ifstream file(filename.c_str());

	while (getline(file, line)) {
		stringstream linestream(line);
		string s;
		getline(linestream, s, ';');
		long long id = abs(atoll(s.c_str()));
		getline(linestream, s, ';');
		double lat = strtod(s.c_str(), NULL);
		getline(linestream, s, ';');
		double lon = strtod(s.c_str(), NULL);
		getline(linestream, s, ';');
		double latRad = strtod(s.c_str(), NULL);
		getline(linestream, s, ';');
		double lonRad = strtod(s.c_str(), NULL);
		Node* node = new Node(id, lat, lon, latRad, lonRad);
		nodes.push_back(node);

	}

	return nodes;
}

vector<Road*> Files::loadRoads(int numNodes) {
	vector<Road*> roads;
	std::stringstream sstm;
	sstm << ROADFILE << numNodes << TXTEXT;
	string filename = sstm.str();
	if (numNodes==0)	filename = "roads.txt";
	string line;
	ifstream file(filename.c_str());

	while (getline(file, line)) {
		stringstream linestream(line);
		string s;
		getline(linestream, s, ';');
		long long id = atoll(s.c_str());
		getline(linestream, s, ';');
		string name = s;
		getline(linestream, s, ';');
		bool b;
		istringstream(s) >> std::boolalpha >> b;
		Road* road = new Road(id, name, b);
		roads.push_back(road);

	}

	return roads;
}

vector<RoadConnection*> Files::loadConnections(int numNodes) {
	vector<RoadConnection*> connections;

	std::stringstream sstm;
	sstm << EDGEFILE << numNodes << TXTEXT;
	string filename = sstm.str();
	if (numNodes==0)	filename = "edges.txt";
	string line;
	ifstream file(filename.c_str());

	while (getline(file, line)) {
		stringstream linestream(line);
		string s;
		getline(linestream, s, ';');
		long long id = atoll(s.c_str());
		getline(linestream, s, ';');
		long long node1 = atoll(s.c_str());
		getline(linestream, s, ';');
		long long node2 = atoll(s.c_str());
		getline(linestream, s, ';');
		RoadConnection* conn = new RoadConnection(id, node1, node2);
		connections.push_back(conn);

	}

	return connections;
}

vector<Supermarket*> Files::loadSupermarkets() {
	vector<Supermarket*> supermarkets;

	string filename = "supermarkets.txt";
	string line;
	ifstream file(filename.c_str());

	while (getline(file, line)) {
		stringstream linestream(line);
		string s;
		getline(linestream, s, ';');
		int id = atoi(s.c_str());
		getline(linestream, s, ';');
		string name = s;
		getline(linestream, s, ';');
		long long node = atoll(s.c_str());
		Supermarket* supermarket = new Supermarket(id, name, node);
		supermarkets.push_back(supermarket);

	}

	return supermarkets;
}

vector<Client*> Files::loadClients() {
	vector<Client*> clients;

	string filename = "clients.txt";
	string line;
	ifstream file(filename.c_str());

	while (getline(file, line)) {
		stringstream linestream(line);
		string s;
		getline(linestream, s, ';');
		int id = atoi(s.c_str());
		getline(linestream, s, ';');
		string name = s;
		getline(linestream, s, ';');
		long long node = atoll(s.c_str());
		getline(linestream, s, ';');
		string address = s;
		getline(linestream, s, ';');
		int supermarket = atoi(s.c_str());
		Client* client = new Client(id, name, node, address, supermarket);
		clients.push_back(client);

	}


	return clients;
}

vector<Truck*> Files::loadTruck(vector<Client*> clients) {
	vector<Truck*> trucks;

	string filename = "trucks.txt";
	string line;
	ifstream file(filename.c_str());

	while (getline(file, line)) {
		stringstream linestream(line);
		string s;
		getline(linestream, s, ';');
		int id = atoi(s.c_str());
		getline(linestream, s, ';');
		string numRota = s;
		getline(linestream, s, ';');
		long long capacity = atoi(s.c_str());
		getline(linestream, s, ';');
		int supermarket = atoi(s.c_str());
		Truck* truck = new Truck(id, numRota, capacity, supermarket);

		for (unsigned int i = 0; i < clients.size(); i++) {
			if (clients[i]->getMySuper() == supermarket)
				truck->addClient(clients[i]);
		}

		trucks.push_back(truck);

	}

	return trucks;
}
