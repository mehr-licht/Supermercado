//#include "files.h"
//
//using namespace std;
//
//void loadEdges() {
//	string line;
//
//	ifstream file("Edges.txt");
//
//	if (file.is_open()) {
//		while (getline(file, line)) {
//
//			std::stringstream linestream(line);
//			string data;
//
//			int idEdge;
//			int idNoInicio;
//			int idNoFim;
//
//			linestream >> idEdge;
//
//			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//			linestream >> idNoInicio;
//			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//			linestream >> idNoFim;
//
//			Node n;
//			Node nodeInit;
//			Node nodeFinal;
//
//			for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {
//
//				if (idNoInicio
//						== myGraph.getVertexSet().at(i)->getInfo().getID())
//					nodeInit = myGraph.getVertexSet().at(i)->getInfo();
//
//				if (idNoFim
//						== myGraph.getVertexSet().at(i)->getInfo().getID()) {
//					nodeFinal = myGraph.getVertexSet().at(i)->getInfo();
//				}
//			}
//
//			double weight;
//			weight = sqrt(
//					pow(nodeFinal.getX() - nodeInit.getX(), 2)
//							+ pow(nodeFinal.getY() - nodeInit.getY(), 2));
//			myGraph.addEdge(nodeInit, nodeFinal, weight);
//
//		}
//
//		file.close();
//	} else {
//		cerr << "e File not found!\n";
//	}
//	return;
//}
//
//
//void loadClients() {
//	string line;
//	ifstream file("petrolStations.txt");
//
//	if (file.is_open()) {
//		while (getline(file, line)) {
//
//			int id;
//
//			std::stringstream linestream(line);
//
//			linestream >> id;
//
//			for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {
//				if (myGraph.getVertexSet().at(i)->getInfo().getID() == id) {
//					vecPetrolStations.push_back(myGraph.getVertexSet().at(i));
//				}
//			}
//		}
//
//		file.close();
//	} else {
//		cerr << "n File not found!\n";
//	}
//	return;
//}
//
//void loadSupermarket() {
//	string line;
//	ifstream file("Parking.txt");
//
//	if (file.is_open()) {
//		while (getline(file, line)) {
//
//			std::stringstream linestream(line);
//			string data;
//
//			int id;
//			int nodeID;
//			string name;
//			float price;
//			int garagem;
//
//			linestream >> id;
//
//			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//			linestream >> nodeID;
//			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//			linestream >> name;
//			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//			linestream >> price;
//			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//			linestream >> garagem;
//
//			Vertex<Node> *vert = NULL;
//
//			for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {
//				if (nodeID == myGraph.getVertexSet().at(i)->getInfo().getID()) {
//					vert = myGraph.getVertexSet().at(i);
//					break;
//				}
//			}
//
//			Supermarket plot = Supermarket(id, vert, name, price, garagem);
//			vecParking.push_back(plot);
//
//		}
//
//		file.close();
//	} else {
//		cerr << "p File not found!\n";
//	}
//	return;
//}
//
//void loadNodes() {
//	string line;
//
//	ifstream file("Nodes.txt"); //ficheiro com 26 nos
//	//ifstream file("1v200.txt"); //ficheiro com 200 nos
//	//ifstream file("2v600.txt"); //ficheiro com 600 nos
//	//ifstream file("3v1000.txt"); //ficheiro com 1000 nos
//
//	if (file.is_open()) {
//		while (getline(file, line)) {
//
//			std::stringstream linestream(line);
//			string data;
//
//			int id;
//			int x;
//			int y;
//			string name;
//
//			linestream >> id;
//
//			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//			linestream >> x;
//			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//			linestream >> y;
//			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//			linestream >> name;
//
//			Node node = Node(id, x, y, name);
//
//			myGraph.addVertex(node);
//		}
//
//		file.close();
//	} else {
//		cerr << "n File not found!\n";
//	}
//	return;
//}
//
//void loadStreets() {
//	string line;
//	ifstream file("Streets.txt");
//
//	if (file.is_open()) {
//		while (getline(file, line)) {
//
//			int id;
//			string name;
//			int way;
//			int NoID;
//			char token;
//
//			vector<int> idNodes;
//
//			std::stringstream linestream(line);
//			string data;
//
//			linestream >> id >> token;
//			std::getline(linestream, name, ';');
//			linestream >> way >> token;
//
//			do {
//				linestream >> NoID >> token;
//				idNodes.push_back(NoID);
//			} while (token == ',');
//
//			vector<Vertex<Node>*> vrtxs;
//
//			for (unsigned int j = 0; j < idNodes.size(); j++) {
//
//				Vertex < Node > *vertex = NULL;
//
//				for (unsigned int i = 0; i < myGraph.getVertexSet().size();
//						i++) {
//
//					if (idNodes.at(j)
//							== myGraph.getVertexSet().at(i)->getInfo().getID()) {
//						vertex = myGraph.getVertexSet().at(i);
//						break;
//					}
//				}
//
//				vrtxs.push_back(vertex);
//			}
//
//			if (way == 1) { //rua tem dois sentidos
//
//				for (int i = vrtxs.size() - 1; i > 0; i--) {
//
//					Node nodeInit = vrtxs.at(i)->getInfo();
//					Node nodeFinal = vrtxs.at(i - 1)->getInfo();
//
//					double weight = sqrt(
//							pow(nodeFinal.getX() - nodeInit.getX(), 2)
//									+ pow(nodeFinal.getY() - nodeInit.getY(),
//											2));
//
//					vrtxs.at(i)->addEdge(vrtxs.at(i - 1), weight);
//
//				}
//
//			}
//
//			Street st = Street(id, name, vrtxs, way);
//			vecStreets.push_back(st);
//		}
//
//		file.close();
//	} else {
//		cerr << "s File not found!\n";
//	}
//	return;
//}
//
//void loadData() {
//	loadNodes();
//	loadEdges();
//	loadSupermarket();
//	loadStreets();
//	loadClients();
//	return;
//}
//
//void printGraph() {
//
//	gv->createWindow(800, 800);
//
//	gv->defineEdgeCurved(false);
//
//	gv->defineEdgeColor("black");
//	gv->defineVertexIcon("res/emptyIcon.png");
//
//	for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {
//
//		int idNo = myGraph.getVertexSet().at(i)->getInfo().getID();
//		string name = myGraph.getVertexSet().at(i)->getInfo().getName();
//		int x = myGraph.getVertexSet().at(i)->getInfo().getX();
//		int y = myGraph.getVertexSet().at(i)->getInfo().getY();
//
//		gv->addNode(idNo, x * 5 + 50, -(y * 5) + 600);
//
//		if (isSupermarket(idNo)) {
//
//			float price = 0;
//
//			string nodeLabel;
//
//			for (unsigned int j = 0; j < vecParking.size(); j++) {
//				if (vecParking.at(j).getNode()->getInfo().getID() == idNo) {
//					price = vecParking.at(j).getPrice();
//				}
//			}
//
//			nodeLabel = intToString(idNo) + " (" + floatToString(price)
//					+ " €/h)";
//
//			gv->setVertexIcon(idNo, "res/parkIcon.png");
//			gv->setVertexLabel(idNo, nodeLabel);
//			continue;
//		}
//
//		if (isClient(idNo)) {
//			gv->setVertexIcon(idNo, "res/gasIcon.png");
//			continue;
//		}
//
//		if (name == "mall") {
//			gv->setVertexIcon(idNo, "res/cartIcon.png");
//			continue;
//		}
//
//		if (name == "food") {
//			gv->setVertexIcon(idNo, "res/foodIcon.png");
//			continue;
//		}
//
//		if (name == "cinema") {
//			gv->setVertexIcon(idNo, "res/movieIcon.png");
//			continue;
//		}
//
//		if (name == "uni") {
//			gv->setVertexIcon(idNo, "res/upIcon.png");
//			continue;
//		}
//
//	}
//
//	for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {
//
//		int idNoOrigem = myGraph.getVertexSet().at(i)->getInfo().getID();
//
//		vector < Edge<Node> > adj = myGraph.getVertexSet().at(i)->getAdj();
//
//		for (unsigned int j = 0; j < adj.size(); j++) {
//
//			int idNoDestino = adj.at(j).getNode()->getInfo().getID();
//
//			int idAresta = 1000 * idNoOrigem + idNoDestino;
//
//			//string weight = std::to_string(adj.at(j).getWeight());
//			string weight = doubleToString(adj.at(j).getWeight());
//
//			if (weight.find(".") != string::npos) {
//				for (size_t i = weight.find(".") + 2; i < weight.size(); i++)
//					weight.erase(i);
//			}
//
//			gv->addEdge(idAresta, idNoOrigem, idNoDestino, EdgeType::DIRECTED);
//			gv->setEdgeLabel(idAresta, weight);
//		}
//
//	}
//
//	gv->rearrange();
//}
//
//void paintPath(vector<Node> path) {
//
//	for (size_t i = 0; i < path.size() - 1; i++) {
//		int id = path.at(i).getID() * 1000 + path.at(i + 1).getID();
//
//		gv->setEdgeThickness(id, 4);
//		gv->setEdgeColor(id, "BLUE");
//	}
//
//	gv->setVertexIcon(path.at(0).getID(), "res/personIcon.png");
//	gv->rearrange();
//}
//
//
//Node getNodeByID(int id) {
//
//	Node node;
//
//	for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {
//		if (myGraph.getVertexSet().at(i)->getInfo().getID() == id) {
//			node = myGraph.getVertexSet().at(i)->getInfo();
//		}
//	}
//
//	return node;
//
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
///*
////------------------------------------------------
//	int nTimeStart = GetMilliCount();
////------------------------------------------------
//
//	vector<Node> path = calculatePath(source, dest, maxDistance, Cheap_Near,
//			passPetrolStation);
//
//	if (path.size() != 0) { //se ha de facto um path
//		cout << "> PATH: ";
//		for (unsigned int i = 0; i < path.size(); i++) {
//			cout << path.at(i).getID() << " ";
//		}
//	}
//
//	//time--------------------------------------------
//	int nTimeElapsed = GetMilliSpan(nTimeStart);
//	cout << endl << endl;
//	cout << "> EXECUTION TIME (ms): " << nTimeElapsed << endl;
//	//------------------------------------------------
//
//	//connection--------------------------------------
//	cout << "> IS GRAPH STRONGLY CONNECTED: ";
//	if (myGraph.isStronglyConnected())
//		cout << "yes" << endl;
//	else
//		cout << "no" << endl;
//	//------------------------------------------------
//
//	return path;
//	//TODO: falta fazer o falhanco da coisa
//}
//
////retorna vetor vazio se nao encontroou nenhum path
//vector<Node> calculatePath(int sourceID, int destID, int maxDistance,
//		int Cheap_Near, char passPetrolStation) {
//
////ENCONTRAR PARQUES//
//	Node park;
//
//	if (Cheap_Near == 1) { //se user escolheu encontrar o parque mais barato
//		park = parkCheap(destID, maxDistance);
//	} else { //se user escolheu o user mais perto do destino
//		park = parkNear(destID, maxDistance);
//	}
//
//	if (park.getID() == -1) { //se nao foi encontardo nenhum parque
//		cout << "THERE'S NO PARK WITHIN THAT DISTANCE!" << endl;
//		vector<Node> nullVector;
//		return nullVector;
//	}
//
//	cout << "> PARK: " << park.getID() << endl;
//
////ELABORAR O PATH//
//
//	vector<Node> part1; //path da source ao parque
//	vector<Node> part2; //path do parque a dest
//	vector<Node> vec; //path da source a dest, passando pelo parque
//
//	if (park.getID() == sourceID && park.getID() == destID) { //se a source, o dest e o parque sao o mesmo ponto
//
////vec teria apenas dois elementos, que serï¿½o iguais, mas um representa a origem e outro o destino
//		vec.push_back(getNodeByID(sourceID));
//		vec.push_back(getNodeByID(destID));
//
//		if (passPetrolStation == 'y') { //se o user escolheu abastecer
//			addPetrolToPath(vec);
//		}
//
//	} else if (park.getID() == sourceID || park.getID() == destID) { //se a source ou o destino sï¿½o o parque
//
////vec teria o caminho mais perto de source a dest
//		vec = myGraph.getPath(getNodeByID(sourceID), getNodeByID(destID));
//
//		if (passPetrolStation == 'y') { //se o user escolheu abastecer
//			addPetrolToPath(vec);
//		}
//
//	} else {
//
//		part1 = myGraph.getPath(getNodeByID(sourceID),
//				getNodeByID(park.getID())); // caminho mais curto da source ao parque
//		part2 = myGraph.getPath(getNodeByID(park.getID()), getNodeByID(destID)); //caminho mais cuto do parque ao dest
//
//		if (passPetrolStation == 'y') { //se o user escolheu abastecer
//			addPetrolToPath(part1); //adiciona bomba de gasolina ao path source-park visto que o user ja nao terï¿½ o carro em park-dest
//		}
//
//		part2.erase(part2.begin()); //apaga o primeiro elemento de part2 porque ï¿½ igual ao ultimo elemento da part1, ou seja, o parque
//
//		part1.insert(part1.end(), part2.begin(), part2.end()); //concatena as duas partes
//		vec = part1;
//	}
//
//	return vec;
//
//}
//
//*/
