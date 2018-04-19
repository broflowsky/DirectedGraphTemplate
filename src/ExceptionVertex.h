/*
 * ExceptionVertex.h
 *
 *  Created on: Apr 16, 2018
 *      Author: vpuyf
 */

#ifndef EXCEPTIONVERTEX_H_
#define EXCEPTIONVERTEX_H_
#include <exception>
#include <string>
using std::string;
using std::exception;

class ExceptionVertex : public std::exception{
protected: std::string error;
public:
	ExceptionVertex(std::string = "No message provided");
	virtual std::string what() = 0 ;
};

#endif /* EXCEPTIONVERTEX_H_ */
