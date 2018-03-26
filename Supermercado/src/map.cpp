/*
 * map.cpp
 *
 *  Created on: 26/03/2018
 *      Author: luis
 */

#include "map.h"

map::map() {
	gv = new GraphViewer(600, 600, false);
}

map::~map() {
}

void map::loadEdges() {
	string line;

	ifstream file("Edges.txt"); //ficheiro com 46 arestas
	//ifstream file("1a100.txt"); //ficheiro com 100 arestas
	//ifstream file("2a300.txt"); //ficheiro com 200 arestas
	//ifstream file("3a500.txt"); //ficheiro com 500 arestas

	if (file.is_open()) {
		while (getline(file, line)) {

			std::stringstream linestream(line);
			string data;

			int idEdge;
			int idNoInicio;
			int idNoFim;

			linestream >> idEdge;

			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
			linestream >> idNoInicio;
			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
			linestream >> idNoFim;

			Node n;
			Node nodeInit;
			Node nodeFinal;

			for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {

				if (idNoInicio
						== myGraph.getVertexSet().at(i)->getInfo().getID())
					nodeInit = myGraph.getVertexSet().at(i)->getInfo();

				if (idNoFim
						== myGraph.getVertexSet().at(i)->getInfo().getID()) {
					nodeFinal = myGraph.getVertexSet().at(i)->getInfo();
				}
			}

			double weight;
			weight = sqrt(
					pow(nodeFinal.getX() - nodeInit.getX(), 2)
							+ pow(nodeFinal.getY() - nodeInit.getY(), 2));
			myGraph.addEdge(nodeInit, nodeFinal, weight);

		}

		file.close();
	} else {
		cerr << "e File not found!\n";
	}
	return;
}

void map::loadNodes() {
	string line;

	ifstream file("Nodes.txt"); //ficheiro com 26 nos
	//ifstream file("1v200.txt"); //ficheiro com 200 nos
	//ifstream file("2v600.txt"); //ficheiro com 600 nos
	//ifstream file("3v1000.txt"); //ficheiro com 1000 nos

	if (file.is_open()) {
		while (getline(file, line)) {

			std::stringstream linestream(line);
			string data;

			int id;
			int x;
			int y;
			string name;

			linestream >> id;

			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
			linestream >> x;
			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
			linestream >> y;
			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
			linestream >> name;

			Node node = Node(id, x, y, name);

			myGraph.addVertex(node);
		}

		file.close();
	} else {
		cerr << "n File not found!\n";
	}
	return;
}

void map::loadSupermarket() {
	string line;
	ifstream file("Parking.txt");

	if (file.is_open()) {
		while (getline(file, line)) {

			std::stringstream linestream(line);
			string data;

			int id;
			int nodeID;
			string name;
			float price;
			int garagem;

			linestream >> id;

			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
			linestream >> nodeID;
			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
			linestream >> name;
			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
			linestream >> price;
			std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
			linestream >> garagem;

			Vertex<Node> *vert = NULL;

			for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {
				if (nodeID == myGraph.getVertexSet().at(i)->getInfo().getID()) {
					vert = myGraph.getVertexSet().at(i);
					break;
				}
			}

			Supermarket plot = Supermarket(id, vert, name, price, garagem);
			vecParking.push_back(plot);

		}

		file.close();
	} else {
		cerr << "p File not found!\n";
	}
	return;
}

void map::loadStreets() {
	string line;
	ifstream file("Streets.txt");

	if (file.is_open()) {
		while (getline(file, line)) {

			int id;
			string name;
			int way;
			int NoID;
			char token;

			vector<int> idNodes;

			std::stringstream linestream(line);
			string data;

			linestream >> id >> token;
			std::getline(linestream, name, ';');
			linestream >> way >> token;

			do {
				linestream >> NoID >> token;
				idNodes.push_back(NoID);
			} while (token == ',');

			vector<Vertex<Node>*> vrtxs;

			for (unsigned int j = 0; j < idNodes.size(); j++) {

				Vertex<Node> *vertex = NULL;

				for (unsigned int i = 0; i < myGraph.getVertexSet().size();
						i++) {

					if (idNodes.at(j)
							== myGraph.getVertexSet().at(i)->getInfo().getID()) {
						vertex = myGraph.getVertexSet().at(i);
						break;
					}
				}

				vrtxs.push_back(vertex);
			}

			if (way == 1) { //rua tem dois sentidos

				for (int i = vrtxs.size() - 1; i > 0; i--) {

					Node nodeInit = vrtxs.at(i)->getInfo();
					Node nodeFinal = vrtxs.at(i - 1)->getInfo();

					double weight = sqrt(
							pow(nodeFinal.getX() - nodeInit.getX(), 2)
									+ pow(nodeFinal.getY() - nodeInit.getY(),
											2));

					vrtxs.at(i)->addEdge(vrtxs.at(i - 1), weight);

				}

			}

			Street st = Street(id, name, vrtxs, way);
			vecStreets.push_back(st);
		}

		file.close();
	} else {
		cerr << "s File not found!\n";
	}
	return;
}

