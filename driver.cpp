/*
 * driver.cpp
 *
 *  Created on: May 1, 2019
 *      Author: bro
 */



//file: driver.cpp
// this file contains the process definitions
#include "driver.h"

void driver::prc_driver()
{
	in = sc_bit('1');
	wait(10, SC_NS);

	in = sc_bit('0');
	wait(10, SC_NS);

	in = sc_bit('1');
	wait(10, SC_NS);

	in = sc_bit('1');
	wait(10, SC_NS);

	in = sc_bit('0');
	wait(10, SC_NS);

	in = sc_bit('0');
	wait(10, SC_NS);

	sc_stop();
}
