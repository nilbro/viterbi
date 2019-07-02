/*!**************************************************************************/
/*	\file 		viterbi_decoder.h
 *
 *	\brief 		This file defines all the necessary definitions and parameters
 *				of a n,k,m cross functional viterbi decoder
 *
 *	\author		Arjun Haritsa
 *	\date		30-Jun-2019
 */
/***************************************************************************/

#ifndef VITERBI_DECODER_FUNCTIONS_H_
#define VITERBI_DECODER_FUNCTIONS_H_


#include "systemc.h"

/*!**************************************************************************
 * DECODER PREPROCESSING PARAMETERS
 * \ingroup viterbiDecoder_Parameters @{
 ***************************************************************************/

#define C_DECODER_N				2
/*! The number of output bits of the encoder or the input bits to the decoder */

#define C_DECODER_K				1
/*! The number of input bits of the encoder or the output bits to the decoder */

#define C_DECODER_M				3
/*! The number of delays realized by memory registers */

#define C_DECODER_OUTPUT		16
/*! output buffer of the decoder */

#define C_MAX_DEGREE_POLY		9
/*! The maximum number of polynomials required */

#define C_POLYNOMIAL_G1_B		0b110
/*! Define generator polynomial G1 */

#define C_POLYNOMIAL_G2_B		0b111
/*! Define generator polynomial G2 */

#define C_POLYNOMIAL_G3_B		0b000
/*! Define generator polynomial G3 */

#define C_POLYNOMIAL_G4_B		0b000
/*! Define generator polynomial G4 */

#define C_POLYNOMIAL_G5_B		0b000
/*! Define generator polynomial G5 */

#define C_POLYNOMIAL_G6_B		0b000
/*! Define generator polynomial G6 */

#define C_POLYNOMIAL_G7_B		0b000
/*! Define generator polynomial G7 */

#define C_POLYNOMIAL_G8_B		0b000
/*! Define generator polynomial G8 */

#define C_POLYNOMIAL_G9_B		0b000
/*! Define generator polynomial G9 */

/*!*************************************************************************
 * @}
 * *************************************************************************/

/*!**************************************************************************
 * DECODER GLOBAL PARAMETERS
 * \ingroup viterbiDecoder_Datatypes @{
 ***************************************************************************/

typedef struct c_stateTable_N
{
	unsigned int input_i;
	unsigned int currentState_i;
	bool output_i[C_DECODER_N];
	unsigned int nextState_i;
}c_stateTable_N;
/*! state table elemental structure */

typedef struct c_transitionNodes_N
{
	unsigned int output;
	unsigned int hammingDistance;
}c_transitionNodes_N;
/*! Node definition of Trellis diagram */

/*!*************************************************************************
 * @}
 * *************************************************************************/

/*!**************************************************************************
 * DECODER FUCNTION SWITCHES
 * \ingroup viterbiDecoder_FunctionSwitches @{
 ***************************************************************************/

#define	C_DEBUGTRACE_ENABLE		1
/*! Enable console tracing */

#define C_DEBUGTRACE_DISABLE	0
/*! Disable console tracing */

#define C_DEBUGTRACE			C_DEBUGTRACE_DISABLE
/*! Function switch to enable/disable tracing */

/*!*************************************************************************
 * @}
 * *************************************************************************/


/*!**************************************************************************
 * DECODER MODULE DECLARATION
 * \ingroup viterbiDecoder_Class @{
 ***************************************************************************/

SC_MODULE (viterbi_decoder)
{
	sc_in_clk     						clock ;
	/*! @ingroup viterbiDecoder_Private Clock input of the module */

	sc_in<bool>   						reset ;
	/*! @ingroup viterbiDecoder_Private Reset of the module */

	sc_in<bool>   						enable;
	/*! @ingroup viterbiDecoder_Private Enable of the module */

	sc_out<sc_uint <C_DECODER_OUTPUT> > decodedValue;
	/*! @ingroup viterbiDecoder_Private output of the decoder */

	sc_in<sc_uint <C_DECODER_N> > 		encodedValue;
	/*! @ingroup viterbiDecoder_Private output of the decoder */


	/* Handshaking mechanism */

	sc_in<bool>							input_valid;
	/*! @ingroup viterbiDecoder_Private input valid from subsequent module */

	sc_out<bool>						input_ready;
	/*! @ingroup viterbiDecoder_Private current module ready to receive values from the subsequent module */

	/* Output Handshaking */

	sc_out<bool>						output_valid;
	/*! @ingroup viterbiDecoder_Private output is valid to the subsequent module */

	sc_in<bool>							output_ready;
	/*! @ingroup viterbiDecoder_Private subsequent module is ready to receive the input */


	void FUN_Execute_ViterbiDecoder_v(void);

	/*!*************************************************************************
	 *
	 *\brief	Constructor of the class viterbi_decoder
	 *
	 *\ingroup 	viterbiDecoder_Functions
	 ***************************************************************************/
	SC_CTOR (viterbi_decoder)
	{
		 SC_CTHREAD(FUN_Execute_ViterbiDecoder_v, clock.pos());
		 reset_signal_is(reset,true);
	}
};

/*!*************************************************************************
 * @}
 * *************************************************************************/

#endif /* viterbi_DECODER_BA_H_ */