void map::loadClients() {
	string line;
	ifstream file("petrolStations.txt");

	if (file.is_open()) {
		while (getline(file, line)) {

			int id;

			std::stringstream linestream(line);

			linestream >> id;

			for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {
				if (myGraph.getVertexSet().at(i)->getInfo().getID() == id) {
					vecClients.push_back(myGraph.getVertexSet().at(i));
				}
			}
		}

		file.close();
	} else {
		cerr << "n File not found!\n";
	}
	return;
}

void map::loadData() {
	loadNodes();
	loadEdges();
	loadSupermarket();
	loadStreets();
	loadClients();
	return;
}

void map::printGraph() {

	gv->createWindow(800, 800);

	gv->defineEdgeCurved(false);

	gv->defineEdgeColor("black");
	gv->defineVertexIcon("res/emptyIcon.png");

	for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {

		int idNo = myGraph.getVertexSet().at(i)->getInfo().getID();
		string name = myGraph.getVertexSet().at(i)->getInfo().getName();
		int x = myGraph.getVertexSet().at(i)->getInfo().getX();
		int y = myGraph.getVertexSet().at(i)->getInfo().getY();

		gv->addNode(idNo, x * 5 + 50, -(y * 5) + 600);

		if (isSupermarket(idNo)) {

			float price = 0;

			string nodeLabel;

			for (unsigned int j = 0; j < vecParking.size(); j++) {
				if (vecParking.at(j).getNode()->getInfo().getID() == idNo) {
					price = vecParking.at(j).getPrice();
				}
			}

			nodeLabel = intToString(idNo) + " (" + floatToString(price)
					+ " €/h)";

			gv->setVertexIcon(idNo, "res/supermarketIcon.png");
			gv->setVertexLabel(idNo, nodeLabel);
			continue;
		}

		if (isClient(idNo)) {
			gv->setVertexIcon(idNo, "res/gasIcon.png");
			continue;
		}

		if (name == "mall") {
			gv->setVertexIcon(idNo, "res/cartIcon.png");
			continue;
		}

		if (name == "food") {
			gv->setVertexIcon(idNo, "res/foodIcon.png");
			continue;
		}

		if (name == "cinema") {
			gv->setVertexIcon(idNo, "res/movieIcon.png");
			continue;
		}

		if (name == "uni") {
			gv->setVertexIcon(idNo, "res/upIcon.png");
			continue;
		}

	}

	for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {

		int idNoOrigem = myGraph.getVertexSet().at(i)->getInfo().getID();

		vector<Edge<Node> > adj = myGraph.getVertexSet().at(i)->getAdj();

		for (unsigned int j = 0; j < adj.size(); j++) {

			int idNoDestino = adj.at(j).getNode()->getInfo().getID();

			int idAresta = 1000 * idNoOrigem + idNoDestino;

			//string weight = std::to_string(adj.at(j).getWeight());
			string weight = doubleToString(adj.at(j).getWeight());

			if(weight.find(".") != string::npos){
				for (size_t i = weight.find(".") + 2; i < weight.size(); i++)
					weight.erase(i);
			}

			gv->addEdge(idAresta, idNoOrigem, idNoDestino, EdgeType::DIRECTED);
			gv->setEdgeLabel(idAresta, weight);
		}

	}

	gv->rearrange();
}

void map::paintPath(vector<Node> path) {

	for (size_t i = 0; i < path.size() - 1; i++) {
		int id = path.at(i).getID() * 1000 + path.at(i + 1).getID();

		gv->setEdgeThickness(id, 4);
		gv->setEdgeColor(id, "BLUE");
	}

	gv->setVertexIcon(path.at(0).getID(), "res/personIcon.png");
	gv->rearrange();
}

