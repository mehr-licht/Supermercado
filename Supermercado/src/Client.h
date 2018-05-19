
#ifndef CLIENT_H_
#define CLIENT_H_
#include <limits>
#include <string>
#include "Node.h"
#include "iostream"
#include "Supermarket.h"

const int INT_INF = std::numeric_limits<int>::max();

class Client {
	int id;
	std::string name;
	long long node;
	std::string address;
	int mySuper;
	int distMySuper;

public:
	/**
	 * Client default constructor.
	 */
	Client();

	/**
	 * Client constructor
	 * @param id
	 * @param n
	 * @param h
	 * @param s
	 */
	Client(int id, std::string name, long long node, std::string address,
			long long mySuper);
	/**
	 * Get Client's name.
	 * @return Client's name.
	 */
	std::string getName();
	/**
	 * Get Client's node id.
	 * @return Client's node id.
	 */
	long long getNode();
	/**
	 * Get Client's address.
	 * @return Client address.
	 */
	std::string getAddress();

	/**
	 * Get Client id.
	 * @return Client id.
	 */
	int getId();

	/**
	 * prints a client in a friendly way
	 */
	void print();

	/**
	 * get client's assigned supermarket
	 * @return Client assigned supermarket
	 */
	int getMySuper();

	/**
	 * set client's assigned supermarket
	 *
	 */
	void setMySuper(int super);

	/**
	 * get client's distance to his assigned supermarket
	 * @return distance to Client assigned supermarket
	 */
	double getDistMySuper();

	/**
	 *  set client's distance to his assigned supermarket
	 *
	 */
	void setDistMySuper(double dist);

};

#endif /* CLIENT_H_ */
