#include "Menu.h"



Menu::Menu() {
	int numNodes = 0;

	compareStruct.biMethod.totalMillis = 0;
	compareStruct.dOdMethod.totalMillis = 0;
	compareStruct.fwMethod.totalMillis = 0;
	do {
		cout << "Quantos nós? (negativo para sair)\n";
		cout << "1 : 649\n";
		cout << "2 : 1329\n";
		cout << "3 : 2543\n";
		cout << "4 : 3980\n";
		cout << "0 : Usar predefinido\n";
		cin >> numNodes;
	} while (numNodes > 4);
	if (numNodes < 0)
		return;
	cout << "\n\n\nA Ler Os Ficheiros\n";
	loadFiles(numNodes);

	cout << "\nficheiros lidos!\nprima uma tecla para continuar\n";
	getchar();
	menu();
	return;
}

bool Menu::isSupermarket(int idNo) {
	for (unsigned int i = 0; i < supermarkets.size(); i++) {
		if (idNo == supermarkets.at(i)->getNode()) {
			return true;
		}
	}
	return false;
}

bool Menu::isClient(int idNo) {
	for (unsigned int i = 0; i < clients.size(); i++) {
		if (clients.at(i)->getNode() == idNo)
			return true;
	}
	return false;
}

void Menu::assignClients(int supers, int camioes) {
	assignClientToSuper(supers);
	assignClientToTruck(camioes);
	return;
}

void Menu::assignClientToSuper(int supers) {
	double total, tmpsuper = 0;
	double tmp = INT_INFINITY;
	bool added = false;
	int n;
	srand(time(NULL));

	supermarkets.clear();
	for (int s = (int) supermarkets.size(); s < supers; s++) {

		added = false;
		while (!added) {

			n = rand() % nodes.size();

			if (!isClient(nodes.at(n)->getId())
					&& !isSupermarket(nodes.at(n)->getId())) {

				supermarkets.push_back(
						new Supermarket(s, "super" + s, nodes.at(n)->getId()));	//add necessary supers
				added = true;

			}

		}

	}
	cout << supermarkets.size() << " supermercados criados\n\n";

	for (unsigned int s = 0; s < supermarkets.size(); s++) {
		//write(STDOUT_FILENO, "\nS__\n", 5);
		graph.dijkstraShortestPath(supermarkets.at(s)->getNode(), total);
		//write(STDOUT_FILENO, "\nS00\n", 5);
		for (unsigned int c = 0; c < clients.size(); c++) {

			if (clients.at(c)->getDistMySuper() < tmp) {	//OK
				tmp = clients.at(c)->getDistMySuper();
				tmpsuper = s;
			}
			clients.at(c)->setMySuper(tmpsuper);	//s começa em 0
			clients.at(c)->setDistMySuper(tmpsuper);
		}
	}
	for (int c = 0; c < (int) clients.size(); c++) {
	}

	return;
}

int Menu::numberOfClientsOfSupermarket(int super) {
	//cout << "quantos" << super << endl;
	int total = 0;
	for (int c = 0; c < (int) clients.size(); c++) {
		if (clients.at(c)->getMySuper() == super)
			total += 1;
	}
//	cout << "super" << super << "\ttotal" << total << endl;
	return total;
}

void Menu::assignClientToTruck(int camioes) {

	int truck, trucksLeft, clientsLeft, updatedClientsPerTruck = 0;

	trucks.clear();
	for (int z = 0; z < (int) supermarkets.size(); z++) {

		for (int t = 0; t < camioes; t++) {

			trucks.push_back(new Truck(t, "truck" + t, INT_INFINITY, z));//add necessary trucks

		}
	}

	cout << trucks.size() << " camioes criados\n\n";

	for (unsigned int c = 0; c < clients.size(); c++) {

		trucksLeft = camioes;

		for (int s = 0; s < (int) supermarkets.size(); s++) {

			if (clients.at(c)->getMySuper() == s) {

				clientsLeft = numberOfClientsOfSupermarket(s);

				while (truck < camioes && clientsLeft > 0) {

					updatedClientsPerTruck = (ceil(clientsLeft / trucksLeft));

					while (updatedClientsPerTruck > 0) {

						trucks.at(truck)->addClient(clients.at(c));

						trucks.at(truck)->setSupermarket(
								clients.at(c)->getMySuper());

						clientsLeft--;

						updatedClientsPerTruck--;

					}

					cout << "clientes do truck " << truck << " = "
							<< trucks.at(truck)->getClients().size() << endl;
					getchar();
					truck++;
				}
			}

		}

	}

	return;
}

