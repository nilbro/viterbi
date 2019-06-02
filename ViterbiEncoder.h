/*
 * ViterbiEncoder.h
 *
 *  Created on: May 4, 2019
 *      Author: bro
 */
#ifndef VITERBIENCODER_H_
#define VITERBIENCODER_H_

#include<systemc.h>

SC_MODULE(Viterbi_Encoder){
	 sc_in<bool> clk;
	 sc_in<sc_bit> in;
	 sc_out<sc_bit> op1,op2;
	 sc_bv<3>  r;

	    // methods
	void encode();

	    //Constructor
	SC_CTOR( Viterbi_Encoder ) {
		r = "000";
		SC_THREAD(encode);
	 	sensitive<< clk;
	    }
};

#endif
