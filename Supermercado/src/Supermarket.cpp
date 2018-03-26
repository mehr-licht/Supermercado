/*
 * Supermarket.cpp
 *
 *  Created on: 26/03/2018
 *      Author: luis
 */


#include "Supermarket.h"

Supermarket::Supermarket() {
}

Supermarket::Supermarket(int id, Vertex<Node> *node, string name, float price,
		int isGarage) {
	this->id = id;
	this->node = node;
	this->name = name;
	this->price = price;

	if (isGarage)
		this->isGarage = true;
	else
		this->isGarage = false;
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

float Supermarket::getPrice() {
	return this->price;
}

bool Supermarket::getIsGarage() {
	return this->isGarage;
}

