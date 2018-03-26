#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

void usage() {
	cout << "\n\nOnline Supermarket : invalid syntax\n" << endl << endl;
	cout << "usage:\t";
	cout << "super [from_id] file [to_id] [METHOD]" << endl << endl;
	cout << "file:\tfile with the clients to be included in the route\n";
	cout << "\nmethods:\n";
	cout
			<< "ALLFROMONE:\tthe application calculates one best route to and from the same supermarket\n";
	cout
			<< "EACHFROMSELF:\tthe application calculates all routes from each supermarket to the clients on its area\n";
	cout
			<< "FROMTO:\t\tthe application calculates one best route from one supermarket to another (or itself...)\n";
	cout
			<< "OPTIMAL:\tthe application calculates one best route to and from the same supermarket (best method)\n";
	cout << "\nexamples:\n";
	cout
			<< "super clientes1.txt ALLFROMONE\t\troute goes through all clients from the and to the same supermarket\n";
	cout
			<< "super clientes1.txt 1 ALLFROMONE\troute goes through all clients from and to supermarket 1\n";
	cout
			<< "super clientes1.txt EACHFROMSELF\tthis method returns the routes from (and to the same) all the supermarkets\n\t\t\t\t\t to their own clients (supermarkets have their own clients within a range)\n";
	cout
			<< "super 1 clientes1.txt 2 FROMTO\troute goes through all clients from supermarket 1 to supermarket 2\n";
	cout
			<< "super 1 clientes1.txt FROMTO\troute goes through all clients from supermarket 1 to the best supermarket it calculates\n";
	cout
			<< "super clientes1.txt 2 FROMTO\troute goes through all clients from the best supermarket it calculates to supermarket 2\n";
	cout
			<< "super clientes1.txt FROMTO\troute goes through all clients from the best supermarket it calculates \n\t\t\t\tto the best supermarket it calculates\n";
	cout
			<< "super clientes1.txt OPTIMAL\troute goes through all clients from the and to the same supermarket\n";
	cout
			<< "super clientes1.txt\t\treturns best route from all the above methods with no constraints\n";
	cout
			<< "super 1 clientes1.txt\t\treturns best route from all the above methods which have FROM constraints\n";
	cout
			<< "super clientes1.txt 2\t\treturns best route from all the above methods which have TO constraints\n";
	cout
			<< "super 1 clientes1.txt 2\t\treturns best route from all the above methods which have TO and FROM constraints\n";
}

int main(int argc, char*argv[]) {





	if (argc < 2 || argc > 5){
		usage();
	}else if (argc==2){
		//runs all the *
	}else if(argc==3 && argv[3]){

	}














}
