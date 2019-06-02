/**
 * @file monitor.h
 * @author bro
 * @date May 1, 2019
 * @brief Monitor header for the Viterbi Encoder
 *
 * The header file defines the input and output for the display
 */


#ifndef MONITOR_H_
#define MONITOR_H_


#include "systemc.h"

SC_MODULE(monitor)
{
	 sc_in<sc_bit> in;/**< Incoming bit to the Encoder */
	 sc_out<sc_bit> op1,op2;/**< Output bits from the Encoder */
	 sc_in<bool> clk;/**< Clock driver */

void prc_monitor();


SC_CTOR(monitor)
{

	SC_METHOD(prc_monitor);
	sensitive << clk ;
}
};


#endif /* MONITOR_H_ */
