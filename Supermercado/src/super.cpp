#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <ctype.h>
#include "methods.h"

using namespace std;

void usage() {
	cout << "\n\nOnline Supermarket : invalid syntax\n" << endl << endl;
	cout << "usage:\t";
	cout << "Supermercado [from_id] file [to_id] [METHOD]" << endl;
	cout
			<< "if no method is provided it returns the best option from all methods\n\n	";
	cout << "file:\tfile with the clients to be included in the route\n";

	cout << "\nmethods:\n";
	cout
			<< "ALLFROMONE:\tthe application calculates one best route to and from the same Supermercadomarket\n";
	cout
			<< "EACHFROMSELF:\tthe application calculates all routes from each Supermercadomarket to the clients on its area\n";
	cout
			<< "FROMTO:\t\tthe application calculates one best route from one Supermercadomarket to another (or itself...)\n";
	cout
			<< "OPTIMAL:\tthe application calculates one best route to and from the same Supermercadomarket (best method)\n";
	cout
			<< "if no method is provided it returns the best option from all methods\n";
	cout << "\nexamples:\n";
	cout
			<< "Supermercado clientes1.txt ALLFROMONE\t\troute goes through all clients from the and to the same Supermercadomarket\n";
	cout
			<< "Supermercado clientes1.txt 1 ALLFROMONE\troute goes through all clients from and to Supermercadomarket 1\n";
	cout
			<< "Supermercado clientes1.txt EACHFROMSELF\tthis method returns the routes from (and to the same) all the Supermercadomarkets\n\t\t\t\t\t to their own clients (Supermercadomarkets have their own clients within a range)\n";
	cout
			<< "Supermercado 1 clientes1.txt 2 FROMTO\troute goes through all clients from Supermercadomarket 1 to Supermercadomarket 2\n";
	cout
			<< "Supermercado 1 clientes1.txt FROMTO\troute goes through all clients from Supermercadomarket 1 to the best Supermercadomarket it calculates\n";
	cout
			<< "Supermercado clientes1.txt 2 FROMTO\troute goes through all clients from the best Supermercadomarket it calculates to Supermercadomarket 2\n";
	cout
			<< "Supermercado clientes1.txt FROMTO\troute goes through all clients from the best Supermercadomarket it calculates \n\t\t\t\tto the best Supermercadomarket it calculates\n";
	cout
			<< "Supermercado clientes1.txt OPTIMAL\troute goes through all clients from the and to the same Supermercadomarket\n";
	cout
			<< "Supermercado clientes1.txt\t\treturns best route from all the above methods with no constraints\n";
	cout
			<< "Supermercado 1 clientes1.txt\t\treturns best route from all the above methods which have FROM constraints\n";
	cout
			<< "Supermercado clientes1.txt 2\t\treturns best route from all the above methods which have TO constraints\n";
	cout
			<< "Supermercado 1 clientes1.txt 2\t\treturns best route from all the above methods which have TO and FROM constraints\n";
}

bool isNumber(char number[]) {
	int i, num = 0;

	for (; number[i] != 0; i++) {
		if (!isdigit(number[i])) {
			return false;
		} else {
			num *= pow(10, i);
			num += number[i];
		}
	}
	return num;
}

int main(int argc, char*argv[]) {
	cout << "-10\n";
	int arg = -1, arg2 = -1;
	if (argc < 2 || argc > 5) {
		cout << "-0\n";
		usage();
	} else if (argc == 2 && !isNumber(argv[1])) {
		cout << "00\n";
		//FILE 8
		runAllMethods(-1, -1);
	} else if (argc == 2) { //runs all the *
		cout << "01\n";
		if ((arg = isNumber(argv[2])) && !isNumber(argv[1])) {
			cout << "011\n";
			//FILE # 10
			runAllMethods(-1, arg);
		} else if (argv[2] == "ALLFROM" && !isNumber(argv[1])) {
			cout << "012\n";
			//FILE ALLFROM 0
			allFromOne(-1, -1);
		} else if (argv[2] == "EACHFROMSELF" && !isNumber(argv[1])) {
			cout << "013\n";
			//FILE EACHFROMSELF 2
			eachFromSelf();
		} else if (argv[2] == "FROMTO" && !isNumber(argv[1])) {
			cout << "014\n";
			//FILE FROMTO 6
			fromTo(-1, -1);
		} else if (argv[2] == "OPTIMAL" && !isNumber(argv[1])) {
			cout << "015\n";
			//FILE OPTIMAL 7
			optimal();
		} else {
			cout << "016\n";
			usage();
		}

	} else if (argc == 4 && !isNumber(argv[3]) && !isNumber(argv[2])) {
		cout << "02\n";
		arg = isNumber(argv[1]);
		//# FILE FROMTO # 3
		fromTo(arg, -1);
	} else if (arg = isNumber(argv[1])) {
		cout << "03\n";
		if (argc == 3 && !isNumber(argv[2]) && isNumber(argv[1])) {
			cout << "031\n";
			//# FILE 9
			runAllMethods(arg, -1);
		} else if ((arg2 = isNumber(argv[3])) && (arg = isNumber(argv[1]))
				&& !isNumber(argv[2])) {
			cout << "032\n";
			//# FILE # 11
			runAllMethods(arg, arg2);
		} else if (argv[3] == "FROMTO" && (arg = isNumber(argv[1]))
				&& !isNumber(argv[2])) {
			cout << "033\n";
			//# FILE FROMTO 4
			fromTo(arg, -1);
		} else {
			cout << "034\n";
			usage();
		}

	} else if (argc == 4 && isNumber(argv[2])) {
		cout << "04\n";
		if (argv[3] == "ALLFROM" && (arg = isNumber(argv[2]))
				&& !isNumber(argv[1])) {
			cout << "041\n";
			//FILE # ALLFROM 1
			runAllMethods(-1, arg);
		} else if (argv[3] == "FROMTO" && (arg = isNumber(argv[2]))
				&& !isNumber(argv[1])) {
			cout << "042\n";
			//FILE # FROMTO 5
			fromTo(-1, arg);
		} else {
			cout << "043\n";
			usage();
		}

	} else {
		cout << "05\n";
		usage();
	}
return 0;
}


//map::instance()->loadData();
//
//	vector<Node> path;
//	path = map::instance()->insertValues();
//
//	if (path.size() != 0) {
//		map::instance()->printGraph();
//		map::instance()->paintPath(path);
//	} else
//		cerr << "Program ended.\n";
//
//	getchar();
//	getchar();
//
//return 0;

