/*
 * Node.cpp
 *
 *  Created on: 26/03/2018
 *      Author: luis
 */




#include "Node.h"

Node::Node() {
	this->id = 0;
}

Node::Node(int id, int x, int y, std::string name) {
	this->id = id;
	this->coords.first = x;
	this->coords.second = y;
	this->name = name;
}

Node::~Node() {
}

void Node::setID(int id) {
	this->id = id;
}

int Node::getID() const {
	return this->id;
}

int Node::getX() const {
	return this->coords.first;
}

int Node::getY() const {
	return this->coords.second;
}

std::string Node::getName() const {
	return this->name;
}

bool Node::operator ==(const Node &n2) const {
	return (id == n2.id);
}