void Menu::createClients(int clientes) {
	bool added;
	int n;
	string d;
	clients.clear();	//erases all clients

	for (int c = 1; c <= clientes; c++) {

		added = false;
		while (!added) {

			n = rand() % nodes.size();
			//for (unsigned int n = 0; n < nodes.size(); n++) {
			if (!isClient(nodes.at(n)->getId())
					&& !isSupermarket(nodes.at(n)->getId())) {

				if (c < 10) {
					d = "cliente_00" + c;
				} else if (c < 100) {
					d = "cliente_0" + c;
				} else {
					d = c;
				}
				//int id;

				clients.push_back(
						new Client(c, d, nodes.at(n)->getId(), "rua", 0)); //add necessary clients
				added = true;

			}

		}

	}
	cout << clients.size() << " clientes criados\n\n";
	return;
}

void Menu::menu() {
	statsShown = false;
	long long choice = -1, supers = 1, trucks = 1, clientes = 14;
	system("clear");

	cout << "Quantos clientes ? (0 para usar ficheiros)\n";
	cin >> clientes;
	if (clientes != 0)
		createClients(clientes);

	cout << "Quantos supermercados ? (0 para usar ficheiros)\n";
	cin >> supers;

	if (supers != 0) {
		cout << "\n";

		cout << "Quantos camioes ?\n";
		cin >> trucks;

		assignClients(supers, trucks);
	}

	cout << "\n";

	do {
	cout<<"\n\ncomo quer visualizar a(s) rota(s)\n\n";
	cout<<"1 - na consola\n";
	cout<<"2 - no graphViewer\n";
	cout<<"0 - sair\n";
	cin>>choice;
	}while (choice !=0 && choice !=1 && choice !=2);

	switch (choice){
	case 1:
		textRoute();
		break;
	case 2:
		gvRoute();
		break;
	default:
		return;
		break;
	}


	return;
}

void Menu::getGraphStats() {
	system("clear");
	cout << "Informação do grafo criado\n";

	//analise da densidade
	int numVertices = graph.getVertexSet().size();
	int numEdges = 0;
	for (int i = 0; i < numVertices; i++) {
		numEdges += graph.getVertexSet().at(i)->getNumEdges();
	}
	if (greatness(numEdges) < greatness(numVertices * numVertices))
		cout << "O grafo criado é esparso\n" << endl;
	else
		cout << "O grafo criado é denso\n" << endl;

	cout << "O grafo criado "
			<< (numEdges == numVertices * (numVertices - 1) ? "" : "não")
			<< " é completo\n" << endl;

	//avalia a conectividade (requisito do enunciado)
	cout << "O grafo criado " << (graph.isStronglyConnected() ? "" : "não ")
			<< "é fortemente conexo\n";
	cout << "\n\n\nprima uma tecla para continuar\n";
	getchar();
	return;
}

void Menu::textRoute() {

	int choice = -1;

	if (!statsShown) {
		getGraphStats();
	}
	while (choice != 0) {
		do {

			cout << "qual o metodo?\n";
			cout << "1 - Dijkstra de Dijkstra?\n";
			cout << "2 - bidireccional?\n";
			cout << "3 - Floyd-Warshall?\n";
			cout << "4 - compare\n";
			cout << "0 - sair\n";

			cin >> choice;

		} while (choice != 0 && choice != 1 && choice != 2 && choice != 3
				&& choice != 4);

		system("clear");
		double totaltotal = 0;
		double total = 0;

		switch (choice) {
		case 1:
			if (compareStruct.dOdMethod.totalMillis == 0) {
				DoD(total, true);
			} else {
				for (unsigned int s = 0; s < supermarkets.size(); s++) {
					for (unsigned int t = 0; t < trucks.size(); t++) {
						for (unsigned int i = 0;
								i < compareStruct.dOdMethod.routes.size(); i++)
							printRoute(compareStruct.dOdMethod.routes.at(i), s,
									t);
					}
				}
			}
			break;
		case 2:
			if (compareStruct.biMethod.totalMillis == 0) {
				bi(total, true);
			} else {
				for (unsigned int s = 0; s < supermarkets.size(); s++) {
					for (unsigned int t = 0; t < trucks.size(); t++) {
						for (unsigned int i = 0;
								i < compareStruct.biMethod.routes.size(); i++)
							printRoute(compareStruct.biMethod.routes.at(i), s,
									t);
					}
				}
			}
			break;
		case 3:
			if (compareStruct.fwMethod.totalMillis == 0) {
				fw(total, true);
			} else {
				for (unsigned int s = 0; s < supermarkets.size(); s++) {
					for (unsigned int t = 0; t < trucks.size(); t++) {
						for (unsigned int i = 0;
								i < compareStruct.fwMethod.routes.size(); i++)
							printRoute(compareStruct.fwMethod.routes.at(i), s,
									t);
					}
				}
			}
			break;
		case 4:

			compareMethods();

			break;
		default:
			return;
			break;
		}

		//totaltotal += total;

		//	cout << "soma das rotas=" << totaltotal << "\n";
		cout << "\n\n";

		cout << "\nprima uma tecla para continuar\n";
		getchar();
	}
	//and to the choice menu again
//	textRoute();
	return;
}


