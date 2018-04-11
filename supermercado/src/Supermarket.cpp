/*
 * Supermarket.cpp
 *
 *  Created on: 26/03/2018
 *      Author: luis
 */


#include "Supermarket.h"

Supermarket::Supermarket() {
}

Supermarket::Supermarket(int id, Vertex<Node> *node, string name) {
	this->id = id;
	this->node = node;
	this->name = name;

}

Supermarket::~Supermarket() {
}

int Supermarket::getID() {
	return this->id;
}

Vertex<Node>* Supermarket::getNode() {
	return this->node;
}

string Supermarket::getName() {
	return this->name;
}




