/*
 * NullEdge.h
 *
 *  Created on: Apr 16, 2018
 *      Author: vpuyf
 */

#ifndef NULLEDGE_H_
#define NULLEDGE_H_

#include "ExceptionVertex.h"

class Null_Edge: public ExceptionVertex {
public:
	Null_Edge(string error):ExceptionVertex(error){}
	string what(){ return error;}
};

#endif /* NULLEDGE_H_ */
