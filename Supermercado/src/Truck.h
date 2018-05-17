#ifndef TRUCK_H_
#define TRUCK_H_

#include <string>
#include <vector>
#include "Client.h"
#include <iostream>

class Truck {
	long long id;
	std::string numRota;
	long long capacity;
	long long supermarket;
	std::vector<Client*> clients;

public:
	/**
	 * Truck default constructor.
	 */
	Truck();

	/**
	 * Truck constructor.
	 * @param id
	 * @param numRota
	 * @param max_capacity
	 * @param supermarket
	 */
	Truck(long long id, std::string numRota, long long max_capacity,
			long long supermarket) {
		this->id = id;
		this->numRota = numRota;
		this->capacity = max_capacity;
		this->supermarket = supermarket;
	}

	/**
	 * Get Truck id.
	 * @return Id of the Truck.
	 */
	long long getId();

	/**
	 * Get Truck numRota.
	 * @return numRota of the Truck.
	 */
	std::string getnumRota();

	/**
	 * Get Truck capacity.
	 * @return Capacity of the Truck.
	 */
	long long getCapacity();
	/**
	 * Get Truck supermarket.
	 * @return supermarket of the Truck.
	 */
	long long getSupermarket();

	/**
	 * Set Truck supermarket.
	 *
	 */
	void setSupermarket(int super);

	/**
	 * Add client to truck.
	 * @param client
	 */
	void addClient(Client* client);

	/**
	 * erase clients assigned to truck
	 */
	void eraseClients();

	/**
	 * Get truck clients.
	 * @return 	Clients associated with trucks.
	 */
	std::vector<Client*> getClients();

	/**
	 * Get stops.
	 * @return Nodes corresponding to clients' nodes.
	 */
	std::vector<long long> getStops();

	/**
	 * Checks if nodes in truck route are clients.
	 *  @param Node id
	 * @return True if node in truck route is client, false otherwise.
	 */
	bool nodeExistsAsClients(int idNode);

	/**
	 * Get clients name in truck route node.
	 *  @param Node id
	 * @return clients name in truck route node.
	 */
	std::string getClientsName(int idNode);

	/**
	 * adds client to stops of the truck
	 * @param client to add
	 */
	void addNewStop(Client * newC);
};

#endif /* TRUCK_H_ */