void Menu::gvRoute() {

	int choice = -1;

	if (!statsShown) {
		getGraphStats();
	}
	while (choice != 0) {
		do {

			cout << "qual o metodo?\n";
			cout << "1 - Dijkstra de Dijkstra?\n";
			cout << "2 - bidireccional?\n";
			cout << "3 - Floyd-Warshall?\n";
			cout << "0 - sair\n";

			cin >> choice;

		} while (choice != 0 && choice != 1 && choice != 2 && choice != 3);

		system("clear");


		switch (choice) {
		case 1:
			gvRouteDoD();
			break;
		case 2:
			gvRouteBi();
			break;
		case 3:
			gvRouteFW();
			break;

		default:
			return;
			break;
		}

		cout << "\n\n";

		cout << "\nprima uma tecla para continuar\n";
		getchar();
	}
	//and to the choice menu again
//	textRoute();
	return;
}


void Menu::compareMethods() {

	int choice = 0;
	double totaltotal = 0;
	double total = 0;

//corre os métodos que ainda não tiverem sido corridos
	if (compareStruct.dOdMethod.totalMillis == 0)
		DoD(total, false);
	if (compareStruct.biMethod.totalMillis == 0)
		bi(total, false);
	if (compareStruct.fwMethod.totalMillis == 0)
		fw(total, false);

	int minMillis = compareStruct.biMethod.totalMillis;
	if (compareStruct.dOdMethod.totalMillis < minMillis) {
		minMillis = compareStruct.dOdMethod.totalMillis;
	}
	if (compareStruct.fwMethod.totalMillis < minMillis) {
		minMillis = compareStruct.fwMethod.totalMillis;
		cout << "o algoritmo mais rápido a calcular é o Floyd-Warshall" << endl;
	}

	cout << "o algoritmo mais rápido a calcular é o"
			<< (compareStruct.biMethod.totalMillis
					< compareStruct.dOdMethod.totalMillis ?
					"bidireccional" : "Dijkstra of Dijkstras") << endl;
	cout << "DoD: " << compareStruct.dOdMethod.totalMillis << " ms\n";
	cout << "bi: " << compareStruct.biMethod.totalMillis << " ms\n";
	cout << "FW: " << compareStruct.fwMethod.totalMillis << " ms\n\n\n";

	int minWeight = compareStruct.biMethod.totalWeight;
	if (compareStruct.dOdMethod.totalWeight < minWeight) {
		minWeight = compareStruct.dOdMethod.totalWeight;
	}
	if (compareStruct.fwMethod.totalWeight < minWeight) {
		minWeight = compareStruct.fwMethod.totalWeight;
		cout
				<< "o algoritmo que devolve o percurso total menor é o Floyd-Warshall"
				<< endl;
	}
	cout << "o algoritmo que devolve o percurso total menor é o"
			<< (compareStruct.biMethod.totalWeight
					< compareStruct.dOdMethod.totalWeight ?
					"bidireccional" : "Dijkstra of Dijkstras") << endl;
	cout << "DoD: " << compareStruct.dOdMethod.totalWeight << " m\n";
	cout << "bi: " << compareStruct.biMethod.totalWeight << " m\n";
	cout << "FW: " << compareStruct.fwMethod.totalWeight << " m\n\n\n";

	int minNodes = compareStruct.biMethod.totalNodes;
	if (compareStruct.dOdMethod.totalNodes < minNodes) {
		minNodes = compareStruct.dOdMethod.totalNodes;
	}
	if (compareStruct.fwMethod.totalNodes < minNodes) {
		minNodes = compareStruct.fwMethod.totalNodes;
		cout
				<< "o algoritmo que devolve o percurso total com menos nós é o Floyd-Warshall"
				<< endl;
	}
	cout << "o algoritmo que devolve o percurso total com menos nós é o"
			<< (compareStruct.biMethod.totalNodes
					< compareStruct.dOdMethod.totalNodes ?
					"bidireccional" : "Dijkstra of Dijkstras") << endl;
	cout << "DoD: " << compareStruct.dOdMethod.totalNodes << " nodes\n";
	cout << "bi: " << compareStruct.biMethod.totalNodes << " nodes\n";
	cout << "FW: " << compareStruct.fwMethod.totalNodes << " nodes\n\n\n";
cout<<"\nprima uma tecla para continuar\n";
	getchar();

	textRoute(); //para escolher ver caminhos

	return;
}

