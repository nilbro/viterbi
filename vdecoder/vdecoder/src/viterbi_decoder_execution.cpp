/*!**************************************************************************/
/*	\file 		decoderTestBench.cpp
 *
 *	\brief 		This file creates test cases for the given viterbi module
 *
 *	\author		Arjun Haritsa
 *	\date		30-Jun-2019
 */
/***************************************************************************/

#include "systemc.h"
#include "viterbi_decoder_functions.h"
#include "viterbi_decoder_testBench.h"


/*!**************************************************************************
 * DECODER MODULE DECLARATION
 * \ingroup viterbiDecoder_Test_Class @{
 ***************************************************************************/

SC_MODULE(mainsystem)
{
	/*Instances*/
	viterbi_decoder 			*lp_vi_decoder;
	viterbi_testbench 			*lp_vi_test;

	/* Input Outputs */
	sc_signal<sc_uint<2> >		input;
	sc_signal<sc_uint<16> >		output;
	sc_signal<bool>				enable;
	sc_signal<bool>				reset;

	/* System clock */
	sc_clock					clock;

	/*Hand shaking*/
	sc_signal<bool>				input_valid;
	sc_signal<bool>				input_ready;
	sc_signal<bool>				output_valid;
	sc_signal<bool>				output_ready;

	/* construct decoder and test bench object and set a clock rate at 1000NS */
	SC_CTOR(mainsystem) : clock ("clock",1000,SC_NS)
	{
		/* signal binding */
		lp_vi_decoder = new viterbi_decoder("lp_vi_decoder");
		lp_vi_decoder->clock(clock);
		lp_vi_decoder->decodedValue(output);
		lp_vi_decoder->encodedValue(input);
		lp_vi_decoder->reset(reset);
		lp_vi_decoder->enable(enable);

		lp_vi_decoder->input_valid(input_valid);
		lp_vi_decoder->input_ready(input_ready);
		lp_vi_decoder->output_valid(output_valid);
		lp_vi_decoder->output_ready(output_ready);

		/* signal binding */
		lp_vi_test	  = new	viterbi_testbench("viterbi_testbench");
		lp_vi_test->clock(clock);
		lp_vi_test->decodedValue(output);
		lp_vi_test->encodedValue(input);
		lp_vi_test->reset(reset);
		lp_vi_test->enable(enable);

		lp_vi_test->input_valid(input_valid);
		lp_vi_test->input_ready(input_ready);
		lp_vi_test->output_valid(output_valid);
		lp_vi_test->output_ready(output_ready);
	}

	~mainsystem()
	{
		delete lp_vi_decoder;
		delete lp_vi_test;
	}
};

/*!*************************************************************************
 * @}
 * *************************************************************************/

int sc_main(int argc, char* argv[]) {

	mainsystem *ms = NULL;

	/* create decoder system object and run it */
	ms = new mainsystem("ms");
	sc_start();

	return(0);
}
