/*
 * driver.h
 *
 *  Created on: May 1, 2019
 *      Author: bro
 */

#ifndef DRIVER_H_
#define DRIVER_H_

//file: driver.h
// this is the driver program for the OR gate
#include "systemc.h"


SC_MODULE (driver) {
	sc_out<sc_bit> in;

	void prc_driver();

	SC_CTOR( driver) {
		SC_THREAD( prc_driver);
	}
};


#endif /* DRIVER_H_ */
