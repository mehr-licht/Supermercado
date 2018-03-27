/*
 * Client.cpp
 *
 *  Created on: 26/03/2018
 *      Author: luis
 */

#include "Client.h"

Client::Client() {
}

Client::Client(int id, Vertex<Node> *node, string name) {
	this->id = id;
	this->node = node;
	this->name = name;
	this->visited = false;

	}

Client::~Client() {
}

void Client::setNotVisited() {
	this->visited=false;
}

void Client::setVisited() {
	this->visited=true;
}

bool Client::getVisited() {
	return this->visited;
}

int Client::getID() {
	return this->id;
}

Vertex<Node>* Client::getNode() {
	return this->node;
}

string Client::getName() {
	return this->name;
}







