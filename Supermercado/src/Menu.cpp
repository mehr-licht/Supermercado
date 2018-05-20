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
		cout << "5 : 57480\n";
		cout << "6 : 145980\n";
		cout << "0 : Usar predefinido\n";
		cin >> numNodes;
	} while (numNodes > 6);
	if (numNodes < 0)
		return;
	cout << "\n\n\nA Ler Os Ficheiros\n";
	loadFiles(numNodes);
	this->setMap(numNodes);
	cout << "\nficheiros lidos!\nprima uma tecla para continuar\n";
	getchar();
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
	for (int s = 0; s < supers; s++) {

		added = false;
		while (!added) {

			n = rand() % nodes.size();

			if (!isClient(nodes.at(n)->getId())
					&& !isSupermarket(nodes.at(n)->getId())) {

				std::stringstream sstm;
				sstm << SUPERNAME << s;
				string d = sstm.str();
				string f = "adicionado";
				supermarkets.push_back(
						new Supermarket(s, d, nodes.at(n)->getId(), f)); //add necessary supers
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

		for (int t = 1; t < camioes + 1; t++) {
			std::stringstream sstm;
			sstm << "truck" << t << "from" << z;
			string d = sstm.str();
			trucks.push_back(new Truck(t, d, INT_INFINITY, z));//add necessary trucks

		}
	}

	cout << trucks.size() << " camioes criados\n\n";
	truck = 0;
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

					cout << "clientes do truck "
							<< trucks.at(truck)->getnumRota() << " = "
							<< trucks.at(truck)->getClients().size() << endl;

					truck++;
				}
			}

		}

	}
	getchar();
	return;
}

