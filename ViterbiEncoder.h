/**
 * @file ViterbiEncoder.h
 * @author bro
 * @date May 1, 2019
 * @brief Header for the Viterbi Encoder
 *
 * The header file defines the input, output, clock and state of the encoder
 */

#ifndef VITERBIENCODER_H_
#define VITERBIENCODER_H_

#include<systemc.h>

SC_MODULE(Viterbi_Encoder){
	 sc_in<bool> clk;/**< Clock driving the Encoder */
	 sc_in<sc_bit> in;/**< Incoming bit to the Encoder */
	 sc_out<sc_bit> op1,op2;/**< Output bits from the Encoder */
	 sc_bv<3> r;/**<  3 bit Encoder */

	void encode();

	SC_CTOR( Viterbi_Encoder ) {
		r = "000";/**< Initial state of the Encoder */
		SC_THREAD(encode);
	 	sensitive<< clk;/**< The Encoder is sensitive to the change in clock levels */
	    }
};

#endif
