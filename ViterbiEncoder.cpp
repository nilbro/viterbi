/*
 * ViterbiEncoder.cpp
 *
 *  Created on: May 4, 2019
 *      Author: bro
 */
#include "ViterbiEncoder.h"
#include <systemc.h>


void Viterbi_Encoder::encode(void){

	//r = "000";
	sc_bit out1, out2;
	while (1) {
		wait(); // wait for any signal on sensitivity list
		//r = r;

		r[3] = r[2];
		r[2] = r[1];
		r[1] = r[0];
		r[0] = in;
		wait(2, SC_NS); // delay to produce outputs.
		out1 = r[1]^r[2]^r[0];
		out2 = r[0]^r[1];
		op1.write(out1);
		op2.write(out2);
		}
}