void Menu::fw(double &total, bool toPrint) {
	//loadFiles(numNodes);

	int totaltotal = 0;
	vector<long long> route;
	vector<long long> routeBack;
	vector<long long> supermarketLocation;
	vector<long long> stops;
	vector<long long> completeRoute;

	long long LastStop;

	cout << "\nalgoritmo de Floyd-Warshall:\n";
	write(STDOUT_FILENO, "\n\nem processamento\n", 19);

//------------------------------------------------
	long long nTimeStart = GetMilliCount();
//------------------------------------------------

	for (unsigned int s = 0; s < supermarkets.size(); s++) {

		for (unsigned int t = 0; t < trucks.size(); t++) {
			total = 0;

			if (trucks.at(t)->getSupermarket() == supermarkets.at(s)->getId()) {

				route.clear();
				routeBack.clear();
				supermarketLocation.clear();

				stops.clear();
				stops = trucks.at(t)->getStops();

				supermarketLocation.push_back(supermarkets.at(s)->getNode());

				route = getFW(supermarkets.at(s)->getNode(),
						trucks.at(t)->getStops(), supermarkets.at(s)->getNode(),
						total);

				LastStop = route.at(route.size() - 1);

				routeBack = getFW(LastStop, supermarketLocation,
						supermarkets.at(s)->getNode(), total);

				//CONCATENATE BOTH ROUTES
				completeRoute.clear();
				completeRoute.reserve(route.size() + routeBack.size());
				completeRoute.insert(completeRoute.end(), route.begin(),
						route.end());
				completeRoute.insert(completeRoute.end(), routeBack.begin(),
						routeBack.end() - 1);	//-1 para não repetir a chegada
				cout << "\nnumber of nodes in path:" << completeRoute.size()
						<< endl;

				write(STDOUT_FILENO, "\n\n", 2);

				cout << "rota " << t + 1 << "/" << trucks.size()
						<< " do supermercado " << s + 1 << "/"
						<< supermarkets.size() << "\n";

				if (toPrint)
					printRoute(completeRoute, s, t);

				cout << "\ntotal=" << total << endl;
				totaltotal += total;
				compareStruct.fwMethod.routes.push_back(completeRoute);
				compareStruct.fwMethod.totalNodes += completeRoute.size();
			}	//fim verificacao cliente truck super
		}	//fim for truck
	}	//fim for super
//time--------------------------------------------
	long long nTimeElapsed = GetMilliSpan(nTimeStart);
	cout << endl << endl;
	cout << "> Floyd-Warshall's Algorithm execution time (ms): " << nTimeElapsed
			<< endl;
//------------------------------------------------
	cout << "\ntotal de nós rotas =" << compareStruct.fwMethod.totalNodes
			<< endl;
	cout << "\ntotal das rotas =" << totaltotal << " m" << endl;
	compareStruct.fwMethod.totalWeight = totaltotal;
	compareStruct.fwMethod.totalMillis = nTimeElapsed;
	cout << "\n";
	return;
}

void Menu::DoD(double &total, bool toPrint) {

	int totaltotal = 0;
	cout << "\nalgoritmo de Dijkstra sobre algoritmos de Dijkstra:\n";

	write(STDOUT_FILENO, "\n\nem processamento\n", 19);
	compareStruct.dOdMethod.totalNodes = 0;

//------------------------------------------------
	long long nTimeStart = GetMilliCount();
//------------------------------------------------
	vector<long long> completeRoute;
	vector<long long> route;
	vector<long long> routeBack;
	vector<long long> supermarketLocation;
	vector<long long> stops;

	long long LastStop;
	for (unsigned int s = 0; s < supermarkets.size(); s++) {

		for (unsigned int t = 0; t < trucks.size(); t++) {

			total = 0;
			if (trucks.at(t)->getSupermarket() == supermarkets.at(s)->getId()) {

				completeRoute.clear();
				route.clear();
				routeBack.clear();
				supermarketLocation.clear();
				stops.clear();
				stops = trucks.at(t)->getStops();

				supermarketLocation.push_back(supermarkets.at(s)->getNode());

				route = dijkstraOfDijkstras(supermarkets.at(s)->getNode(),
						trucks.at(t)->getStops(), supermarkets.at(s)->getNode(),
						total);

				LastStop = route.at(route.size() - 1);
				//	cout << "last Stop=" << LastStop << endl;

				routeBack = dijkstraOfDijkstras(LastStop, supermarketLocation,
						supermarkets.at(s)->getNode(), total);

				completeRoute.reserve(route.size() + routeBack.size());
				completeRoute.insert(completeRoute.end(), route.begin(),
						route.end());

				completeRoute.insert(completeRoute.end(), routeBack.begin(),
						routeBack.end() - 1);	//-1 para não repetir a chegada
				cout << "\nnumber of nodes in path:" << completeRoute.size()
						<< endl;

				write(STDOUT_FILENO, "\n\n", 2);

				cout << "rota " << t + 1 << "/" << trucks.size()
						<< " do supermercado " << s + 1 << "/"
						<< supermarkets.size() << "\n";

				if (toPrint)
					printRoute(completeRoute, s, t);

				cout << "\ntotal=" << total << endl;
				totaltotal += total;
				compareStruct.dOdMethod.routes.push_back(completeRoute);
				compareStruct.dOdMethod.totalNodes += completeRoute.size();
			}	//fim verificacao cliente truck super
		}	//fim for truck
	}	//fim for super

//time--------------------------------------------
	long long nTimeElapsed = GetMilliSpan(nTimeStart);
	cout << endl << endl;
	cout << "> Consecutive Dijkstra's Algorithm execution time (ms): "
			<< nTimeElapsed << endl;
//------------------------------------------------
	cout << "\ntotal de nós rotas =" << compareStruct.dOdMethod.totalNodes
			<< endl;
	cout << "\ntotal das rotas =" << totaltotal << " m" << endl;
	compareStruct.dOdMethod.totalWeight = totaltotal;
	compareStruct.dOdMethod.totalMillis = nTimeElapsed;
	cout << "\n";
	return;
}

