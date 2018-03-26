/*
 * Supermarket.h
 *
 *  Created on: 26/03/2018
 *      Author: luis
 */

#ifndef SRC_SUPERMARKET_H_
#define SRC_SUPERMARKET_H_
#include <iostream>
#include <string>
#include "Node.h"
#include "Graph.h"

using namespace std;

class Supermarket {
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
	Supermarket();

	/**
	 * Destrutor default.
	 */
	~Supermarket();

	/**
	 * Construtor de Supermarket
	 * @param id int que represente o id do parque de estacionamento.
	 * @param node aponador para o vertex a que esse parque de estacionamento está associado.
	 * @param name string do nome do parque de estacionamento.
	 * @param price float do preço do parque de estacionamento.
	 * @param isGarage int que representa se o parque é garagem ou parque de rua. Se 0 é parque de rua, se o 1 é garagem.
	 */
	Supermarket(int id, Vertex<Node> *node, string name, float price,
			int isGarage);

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




#endif /* SRC_SUPERMARKET_H_ */