Node map::getNodeByID(int id) {

	Node node;

	for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {
		if (myGraph.getVertexSet().at(i)->getInfo().getID() == id) {
			node = myGraph.getVertexSet().at(i)->getInfo();
		}
	}

	return node;

}

bool map::isSupermarket(int idNo) {
	for (unsigned int i = 0; i < vecParking.size(); i++) {
		if (vecParking.at(i).getNode()->getInfo().getID() == idNo)
			return true;
	}

	return false;
}

bool map::isClient(int idNo) {
	for (unsigned int i = 0; i < vecClients.size(); i++) {
		if (vecClients.at(i)->getInfo().getID() == idNo)
			return true;
	}
	return false;
}

//retorna node com id -1, se nao nenhum parque dentro dos limites impostos pelo user
Node map::superNear(int id, int maxDistance) {

	int distMinima = INT_MAX;
	int pos = -1;
	Node node = getNodeByID(id);

	myGraph.dijkstraShortestPath(node);

	for (unsigned int i = 0; i < vecParking.size(); i++) {

		int distAtual = vecParking.at(i).getNode()->getDist(); //distancia do parque analisado ao node

		if (distAtual <= maxDistance) { //se distancia do parque analisado esta dentro dos limites impostos pelo user
			if (distAtual < distMinima) { //se a distancia for menor que a guardada
				pos = i; //atualiza a posiï¿½ao
				distMinima = distAtual; //atualiza distancia guardada
			}
		}
	}

	if (pos == -1) { //se nenhum parque foi encontrado
		Node nullNode;
		nullNode.setID(-1);
		return nullNode;
	} else
		return vecParking.at(pos).getNode()->getInfo();
}

Node map::clientNear(int id) {

	Node node = getNodeByID(id);
	int distMinima = INT_MAX;
	int pos = -1;

	for (unsigned int i = 0; i < vecClients.size(); i++) {

		myGraph.dijkstraShortestPath(vecClients.at(i)->getInfo()); //faz dijkstra para a bomba analisada

		int distAtual = myGraph.getVertex(node)->getDist(); //distancia da bomba analisada ate ao node

		if (distAtual <= distMinima) { //se distancia atual menor que a distancia guardada
			pos = i; //atualiza posicao
			distMinima = distAtual; //atualiza distancia guardada
		}

	}

	return vecClients.at(pos)->getInfo();

}

string map::mainMenu(bool source) {
	int option;
	string input;

	if (source)
		cout << "> WHERE ARE YOU ?\n";
	else
		cout << "> WHERE DO YOU WANT TO GO ?\n";

	cout << "[1]Mall           [4]Restaurant\n"
			<< "[2]Cinema         [5]University\n"
			<< "[3]Gas Station    [6]Parking Lot\n" << "[0]Other\n\n";

	cout << "> Option: ";
	cin >> option;
	cout << endl;

	if (option >= 0 && option <= 6) {

		switch (option) {
		case 0:
			input = "null";
			break;
		case 1:
			input = "mall";
			break;
		case 2:
			input = "cinema";
			break;
		case 3:
			input = "gas";
			break;
		case 4:
			input = "food";
			break;
		case 5:
			input = "uni";
			break;
		case 6:
			input = "supermarket";
			break;
		default:
			break;
		}
	}

	return input;
}

vector<int> map::getStreets(bool source) {
	vector<int> streets;
	string input = mainMenu(source);

	if (!input.empty()) {

		cout << " ID      Street\n-----------------\n";

		for (size_t i = 0; i < vecStreets.size(); i++) {
			for (size_t j = 0; j < vecStreets.at(i).getVertexs().size(); j++) {
				int id = vecStreets.at(i).getVertexs().at(j)->getInfo().getID();
				string name = vecStreets.at(i).getName();
				string local =
						vecStreets.at(i).getVertexs().at(j)->getInfo().getName();

				if (input == local) {
					cout << id << "  :  " << name << endl;
					streets.push_back(id);
				}
			}
		}
		cout << endl;
	}

	return streets;
}

bool map::verifyChoice(const vector<int> st, int id) {
	for (size_t i = 0; i < st.size(); i++) {
		if (id == st.at(i))
			return true;
	}
	return false;
}

