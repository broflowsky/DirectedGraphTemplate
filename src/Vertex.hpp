/*
 * Vertex.h
 *
 *  Created on: Apr 16, 2018
 *      Author: vpuyf
 */

#ifndef VERTEX_HPP_
#define VERTEX_HPP_

#include <vector>
#include <iostream>

#include "Edge.hpp"
using std::vector;

template<class T> class Vertex;
template<class Y> std::ostream& operator<<(std::ostream& out, const Vertex<Y>& v);//forward declaration

template<class T> class Vertex {
	static int counter;
	T value;
	int id;
	vector<Edge<T>*> edges;

public:

	Vertex(T t = T()) {
		value = t;//default constructor for type T
		id = counter++;
	};
	Vertex(const Vertex<T>& v){
		value = v.value;
		id = v.id;
		edges = v.edges;//improve may be a better way to do this
	}
	virtual ~Vertex(){

	}

	void setValue(T t){
		value = t;
	}


	T getValue()const{
		return value;
	}
	int getId()const{
		return id;
	}
	void add(Edge<T>& e){
		edges.push_back(&e);
	}
	void remove(Edge<T>& e){
		edges.remove(e);
	}

	const vector<Edge<T>*>& getListEdge()const{
		return edges;
	}

	bool operator==(const Vertex<T>& v)const{
		return id == v.id;
	}
	bool operator!=(const Vertex<T>& v)const{
		return !(*this == v);
	}
	const Vertex<T>& operator=(const Vertex<T>& v){
		this->id = v.id;
		this->edges.clear();
		this->edges = v.edges;
		this->value = v.value;
		return *this;
	}
	friend std::ostream& operator<<<T>(std::ostream& out, const Vertex<T>& v);
};

template <class T> int Vertex<T>::counter = 0;
template<class Y>
	std::ostream& operator<<(std::ostream& out, const Vertex<Y>& v){
		out << "\nVertex id: " << v.id
			<< "\nVertex value: "<< v.value;

		return out;
	}

#endif /* VERTEX_HPP_ */
