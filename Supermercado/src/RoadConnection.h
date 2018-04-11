
#ifndef ROADCONNECTION_H_
#define ROADCONNECTION_H_


#include <string>
#include "connection.h"


class RoadConnection {
	long long  roadId;
	long long  node1;
	long long  node2;

public:
	/**
	 * RoadConnection default constructor.
	 */
	RoadConnection();
	/**
	 * RoadConnection constructor.
	 * @param road
	 * @param node1
	 * @param node2
	 */
	RoadConnection(long long road, long long node1, long long node2) {
		this->roadId=road;
		this->node1=node1;
		this->node2=node2;
	};

	/**
	 * Get id of connection's road.
	 * @return Road's id.
	 */
	long long getRoadId();
	/**
	 * Get node source.
	 * @return Node source.
	 */
	long long getNode1();
	/**
	 * Get node destination.
	 * @return Node destination.
	 */
	long long getNode2();
};


#endif /* _ROADCONNECTION_H_ */
