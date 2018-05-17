#ifndef ROAD_H_
#define ROAD_H_

#include <string>
#include "connection.h"

class Road {

public:
	long long id;
	string name;
	bool two_way;

	/**
	 * Road default constructor.
	 */
	Road();

	/**
	 * Road constructor.
	 * @param id
	 * @param name
	 * @param two_way
	 */
	Road(unsigned int id, string name, bool two_way) {
		this->id = id;
		this->name = name;
		this->two_way = two_way;
	}
	;

	/**
	 * Get road's id.
	 * @return Id.
	 */
	long long getId();


	/**
	* Get road's name.
	* @return name.
	*/
	std::string getName();


	/**
	 * Check if road is two way or not.
	 * @return True if road is two way, false otherwise.
	 */
	bool isTwoWay();
};

#endif /* ROAD_H_ */