void Menu::printRoute(vector<long long> & completeRoute, int s, int t) {
	long long anterior = 0;

	int count = 1;
	bool stay = true;

	for (unsigned int i = 0; i < completeRoute.size(); i++, count++) {
		while (completeRoute.at(i) == anterior && stay) {//para saltar repetidos seguidos
			anterior = completeRoute.at(i);
			if (i < completeRoute.size() - 1) {
				i++;
			} else {
				stay = false;
				break;
			}
		}
		anterior = completeRoute.at(i);

		if (completeRoute.at(i) == supermarkets.at(s)->getNode()) {
			cout << "\n# " << supermarkets.at(s)->getName() << " # \n";

			count = 1;

		} else if (trucks.at(t)->nodeExistsAsClients(completeRoute.at(i))) {
			cout << "\n # " << trucks.at(t)->getClientsName(completeRoute.at(i))
					<< " # \n";

			count = 1;

		} else {
			cout << completeRoute.at(i);

			if (i != completeRoute.size() - 1) {
				cout << "->";
			}
			if (count == 5) {
				count = 0;
				cout << "\n->";
			}
		}
	}
	return;
}

void Menu::bi(double &total, bool toPrint) {
	cout << "entrou bi\n";
	int totaltotal = 0;
	cout << "\nNosso algoritmo bidireccional:\n";
//cout << "em processamento ";
	write(STDOUT_FILENO, "\n\nem processamento\n", 19);

//------------------------------------------------
	long long nTimeStart = GetMilliCount();
//------------------------------------------------
	vector<long long> completeRoute;
	vector<long long> route;
	vector<long long> routeBack;
	vector<long long> supermarketLocation;
	vector<long long> stops;

	for (unsigned int s = 0; s < supermarkets.size(); s++) {

		for (unsigned int t = 0; t < trucks.size(); t++) {
			total = 0;

			if (trucks.at(t)->getSupermarket() == supermarkets.at(s)->getId()) {

				completeRoute.clear();
				route.clear();
				routeBack.clear();
				supermarketLocation.clear();
				stops.clear();

				stops = trucks.at(t)->getStops();

				supermarketLocation.push_back(supermarkets.at(s)->getNode());

				route = graph.getOurRoute(supermarkets.at(s)->getNode(),
						trucks.at(t)->getStops(), supermarkets.at(s)->getNode(),
						total);

				//	LastStop = route.at(route.size() - 1);
				//	cout << "last Stop=" << LastStop << endl;

				//PENSO QUE A MAIS			routeBack = graph.getOurRoute(LastStop, supermarketLocation,supermarkets.at(s)->getNode(), total);

				//	completeRoute.reserve(route.size() + routeBack.size());
				completeRoute.insert(completeRoute.end(), route.begin(),
						route.end());
				cout << "08\n";
				//	completeRoute.insert(completeRoute.end(), routeBack.begin(),routeBack.end() - 1);	//-1 para não repetir a chegada
				cout << "\nnumber of nodes in path:" << completeRoute.size()
						<< endl;

				write(STDOUT_FILENO, "\n\n", 2);

				cout << "rota " << t + 1 << "/" << trucks.size()
						<< " do supermercado " << s + 1 << "/"
						<< supermarkets.size() << "\n";

				if (toPrint)
					printRoute(completeRoute, s, t);
				cout << "\ntotal=" << total << endl;

				totaltotal += total;

				compareStruct.biMethod.routes.push_back(completeRoute);

				compareStruct.biMethod.totalNodes += completeRoute.size();

			}	//fim verificacao cliente truck super

		}	//fim for truck

	}	//fim for super

//time--------------------------------------------
	long long nTimeElapsed = GetMilliSpan(nTimeStart);
	cout << endl << endl;
	cout << "> Our Bidireccional Algorithm execution time (ms): "
			<< nTimeElapsed << endl;
//------------------------------------------------
	cout << "\ntotal de nós rotas =" << compareStruct.biMethod.totalNodes
			<< endl;
	cout << "\ntotal das rotas =" << totaltotal << " m" << endl;
	compareStruct.biMethod.totalWeight = totaltotal;
	compareStruct.biMethod.totalMillis = nTimeElapsed;
	cout << "\n";
	return;
}