vector<Node> map::insertValues() {

	int source, dest, Cheap_Near;
	float maxDistance;
	char passClient;
	vector<int> options;
	vector<Node> failed;

	options = getStreets(true);

	if (options.empty()) {
		cerr << "Invalid option.\n";
		return failed;
	}

	cout << "> CHOOSE YOUR CURRENT LOCATION'S ID: ";
	cin >> source;
	cout << endl;

	if (!verifyChoice(options, source)) {
		cerr << "Invalid option.\n";
		return failed;
	}

	options.clear();
	options = getStreets(false);

	if (options.empty()) {
		cerr << "Invalid option.\n";
		return failed;
	}

	cout << "> CHOOSE YOUR DESTINATION'S ID: ";
	cin >> dest;
	cout << endl;

	if (!verifyChoice(options, dest)) {
		cerr << "Invalid option.\n";
		return failed;
	}

	cout << "> MAX DISTANCE (m): ";
	cin >> maxDistance;
	cout << endl;

	cout << "> WHICH TYPE OF PARKING LOT DO YOU PREFER ?\n";
	cout << "[1]Cheap           [2]Near Your Destiny\n\n";

	cout << "> Option: ";
	cin >> Cheap_Near;
	cout << endl;

	if (Cheap_Near != 1 && Cheap_Near != 2) {
		cerr << "Invalid option.\n";
		return failed;
	}

	cout << "> DO YOU WANT TO FILL UP THE CAR ? (y/n): ";
	cin >> passClient;
	cout << endl;

	if (passClient != 'y' && passClient != 'n') {
		cerr << "Invalid option.\n";
		return failed;
	}

//------------------------------------------------
	int nTimeStart = GetMilliCount();
//------------------------------------------------

	vector<Node> path = calculatePath(source, dest, maxDistance, Cheap_Near,
			passClient);

	if (path.size() != 0) { //se ha de facto um path
		cout << "> PATH: ";
		for (unsigned int i = 0; i < path.size(); i++) {
			cout << path.at(i).getID() << " ";
		}
	}


	//time--------------------------------------------
	int nTimeElapsed = GetMilliSpan(nTimeStart);
	cout << endl << endl;
	cout << "> EXECUTION TIME (ms): " << nTimeElapsed << endl;
	//------------------------------------------------

	//connection--------------------------------------
	cout << "> IS GRAPH STRONGLY CONNECTED: ";
	if (myGraph.isStronglyConnected())
		cout << "yes" << endl;
	else
		cout << "no" << endl;
	//------------------------------------------------

	return path;
	//TODO: falta fazer o falhanco da coisa
}

//retorna vetor vazio se nao encontroou nenhum path
vector<Node> map::calculatePath(int sourceID, int destID, int maxDistance,
		int Cheap_Near, char passClient) {



//ELABORAR O PATH//

	vector<Node> part1; //path da source ao parque
	vector<Node> part2; //path do parque a dest
	vector<Node> vec; //path da source a dest, passando pelo parque

	if (supermarket.getID() == sourceID && supermarket.getID() == destID) { //se a source, o dest e o parque sao o mesmo ponto

//vec teria apenas dois elementos, que serï¿½o iguais, mas um representa a origem e outro o destino
		vec.push_back(getNodeByID(sourceID));
		vec.push_back(getNodeByID(destID));

		if (passClient == 'y') { //se o user escolheu abastecer
			addClientToPath(vec);
		}

	} else if (supermarket.getID() == sourceID || supermarket.getID() == destID) { //se a source ou o destino sï¿½o o parque

//vec teria o caminho mais perto de source a dest
		vec = myGraph.getPath(getNodeByID(sourceID), getNodeByID(destID));

		if (passClient == 'y') { //se o user escolheu abastecer
			addClientToPath(vec);
		}

	} else {

		part1 = myGraph.getPath(getNodeByID(sourceID),
				getNodeByID(supermarket.getID())); // caminho mais curto da source ao parque
		part2 = myGraph.getPath(getNodeByID(supermarket.getID()), getNodeByID(destID)); //caminho mais cuto do parque ao dest

		if (passClient == 'y') { //se o user escolheu abastecer
			addClientToPath(part1); //adiciona bomba de gasolina ao path source-supermarket visto que o user ja nao terï¿½ o carro em supermarket-dest
		}

		part2.erase(part2.begin()); //apaga o primeiro elemento de part2 porque ï¿½ igual ao ultimo elemento da part1, ou seja, o parque

		part1.insert(part1.end(), part2.begin(), part2.end()); //concatena as duas partes

		vec = part1;
	}

	return vec;

}

