/*!**************************************************************************/
/*	\file 		decoderTestBench.h
 *
 *	\brief 		This file defines all the necessary definitions and parameters
 *				to test a n,k,m cross functional viterbi decoder
 *
 *	\author		Arjun Haritsa
 *	\date		30-Jun-2019
 */
/***************************************************************************/

#ifndef VITERBI_DECODER_TESTBENCH_H_
#define VITERBI_DECODER_TESTBENCH_H_

#include "systemc.h"

#include "viterbi_decoder_functions.h"

/*!**************************************************************************
 * DECODER TEST PREPROCESSING PARAMETERS
 * \ingroup viterbiDecoder_Test_Parameters @{
 ***************************************************************************/
#define C_TESTCASE				004

/*!*************************************************************************
 * @}
 * *************************************************************************/

/*!**************************************************************************
 * DECODER MODULE DECLARATION
 * \ingroup viterbiDecoder_Test_Class @{
 ***************************************************************************/

SC_MODULE (viterbi_testbench)
{
	sc_in_clk     						clock ;
	/*! @ingroup viterbiDecoder_Test__Private Clock input of the module */

	sc_out<bool>   						reset ;
	/*! @ingroup viterbiDecoder_Test__Private Reset of the module */

	sc_out<bool>   						enable;
	/*! @ingroup viterbiDecoder_Test__Private Enable of the module */

	sc_in<sc_uint <C_DECODER_OUTPUT> > 	decodedValue;
	/*! @ingroup viterbiDecoder_Test_Private output of the decoder */

	sc_out<sc_uint <C_DECODER_N> > 		encodedValue;
	/*! @ingroup viterbiDecoder_Test_Private output of the decoder */


	/* Handshaking mechanism */

	sc_in<bool>							input_ready;
	/*! @ingroup viterbiDecoder_Test_Private current module is ready to receive values from the subsequent module*/

	sc_out<bool>						input_valid;
	/*! @ingroup viterbiDecoder_Test_Private input valid from subsequent module  */

	/* Output Handshaking */

	sc_in<bool>							output_valid;
	/*! @ingroup viterbiDecoder_Test_Private output is valid from the subsequent module */

	sc_out<bool>						output_ready;
	/*! @ingroup viterbiDecoder_Test_Private current module is ready to receive the input */


	/* Latency calculation*/
	sc_time	beginTime,EndTime,Latency;


	void FUN_Execute_TestBench_v(void);
	void FUN_Monitor_TestBench(void);

	/*!*************************************************************************
	 *
	 *\brief	Constructor of the class viterbi_decoder
	 *
	 *\ingroup 	viterbiDecoder_Functions
	 ***************************************************************************/
	SC_CTOR (viterbi_testbench)
	{
		 SC_CTHREAD(FUN_Execute_TestBench_v, clock.pos());
		 SC_CTHREAD(FUN_Monitor_TestBench, clock.pos());

		 reset_signal_is(reset,true);
	}
};

#endif /* VITERBI_DECODER_TESTBENCH_H_ */
