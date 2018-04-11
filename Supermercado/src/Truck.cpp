

#include "Truck.h"
using namespace std;

long long Truck::getId() {
	return this->id;
}

string Truck::getnumRota() {
	return this->numRota;
}

long long Truck::getCapacity() {
	return this->capacity;
}

long long Truck::getSupermarket() {
	return this->supermarket;
}

void Truck::setSupermarket(int super) {
	this->supermarket = super;
}

void Truck::addClient(Client* client) {
	this->clients.push_back(client);
}

void Truck::eraseClients() {
	this->clients.clear();
}

vector<Client*> Truck::getClients() {
	return this->clients;
}

vector<long long> Truck::getStops() {
	vector<long long> stops;
	for (unsigned int i = 0; i < this->getClients().size(); i++) {
		stops.push_back(this->getClients().at(i)->getNode());
	}
	return stops;
}

bool Truck::nodeExistsAsClients(int idNode) {

	for (unsigned int i = 0; i < this->getClients().size(); i++) {
		if (this->getClients()[i]->getNode() == idNode) {
			return true;
		}
	}
	return false;
}

string Truck::getClientsName(int idNode) {
	string outstring = "";
	for (unsigned int i = 0; i < this->getClients().size(); i++) {
		if (this->getClients()[i]->getNode() == idNode) {
			outstring = this->getClients()[i]->getName();
		}
	}
	return outstring;
}
