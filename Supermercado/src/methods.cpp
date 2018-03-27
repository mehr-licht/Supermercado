/*
 * methods.cpp
 *
 *  Created on: 26/03/2018
 *      Author: luis
 */
#include "methods.h"
#include <iostream>

using namespace std;

void allFromOne(map* obj,int from,int to){
	cout<<"allFromOne("<<from<<","<<to<<")\n";
	cout<<"1_Dijkstra mais volta desde o último\n";
		cout<<"2_toAndFrom()\n";
}

void eachFromSelf(map* obj){
	cout<<"eachFromSelf\n";

}
void fromTo(map* obj,int from,int to){
	cout<<"fromTo("<<from<<","<<to<<")\n";
}
void optimal(){
	cout<<"optimal\n";
}

void runAllMethods(map* obj,int from,int to){
	cout<<"entra all"<<endl;
	cout<<"\n";
	allFromOne(obj,from,to);
	cout<<"\n";
	eachFromSelf(obj);
	//fromTo(from, to);
	//optimal();
	cout<<"\n";
	cout<<"sai all"<<endl;

}



