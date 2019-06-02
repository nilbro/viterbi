
 /**
  * @file driver.h
  * @author bro
  * @date May 1, 2019
  * @brief Driver header for the Viterbi Encoder
  *
  * The header file defines the input bits to the encoder
  */

#ifndef DRIVER_H_
#define DRIVER_H_


#include "systemc.h"


SC_MODULE (driver) {

	sc_out<sc_bit> in; /**< Incoming bit to the Encoder */
	void encoder_driver(); /**< Function definition of how the inputs are fed to the encoder */

	SC_CTOR( driver) {
		SC_THREAD(encoder_driver);
	}
};


#endif /* DRIVER_H_ */
