/*
 * Nullvertex.h
 *
 *  Created on: Apr 16, 2018
 *      Author: vpuyf
 */

#ifndef NULLVERTEX_H_
#define NULLVERTEX_H_

#include "ExceptionVertex.h"
#include <string>

class Null_vertex: public ExceptionVertex {
public:
	Null_vertex(std::string error) : ExceptionVertex(error){}
	std::string what(){ return error;}

};

#endif /* NULLVERTEX_H_ */
