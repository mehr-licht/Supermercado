
#include "Node.h"

Node::Node() {
	this->id = 0;
}

Node::Node (long long id, double lat, double lon, double latRad, double lonRad) {
	this->id = id;
	this->lat = lat;
	this->lon = lon;
	this->latRad = latRad;
	this->lonRad = lonRad;
	this->x = scaleLon();
	this->y = scaleLat();
};

double Node::scaleLon() {
	double lonmin = -8.620372;
	double lonmax = -8.598513;
	double dif = (lonmax - lonmin);
	return floor(((this->lon - lonmin) * WIDTH) / dif) + 500;
}

double Node::scaleLat() {
	double latmin = 41.14026;
	double latmax = 41.1536;

	double dif = (latmax - latmin);
	return floor(498 - ((this->lat - latmin) * HEIGHT) / dif) + 500;
}

long long Node::getId()  const{
	return id;
}

double Node::getLat() const {
	return lat;
}

double Node::getLon() const {
	return lon;
}

double Node::getLatRad() const {
	return latRad;
}

double Node::getLonRad()  const{
	return lonRad;
}

double Node::getX()  const{
	return x;
}

double Node::getY()  const{
	return y;
}


