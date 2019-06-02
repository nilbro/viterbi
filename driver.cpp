/**
 * @file driver.cpp
 * @author bro
 * @date May 1, 2019
 * @brief Driver implementation for the Viterbi Encoder
 *
 * The file has the input bits to the encoder
 */

#include "driver.h"

/**
 * This method will be used to drive input bits to the Encoder
 * @author bro
 * @param in The Input Bit
 * @date May 1, 2019
 */

void driver::encoder_driver()
{
	in = sc_bit('1');
	wait(10, SC_NS);

	in = sc_bit('1');
	wait(10, SC_NS);

	in = sc_bit('0');
	wait(10, SC_NS);

	in = sc_bit('1');
	wait(10, SC_NS);

	in = sc_bit('0');
	wait(10, SC_NS);

	in = sc_bit('0');
	wait(10, SC_NS);

	sc_stop();
}
