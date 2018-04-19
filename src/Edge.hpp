/*
 * Edge.h
 *
 *  Created on: Apr 16, 2018
 *      Author: vpuyf
 */

#ifndef EDGE_HPP_
#define EDGE_HPP_

#include <iostream>
#include "Nullvertex.h"


template <class T> class Vertex; // forward declaration
template <class T> class Edge;
template<class T> std::ostream& operator<<(std::ostream& out, const Edge<T>& e);



template <class T> class Edge {
	static int counter;
	int id;
	int weight;
	Vertex<T> *vertexStart;
	Vertex<T> *vertexEnd;
public:
	Edge(int weight= 0, Vertex<T> *start = nullptr, Vertex<T> *end = nullptr) {
		id = counter++;
		this->weight = weight;
		vertexStart = start;
		vertexEnd = end;
	}
	Edge(const Edge<T>& e){
		id=e.id;
		weight=e.weight;
		vertexStart=e.vertexStart;
		vertexEnd=e.vertexEnd;
	}
	virtual ~Edge(){
		delete[] vertexEnd;
		delete[] vertexStart;
	}

	void setWeight(int w){
		weight = w;
	}
	void setStart(Vertex<T>* s){ //exception
		if(s != nullptr)
			vertexStart = s;
		else throw Null_vertex("\nVertex is null!");
	}
	void setEnd(Vertex<T>* e){//exception
		if(e != nullptr)
			vertexEnd = e;
		else {std::cerr<<"\nEdge<>::setEnd()";
			throw Null_vertex("\nVertex is null!");
		}
	}

	int getWeight()const{
		return weight;
	}
	int getId()const{
		return id;
	}
	Vertex<T>* getStart()const{
		return vertexStart;
	}
	Vertex<T>* getEnd()const{
		return vertexEnd;
	}

	bool operator==(const Edge<T>& e)const{
		return this->id == e.id;
	}
	bool operator!=(const Edge<T>& e)const{
		return !(*this == e);
	}
	Edge<T>& operator++(){//prefix operator
		++weight;
		return *this;
	}//++e
	const Edge<T>& operator=(const Edge<T>& e){
		this->id = e.id;
		this->weight = e.weight;

		delete vertexStart;
		delete vertexEnd;

		this->vertexStart = &*(e.vertexStart);
		this->vertexEnd = &*(e.vertexEnd);

		return *this;
	}
	friend std::ostream& operator<<<T>(std::ostream& out, const Edge<T>& e);


};
template <typename T> int Edge<T>::counter = 0;
template<typename Y>
	std::ostream& operator<<(std::ostream& out, const Edge<Y>& e){

	out << "\nEdge id: " << e.id
		<< "\nEdge weight: "<< e.weight;

	return out;
}
#endif /* EDGE_HPP_ */