void Menu::createClients(int clientes) {
	bool added;
	int n;
	string d;
	clients.clear();	//erases all clients

	for (int c = 0; c < clientes; c++) {

		added = false;
		while (!added) {

			n = rand() % nodes.size();
			//for (unsigned int n = 0; n < nodes.size(); n++) {
			if (!isClient(nodes.at(n)->getId())
					&& !isSupermarket(nodes.at(n)->getId())) {
				std::stringstream sstm;

				if (c < 10) {
					sstm << "client_00" << c;

				} else if (c < 100) {
					sstm << "client_0" << c;

				} else {
					sstm << "client" << c;

				}
				string d = sstm.str();

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
	cout << "entra Menu" << endl;
	statsShown = false;
	long long choice = -1, supers = 1, trucks = 1, clientes = 14;
	system("clear");

	while (choice != 0) {
		do {
			system("clear");
			cout << "\n\nO que pretende?\n\n";
			cout << "1 - Strings\n\n";
			cout << "2 - Rotas\n\n";
			//cout << "3 - testes\n\n";
			//cout << "4 - reset à rota\n\n";
			cout << "0 - sair\n";
			cin >> choice;
		} while (choice != 0 && choice != 1 && choice != 2 && choice != 3
				&& choice != 4);

		switch (choice) {
		case 4: {
			//reset à rota
			system("clear");
			char opt;

			while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N') {
				cout
						<< "\n\do you really want to reset the current route? (y/n)\n";
				cin >> opt;
			}

			switch (toupper(opt)) {
			case 'Y':
				this->setSource(NULL);
				this->trucks.at(0)->getStops().clear();
				cout << "the route was reset\n";
				getchar();
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			case 'N':

				break;
			}

			break;
		}
		case 1: {
			stringMenu();
			break;
		}
		case 2: {
			if (!this->created) {
				cout << "\nplease wait while building graph\n";
				for (unsigned int i = 0; i < nodes.size(); i++) {

					graph.addVertex(nodes.at(i)->getId());
				}

				for (unsigned int i = 0; i < connections.size(); i++) {

					double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
					bool twoWay = false;

					for (unsigned int j = 0; j < roads.size(); j++) {

						if (roads.at(j)->getId()
								== connections.at(i)->getRoadId()) {
							twoWay = roads.at(j)->isTwoWay();
							break;
						}
					}

					for (unsigned int j = 0; j < nodes.size(); j++) {

						if (nodes.at(j)->getId()
								== connections.at(i)->getNode1()) {
							x1 = nodes.at(j)->getX();
							y1 = nodes.at(j)->getY();
							break;
						}
					}

					for (unsigned int j = 0; j < nodes.size(); j++) {

						if (nodes.at(j)->getId()
								== connections.at(i)->getNode2()) {
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
			}

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

			routeMenu();
			break;
		}
		case 3: //APAGAR ISTO TUDO - não esquecer && != 3 no menu
		{
			system("clear");
			cout << "****TESTS****\n\n";
			vector<int> vals;
			int opc = 0, opc2 = 0;
			string textobase, padrao, filen;
			struct timeval st, et;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "padrao a procurar:\n";
			getline(cin, padrao);
			if (padrao.length() < 3) {
				cout << "introduzir padroes com pelo menos 3 caracteres\n";
				break;
			}
			while (opc2 != 1 && opc2 != 2) {
				cout << "em ficheiro(1) ou em texto(2)?\n";
				cin >> opc2;
				switch (opc2) {
				case 1:
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "nome do ficheiro (com path):\n";
					getline(cin, filen);
					break;
				case 2:
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "texto no qual se vai procurar:\n";
					getline(cin, textobase);
					break;
				default:
					break;
				}
			}

			while (opc != 1 && opc != 2) {
				cout << "teste de string exacta(1) ou aproximada(2)?\n";
				cin >> opc;
				switch (opc) {
				case 1:
					if (opc2 == 1) {
						cout << "para já ir pelas strings e supermercados\n";
						superExacta(padrao);/*
						 gettimeofday(&st, NULL);

						 vals = numStringMatching(filen, padrao);
						 gettimeofday(&et, NULL);
						 int elapsed = ((et.tv_sec - st.tv_sec) * 1000000)
						 + (et.tv_usec - st.tv_usec);

						 cout << "demorou" << elapsed << " microsegundos";*/
						getchar();
					} else {
						gettimeofday(&st, NULL);
						int i = kmpMatcher(textobase, padrao);

						gettimeofday(&et, NULL);

						if (i)
							cout << "encontrou na posicao "
									<< textobase.find_first_of(padrao, i)
									<< ", o padrao "
									<< textobase.substr(i - 1, padrao.length())
									<< "\n";

						cout << "tamanho do padrao=" << padrao.length() << endl;
						cout << "tamanho do texto=" << textobase.length()
								<< endl;
						getchar();
						int elapsed = ((et.tv_sec - st.tv_sec) * 1000000)
								+ (et.tv_usec - st.tv_usec);

						cout << "demorou" << elapsed << " microsegundos / "
								<< elapsed / 1000 << " milisegundos / "
								<< elapsed / 1000000 << " segundos" << endl;

					}
					break;

				case 2:
					if (opc2 == 1) {
						cout << "para já ir pelas strings e supermercados\n";
						superApprox(padrao);/*
						 gettimeofday(&st, NULL);

						 numApproximateStringMatching(filen, padrao);
						 gettimeofday(&et, NULL);
						 int elapsed = ((et.tv_sec - st.tv_sec) * 1000000)
						 + (et.tv_usec - st.tv_usec);

						 cout << "demorou" << elapsed << " microsegundos";
						 */

						getchar();
					} else { //texto aprox
						cout
								<< "encontrar palavra num conjunto e não comparar palavras\n";
						stringstream s1(textobase);
						string word1;
						int num = 0, nwords = 0;

						gettimeofday(&st, NULL);

						while (!s1.eof()) {

							s1 >> word1;
							num += editDistance(padrao, word1);
							nwords++;
						}
						gettimeofday(&et, NULL);

						int elapsed = ((et.tv_sec - st.tv_sec) * 1000000)
								+ (et.tv_usec - st.tv_usec);

						float res = (float) num / nwords;
						cout << "parecença=" << res
								<< " (se superior a 5,5=>ok)" << endl;

						getchar();
						cout << "demorou" << elapsed << " microsegundos / "
								<< elapsed / 1000 << " milisegundos / "
								<< elapsed / 1000000 << " segundos" << endl;

					}
					break;

				default:
					break;
				} //fecha switch de dentro
			} //fecha while opc
			break;
		}
		default:
			break;
		}
	}

	return;
}

void Menu::stringMenu() {

	int choice = -1;
	string pattern;
	while (choice != 0) {
		do {
			pattern = "";
			system("clear");
			cout << "\n\n\n\n";
			cout << "\t1 - procura exacta de supermercados (com a sua rua)\n\n";
			cout
					<< "\t2 - procura aproximada de supermercados (com a sua rua)\n\n";
			cout << "\t3 - procura exacta de ruas (e seus supermercados)\n\n";
			cout
					<< "\t4 - procura aproximada de ruas (e seus supermercados)\n\n";
			cout << "\t5 - procura exacta de supermercados em cruzamentos\n\n";
			cout
					<< "\t6 - procura aproximada de supermercados em cruzamentos\n\n";
			cout << "\t7 - procura exacta de supermercados em freguesias\n\n";

			cout
					<< "\t8 - procura aproximada de supermercados em freguesias\n\n";
			cout << "\t9 - fechar rota e mostrar\n\n";
			cout << "\t0 - para trás\n";
			cin >> choice;
		} while (choice != 0 && choice != 1 && choice != 2 && choice != 3
				&& choice != 4 && choice != 5 && choice != 6 && choice != 7
				&& choice != 8 && choice != 9);

		if (choice && choice != 5 && choice != 6 && choice != 9) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			while (pattern.size() < 3) {
				cout << "\n\ntexto a pesquisar (pelo menos 3 caracteres):\n";

				getline(cin, pattern);

			}
		}

		switch (choice) {
		case 1:
			superExacta(pattern);
			break;
		case 2:
			superApprox(pattern);
			break;
		case 3:
			ruaExacta(pattern);
			break;
		case 4:
			ruaApprox(pattern);
			break;
		case 5:
			crossExacta();
			break;
		case 6:
			crossApprox();
			break;
		case 7:
			fregExacta(pattern);
			break;
		case 8:
			fregApprox(pattern);
			break;
		case 9:
			closeRoute();
			break;
		default:
			return;
			break;

		}

	}

	return;
}

void Menu::routeMenu() {

	int choice = -1;
	while (choice != 0) {
		do {
			system("clear");
			cout << "\n\ncomo quer visualizar a(s) rota(s)\n\n";
			cout << "1 - na consola\n";
			cout << "2 - no graphViewer\n";
			cout << "0 - sair\n";
			cin >> choice;
		} while (choice != 0 && choice != 1 && choice != 2);

		switch (choice) {
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
	}
	return;
}

void Menu::superExacta(string pattern) {
	system("clear");
	int id;
	string ind;
	std::stringstream sstm;
	set<string> ruas;
	vector<Supermarket*> tmp;
	struct timeval st, et;

	cout << "pesquisa exacta de supermercados com o texto \"" << pattern
			<< "\".\n";

	/*  // correr 5 vezes e fazer a média (quando é muito rápido)
	 int i, num_runs = 5;

	 gettimeofday(&st,NULL);
	 for (i=0; i<num_runs; i++) {
	 bubble(a,n);
	 }
	 gettimeofday(&et,NULL);

	 int elapsed = (((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec)) / num_runs;
	 */

	gettimeofday(&st, NULL);
	vector<int> ids = numStringMatching("supermarkets.txt", pattern);
	gettimeofday(&et, NULL);
	int elapsed = ((et.tv_sec - st.tv_sec) * 1000000)
			+ (et.tv_usec - st.tv_usec);

	for (unsigned int i = 0; i < ids.size(); i++) {
		tmp.push_back(supermarkets[ids.at(i) - 1]);
	}

	cout << "\n\n\n\n\n";
	if (tmp.size()) {

		cout << "\tSupermercados encontrados que correspondem à pesquisa de "
				<< pattern << ":\n\n";
		cout << "\n********************************************\n\n";
		for (unsigned int i = 0; i < tmp.size(); i++) {
			cout << "\t" << i + 1 << ")\n";
			cout << "\t\tID: " << tmp.at(i)->getId() << "\n";
			cout << "\t\tName: " << tmp.at(i)->getName() << "\n";
			cout << "\t\tNode ID: " << tmp.at(i)->getNode() << "\n\n";
			if ((ruas = getRoadByNode(tmp.at(i)->getNode())).size()) {
				cout << "\n\t\t\truas do cruzamento:\n";
				for (set<string>::iterator it = ruas.begin(); it != ruas.end();
						it++) {
					//for (unsigned int j = 0; j < ruas.size(); j++) {

					if (*it == "") {
						cout << "\tRua sem nome" << endl;
					} else {
						cout << "\t\t" << *it << "\n";
					}
				}

			} else {

				cout << "\t\truas do cruzamento nao encontradas\n";
			}

			cout << "\n********************************************\n\n";
		}
		//cin.clear();
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\tadicionar como supermercado da rota:\n";
		cin >> id;
		//	getline(cin, ind);
		//sstm.clear();
		//sstm.str(ind);
		//sstm >> id;
		adicionaSuper(tmp.at(id - 1)->getId());
//		for (unsigned int i = 0; i < tmp.size(); i++) {
//			if (tmp.at(i)->getId() == id) {
//				adicionaSuper(id);
//				break;
//			}
//		}

	}

	if (!tmp.size()) {
		cout << "\n\n\n\tNão foram encontrados supermercados com " << pattern
				<< " !\n";

	}

	cout << endl << endl;
	cout << "\tA pesquisa exacta de supermercados demorou " << elapsed
			<< " microsegundos / " << elapsed / 1000 << " milisegundos / "
			<< elapsed / 1000000 << " segundos." << endl;

	cout << "\n\tprima uma tecla para continuar" << endl;
	getchar();
	return;
}

void Menu::superApprox(string pattern) {
	system("clear");
	int id;
	string ind;
	std::stringstream sstm;
	vector<std::pair<float, Supermarket *> > tmp;
	cout << "\tpesquisa aproximada de supermercados com o texto \"" << pattern
			<< "\".\n";

	set<string> ruas;
	struct timeval st, et;
	//vector<Supermarket*> tmp;
	float min = 999;
	float max = 0;

	gettimeofday(&st, NULL);

	vector<float> val = numApproximateStringMatching("supermarkets.txt",
			pattern);
	gettimeofday(&et, NULL);
	int elapsed = ((et.tv_sec - st.tv_sec) * 1000000)
			+ (et.tv_usec - st.tv_usec);

	for (unsigned int i = 0; i < val.size(); i++) {
		if (val.at(i) > max) {
			max = val.at(i);
		}
	}
	cout << "\n\n\tMINIMUM:" << max;

	set<Supermarket*> tmpset;
	for (float i = 0; i < val.size(); i++) {

		if (val.at(i) > 0.66 || val.at(i) == max)
			tmp.push_back(
					pair<float, Supermarket *>(val.at(i), supermarkets.at(i)));
		//tmp.push_back(supermarkets.at(i));
	}
	std::sort(tmp.begin(), tmp.end(), sortPairS);
	cout << "\n\n\n\n\n";
	if (tmp.size() >= 1) {

		cout << "\tSupermercados encontrados que correspondem à pesquisa de "
				<< pattern << ":\n\n";
		cout << "\n********************************************\n\n";
		for (unsigned int i = 0; i < tmp.size(); i++) {
			cout << "\t" << i + 1 << ")\tparecença=" << tmp.at(i).first << "\n";
			cout << "\tID: " << (tmp.at(i).second)->getId() << "\n";
			cout << "\tName: " << (tmp.at(i).second)->getName() << "\n";
			cout << "\tNode ID: " << (tmp.at(i).second)->getNode() << "\n\n";
			if ((ruas = getRoadByNode((tmp.at(i).second)->getNode())).size()) {
				cout << "\n\t\truas do cruzamento:\n";
				for (set<string>::iterator it = ruas.begin(); it != ruas.end();
						it++) {
					tmpset.insert((tmp.at(i).second));

					if (*it == "") {
						cout << "\tRua sem nome" << endl;
					} else {
						cout << "\t\t" << *it << "\n";
					}
				}

			} else {

				cout << "\t\truas do cruzamento nao encontradas\n";
			}

			cout << "\n********************************************\n\n";
		}
		cin.clear();
		cout << "\t\tadicionar como supermercado da rota:\n";
		//	cin >> id;
		getline(cin, ind);
		sstm.clear();
		sstm.str(ind);
		sstm >> id;
		cout << "antes\n";
		adicionaSuper((tmp.at(id - 1).second)->getId());
		cout << "após\n";
//		for (unsigned int i = 0; i < tmp.size(); i++) {
//			if (tmp.at(i)->getId() == id) {
//				adicionaSuper(id);
//				break;
//			}
//		}
	}

	if (!tmp.size()) {
		cout << "\n\n\n\tNão foram encontrados supermercados com " << pattern
				<< " !\n";
	}

	cout << endl << endl;
	cout << "\tA pesquisa aproximada de supermercados demorou " << elapsed
			<< " microsegundos / " << elapsed / 1000 << " milisegundos / "
			<< elapsed / 1000000 << " segundos" << endl;

	cout << "\n\tprima uma tecla para continuar" << endl;
	getchar();
	return;
}

void Menu::ruaExacta(string pattern) {
	system("clear");
	int id;
	string ind;
	std::stringstream sstm;
	set<string> supermercados;
	vector<Road*> tmp;
	struct timeval st, et;

	cout << "\tpesquisa exacta de ruas com o texto \"" << pattern << "\".\n";
	std::stringstream sstmm;
	sstmm << "roads" << getMap() << ".txt";
	string tmp2 = sstmm.str();

	gettimeofday(&st, NULL);
	vector<int> ids = numStringMatchingRoad(tmp2, pattern);
	gettimeofday(&et, NULL);
	int elapsed = ((et.tv_sec - st.tv_sec) * 1000000)
			+ (et.tv_usec - st.tv_usec);

	for (unsigned int i = 0; i < ids.size(); i++) {
		tmp.push_back(roads[ids.at(i) - 1]);
	}

	cout << "\n\n\n\n\n";
	if (tmp.size()) {

		cout << "\tRuas encontradas que correspondem à pesquisa exacta de "
				<< pattern << ":\n\n";
		cout << "\n********************************************\n\n";
		for (unsigned int i = 0; i < tmp.size(); i++) {
			cout << "\t" << i + 1 << ")\n";
			cout << "\tID: " << tmp.at(i)->getId() << "\n";
			cout << "\tName: " << tmp.at(i)->getName() << "\n";

			if ((supermercados = getSupermarketByRoadId(tmp.at(i)->getId())).size()) {
				cout << "\n\t\tsupermercados nesta rua:\n";
				for (set<string>::iterator it = supermercados.begin();
						it != supermercados.end(); it++) {
					cout << "\t" << *it << "\n";
				}
			} else {

				cout
						<< "\n\tNão foi encontrado nenhum supermercado nesta rua\n";
			}

			cout << "\n********************************************\n\n";
		}

		while (!(id > 0 && id <= (int) tmp.size())) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\t\tadicionar como paragem da rota:\n";
			//	cin >> id;
			getline(cin, ind);
			sstm.clear();
			sstm.str(ind);
			sstm >> id;

		}
		adicionaParagem(tmp.at(id - 1)->getId());

//		for (unsigned int i = 0; i < tmp.size(); i++) {
//			if (tmp.at(i)->getId() == id) {
//				adicionaParagem(id);
//				break;
//			}
//		}
	}

	if (!tmp.size()) {
		cout << "\n\n\n\tNão foi encontrada qualquer rua" << pattern << " !\n";

	}

	cout << endl << endl;
	cout << "\tA pesquisa exacta de ruas demorou " << elapsed
			<< " microsegundos / " << elapsed / 1000 << " milisegundos / "
			<< elapsed / 1000000 << " segundos" << endl;
	cout << "\n\tprima uma tecla para continuar" << endl;
	getchar();
	return;
}

void Menu::ruaApprox(string pattern) {
	system("clear");
	int id = 0;
	string ind;
	std::stringstream sstm;
	set<string> supermercados;
	vector<std::pair<float, Road *> > tmp;
	float min = 999;
	float max = 0;
	struct timeval st, et;

	cout << "\tpesquisa aproximada de ruas com o texto \"" << pattern
			<< "\".\n";

	std::stringstream sstmm;
	sstmm << "roads" << getMap() << ".txt";
	string tmp2 = sstmm.str();
	gettimeofday(&st, NULL);

	vector<float> val = numApproximateStringMatchingRoad(tmp2, pattern);
	gettimeofday(&et, NULL);
	int elapsed = ((et.tv_sec - st.tv_sec) * 1000000)
			+ (et.tv_usec - st.tv_usec);

	set<Road*> tmpset;
	for (float i = 0; i < val.size(); i++) {

		if (val.at(i) > max) {
			max = val.at(i);
		}
	}
	cout << "\n\n\tMINIMUM:" << max;

	for (float i = 0; i < val.size(); i++) {
		if (val.at(i) > 0.66 || val.at(i) == max)

			tmp.push_back(pair<float, Road *>(val.at(i), roads.at(i)));
	}
	std::sort(tmp.begin(), tmp.end(), sortPair);
	cout << "\n\n\n\n\n";

	if (tmp.size()) {

		cout << "\tRuas encontradas que correspondem à pesquisa aproximada de "
				<< pattern << ":\n\n";
		cout << "\n********************************************\n\n";
		for (unsigned int i = 0; i < tmp.size(); i++) {
			cout << "\t" << i + 1 << ")\tparecença=" << tmp.at(i).first << "\n";
			cout << "\tID: " << (tmp.at(i).second)->getId() << "\n";
			cout << "\tName: " << (tmp.at(i).second)->getName() << "\n";

			if ((supermercados = getSupermarketByRoadId(
					(tmp.at(i).second)->getId())).size()) {
				cout << "\n\t\tsupermercados nesta rua:\n";
				for (set<string>::iterator it = supermercados.begin();
						it != supermercados.end(); it++) {
					tmpset.insert((tmp.at(i).second));
					cout << "\t" << *it << "\n";
				}
			} else {

				cout
						<< "\n\tNão foi encontrado nenhum supermercado nesta rua\n";
			}

			cout << "\n********************************************\n\n";
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\t\tadicionar como paragem da rota:\n";

		getline(cin, ind);
		sstm.clear();
		sstm.str(ind);
		sstm >> id;
		if ((int) id)
			adicionaParagem((tmp.at(id - 1).second)->getId());

	}

	if (!tmp.size()) {
		cout << "\n\n\n\tNão foram encontradas ruas com " << pattern << " !\n";

	}

	cout << endl << endl;
	cout << "\tA pesquisa aproximada de ruas demorou " << elapsed

	<< " microsegundos / " << elapsed / 1000 << " milisegundos / "
			<< elapsed / 1000000 << " segundos" << endl;
	cout << "\n\tprima uma tecla para continuar" << endl;
	getchar();
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
		case 0:

			exit(0);

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

	char choiceChar = 'Z';
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

	cout << "o algoritmo mais rápido a calcular é o "
			<< (compareStruct.biMethod.totalMillis
					< compareStruct.dOdMethod.totalMillis ?
					"bidireccional" : "Dijkstra of Dijkstras") << endl;
	cout << "DoD: " << compareStruct.dOdMethod.totalMillis << " ms\n";
	cout << "bi: " << compareStruct.biMethod.totalMillis << " ms\n";
	cout << "FW: " << compareStruct.fwMethod.totalMillis << " ms\n\n\n";

//	int minWeight = compareStruct.biMethod.totalWeight;
//	if (compareStruct.dOdMethod.totalWeight < minWeight) {
//		minWeight = compareStruct.dOdMethod.totalWeight;
//	}
//	if (compareStruct.fwMethod.totalWeight < minWeight) {
//		minWeight = compareStruct.fwMethod.totalWeight;
//		cout
//				<< "o algoritmo que devolve o percurso total menor é o Floyd-Warshall"
//				<< endl;
//	}
//	cout << "o algoritmo que devolve o percurso total menor é o "
//			<< (compareStruct.biMethod.totalWeight
//					< compareStruct.dOdMethod.totalWeight ?
//					"bidireccional" : "Dijkstra of Dijkstras") << endl;
//	cout << "DoD: " << compareStruct.dOdMethod.totalWeight << " m\n";
//	cout << "bi: " << compareStruct.biMethod.totalWeight << " m\n";
//	cout << "FW: " << compareStruct.fwMethod.totalWeight << " m\n\n\n";

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
	cout << "o algoritmo que devolve o percurso total com menos nós é o "
			<< (compareStruct.biMethod.totalNodes
					< compareStruct.dOdMethod.totalNodes ?
					"bidireccional" : "Dijkstra of Dijkstras") << endl;
	cout << "DoD: " << compareStruct.dOdMethod.totalNodes << " nodes\n";
	cout << "bi: " << compareStruct.biMethod.totalNodes << " nodes\n";
	cout << "FW: " << compareStruct.fwMethod.totalNodes << " nodes\n\n\n";

	do {
		cout << "\nprima C para continuar\n";
		cin >> choiceChar;
	} while (choiceChar != 'c' && choiceChar != 'C');

	textRoute(); //para escolher ver caminhos

	return;
}

void Menu::fw(double &total, bool toPrint) {
//loadFiles(numNodes);

	int totaltotal = 0;
	vector<long long> route;

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

				supermarketLocation.clear();

				stops.clear();
				stops = trucks.at(t)->getStops();

				supermarketLocation.push_back(supermarkets.at(s)->getNode());

				route = getFW(supermarkets.at(s)->getNode(),
						trucks.at(t)->getStops(), total);

				completeRoute.insert(completeRoute.end(), route.begin(),
						route.end());
				LastStop = route.at(route.size() - 1);
				route = getFW(LastStop, supermarketLocation, total);
				completeRoute.insert(completeRoute.end(), route.begin(),
						route.end() - 1);

				cout << "\nnumber of nodes in path:" << completeRoute.size()
						<< endl;

				write(STDOUT_FILENO, "\n\n", 2);

				cout << "rota " << t + 1 << "/" << trucks.size()
						<< " do supermercado " << s + 1 << "/"
						<< supermarkets.size() << "\n";

				if (toPrint)
					printRoute(completeRoute, s, t);

				//	cout << "\ntotal=" << total << endl;
				totaltotal += total;
				compareStruct.fwMethod.routes.push_back(completeRoute);
				compareStruct.fwMethod.totalNodes += completeRoute.size() / 2;
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
//	cout << "\ntotal das rotas =" << totaltotal << " m" << endl;
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
						trucks.at(t)->getStops(), total);
				completeRoute.insert(completeRoute.end(), route.begin(),
						route.end());

				LastStop = route.at(route.size() - 1);

				route = dijkstraOfDijkstras(LastStop, supermarketLocation,
						total);

				completeRoute.insert(completeRoute.end(), route.begin(),
						route.end() - 1);

				cout << "\nnumber of nodes in path:" << completeRoute.size()
						<< endl;

				write(STDOUT_FILENO, "\n\n", 2);

				cout << "rota " << t + 1 << "/" << trucks.size()
						<< " do supermercado " << s + 1 << "/"
						<< supermarkets.size() << "\n";

				if (toPrint)
					printRoute(completeRoute, s, t);

				//	cout << "\ntotal=" << total << endl;
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
//	cout << "\ntotal das rotas =" << totaltotal << " m" << endl;
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

void Menu::printRouteString(vector<long long> & completeRoute, int s, int t) {
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

		if (completeRoute.at(i) == this->getSource()) {
			for (unsigned int i = 0; i < supermarkets.size(); i++) {
				if (supermarkets.at(i)->getNode() == completeRoute.at(i)) {
					cout << "\n# " << supermarkets.at(i)->getName() << " # \n";
				}
			}

			count = 1;

		} else if (isStop(completeRoute.at(i))) {

			for (unsigned int j = 0;
					j < this->trucks.at(0)->getClients().size(); j++) {

				if (completeRoute.at(i)
						== trucks.at(0)->getClients().at(j)->getNode()) {

					cout << "\n # "
							<< trucks.at(0)->getClientsName(completeRoute.at(i))
							<< " # \n";
//					cout << "\n # "
//							<< trucks.at(0)->getClients().at(j)->getName()
//							<< " # \n";
				}

			}

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
						trucks.at(t)->getStops(), total);

				completeRoute.insert(completeRoute.end(), route.begin(),
						route.end() - 1);

				cout << "\nnumber of nodes in path:" << completeRoute.size()
						<< endl;

				write(STDOUT_FILENO, "\n\n", 2);

				cout << "rota " << t + 1 << "/" << trucks.size()
						<< " do supermercado " << s + 1 << "/"
						<< supermarkets.size() << "\n";

				if (toPrint)
					printRoute(completeRoute, s, t);
				//	cout << "\ntotal=" << total << endl;

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
//cout << "\ntotal das rotas =" << totaltotal << " m" << endl;
	compareStruct.biMethod.totalWeight = totaltotal;
	compareStruct.biMethod.totalMillis = nTimeElapsed;
	cout << "\n";
	return;
}

void Menu::gvRouteFW() {
//loadFiles(numNodes);	//one truck at a time
	double total = 0;
	long long id;
	cout << "\nprima uma tecla para continuar\n";
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
	vector<long long> completeRoute;
	vector<long long> supermarketLocation;

	vector<long long> stops = trucks.at(id - 1)->getStops();

	supermarketLocation.push_back(supermarkets.at(supermarket)->getNode());

	route = getFW(supermarkets.at(supermarket)->getNode(),
			trucks.at(id - 1)->getStops(), total);
	completeRoute.insert(completeRoute.end(), route.begin(), route.end());
	long long LastStop = route.at(route.size() - 1);
	route = getFW(LastStop, supermarketLocation, total);
	completeRoute.insert(completeRoute.end(), route.begin(), route.end() - 1);

	cout << "mais um pouco\n";

	viewGraph(true, id, completeRoute);

	return;
}

void Menu::gvRouteBi() {
	bool found = false;
	long long id;
	int totaltotal = 0;

	double total = 0;
	vector<long long> completeRoute;
	vector<long long> route;
	vector<long long> routeBack;
	vector<long long> supermarketLocation;
	vector<long long> stops;

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
	completeRoute.clear();
	route.clear();
	routeBack.clear();
	supermarketLocation.clear();
	stops.clear();

	stops = trucks.at(id - 1)->getStops();

	supermarketLocation.push_back(supermarkets.at(supermarket)->getNode());

	route = graph.getOurRoute(supermarkets.at(supermarket)->getNode(),
			trucks.at(id - 1)->getStops(), total);

	completeRoute.insert(completeRoute.end(), route.begin(), route.end() - 1);

	cout << "mais um pouco\n";

	viewGraph(true, id, completeRoute);

	return;
}

void Menu::gvRouteDoD() {
	long long id;
	double total = 0;
	bool found = false;
	vector<long long> completeRoute;
	vector<long long> route;
	vector<long long> routeBack;
	vector<long long> supermarketLocation;
	vector<long long> stops;

	long long LastStop;

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

	stops = trucks.at(id - 1)->getStops();

	supermarketLocation.push_back(supermarkets.at(supermarket)->getNode());

	route = dijkstraOfDijkstras(supermarkets.at(supermarket)->getNode(),
			trucks.at(id - 1)->getStops(), total);
	completeRoute.insert(completeRoute.end(), route.begin(), route.end());

	LastStop = route.at(route.size() - 1);

	route = dijkstraOfDijkstras(LastStop, supermarketLocation, total);

	completeRoute.insert(completeRoute.end(), route.begin(), route.end() - 1);

//}	//fim verificacao cliente truck super

	if (completeRoute.size() == 0) {
		cout << "rota vazia\n";
		return;
	}

	cout << "mais um pouco\n";

	viewGraph(true, id, completeRoute);

	return;
}

void Menu::gvRouteDoDString() {
	long long id;
	double total = 0;
	bool found = false;
	vector<long long> completeRoute;
	vector<long long> route;
	vector<long long> routeBack;
	vector<long long> supermarketLocation;
	vector<long long> stops;

	long long LastStop;

//	do {
	//	cout << "qual a rota?\n";
	//cin >> id;
	//for (unsigned int i = 0; i < trucks.size(); i++) {
	//if (trucks.at(0)->getId() == id) {
	//found = true;
	//	break;
	//	}
	//	}
	//	if (found == false) {
	//	cout << "nao existe essa rota.\n qual a rota?\n";
	//	}
	//} while (found == false);
	system("clear");
	write(STDOUT_FILENO, "\n\nem processamento\n", 19);

	long long supermarket = this->getSource();//supermercado onde esta o camiao

	stops = trucks.at(0)->getStops();

	supermarketLocation.push_back(supermarket);

	route = dijkstraOfDijkstras(supermarket, trucks.at(0)->getStops(), total);
	completeRoute.insert(completeRoute.end(), route.begin(), route.end());

	LastStop = route.at(route.size() - 1);

	route = dijkstraOfDijkstras(LastStop, supermarketLocation, total);

	completeRoute.insert(completeRoute.end(), route.begin(), route.end() - 1);

//}	//fim verificacao cliente truck super

	if (completeRoute.size() == 0) {
		cout << "rota vazia\n";
		return;
	}

	cout << "mais um pouco\n";
	cout << "00\n";
	viewGraph(true, 1, completeRoute); //para truck 0
	cout << "99\n";
	return;
}

void Menu::loadFiles(int numNodes) {
	Files fl;

	nodes = fl.loadNodes(numNodes);
	cout << nodes.size() << " NODES LOADED" << endl;

	connections = fl.loadConnections(numNodes);
	cout << connections.size() << " EDGES LOADED" << endl;

	roads = fl.loadRoads(numNodes);
	cout << roads.size() << " ROADS LOADED" << endl;

	supermarkets = fl.loadSupermarkets();
	cout << supermarkets.size() << " SUPERMARKETS LOADED" << endl;

	clients = fl.loadClients();
	cout << clients.size() << " CLIENTS LOADED" << endl;

	trucks = fl.loadTruck(clients);
	cout << trucks.size() << " TRUCKS LOADED" << endl;

//	cout << "\nprima uma tecla para continuar\n";
//	getchar();
	return;
}

void Menu::viewGraph(bool toSupermarket, long long idtruck,
		vector<long long> route) {
	int numNodes = 1, width = 1000, height = 498;

	switch (graph.getNumVertex()) {
	case 649:
		numNodes = 1;
		width = 600;
		height = 535;
		break;
	case 1329:
		numNodes = 2;
		width = 862;
		height = 793;
		break;
	case 2543:
		numNodes = 3;
		width = 864;
		height = 680;
		break;
	case 3980:
		numNodes = 4;
		width = 1046;
		height = 789;
		break;
	case 57480:
		numNodes = 5;
		width = 1366;
		height = 907;
		break;
	case 145980:
		numNodes = 6;
		width = 1366;
		height = 904;
		break;
	default:
		break;
	}

	std::stringstream sstm;
	sstm << IMGPRE << numNodes << IMGEXT;
	string imageName = sstm.str();

	gv = new GraphViewer(width, height, false);

	gv->setBackground(imageName);
	gv->createWindow(width, height);

	gv->defineEdgeCurved(false);

	gv->defineEdgeColor("black");

	gv->defineVertexIcon("point_small.png");

//	gv->defineVertexColor("BLUE");

	bool client = false;

	long long edgecount = 0;

	for (unsigned int i = 0; i < route.size(); i++) {
		client = false;
		unsigned int j = 0;
		write(STDOUT_FILENO, ".", 1);

		for (j = 0; j < nodes.size(); j++) {

			if (nodes.at(j)->getId() == route.at(i))
				;
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

		gv->addNode(route.at(i), nodes.at(j)->getX() - 450,
				nodes.at(j)->getY() - 70);

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
		double & total) {
	long long lastNode;
	long long source = firstNode;
	vector<long long> pathOrder;
	pathOrder.push_back(firstNode);
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
		}	//e poe em next a stop seguinte mais perto (pontoSeguinte)

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
		lastNode = stops.at(0);

		stops.erase(stops.begin() + next);

//e apaga da lista de paragens por visitar o pontoSeguinte
	}

//cout<<"\ncaminho totalFW="<<total/pow(10,8)<<"\n";

	pathOrder.push_back(lastNode);

	return pathOrder;

}

vector<long long> Menu::dijkstraOfDijkstras(long long firstNode,
		vector<long long> stops, double &total) {
	stack<long long> dijkstraLeg;
	vector<long long> leg;
	double parcial, tmp = 0;
	long long source = firstNode;
	vector<long long> pathOrder;
	long long next = source;
	double min;
	int k;
	cout << "DOD_000\n";
	cout << "next=" << next << endl;

	if (!isNodeinMap(next)) {
		cout << "supermercado não consta deste mapa\n";
		return pathOrder;
	}
	cout << (graph.getVertex(next))->getDist() << endl;
	pathOrder.push_back((graph.getVertex(next))->getInfo());
	cout << "DOD_010\n";
	while (stops.size() > 0) {
		cout << "DOD_020\n";
		k = 0;
		min = INT_INFINITY;
		parcial = 0;
//vai determinar a etapa
		cout << "DOD_021\n";
		graph.dijkstraShortestPath(source, parcial);//a partir do inicio desta etapa distancias para tudo
		cout << "DOD_022\n";
		for (unsigned int i = 0; i < stops.size(); i++) {//ver qual a stop mais perto do inicio da etapa actual
			cout << "DOD_023\n";
			if ((tmp = graph.getVertex(stops.at(i))->getDist()) < min) {
				cout << "DOD_024\n";
				min = tmp;
				next = stops.at(i);
				k = i;
			}
			cout << "DOD_025\n";
		}
		cout << "DOD_026\n";
//sai com next stop actualizada
		total += parcial;
		leg = graph.getPath(source, next);//vai buscar o caminho da etapa agora calculada e a seguir insere no caminho total
		pathOrder.insert(pathOrder.end(), leg.begin(), leg.end());
		cout << "DOD_027\n";
		if (stops.size() > 1) {
			cout << "DOD_028\n";
			source = (graph.getVertex(next))->getInfo(); //actualiza o inicio da proxima etapa
			cout << "DOD_029\n";
			stops.erase(stops.begin() + k);
		} else {
			cout << "DOD_030\n";
			graph.dijkstraShortestPath(stops.at(0), parcial);
			leg = graph.getPath(stops.at(0), firstNode); //vai buscar o caminho da etapa agora calculada e a seguir insere no caminho total
			pathOrder.insert(pathOrder.end(), leg.begin(), leg.end());
			stops.erase(stops.begin());
			total += parcial;
			cout << "DOD_031\n";
			//break;
		}
		cout << "DOD_032\n";
	}
	cout << "DOD_040\n";
	return pathOrder;
}

double Menu::euclideanDist(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void Menu::crossExacta() {
	string name1, name2, ind;
	int id, op = 0;
	int ii = 0;
	std::stringstream sstm, sstmm;
	set<string> supermercados;
	set<long long> tmpsupers, tmpsupers1, tmpsupers2;
	vector<Road*> tmp1, tmp2;
	float min = 999, max = 0;
	struct timeval st, et;
	set<Road*> tmpset1, tmpset2;
	bool not1 = true, not2 = true;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\tPesquisa exacta de supermercados em cruzamentos\n\n";
	cout << "\tnome de uma rua: ";
	getline(cin, name1);
	cout << "\tnome de outra rua: ";
	getline(cin, name2);
	cout << "\n\n\n\n\n";

	sstmm << "roads" << getMap() << ".txt";
	string tempstring = sstmm.str();

	vector<int> ids = numStringMatchingRoad(tempstring, name1);

	for (unsigned int i = 0; i < ids.size(); i++) {
		tmp1.push_back(roads[ids.at(i) - 1]);
	}

	if (tmp1.size()) {
		for (unsigned int i = 0; i < tmp1.size(); i++) {
			if ((supermercados = getSupermarketByRoadId(tmp1.at(i)->getId())).size()) {
				for (set<string>::iterator it = supermercados.begin();
						it != supermercados.end(); it++) {
					tmpset1.insert(tmp1.at(i));
					tmpsupers1.insert(tmp1.at(i)->getId());
					not1 = false;
				}
			}
		}

	}

	ids = numStringMatchingRoad(tempstring, name2);

	for (unsigned int i = 0; i < ids.size(); i++) {
		tmp2.push_back(roads[ids.at(i) - 1]);
	}

	if (tmp2.size()) {

		for (unsigned int i = 0; i < tmp2.size(); i++) {

			if ((supermercados = getSupermarketByRoadId(tmp2.at(i)->getId())).size()) {

				for (set<string>::iterator it = supermercados.begin();
						it != supermercados.end(); it++) {

					tmpset2.insert(tmp2.at(i));

					tmpsupers2.insert(tmp2.at(i)->getId());

					not2 = false;
				}
			}
		}

	}

	for (set<Road*>::iterator itr1 = tmpset1.begin(); itr1 != tmpset1.end();
			itr1++) {

		for (set<Road*>::iterator itr2 = tmpset2.begin(); itr2 != tmpset2.end();
				itr2++) {

			if (checkCross((**itr1).getId(), (**itr2).getId())) {
				tmpsupers.insert((**itr2).getId());
				//	cout << "encontrado supermercado no cruzamento com id="
				//		<< (**itr2).getId() << endl;
			}

		}
	}

	if (tmp1.size() && tmp2.size()) {
		//continue;
	} else if (!tmp1.size() && !tmp2.size()) {
		cout << "\n\n\n\tNão foram encontradas ruas com " << name1 << "nem com "
				<< name2 << " !\n";
	} else {
		if (!tmp1.size()) {
			cout << "\n\n\n\tNão foram encontradas ruas com " << name1
					<< " !\n";
		} else {
			cout << "\n\n\n\tNão foram encontradas ruas com " << name2
					<< " !\n";
		}
	}

	if (not1 && not2) {

		cout << "\n\n\n\tNão foram encontrados supermercados em " << name1
				<< "nem em " << name2 << " !\n";

	} else if (!(not1 && not2)) {
//		if (!tmpsupers.size()) {
//			for (set<long long>::iterator its1 = tmpsupers1.begin();
//					its1 != tmpsupers1.end(); its1++) {
//				tmpsupers.insert(*its1);
//			}
//			for (set<long long>::iterator its2 = tmpsupers2.begin();
//					its2 != tmpsupers2.end(); its2++) {
//				tmpsupers.insert(*its2);
//			}
//		}

		for (set<long long>::iterator its = tmpsupers.begin();
				its != tmpsupers.end(); its++) {

			cout << "\n\t\tsupermercados nas ruas do cruzamento de " << name1
					<< " com " << name2 << ":\n\n";
			supermercados = getSupermarketByRoadId(*its);			//
			for (set<string>::iterator s = supermercados.begin();
					s != supermercados.end(); s++) {
				ii++;
				cout << "\t" << ii + 1 << ")\n";
				cout << "\tID: " << *its << "\n";
				cout << "\t\t" << *s << "\n";
			}
		}

	} else {
		if (not1) {
			cout << "\n\n\n\tNão foram encontrados supermercados em " << name1
					<< " !\n";
		} else {
			cout << "\n\n\n\tNão foram encontrados supermercados em " << name2
					<< " !\n";
		}
	}

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\t\tadicionar ID como supermercado da rota:\n";

	getline(cin, ind);
	sstm.clear();
	sstm.str(ind);
	sstm >> id;

	for (unsigned int i = 0; i < supermarkets.size(); i++) {
		if (supermarkets.at(i)->getId() == id) {
			adicionaSuper(id - 1);
			break;
		}
	}

	cout << "\n\tprima uma tecla para continuar" << endl;
	getchar();
	return;

}

void Menu::crossApprox() {
	string name1, name2, ind;
	int id, op = 0;
	int ii = 0;
	std::stringstream sstm, sstmm;
	set<string> supermercados;
	vector<std::pair<float, Road *> > tmp1, tmp2;
	set<long long> tmpsupers, tmpsupers1, tmpsupers2;
//	vector<Road*> tmp1, tmp2;
	float min = 999, max = 0;
	struct timeval st, et;
	set<Road*> tmpset1, tmpset2;
	bool not1 = true, not2 = true;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\tPesquisa aproximada de supermercados em cruzamentos\n\n";
	cout << "\tnome de uma rua: ";
	getline(cin, name1);
	cout << "\tnome de outra rua: ";
	getline(cin, name2);
	cout << "\n\n\n\n\n";

	sstmm << "roads" << getMap() << ".txt";
	string tempstring = sstmm.str();
	gettimeofday(&st, NULL);
	vector<float> val = numApproximateStringMatchingRoad(tempstring, name1);
	gettimeofday(&et, NULL);

	for (float i = 0; i < val.size(); i++) {
		if (val.at(i) > max) {
			max = val.at(i);
		}
	}

	for (float i = 0; i < val.size(); i++) {
		if (val.at(i) > 0.66 || val.at(i) == max)
			tmp1.push_back(pair<float, Road *>(val.at(i), roads.at(i)));
		//tmp1.push_back(roads.at(i));
	}
	std::sort(tmp1.begin(), tmp1.end(), sortPair);
	if (tmp1.size()) {
		for (unsigned int i = 0; i < tmp1.size(); i++) {
			if ((supermercados = getSupermarketByRoadId(
					(tmp1.at(i).second)->getId())).size()) {
				for (set<string>::iterator it = supermercados.begin();
						it != supermercados.end(); it++) {
					tmpset1.insert((tmp1.at(i).second));
					tmpsupers1.insert((tmp1.at(i).second)->getId());
					not1 = false;
				}
			}
		}

	}

	gettimeofday(&st, NULL);
	val = numApproximateStringMatchingRoad(tempstring, name2);
	gettimeofday(&et, NULL);

	for (float i = 0; i < val.size(); i++) {
		if (val.at(i) > max) {
			max = val.at(i);
		}
	}

	for (float i = 0; i < val.size(); i++) {
		if (val.at(i) > 0.66 || val.at(i) == max)
			tmp2.push_back(pair<float, Road *>(val.at(i), roads.at(i)));
		//tmp2.push_back(roads.at(i));
	}
	std::sort(tmp2.begin(), tmp2.end(), sortPair);
	if (tmp2.size()) {
		for (unsigned int i = 0; i < tmp2.size(); i++) {
			if ((supermercados = getSupermarketByRoadId(
					(tmp2.at(i).second)->getId())).size()) {
				for (set<string>::iterator it = supermercados.begin();
						it != supermercados.end(); it++) {
					tmpset2.insert((tmp2.at(i).second));
					tmpsupers2.insert((tmp2.at(i).second)->getId());
					not2 = false;
				}
			}
		}

	}

	for (set<Road*>::iterator itr1 = tmpset1.begin(); itr1 != tmpset1.end();
			itr1++) {

		for (set<Road*>::iterator itr2 = tmpset2.begin(); itr2 != tmpset2.end();
				itr2++) {

			if (checkCross((**itr1).getId(), (**itr2).getId())) {
				tmpsupers.insert((**itr2).getId());
				//	cout << "encontrado supermercado no cruzamento com id="
				//		<< (**itr2).getId() << endl;
			}

		}
	}

	if (tmp1.size() && tmp2.size()) {
		//continue;
	} else if (!tmp1.size() && !tmp2.size()) {
		cout << "\n\n\n\tNão foram encontradas ruas com " << name1 << "nem com "
				<< name2 << " !\n";
	} else {
		if (!tmp1.size()) {
			cout << "\n\n\n\tNão foram encontradas ruas com " << name1
					<< " !\n";
		} else {
			cout << "\n\n\n\tNão foram encontradas ruas com " << name2
					<< " !\n";
		}
	}

	if (not1 && not2) {

		cout << "\n\n\n\tNão foram encontrados supermercados em " << name1
				<< "nem em " << name2 << " !\n";

	} else if (!(not1 && not2)) {
//		if (!tmpsupers.size()) {
//			for (set<long long>::iterator its1 = tmpsupers1.begin();
//					its1 != tmpsupers1.end(); its1++) {
//				tmpsupers.insert(*its1);
//			}
//			for (set<long long>::iterator its2 = tmpsupers2.begin();
//					its2 != tmpsupers2.end(); its2++) {
//				tmpsupers.insert(*its2);
//			}
//		}

		for (set<long long>::iterator its = tmpsupers.begin();
				its != tmpsupers.end(); its++) {

			cout << "\n\t\tsupermercados nas ruas do cruzamento de " << name1
					<< " com " << name2 << ":\n\n";
			supermercados = getSupermarketByRoadId(*its);			//
			for (set<string>::iterator s = supermercados.begin();
					s != supermercados.end(); s++) {
				ii++;
				cout << "\t" << ii + 1 << ")\n";
				cout << "\tID: " << *its << "\n";
				cout << "\t\t" << *s << "\n";
			}
		}

	} else {
		if (not1) {
			cout << "\n\n\n\tNão foram encontrados supermercados em " << name1
					<< " !\n";
		} else {
			cout << "\n\n\n\tNão foram encontrados supermercados em " << name2
					<< " !\n";
		}
	}

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\t\tadicionar ID como supermercado da rota:\n";

	getline(cin, ind);
	sstm.clear();
	sstm.str(ind);
	sstm >> id;

	for (unsigned int i = 0; i < supermarkets.size(); i++) {
		if (supermarkets.at(i - 1)->getId() == id) {
			adicionaSuper(id - 1);
			break;
		}
	}

	cout << "\n\tprima uma tecla para continuar" << endl;
	getchar();
	return;

}

set<string> Menu::getRoadByNode(long long node) {
	vector<long long> tmp;
	std::set<string> ruas;
	for (unsigned int i = 0; i < connections.size(); i++) {
		if (connections.at(i)->getNode1() == node
				|| connections.at(i)->getNode2() == node) {
			tmp.push_back(connections.at(i)->getRoadId());
		}
	}

	for (unsigned int j = 0; j < tmp.size(); j++) {

		for (unsigned int k = 0; k < roads.size(); k++) {
			if (roads.at(k)->getId() == tmp.at(j)) {
				ruas.insert(roads.at(k)->getName());

			}
		}
	}
	return ruas;
}

bool Menu::checkCross(long long id1, long long id2) {
//	cout<<"125957_id="<<connections.at(125956)->getRoadId()<<"\tnode1="<<connections.at(125956)->getNode1() <<"\tnode2="<<connections.at(125956)->getNode2()<<endl;
//	cout << "check00\tid1=" <<id1<<"\tid2="<<id2<< endl;
//	getchar();
	for (unsigned int i = 0; i < connections.size(); i++) {
		//	cout << "check01	" << i << endl;
		if (connections.at(i)->getRoadId() == id1
				|| connections.at(i)->getRoadId() == id2) {
			//	cout << "check02	" << i << endl;
			//getchar();
			for (unsigned int j = 0; j < connections.size(); j++) {
				//	cout << "check03	" << j << endl;
				if (i != j
						&& (connections.at(j)->getRoadId() == id1
								|| connections.at(j)->getRoadId() == id2)) {
					//	cout << "check04	" << connections.at(j)->getRoadId()<< endl;

					if (connections.at(i)->getNode1()
							== connections.at(j)->getNode1()
							|| connections.at(i)->getNode1()
									== connections.at(j)->getNode2()
							|| connections.at(i)->getNode2()
									== connections.at(j)->getNode2()
							|| connections.at(i)->getNode2()
									== connections.at(j)->getNode1()) {

						return true;
					}
					if (connections.at(j)->getRoadId() == id2)
						break;
				}
				if (connections.at(i)->getRoadId() == id1)
					break;
			}
		}
	}
	return false;
}

set<string> Menu::getSupermarketByRoadId(long long id) {
	std::set<string> supers;
	for (unsigned int i = 0; i < connections.size(); i++) {
		if (connections.at(i)->getRoadId() == id) {
			for (unsigned int j = 0; j < supermarkets.size(); j++) {
				if (supermarkets.at(j)->getNode()
						== connections.at(i)->getNode1()
						|| supermarkets.at(j)->getNode()
								== connections.at(i)->getNode2()) {
					supers.insert(supermarkets.at(j)->getName());
				}
			}

		}
	}
	return supers;
}

void Menu::fregExacta(string pattern) {
	system("clear");
	int id;
	string ind;
	std::stringstream sstm;
	set<string> ruas;
	vector<Supermarket*> tmp;
	struct timeval st, et;

	cout << "pesquisa exacta de supermercados na freguesia \"" << pattern
			<< "\".\n";

	/*  // correr 5 vezes e fazer a média (quando é muito rápido)
	 int i, num_runs = 5;

	 gettimeofday(&st,NULL);
	 for (i=0; i<num_runs; i++) {
	 bubble(a,n);
	 }
	 gettimeofday(&et,NULL);

	 int elapsed = (((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec)) / num_runs;
	 */

	gettimeofday(&st, NULL);
	vector<int> ids = numStringMatchingFreg("supermarkets.txt", pattern);
	gettimeofday(&et, NULL);
	int elapsed = ((et.tv_sec - st.tv_sec) * 1000000)
			+ (et.tv_usec - st.tv_usec);

	for (unsigned int i = 0; i < ids.size(); i++) {
		tmp.push_back(supermarkets[ids.at(i) - 1]);
	}

	cout << "\n\n\n\n\n";
	if (tmp.size()) {

		cout << "Supermercados encontrados na freguesia de " << pattern
				<< ":\n\n";
		cout << "\n********************************************\n\n";
		for (unsigned int i = 0; i < tmp.size(); i++) {
			cout << "ID: " << tmp.at(i)->getId() << "\n";
			cout << "Name: " << tmp.at(i)->getName() << "\n";
			cout << "Node ID: " << tmp.at(i)->getNode() << "\n\n";
			cout << "freguesia: " << tmp.at(i)->getFreguesia() << "\n\n";
			if ((ruas = getRoadByNode(tmp.at(i)->getNode())).size()) {
				cout << "\n\truas do cruzamento:\n";
				for (set<string>::iterator it = ruas.begin(); it != ruas.end();
						it++) {
					//for (unsigned int j = 0; j < ruas.size(); j++) {

					if (*it == "") {
						cout << "Rua sem nome" << endl;
					} else {
						cout << "\t" << *it << "\n";
					}
				}
			} else {

				cout << "\truas do cruzamento nao encontradas\n";
			}

			cout << "\n********************************************\n\n";
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\tadicionar como supermercado da rota:\n";
		//cin >> id;
		getline(cin, ind);
		sstm.clear();
		sstm.str(ind);
		sstm >> id;
		adicionaSuper(tmp.at(id - 1)->getId());
//		for (unsigned int i = 0; i < tmp.size(); i++) {
//			if (tmp.at(i)->getId() == id) {
//				adicionaSuper(id);
//				break;
//			}
//		}
	}

	if (!tmp.size()) {
		cout << "\n\n\nNão foram encontrados supermercados na freguesia "
				<< pattern << " !\n";

	}

	cout << endl << endl;
	cout << "A pesquisa exacta de supermercados na freguesia demorou "
			<< elapsed << " microsegundos / " << elapsed / 1000
			<< " milisegundos / " << elapsed / 1000000 << " segundos" << endl;

	cout << "\nprima uma tecla para continuar" << endl;
	getchar();
	return;
}

void Menu::fregApprox(string pattern) {
	system("clear");
	int id;
	string ind;
	std::stringstream sstm;
	cout << "pesquisa aproximada de supermercados em freguesia \"" << pattern
			<< "\".\n";
	vector<std::pair<float, Supermarket *> > tmp;
	set<string> ruas;
	struct timeval st, et;
//	vector<Supermarket*> tmp;
	float min = 999;
	float max = 0;

	gettimeofday(&st, NULL);

	vector<float> val = numApproximateStringMatchingFreg("supermarkets.txt",
			pattern);
	gettimeofday(&et, NULL);
	int elapsed = ((et.tv_sec - st.tv_sec) * 1000000)
			+ (et.tv_usec - st.tv_usec);

	set<Supermarket*> tmpset;
	for (float i = 0; i < val.size(); i++) {

		if (val.at(i) > max) {
			max = val.at(i);
		}
	}
	cout << "\n\nMINIMUM:" << max;

	for (float i = 0; i < val.size(); i++) {
		if (val.at(i) > 0.66 || val.at(i) == max)
			tmp.push_back(
					pair<float, Supermarket *>(val.at(i), supermarkets.at(i)));
		//tmp.push_back(supermarkets.at(i));
	}
	std::sort(tmp.begin(), tmp.end(), sortPairS);
	cout << "\n\n\n\n\n";
	if (tmp.size() >= 1) {

		cout << "\tSupermercados encontrados na freguesia de " << pattern
				<< ":\n\n";
		cout << "\n********************************************\n\n";
		for (unsigned int i = 0; i < tmp.size(); i++) {
			cout << "\t" << i + 1 << ")\tparecença=" << tmp.at(i).first << "\n";
			cout << "\tID: " << (tmp.at(i).second)->getId() << "\n";
			cout << "\tName: " << (tmp.at(i).second)->getName() << "\n";
			cout << "\tNode ID: " << (tmp.at(i).second)->getNode() << "\n\n";
			cout << "\tfreguesia: " << (tmp.at(i).second)->getFreguesia()
					<< "\n\n";
			if ((ruas = getRoadByNode((tmp.at(i).second)->getNode())).size()) {
				cout << "\n\t\truas do cruzamento:\n";
				for (set<string>::iterator it = ruas.begin(); it != ruas.end();
						it++) {
					tmpset.insert((tmp.at(i).second));

					if (*it == "") {
						cout << "\tRua sem nome" << endl;
					} else {
						cout << "\t\t" << *it << "\n";
					}
				}
			} else {

				cout << "\t\truas do cruzamento nao encontradas\n";
			}

			cout << "\n********************************************\n\n";
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\t\tadicionar como supermercado da rota:\n";
		//cin >> id;
		getline(cin, ind);
		sstm.clear();
		sstm.str(ind);
		sstm >> id;
		adicionaSuper((tmp.at(id - 1).second)->getId());
//		for (unsigned int i = 0; i < tmp.size(); i++) {
//			if (tmp.at(i)->getId() == id) {
//				adicionaSuper(id);
//				break;
//			}
//		}
	}

	if (!tmp.size()) {
		cout << "\n\n\n\tNão foram encontrados supermercados na freguesia "
				<< pattern << " !\n";
	}

	cout << endl << endl;
	cout << "\tA pesquisa aproximada de supermercados na freguesia demorou "
			<< elapsed << " microsegundos / " << elapsed / 1000
			<< " milisegundos / " << elapsed / 1000000 << " segundos" << endl;

	cout << "\n\tprima uma tecla para continuar" << endl;
	getchar();
	return;
}

void Menu::setSource(long long node) {
	this->source = node;
}
/*
 void Menu::setDestination(long long node) {
 this->destination = node;
 }*/

long long Menu::getSource() {
	return this->source;
}
/*
 long long Menu::getDestination() {
 return this->destination;
 }*/

void Menu::stringDoD(double &total, bool toPrint) {
	if (!this->created) {
		cout << "\nplease wait while building graph\n";

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
	}

	system("clear");
	int totaltotal = 0;
	cout << "\nalgoritmo de Dijkstra sobre algoritmos de Dijkstra:\n";

	write(STDOUT_FILENO, "\n\nem processamento\n", 19);

//------------------------------------------------
//	long long nTimeStart = GetMilliCount();
//------------------------------------------------

	vector<long long> completeRoute;
	vector<long long> route;
	vector<long long> routeBack;
	vector<long long> supermarketLocation;
	vector<long long> stops;

	long long LastStop;
	total = 0;

	completeRoute.clear();
	route.clear();
	routeBack.clear();
	supermarketLocation.clear();
	stops.clear();
	stops = trucks.at(0)->getStops();
	if (!isNodeinMap(this->getSource())) {
		cout << "supermercado não consta deste mapa\n";
		getchar();
		return;
	}
	supermarketLocation.push_back(this->getSource());

	cout << "source=" << this->getSource() << endl;
	route = dijkstraOfDijkstras(this->getSource(), stops, total);

	completeRoute.insert(completeRoute.end(), route.begin(), route.end());
	cout << "01_3\n";
	LastStop = route.at(route.size() - 1);
	cout << "01_4\n";
	route = dijkstraOfDijkstras(LastStop, supermarketLocation, total);
	cout << "01_5\n";
	completeRoute.insert(completeRoute.end(), route.begin(), route.end() - 1);
	cout << "01_6\n";
	cout << "\nnumber of nodes in path:" << completeRoute.size() << endl;
	cout << "02\n";
	write(STDOUT_FILENO, "\n\n", 2);

	if (toPrint)
		printRouteString(completeRoute, 0, 0);
	cout << "03\n";
	cout << "\ntotal=" << total << endl;
	totaltotal += total;

//time--------------------------------------------
//	long long nTimeElapsed = GetMilliSpan(nTimeStart);
//cout << endl << endl;
//	cout << "> Consecutive Dijkstra's Algorithm execution time (ms): "
//		<< nTimeElapsed << endl;
//------------------------------------------------
//	cout << "\ntotal de nós rotas =" << compareStruct.dOdMethod.totalNodes
//		<< endl;
//	cout << "\ntotal das rotas =" << totaltotal << " m" << endl;
	cout << "\n";
	getchar;

	char opt;
	while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N') {
		cout << "quer ver em modo gráfico(y/n)?\n";
		cin >> opt;
	}
	if (toupper(opt) == 'Y') {
		gvRouteDoDString();
	}

	return;
}

void Menu::stringbi(double &total, bool toPrint) {

//	int totaltotal = 0;
	cout << "\nNosso algoritmo bidireccional:\n";
//cout << "em processamento ";
	write(STDOUT_FILENO, "\n\nem processamento\n", 19);

//------------------------------------------------
//	long long nTimeStart = GetMilliCount();
//------------------------------------------------
	vector<long long> completeRoute;
	vector<long long> route;
	vector<long long> routeBack;
//vector<long long> supermarketLocation;
	vector<long long> stops;

//	for (unsigned int s = 0; s < supermarkets.size(); s++) {

//	for (unsigned int t = 0; t < trucks.size(); t++) {
	total = 0;

//if (trucks.at(t)->getSupermarket() == supermarkets.at(s)->getId()) {

	completeRoute.clear();
	route.clear();
	routeBack.clear();
//		supermarketLocation.clear();
	stops.clear();

	stops = trucks.at(0)->getStops();
//stops.push_back(this->getDestination());
//	supermarketLocation.push_back(this->getSource());

	route = graph.getOurRoute(this->getSource(), stops, total);

	completeRoute.insert(completeRoute.end(), route.begin(), route.end() - 1);

	cout << "\nnumber of nodes in path:" << completeRoute.size() << endl;

	write(STDOUT_FILENO, "\n\n", 2);

//	cout << "rota " << t + 1 << "/" << trucks.size()
//		<< " do supermercado " << s + 1 << "/"
//	<< supermarkets.size() << "\n";

	if (toPrint)
		printRoute(completeRoute, 0, 0);
//	cout << "\ntotal=" << total << endl;

//		totaltotal += total;

//	compareStruct.biMethod.routes.push_back(completeRoute);

//compareStruct.biMethod.totalNodes += completeRoute.size();

//	}	//fim verificacao cliente truck super

//}	//fim for truck

//}	//fim for super

//time--------------------------------------------
//	long long nTimeElapsed = GetMilliSpan(nTimeStart);
//cout << endl << endl;
//	cout << "> Our Bidireccional Algorithm execution time (ms): "
//		<< nTimeElapsed << endl;
//------------------------------------------------
//cout << "\ntotal de nós rotas =" << compareStruct.biMethod.totalNodes
//			<< endl;
//cout << "\ntotal das rotas =" << totaltotal << " m" << endl;
//	compareStruct.biMethod.totalWeight = totaltotal;
//compareStruct.biMethod.totalMillis = nTimeElapsed;
	cout << "\n";
	return;
}

void Menu::adicionaSuper(long long id) {
	long long node;
	for (unsigned int i = 0; i < supermarkets.size(); i++) {
		if (supermarkets.at(i)->getId() == id) {
			node = supermarkets.at(i)->getNode();
		}
	}

	this->setSource(node);
	cout << "\t supermercado definido \n";
}

void Menu::adicionaParagem(long long id) {
	if (!this->newtruck) {
		this->trucks.at(0)->getStops().clear();
		this->trucks.at(0)->eraseClients();
		this->newtruck = true;
	}
	long long node;

	string nome, nomeRua;

	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "nome do Cliente:\n";
	getline(cin, nome);

	//string d = sstm.str();

	for (unsigned int i = 0; i < roads.size(); i++) {

		if (roads.at(i)->getId() == id) {
			nomeRua = roads.at(i)->getName();
			node = edgeId2Node(roads.at(i)->getId());
		}
	}

	Client * newC = new Client(c, nome, node, nomeRua, 0);
	this->trucks.at(0)->addNewStop(newC);

	clients.push_back(newC);
	this->trucks.at(0)->addClient(newC);
	cout << "\t paragem adicionada para o cliente " << nome << " no nó " << node
			<< "\n";
}

int Menu::getC() {
	return this->c;
}

void Menu::incC() {
	this->c++;
}

void Menu::setMap(int map) {
	this->map = map;
}

int Menu::getMap() {
	return this->map;
}

void Menu::closeRoute() {
	system("clear");
	char opt = ' ';
	double total = 0;
	while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N') {
		cout << "\n\tdo you really want to close the current route? (y/n)\n";
		cin >> opt;
	}

	//verifica se tem source e dests...
	if (!this->trucks.at(0)->getStops().size() || !this->getSource()) {
		cout << "\n\tNao tem supermercado e/ou paragens adicionadas\n";
		getchar();
		getchar();
		return;
	}

	switch (toupper(opt)) {
	case ('Y'):
		stringDoD(total, true);
		break;
	case ('N'):
		return;
		break;
	}
	return;
}

long long Menu::edgeId2Node(long long id) {
	long long node = NULL;
	for (unsigned int i = 0; i < connections.size(); i++) {
		if (connections.at(i)->getRoadId() == id) {

			node = connections.at(i)->getNode1();
		}
	}
	return node;
}

bool Menu::isNodeinMap(long long node) {
	for (unsigned int in = 0; in < nodes.size(); in++) {
		if (nodes.at(in)->getId() == node) {
			return true;
		}
	}
	return false;
}

bool Menu::isStop(long long node) {
	for (unsigned int i = 0; i < this->trucks.at(0)->getClients().size(); i++) {
		if (this->trucks.at(0)->getClients().at(i)->getNode() == node) {
			return true;
		}
		return false;
	}
}
