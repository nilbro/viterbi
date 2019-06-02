/**
 * @file ViterbiEncoder.cpp
 * @author bro
 * @date May 1, 2019
 * @brief Implements the behaviour of the encoder
 *
 * The file implements the shifting of bits through the encoder
 * Also defines the outputs according to the convolutional codes
 */

#include "ViterbiEncoder.h"
#include <systemc.h>

/**
 * This method will be used to drive a single character to the lcd.
 * @author bro
 * @param in The Input Bit
 * @param out1 Output Bit 1
 * @param out2 Output Bit 2
 * @param r The Encoder state
 * @date May 1, 2019
 */

void Viterbi_Encoder::encode(void){

	sc_bit out1, out2;
	while (true) {
		wait(); /**< wait for any signal on sensitivity list*/
		r[2] = r[1];
		r[1] = r[0];
		r[0] = in;

		out1 = r[1]^r[2]^r[0];
		out2 = r[0]^r[1];

		op1.write(out1);
		op2.write(out2);

		wait(2, SC_NS); /**< delay to produce outputs.*/

		}
}
