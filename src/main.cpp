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



		test.add(*new Vertex<string>("exception"));
		test.add(*new Vertex<string>("runtime"));
		test.add(*new Vertex<string>("range"));
		test.add(*new Vertex<string>("bad_alloc"));
		test.add(*new Vertex<string>("overflow"));
		test.add(*new Vertex<string>("system"));
		test.add(*new Vertex<string>("file"));
		test.add(*new Vertex<string>("ios"));
		test.add(*new Vertex<string>("bad_cast"));


		test.add(test.link(test.search("exception"),test.search("bad_alloc")));
		test.add(test.link(test.search("exception"),test.search("runtime")));
		test.add(test.link(test.search("runtime"),test.search("system")));
		test.add(test.link(test.search("system"),test.search("ios")));
		test.add(test.link(test.search("system"),test.search("file")));
		test.add(test.link(test.search("runtime"),test.search("overflow")));
		test.add(test.link(test.search("runtime"),test.search("range")));
		test.add(test.link(test.search("exception"),test.search("bad_cast")));
		test.add(test.link(test.search("file"),test.search("overflow")));
		test.add(test.link(test.search("overflow"),test.search("range")));


		cout<<'\n'<<test;




cin.get();
/*		In DirectedGraph destructor when the edges are destroyed, the edge destructor crashes the program*/


	}
	catch(ExceptionVertex& e)
	{
		cerr<<e.what();
		exit(1);
	}
	catch(exception& e)
	{
		cerr<<e.what();
		exit(2);
	}
	catch(...)
	{
		cerr<<"something is thrown";
	}

	return 0;
}
