/*
 * Client.h
 *
 *  Created on: 26/03/2018
 *      Author: luis
 */

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_


#include <iostream>
#include <string>
#include "Node.h"
#include "Graph.h"

//using namespace std;

class Client {
private:

	int id;
	Vertex<Node> *node;
	string name;
	float price;
	bool isGarage;

public:
	/**
	 * Construtor default.
	 */
	Client();

	/**
	 * Destrutor default.
	 */
	~Client();

	/**
	 * Construtor de Client
	 * @param id int que represente o id do parque de estacionamento.
	 * @param node aponador para o vertex a que esse parque de estacionamento está associado.
	 * @param name string do nome do parque de estacionamento.
	 *
	 *
	 */
	Client(int id, Vertex<Node> *node, string name);

	/**
	 * Função que retorna o ID do parking lot.
	 * @return ID do parking lot (int).
	 */
	int getID();

	/**
	 * Função que retorna o apontador para para o vertex a que esse parque de estacionamento está associado.
	 * @return Vertex a que esse parque de estacionamento está associado.
	 */
	Vertex<Node> *getNode();

	/**
	 * Função que retorna o nome do parkingLot.
	 * @return nome do parking lot (string).
	 */
	string getName();

	/**
	 * Função que retorna o preço do parkingLot.
	 * @return preço do parking lot (float).
	 */
	float getPrice();

	/**
	 * Função que nos diz se o parque de estcionamento é garagem ou parque de rua.
	 * @return true se é garagem, false se é parque de rua.
	 */
	bool getIsGarage();
};






#endif /* SRC_CLIENT_H_ */
