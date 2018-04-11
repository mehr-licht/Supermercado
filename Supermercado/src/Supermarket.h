

#ifndef SUPERMARKET_H_
#define SUPERMARKET_H_

#include <string>


class Supermarket {
private:
	int id;
	std::string name;
	long long node;


public:
	/**
	 * Supermarket default constructor.
	 */
	Supermarket();
	/**
	 * Supermarket constructor.
	 * @param id
	 * @param name
	 * @param node
	 */
	Supermarket(int id, std::string name, long long node) {
		this->id = id;
		this->name = name;
		this->node = node;
	}

	/**
	 * Get Supermarket id.
	 * @return Supermarket id.
	 */
	int getId();

	/**
	 * Get Supermarket name.
	 * @return Supermarket name.
	 */
	std::string getName();

	/**
	 * Get Supermarket node.
	 * @return Supermarket node.
	 */
	long long getNode();

	/**
	 * Assign a node to the Supermarket.
	 * @param node
	 */
	void setNode(long long node);


};

#endif /* SUPERMARKET_H_ */
