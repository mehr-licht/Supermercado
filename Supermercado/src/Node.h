

#ifndef NODE_H_
#define NODE_H_

#define WIDTH 1000
#define HEIGHT 400
#define LATMIN 41.14026
#define LATMAX 41.1536
#define LONMIN -8.620372
#define LONMAX -8.598513

#include <string>
#include <math.h>


class Node {
private:
	long long id;
	double lat;
	double lon;
	double latRad;
	double lonRad;
	double x;
	double y;
	double scaleLon();
	double scaleLat();

public:
	/**
	 * Node default constructor.
	 */
	Node();

	/**
	 * Node constructor.
	 * @param id
	 * @param lat
	 * @param lon
	 * @param latRad
	 * @param lonRad
	 */
	Node (long long id, double lat, double lon, double latRad, double lonRad);
	/**
	 * Get node's id.
	 * @return Node's id.
	 */
	long long getId() const;
	/**
	 * Get node's latitude in degrees.
	 * @return Latitude in degrees.
	 */
	double getLat() const;
	/**
	 * Get node's longitude in degrees.
	 * @return Longitude in degrees.
	 */
	double getLon() const;
	/**
	 * Get node's latitude in radians.
	 * @return Latitude in radians.
	 */
	double getLatRad() const;
	/**
	 * Get node's longitude in radians.
	 * @return Longitude in radians.
	 */
	double getLonRad() const;
	/**
	 * Get node's x position.
	 * @return X (horizontal) position.
	 */
	double getX() const;
	/**
	 * Get node's y position.
	 * @return Y (vertical) position.
	 */
	double getY() const;

};



#endif /* NODE_H_ */
