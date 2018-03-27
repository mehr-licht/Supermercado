#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

void exercicio1();
void exercicio2();
void exercicio3();

void exercicio1()
{
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->setBackground("background.jpg");
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->removeNode(1);
	gv->addNode(2);
	gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);
	gv->setVertexLabel(2, "Este é o terceiro nó");
	gv->setEdgeLabel(1, "Esta é a segunda aresta");
	gv->setVertexColor(2, "green");
	gv->setEdgeColor(1, "yellow");

	gv->rearrange();
}

void exercicio2()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);

	ifstream myfile;
	myfile.open ("nos.txt");
	std::string no;

	while (std::getline(myfile, no)) {
		cout << no;
	}

	myfile.close();
	return;
}

void exercicio3() {
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->defineEdgeCurved(true);

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string line;

	int idNo = 0;
	int X = 0;
	int Y = 0;

	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;

		linestream >> idNo;

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> X;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> Y;
		gv->addNode(idNo, X, -Y);

	}

	inFile.close();

	//Ler o ficheiro arestas.txt
	inFile.open("arestas.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	int idAresta = 0;
	int idNoOrigem = 0;
	int idNoDestino = 0;

	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;

		linestream >> idAresta;

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idNoDestino;
		gv->addEdge(idAresta, idNoOrigem, idNoDestino, EdgeType::UNDIRECTED);

	}

	inFile.close();

	gv->rearrange();
}

/*
int main() {
	//exercicio1();
	//exercicio2();
	//exercicio3();
	getchar();
	return 0;
}
*/