void Menu::gvRouteFW() {
	//loadFiles(numNodes);	//one truck at a time
	double total = 0;
	long long id;
	cout<<"\nprima uma tecla para continuar\n";
	getchar();
	bool found = false;

	system("clear");

	do {
		cout << "qual a rota?\n";
		cin >> id;
		for (unsigned int i = 0; i < trucks.size(); i++) {
			if (trucks.at(i)->getId() == id) {
				found = true;
				break;
			}
		}
		if (found == false) {
			cout << "nao existe essa rota.\n qual a rota?\n";
		}
	} while (found == false);
	system("clear");

	write(STDOUT_FILENO, "\n\nem processamento\n", 19);
	long long supermarket = trucks[id - 1]->getSupermarket(); //supermercado onde esta o camiao
	vector<long long> route;
	vector<long long> routeBack;
	vector<long long> supermarketLocation;

//cout << "em processamento...\n[";

	vector<long long> stops = trucks.at(id - 1)->getStops();
//long long sizeStops = stops.size();
//ERROR TRACKING cout<< sizeStops<<"NUM DE STOPS=============================================================================\n";

	supermarketLocation.push_back(supermarkets.at(supermarket)->getNode());

//ROTA: sai do supermercado(armazem) -> passa por todos os clients -> supermercado (armazem)
	route = getFW(supermarkets.at(supermarket)->getNode(),
			trucks.at(id - 1)->getStops(),
			supermarkets.at(supermarket)->getNode(), total);

	long long LastStop = route.at(route.size() - 1);
	routeBack = getFW(LastStop, supermarketLocation, LastStop, total);

//CONCATENATE BOTH ROUTES
	vector<long long> completeRoute;
	completeRoute.reserve(route.size() + routeBack.size());
	completeRoute.insert(completeRoute.end(), route.begin(), route.end());
	completeRoute.insert(completeRoute.end(), routeBack.begin(),
			routeBack.end());

	cout << "esta quase...\n";
	viewGraph(true, id, completeRoute);
	vector<Node> newPath;

	return;
}

void Menu::gvRouteBi() {
long long id;
	int totaltotal = 0;
	int s, t;
	double total = 0;
	vector<long long> completeRoute;
	vector<long long> route;
	vector<long long> routeBack;
	vector<long long> supermarketLocation;
	vector<long long> stops;
	cout << "Rota de que supermercado?\n";
		cin >> s;
		cout << "Rota de que camiao?\n";
		cin >> t;
		int trucksPerSuper = trucks.size() / supermarkets.size();
		id = trucksPerSuper * s + t;


	if (trucks.at(t)->getSupermarket() == supermarkets.at(s)->getId()) {

		completeRoute.clear();
		route.clear();
		routeBack.clear();
		supermarketLocation.clear();
		stops.clear();

		stops = trucks.at(t)->getStops();

		supermarketLocation.push_back(supermarkets.at(s)->getNode());

		route = graph.getOurRoute(supermarkets.at(s)->getNode(),
				trucks.at(t)->getStops(), supermarkets.at(s)->getNode(), total);

		//	LastStop = route.at(route.size() - 1);
		//PENSO QUE A MAIS			routeBack = graph.getOurRoute(LastStop, supermarketLocation,supermarkets.at(s)->getNode(), total);

		//	completeRoute.reserve(route.size() + routeBack.size());
		completeRoute.insert(completeRoute.end(), route.begin(), route.end());

		//	completeRoute.insert(completeRoute.end(), routeBack.begin(),routeBack.end() - 1);	//-1 para não repetir a chegada

	}	//fim verificacao cliente truck super

	cout << "mais um pouco\n";
	viewGraph(true, id, completeRoute);
	vector<Node> newPath;

	return;
}

