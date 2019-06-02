/*
 * monitor.h
 *
 *  Created on: May 1, 2019
 *      Author: bro
 */

#ifndef MONITOR_H_
#define MONITOR_H_

//file: monitor.h
//this the monitor module
#include "systemc.h"

SC_MODULE(monitor)
{
	 sc_in<sc_bit> in;
	 sc_out<sc_bit> op1,op2;
	 sc_in<bool> clk;

void prc_monitor();


SC_CTOR(monitor)
{

	SC_METHOD(prc_monitor);
	sensitive << clk ;
}
};


#endif /* MONITOR_H_ */
