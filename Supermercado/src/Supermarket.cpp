#include "Supermarket.h"

int Supermarket::getId() {
	return this->id;
}

std::string Supermarket::getName() {
	return this->name;
}

long long Supermarket::getNode() {
	return this->node;
}

void Supermarket::setNode(long long node) {
	this->node = node;
}

