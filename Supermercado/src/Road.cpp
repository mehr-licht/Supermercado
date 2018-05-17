
#include "Road.h"

long long Road::getId(){
	return this->id;
}


std::string Road::getName(){
	return this->name;
}

bool Road::isTwoWay() {
	return this->two_way;
}

