//============================================================================
// Name        : DirectedGraph.cpp
// Author      : Valentin Puyfourcat
// Version     :
// Copyright   : Directed Graph using template
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

#include "Edge.hpp"
#include "Nullvertex.h"
#include "Vertex.hpp"
#include "DirectedGraph.hpp"
using namespace std;


int main() {

	try{
		DirectedGraph<string> test;
		cout<<"waaaaa";
		test.add(*new Vertex<string>("Valentin"));

		cout<<test.searchVertex("Valentin");










	}
	catch(ExceptionVertex& e){
		cerr<<e.what();
		exit(1);
	}
	catch(exception& e){
		cerr<<e.what();
		exit(2);
	}

	return 0;
}
