/*
 * methods.cpp
 *
 *  Created on: 26/03/2018
 *      Author: luis
 */
#include "methods.h"
#include <iostream>

using namespace std;

void allFromOne(int from,int to){
	cout<<"allFromOne("<<from<<","<<to<<")\n";
}

void eachFromSelf(){
	cout<<"eachFromSelf\n";
}
void fromTo(int from,int to){
	cout<<"fromTo("<<from<<","<<to<<")\n";
}
void optimal(){
	cout<<"optimal\n";
}

void runAllMethods(int from,int to){
	cout<<"entra all"<<endl;
//	if(from>0){
//
//	}
	allFromOne(from,to);
	eachFromSelf();
	fromTo(from, to);
	optimal();
	cout<<"sai all"<<endl;

}



