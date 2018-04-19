/*
 * Graph.h
 *
 *  Created on: Apr 16, 2018
 *      Author: vpuyf
 */

#ifndef DIRECTEDGRAPH_HPP_
#define DIRECTEDGRAPH_HPP_

#include <list>
#include <sstream>
#include "Edge.hpp"
#include "Vertex.hpp"
#include "Nullvertex.h"
#include "NullEdge.h"

using namespace std;

template<class T> class DirectedGraph;
template<class T> std::ostream& operator<<(std::ostream& o, const DirectedGraph<T>& g);



template<typename T> class DirectedGraph {

	Vertex<T>* base;
	list<Vertex<T>> vertices;
	list<Edge<T>> edges;

public:
	DirectedGraph(Vertex<T>* base = nullptr){
		this->base = base;
	}
	DirectedGraph(const DirectedGraph<T>&g){
		base = g.base;
		try{
			vertices.insert(vertices.end(), g.vertices.begin(), g.vertices.end());
			edges.insert(edges.end(), g.edges.begin(),g.edges.end());
		}
		catch(exception &e){
			cerr<<"Copy constructor: "<<e.what();
		}
	}
	 ~DirectedGraph(){

		if(!clean())
			cerr<<"\nProblem in clean()";
	}


	 Edge<T>& link( Vertex<T>& start,  Vertex<T>& end){
		try{
			Edge<T>* newEdge = new Edge<T>(0,&start,&end);// 0 is int weight
			newEdge->setStart(&start);
			newEdge->setEnd(&end);

			start.add(*newEdge);
			end.add(*newEdge);
			return *newEdge;
		}
		catch(exception& e){
			cerr<<"\nlink"<<e.what();
			exit(3);
		}
	}

	//adds one vertex; returns bool if added successfully.
	 bool add(Vertex<T>& v){
		try{
			if(base == nullptr){
				base = &v;
			}

			vertices.push_back(v);

		}
		catch(std::bad_alloc& ba){
			cerr<<"Caught bad alloc: "<< ba.what();
			return false;
		}
		catch(exception& e){
			cerr<<"add(Vertex&) "<<e.what();
			return false;
		}
		return true;
	}

	//adds an edge; returns true if the edge is added successfully.
	 bool add(Edge<T>& e){
		try{

			edges.push_back(e);

		}
		catch(exception& e){
			cerr<<e.what();
			return false;
		}
		return true;
	}

	//Bonus question: adds in a set of vertices; returns bool if added
	 //successfully
	 bool add(Vertex<T>* v, int size){
		try{
			if(!size)
				throw invalid_argument("Invalid Size");

			for(int i =0 ; i < size; ++i)
				vertices.push_back(v[i]);

		}
		catch(exception&e){
			cerr<<e.what();
			return false;
		}
		return true;
	}

	//Bonus question: removes a set of edges; as a result, some nodes may remain
	//as orphan.
	 bool add(Edge<T>* e,int size){
		try{
			if(!size)
				throw invalid_argument("Invalid Size");
			for(int i =0 ; i < size; ++i)
				edges.push_back(e[i]);

		}
		catch(exception&e){
			cerr<<e.what();
			return false;
		}
		return true;
	}


	//removes a vertex; the edges that have connection with this vertex need to
	 //be removed;
	 bool remove(Vertex<T>& v){
		/*try{
			vertices.remove(v);
		}
		catch(exception& e){
			cerr<<"remove(Vertex&) "<<e.what();
			return false;
		}
		return true;*/
		cerr<<"\n didnt do that function";
		return false;
	}

	// remove the edge
	 bool remove(Edge<T>& e){
		/*try{
			edges.remove(e);
			return true;
		}
		catch(exception& e){
			cerr<<e.what();
			return false;
		}*/
		cerr<<"\n didnt do that function";
		return false;
	}
	// returns bool if a vertex exists in a graph.


	 Vertex<T>& search(T value){


		for(typename list<Vertex<T>>::iterator it = vertices.begin(); it != vertices.end(); ++it)
			if(it->getValue() == value ){

				return *it;
			}
		throw Null_vertex("\nVertex not found");
	}

	 Edge<T>& searchEdge(int id){

		for(typename list<Edge<T>>::iterator it = edges.begin(); it != edges.end(); ++it)
			if(it->getId() == id ){
				return *it;
			}

		throw Null_Edge("\nEdge not found");
	}
	void findPath(const Vertex<T>& v, vector<Vertex<T>>& buffer,bool* visited)const{
		//The path is written from the destination Vertex, going in reverse direction
		try{
			if(base == nullptr)
				throw Null_vertex("invalid base vertex!");

		}catch(exception&e){
			cerr<<e.what();
			throw e;
		}

		if(v == *base)//checking if we reached base
			buffer.push_back(*base);//add base to path

		else if(!visited[v.getId() - base->getId()])//checking if we ve been here before
		{
			visited[v.getId() - base->getId()]=true;//setting the vertex as visited

			for(auto it : v.getListEdge())//NOTE i have no idea what "it" type is!!
			{//iterating through all edges of vertex v

				if( *(it->getEnd()) == v && !visited[ it->getStart()->getId() - base->getId()])
				{//testing if iterator is directed toward Vertex v
					//add vertex to path

					buffer.push_back(v);

					//recursive call
					//testing if the vertex on the other hand of iterator is part of path
					findPath(*it->getStart(),buffer,visited);
				}
			}
			if(!buffer.empty())
			{//means path does not lead back to base
				if(buffer.back() != *base)
					buffer.pop_back();
				else buffer.push_back(buffer[0]);
			}
		}
		visited[v.getId() - base->getId()] = false;//freeing vertex

	}
	// displays the path that contains the vertex.


	void displayEdgeInfo()const{
		for(auto e: edges)
			cout<<'\n'<<e;
	}
	void displayVertexInfo()const{
		for(auto v : vertices)
			cout<<"\n"<<v;
	}
	 void display(Vertex<T>& v,bool debug = false) const{
		//finds the shortest path to vertex
		bool* visited = nullptr;
		do{
			try{
				visited = new bool[vertices.size()];
			}
			catch(exception&e){
				cerr<<e.what();
				cerr<<vertices.size();
				return;
			}
		}while(visited == nullptr);

		for(unsigned int i = 0; i < vertices.size();++i )
			visited[i] = false;

		vector<Vertex<T>> path;
		path.clear();

		findPath(v,path,visited);

		if(path.empty())
			cout<<"\nNo path leading to vertex "<<v.getId()<<".";
		else{
			cout<<'\n';
			if(debug)
				for(auto debug: path)
					cout<<'\n'<<debug;
			for(auto it = path.rbegin(); it != path.rend(); ++it){
				cout<<it->getValue();
				it->getValue()==v.getValue()?cout<<';'<<'\n':cout<<'-'<<'>';
			}


		}
	}

	// displays the path that contains the edge.
	 void display(Edge<T>& e) const{
		//output format
		//prints the series of vertices from the base vertex to the vertex that Edge e points to
		bool* visited = new bool[vertices.size()+1];

		for(unsigned int i = 0; i < vertices.size()+1;++i )
			visited[i] = false;

		vector<Vertex<T>> path;

		findPath(*e.getStart(),path,visited);
		cout<<'\n';

		if(path.empty())
			cout<<"No path contains Edge "<<e.getId()<<".";
		else
			for(auto it = path.rbegin(); it != path.rend();++it)
				cout<<it->getId()<<'-';

		if( !path.empty() && path.begin()->getId() == e.getStart()->getId())
			cout<<e.getEnd()->getId()<<';';

	}

	// displays the whole graph with your own defined format
	 void display() const{
		cout<<toString();
	}
	 // converts the whole graph to a string such as 1-2-4-5; 1-3-5; each path
	 // is separated by ';'
	 string toString()const{
		try{

			stringstream buffer;

			buffer <<"\nAll Graph Paths\n\nFormat:\tBase Vertex ID - intermediate vertices IDs - Destination Vertex ID;\n\n\t";

			if(vertices.empty())
				throw Null_vertex("listVertex is empty!");


			for(auto it : vertices)
			{
				bool* visited;

				//try-catch new operator///
				try{
					visited = new bool[vertices.size()];
				}
				catch(exception& e){
					cerr<<"bool\n"<<e.what();
					throw bad_alloc();
				}
				///////////////////////////

				vector<Vertex<T>> path;
				try
				{
					for(unsigned int i = 0; i < vertices.size();++i )
						visited[i] = false;
					path.clear();

					findPath(it,path,visited);
				}
				catch(exception& e){
					cerr<<"\nerror in findPath\n";
					throw e;
				}
				if(!path.empty())
					for(auto r_it = path.rbegin(); r_it != path.rend();++r_it){
						buffer << r_it->getValue();
						if(r_it->getId() == it.getId())
							buffer << ';'<<'\n'<<'\t';

						else buffer <<'-'<<'>';

					}
				delete visited;
			}

			string s = buffer.str();
			return s;
		}
		catch(exception& e){
			cerr<<"error in toString()\n"<<e.what();
			throw e;
		}
		catch(...){
			cerr<<"Error with stringstream";
			return "Error with stringstream";
		}

	}
	//remove all the vertices and edges;
	 bool clean(){
		try{



			vertices.clear();



			edges.clear();



			delete base;
			base = nullptr;

			return true;
		}catch(exception& e){
			cerr<<'\n'<<e.what();
			return false;
		}catch(...){
			cerr<<"\nUnhandled in clean!";
			return false;
		}
	}

	//Operators
	//=
	/*DirectedGraph<T>& operator=(DirectedGraph<T> g); //cannot be made const
	//==
	bool operator==(const DirectedGraph<T> &graph)const;
	//!=
	bool operator!=(const DirectedGraph<T>&)const;
	//++g
	DirectedGraph<T>& operator++();
	//g++
	DirectedGraph<T> operator++(int);
	//+
	DirectedGraph<T> operator+(DirectedGraph<T>&);
	//>
	bool operator>(const DirectedGraph<T> &g)const;*/
	//<<
	friend std::ostream& operator<<<T>(std::ostream&, const DirectedGraph<T>&);

};
template<class T> std::ostream& operator<<(std::ostream& out, const DirectedGraph<T>& g){
	out << "\n##############################################"
		<< "\nGraph contains "<< g.vertices.size() <<" vertices and " << g.edges.size() << " edges."
		<< g.toString()
		<< "\n##############################################";

	return out;
}
#endif /* DIRECTEDGRAPH_HPP_ */
