#include "Client.h"

Client::Client() {
	this->id = 0;
}


Client::Client(int id, std::string name, long long node, std::string address,
		long long mySuper=0) {
	this->id = id;
	this->name = name;
	this->node = node;
	this->address = address;

	this->mySuper =mySuper;
	this->distMySuper = INT_INF;
}
;

std::string Client::getName() {
	return this->name;
}

long long  Client::getNode() {
	return this->node;
}


int Client::getId() {
	return this->id;
}

std::string Client::getAddress() {
	return this->address;
}


void Client::print() {
	std::cout << "id=" << id << "\tname=" << name << "\tnode=" << node
			<< "\taddress=" << address << "\tmysuper" << mySuper
			<< "\tdistsuper=" << distMySuper << std::endl;
}

int Client::getMySuper() {
	return this->mySuper;
}
void Client::setMySuper(int super) {
	this->mySuper = super;
}

double Client::getDistMySuper() {
	return this->distMySuper;
}
void Client::setDistMySuper(double dist) {
	this->distMySuper = dist;
}