void Menu::gvRouteDoD() {
	long long id;
	double total = 0;
	int s, t;
	vector<long long> completeRoute;
	vector<long long> route;
	vector<long long> routeBack;
	vector<long long> supermarketLocation;
	vector<long long> stops;

	long long LastStop;
	cout << "Rota de que supermercado?\n";
	cin >> s;
	cout << "Rota de que camiao?\n";
	cin >> t;
	int trucksPerSuper = trucks.size() / supermarkets.size();
	id = trucksPerSuper * s + t;

	if (trucks.at(t)->getSupermarket() == supermarkets.at(s)->getId()) {

		completeRoute.clear();
		route.clear();
		routeBack.clear();
		supermarketLocation.clear();
		stops.clear();
		stops = trucks.at(t)->getStops();

		supermarketLocation.push_back(supermarkets.at(s)->getNode());

		route = dijkstraOfDijkstras(supermarkets.at(s)->getNode(),
				trucks.at(t)->getStops(), supermarkets.at(s)->getNode(), total);

		LastStop = route.at(route.size() - 1);
		//	cout << "last Stop=" << LastStop << endl;

		routeBack = dijkstraOfDijkstras(LastStop, supermarketLocation,
				supermarkets.at(s)->getNode(), total);

		completeRoute.reserve(route.size() + routeBack.size());
		completeRoute.insert(completeRoute.end(), route.begin(), route.end());

		completeRoute.insert(completeRoute.end(), routeBack.begin(),
				routeBack.end() - 1);	//-1 para não repetir a chegada

	}	//fim verificacao cliente truck super

	cout << "mais um pouco\n";
	viewGraph(true, id, completeRoute);
	vector<Node> newPath;

	return;
}

void Menu::loadFiles(int numNodes) {
	Files fl;

	roads = fl.loadRoads(numNodes);
	cout << roads.size() << " ROADS LOADED" << endl;

	connections = fl.loadConnections(numNodes);
	cout << connections.size() << " CONNECTIONS LOADED" << endl;

	nodes = fl.loadNodes(numNodes);
	cout << nodes.size() << " NODES LOADED" << endl;

	supermarkets = fl.loadSupermarkets();
	cout << supermarkets.size() << " SUPERMARKETS LOADED" << endl;

	clients = fl.loadClients();
	cout << clients.size() << " CLIENTS LOADED" << endl;

	trucks = fl.loadTruck(clients);
	cout << trucks.size() << " TRUCKS LOADED" << endl;
	for (unsigned int i = 0; i < nodes.size(); i++) {
		graph.addVertex(nodes.at(i)->getId());
	}

	for (unsigned int i = 0; i < connections.size(); i++) {
		double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
		bool twoWay = false;

		for (unsigned int j = 0; j < roads.size(); j++) {
			if (roads.at(j)->getId() == connections.at(i)->getRoadId()) {
				twoWay = roads.at(j)->isTwoWay();
				break;
			}
		}

		for (unsigned int j = 0; j < nodes.size(); j++) {
			if (nodes.at(j)->getId() == connections.at(i)->getNode1()) {
				x1 = nodes.at(j)->getX();
				y1 = nodes.at(j)->getY();
				break;
			}
		}

		for (unsigned int j = 0; j < nodes.size(); j++) {
			if (nodes.at(j)->getId() == connections.at(i)->getNode2()) {
				x2 = nodes.at(j)->getX();
				y2 = nodes.at(j)->getY();
				break;
			}
		}

		double distance = euclideanDist(x1, y1, x2, y2);
		graph.addEdge(connections.at(i)->getNode1(),
				connections.at(i)->getNode2(), distance);
		if (twoWay)
			graph.addEdge(connections.at(i)->getNode2(),
					connections.at(i)->getNode1(), distance);

	}
	cout<<"\nprima uma tecla para continuar\n";
	getchar();
	return;
}

void Menu::viewGraph(bool toSupermarket, long long idtruck,
		vector<long long> route) {

	gv = new GraphViewer(1000, 498, false);

	gv->setBackground("fundo.jpg");
	gv->createWindow(1000, 498);

	gv->defineEdgeCurved(false);

	gv->defineEdgeColor("black");

	gv->defineVertexIcon("res/emptyIcon.png");

//	gv->defineVertexColor("BLUE");

	bool client = false;

	long long edgecount = 0;

	for (unsigned int i = 0; i < route.size(); i++) {
		client = false;
		unsigned int j = 0;
		write(STDOUT_FILENO, ".", 1);
		for (j = 0; j < nodes.size(); j++) {
			if (nodes.at(j)->getId() == route.at(i))
				break;

		}

		for (unsigned int k = 0;
				k < trucks.at(idtruck - 1)->getClients().size(); k++) {
			if (trucks.at(idtruck - 1)->getClients().at(k)->getNode()
					== route.at(i)) {
				client = true;
				break;

			}

		}

		gv->addNode(route.at(i), nodes.at(j)->getX(), nodes.at(j)->getY());
		if (i == 0 && toSupermarket == true)
			gv->setVertexIcon(route.at(i), "super_small.png");
		else if (i == route.size() - 1 && toSupermarket == true)
			gv->setVertexIcon(route.at(i), "super_small.png");
		else if (client == true)
			gv->setVertexIcon(route.at(i), "client_small.png");
		else
			gv->setVertexIcon(route.at(i), "point_small.png");
	}

	for (unsigned int i = 0; i < route.size(); i++) {
		if (i < route.size() - 1)
			gv->addEdge(edgecount++, route.at(i), route.at(i + 1),
					EdgeType::DIRECTED);
	}

	gv->rearrange();

	return;
}

