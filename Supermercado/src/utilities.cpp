/*
 * utilities.cpp
 *
 *  Created on: 27/03/2018
 *      Author: up201607946
 */

#include "utilities.h"
#include <time.h>
#include <sys/timeb.h>
#include <sstream>

using namespace std;

// Something like GetTickCount but portable
// It rolls over every ~ 12.1 days (0x100000/24/60/60)
// Use GetMilliSpan to correct for rollover

int GetMilliCount() {
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int GetMilliSpan(int nTimeStart) {
	int nSpan = GetMilliCount() - nTimeStart;
	if (nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}

string floatToString(float i) {
	stringstream ss;
	ss << i;
	return ss.str();
}

string intToString(int i) {
	stringstream ss;
	ss << i;
	return ss.str();
}

string doubleToString(double i) {
	stringstream ss;
	ss << i;
	return ss.str();
}

bool Visited(unsigned int ordem, vector<Client> clients) {
	for (unsigned int i = 0; i < clients.size(); i++) {
		if (i == ordem) {
			if (clients.at(i).getVisited()) {
				return true;
			} else {
				return false;
			}

		}
	}
	return false;
}

queue<Vertex<Node>*> toAndFrom(Supermarket super, vector<Client> clients) {//eliminar argumentos RECEBE obj!!!!
	//vector<Client> naoVisitados;
	int naoVisitados = clients.size();
	queue<Vertex<Node>*> percurso;
	stack<Vertex<Node>*> regresso;
	Vertex<Node>* actualGo = super.getNode();
	Vertex<Node>* actualCome = super.getNode();
	Vertex<Node>* cliente = super.getNode(); //só para nao dar erro
	Vertex<Node>* cliente2 = super.getNode(); //só para nao dar erro

	//cliente é o mais perto ida ainda nao visitado
	if (naoVisitados) {
		//get mais perto ida desde ponto actualGo
		//ver se nao visitado
		for (int i = 0; i < clients.size(); i++) {
			if (!Visited(i, clients)) {

				//tirar dos nao visitados e actualiza actualGo
				percurso.push(cliente);
				naoVisitados--;
				actualGo = cliente;		//.getNode();
				//e setNotVisited
				for (int i = 0; i < clients.size(); i++) {
					if (clients.at(i).getID() == cliente->getInfo().getID()) {
						clients.at(i).setVisited();
					}
				}
			}
		}
		if (naoVisitados) {
			//get mais perto volta ponto actualCome
			for (int i = 0; i < clients.size(); i++) {
				if (!Visited(i, clients)) {
					regresso.push(cliente2);
					naoVisitados--;
					actualCome = cliente2;
					for (int i = 0; i < clients.size(); i++) {
						if (clients.at(i).getID()
								== cliente2->getInfo().getID()) {
							clients.at(i).setVisited();
						}
					}
				}
			}
		} else {			//nao há por visitar vai unir
			while (!regresso.empty()) {
				percurso.push(regresso.top());
				regresso.pop();
			}
		}

	}
//não há mais clientes
	percurso.push(super.getNode());		//adiciona ponto final (supermercado)
	return percurso;
}

void assignSupers(map* obj) {
	for (unsigned int i = 0; i < obj->vecSupermarket.size(); i++) {

	}
}
