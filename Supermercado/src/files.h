///*
// * files.h
// *
// *  Created on: 26/03/2018
// *      Author: luis
// */
//
//#ifndef SRC_FILES_H_
//#define SRC_FILES_H_
//
//#include <string>
//#include <sstream>
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include "utilities.h"
//#include <cstdio>
//#include "Graph.h"
//#include "Node.h"
//#include "Street.h"
//#include "Supermarket.h"
//#include "Client.h"
//#include "graphviewer.h"
//#include <cmath>
//
//
//
//
//
//#include <iostream>
//#include <string>
//#include <vector>
//#include <fstream>
//#include <sstream>
//#include <cstdio>
//#include "Graph.h"
//#include "Node.h"
//#include "Client.h"
//#include "Street.h"
//#include "graphviewer.h"
//#include "utilities.h"
//
//class Files {
//
//private:
//	static Files* singleton_instance;
//
//	Graph<Node> myGraph;
//	vector<Node> vecNodes;
//	vector<Client> vecParking;
//	vector<Street> vecStreets;
//	vector<Vertex<Node>*> vecPetrolStations;
//
//	GraphViewer *gv;
//
//public:
//	/**
//	 * Construtor default.
//	 */
//	Files();
//
//	/**
//	 * Destrutor default.
//	 */
//	~Files();
//
//	static Files* instance() {
//		if (!singleton_instance)
//			singleton_instance = new Files;
//
//		return singleton_instance;
//	}
//
//	/**
//	 * Funcao que carrega os dados do ficheiro de arestas para as estruturas em Graph.h.
//	 */
//	void loadEdges();
//
//	/**
//	 * Funcao que carrega os dados do ficheiro de nodes, criando objetos da classe Node e adicionando também ao respetivo vertex em myGraph.
//	 */
//	void loadNodes();
//
//	/**
//	 * Funcao que carrega os dados do ficheiro de parques de estacionamento, criando objetos da classe ParkingLot.
//	 */
//	void loadParkingLot();
//
//	/**
//	 * Funcao que carrega os dados do ficheiro de ruas, criando objetos da classe Street.
//	 * Caso as ruas tenham dois sentidos, são adicionadas arestas ao myGraph com sentido contrário ao que está no vetor de Vertexs da rua.
//	 */
//	void loadStreets();
//
//	/**
//	 * Funcao que carrega os dados do ficheiro de bombas de gasolina.
//	 */
//	void loadClients();
//
//	/**
//	 * Funcao que chama todas as funçoes de load.
//	 */
//	void loadData();
//
//	/**
//	 * Funcao que mostra o grafo gv, com todas as arestas e nos em myGraph.
//	 */
//	void printGraph();
//
//	/**
//	 * Funcao que destaca as arestas que ligam os nos passados por argumento no grafo gv.
//	 * @param id Vetor de ids de nos presentes no caminho que é suposto destacar no grafo gv.
//	 */
//	void paintPath(vector<Node> id);
//
//	/**
//	 * Funcao que procura o node de id passado por argumento.
//	 * @param id int do id a procurar.
//	 * @return Node pretendido.
//	 */
//	Node getNodeByID(int id);
//
//	/**
//	 * Funcao que diz se o Node com id passado por argumento é supermercado.
//	 * @param idNo int do id do Node.
//	 * @return true se o Node é um supermercado, false se não é.
//	 */
//	bool isClient(int idNo);
//
//	/**
//	 * Funcao que diz se o Node com id passado por argumento é bomba de gasolina.
//	 * @param idNo int do id do Node.
//	 * @return true se o Node é um supermercado, false se não é.
//	 */
//	bool isSupermarket(int idNo);
//
//	/**
//	 * Funcao que diz qual o supermercado mais proximo do Node com id passado por argumento dentro de uma determinada distância passada também por argumento.
//	 * @param id int do id do Node
//	 * @param maxDistance distancia máxima pretendida.
//	 * @return Se existir um supermercado retorna o Node associado, senão retorna um Node com id -1.
//	 */
//	Node superNear(int id, int maxDistance);
//
//	/**
//	 * Função que diz qual o supermercado mais barato do Node com id passado por argumento dentro de uma determinada distância passada também por argumento.
//	 * @param id int do id do Node
//	 * @param maxDistance distancia máxima pretendida.
//	 * @return Se existir um supermercado retorna o Node associado, senão retorna um Node com id -1.
//	 */
//	Node parkCheap(int id, int maxDistance);
//
//	/**
//	 * Funcao que diz qual a bomba de gasolina mais proximo do Node com id passado por argumento.
//	 * @param id int do id do Node.
//	 * @return Node associado à bomba de gasolina mais proxima.
//	 */
//	Node clientNear(int id);
//
//
//	/**
//	 * Funcao mostra e retorna o vetor de ids dos nodes de um certo local
//	 * @return Vetor de IDs dos nodes
//	 */
//	vector<int> getStreets(bool source);
//
//
//	/**
//	 * Funcao que calcula o path final pretendido.
//	 * @param sourceID int do id do node onde o user está.
//	 * @param destID int do id do no node onde o user quer ir.
//	 * @param maxDistance int da distância maxima à qual o user quer o supermercado do destino.
//	 * @param Cheap_Near char que diz se o user quer o parque mais próximo ('n') ou o parque mais barato('c').
//	 * @param passPetrolStation char que diz se o user quer abastecer ('y') ou não ('n').
//	 * @return Vetor de Nodes do path final pretendido.
//	 */
//	vector<Node> calculatePath(int sourceID, int destID, int maxDistance,
//			int Cheap_Near, char passPetrolStation);
//
//	/**
//	 * Funcao que adiciona uma cliente ao path passado por argumento.
//	 * @param path vetor de nodes do caminho mais curto entre a origem e o supermercado.
//	 */
//	void addClientToPath(vector<Node> &path);
//
//
//
//
//};
//
//
//
//
//#endif /* SRC_FILES_H_ */