vector<long long> Menu::getFW(long long firstNode, vector<long long> stops,
		long long endNode, double & total) {

	long long source = firstNode;
	vector<long long> pathOrder;

	while (stops.size() > 0) {
		//write(STDOUT_FILENO, "\n*", 1);
		graph.dijkstraShortestPath(source, total);

		int next = 0, maxWeight = 0;
		for (unsigned int i = 0; i < stops.size(); i++) {

			int weight = graph.getVertex(stops.at(i))->getDist();
			if (weight >= maxWeight) {

				maxWeight = weight;
				next = i;
			}
		}

//e poe em next a stop seguinte mais perto (pontoSeguinte)

		graph.floydWarshallShortestPath();

//poe no vector tmp o caminho entre o pontoActual e o pontoSeguinte
		vector<long long> tmp = graph.getfloydWarshallPath(source,
				stops.at(next));

//source.getNode().getLon(), source.getNode().getLon(),source.getNode().getLon(),source.getNode().getLon() );
		for (unsigned int i = 0; i < tmp.size(); i++) {

			pathOrder.push_back(tmp.at(i));
		}
//actualiza pontoActual para pontoSegulong longe

		source = stops.at(next);
		endNode = stops.at(0);

		stops.erase(stops.begin() + next);

//e apaga da lista de paragens por visitar o pontoSeguinte
	}

//cout<<"\ncaminho totalFW="<<total/pow(10,8)<<"\n";

	pathOrder.push_back(endNode);

	return pathOrder;

}

vector<long long> Menu::dijkstraOfDijkstras(long long firstNode,
		vector<long long> stops, long long endNode, double &total) {

	stack<long long> dijkstraLeg;
	vector<long long> leg;
	double parcial, tmp = 0;
	long long source = firstNode;
	vector<long long> pathOrder;
	long long next = source;
	double min;
	int k;
	pathOrder.push_back((graph.getVertex(next))->getInfo());
	cout << "size=" << stops.size() << endl;
	while (stops.size() > 0) {
		//	cout << "IMPRIME STOPS" << endl;
		//	for (int st = 0; st < (int) stops.size(); st++) {
		//		cout << "st=" << stops.at(st) << endl;
		//	}
		k = 0;
		//		write(STDOUT_FILENO, ".", 1);
		min = DBL_MAX;
		parcial = 0;
		//vai determinar a etapa

		graph.dijkstraShortestPath(source, parcial);//a partir do inicio desta etapa distancias para tudo
		//cout<<"size="<<stops.size()<<"\tsource="<<source<<endl;

		for (unsigned int i = 0; i < stops.size(); i++) {//ver qual a stop mais perto do inicio da etapa actual

			if ((tmp = graph.getVertex(stops.at(i))->getDist()) < min) {
				//	cout << "i=" << i << endl;

				min = tmp;
				next = stops.at(i);
				k = i;
			}
		}

		//sai com next stop actualizada
		//	cout << "k=" << k << endl;
		//	cout << "size=" << stops.size() << "\tnext=" << next << endl;
		total += parcial;
		leg = graph.getPath(source, next);//vai buscar o caminho da etapa agora calculada e a seguir insere no caminho total
		pathOrder.insert(pathOrder.end(), leg.begin(), leg.end());

		if (stops.size() > 1) {
			source = (graph.getVertex(next))->getInfo(); //actualiza o inicio da proxima etapa
			//	cout<<"stops.at(k)"<<stops.at(k)<<endl;
			stops.erase(stops.begin() + k);	//erro NAO APAGA O QUE DEVE //apaga a stop do cliente calculado nesta etapa
			//	cout << "passou";
		} else {
			graph.dijkstraShortestPath(stops.at(0), parcial);
			leg = graph.getPath(stops.at(0), firstNode); //vai buscar o caminho da etapa agora calculada e a seguir insere no caminho total
			pathOrder.insert(pathOrder.end(), leg.begin(), leg.end());
			stops.erase(stops.begin());
			total += parcial;

			//break;
		}
	}

	return pathOrder;
}

double Menu::euclideanDist(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