void map::addClientToPath(vector<Node> &path) {

	Node source = path.at(0);
	Node dest = path.at(path.size() - 1);

//PART 1 - assumindo bomba mais perto da origem

	int partSource1; //distancia source-bomba
	int partSource2; // distancia bomba-dest
	int partSource; //distancia source-bomba-dest

	vector<Node> pathSource1; //path source-bomba
	vector<Node> pathSource2; //path bomba-dest
	vector<Node> pathSource; //path source-bomba-dest

	Node clientNearSource = clientNear(source.getID());

	if (clientNearSource == source && clientNearSource == dest) { //se a source, a bomba e o parque forem o mesmo

//pathSources tem 3 elementos iguais, mas cada um representa a sua coisa
		pathSource.push_back(source);
		pathSource.push_back(clientNearSource);
		pathSource.push_back(dest);

		//distancia entre eles 0
		partSource = 0;

	} else if (clientNearSource == source || clientNearSource == dest) { //se a bomba mais perto for na origem ou no destino

		pathSource = myGraph.getPath(source, dest); //path entre a origem e o destino
		myGraph.dijkstraShortestPath(source); //dijkstra para a origem
		partSource = myGraph.getVertex(dest)->getDist(); //distancia mais curta da origem ao destino

	} else {
		myGraph.dijkstraShortestPath(source); //disjkstra para a source
		partSource1 = myGraph.getVertex(clientNearSource)->getDist(); //distancia mais curta da origem ï¿½ bomba
		pathSource1 = myGraph.getPath(source, clientNearSource); //path mais curto da origem ï¿½ bomba

		myGraph.dijkstraShortestPath(clientNearSource); //disjkstra para a bomba
		partSource2 = myGraph.getVertex(dest)->getDist();  //distancia mais curta da bomba ao destino
		pathSource2 = myGraph.getPath(clientNearSource, dest);//path mais curto da bomba ao destino

		pathSource2.erase(pathSource2.begin()); //apaga o primeiro elemento de pathSource2 pois vai ser o mesmo que pathSource1, ou seja, a bomba de gasolina
		pathSource1.insert(pathSource1.end(), pathSource2.begin(),
				pathSource2.end()); //concatena os dois vetores
		pathSource = pathSource1; //origem-bomba-destino

		partSource = partSource1 + partSource2; //distancia mais curta entre a origem-bomba-destino
	}

//PART 2 - calcula bomba mais perto do destino, e o caminho origem-bomba-destino

	int partDest1; //distancia source-bomba
	int partDest2; // distancia bomba-dest
	int partDest; //distancia source-bomba-dest

	vector<Node> pathDest1; //path source-bomba
	vector<Node> pathDest2; //path bomba-dest
	vector<Node> pathDest; //path source-bomba-dest

	Node clientNearDest = clientNear(dest.getID());

	if (clientNearDest == source && clientNearDest == dest) {

		pathDest.push_back(source);
		pathDest.push_back(clientNearDest);
		pathDest.push_back(dest);

		partSource = 0;

	} else if (clientNearDest == source || clientNearDest == dest) {

		pathDest = myGraph.getPath(source, dest);
		myGraph.dijkstraShortestPath(source);
		partDest = myGraph.getVertex(dest)->getDist();

	} else {

		myGraph.dijkstraShortestPath(source);
		partDest1 = myGraph.getVertex(clientNearDest)->getDist();
		pathDest1 = myGraph.getPath(source, clientNearDest);

		myGraph.dijkstraShortestPath(clientNearDest);
		partDest2 = myGraph.getVertex(dest)->getDist();
		pathDest2 = myGraph.getPath(clientNearDest, dest);

		pathDest2.erase(pathDest2.begin());
		pathDest1.insert(pathDest1.end(), pathDest2.begin(), pathDest2.end());
		pathDest = pathDest1;

		partDest = partDest1 + partDest2;
	}

	if (partSource < partDest) { //verifica qual o caminho mais curto
		cout << "> GAS STATION: " << clientNearSource.getID() << endl;
		path = pathSource;
	} else {
		cout << "> GAS STATION: " << clientNearDest.getID() << endl;
		path = pathDest;
	}

	return;

}


