/*!**************************************************************************/
/*	\file 		decoderTestBench.cpp
 *
 *	\brief 		This file creates test cases for the given viterbi module
 *
 *	\author		Arjun Haritsa
 *	\date		30-Jun-2019
 */
/***************************************************************************/
#include  <systemc.h>
#include  <iostream>

#include "viterbi_decoder_testBench.h"

void FUN_PrintDataStream_v (unsigned int l_value_ui);

/* Test cases */
#if	C_TESTCASE == 001

	const unsigned int xTestArraySize = 4;
	unsigned int xTestArray[xTestArraySize] = {0b11, 0b11, 0b01, 0b11};

#elif C_TESTCASE == 002

	const unsigned int xTestArraySize = 4;
	unsigned int xTestArray[xTestArraySize] = {0b00, 0b11, 0b00, 0b10};

#elif C_TESTCASE == 003

	const unsigned int xTestArraySize = 4;
	unsigned int xTestArray[xTestArraySize] = {0b00, 0b00, 0b11, 0b00};

#elif C_TESTCASE == 004

	const unsigned int xTestArraySize = 9;
	unsigned int xTestArray[xTestArraySize] = {0b00, 0b11, 0b00, 0b10, 0b010, 0b00, 0b10, 0b10, 0b00 };

#else
	const unsigned int xTestArraySize = 1;
	unsigned int xTestArray[xTestArraySize] = {0b00};

	#error undefined testcase.
#endif

/*!*************************************************************************
 *
 *\brief		Function that is handshaking enabled, outputs encoded data
 *
 *\param 		void
 *\return 		void
 *
 *\param[in]	system clock
 *\param[in]	test array
 *\param[in]	input_ready - handshaking
 *\param[out]	encoded bit stream
 *
 *\ingroup 	viterbiDecoder_Test_Functions
 ***************************************************************************/

void viterbi_testbench::FUN_Execute_TestBench_v(void)
{
		/* Reset the module */
		encodedValue.write(0);

		input_valid.write(0);

		reset.write(1);
		wait();
		reset.write(0);
		wait();

		for(unsigned int i = 0; i < xTestArraySize ; i++)
		{
			input_valid.write(1);
			encodedValue.write(xTestArray[i]);
			beginTime = sc_time_stamp();

			do
			{
				wait();
			}
			while(!input_ready.read());

			input_valid.write(0);
		}

}

/*!*************************************************************************
 *
 *\brief		Function that is handshaking enabled, outputs decoded data
 *
 *\param 		void
 *\return 		void
 *
 *\param[in]	system clock
 *\param[in]	decoded value
 *\param[in]	output_valid - handshaking
 *\param[out]	decoded bit stream
 *
 *\ingroup 	viterbiDecoder_Test_Functions
 ***************************************************************************/

void viterbi_testbench::FUN_Monitor_TestBench(void)
{
	unsigned int decoderOutput;

	output_ready.write(0);

	for(unsigned int i = 0; i < xTestArraySize ; i++)
	{
		output_ready.write(1);

		do
		{
			wait();
		}
		while(!output_valid.read());

		decoderOutput = decodedValue.read();
		EndTime = sc_time_stamp();

		output_ready.write(0);

		Latency = EndTime - beginTime;

		FUN_PrintDataStream_v(decoderOutput);
		cout << "Latency is " << Latency << endl;
	}

	sc_stop();
}

/*!*************************************************************************
 *
 *\brief		Function that mirrors a given value (MSB to LSB and viceversa)
 *
 *\param 		unsigned int value to be printed after mirroring
 *\return 		void
 *
 *\ingroup 	viterbiDecoder_Test_Functions
 ***************************************************************************/
void FUN_PrintDataStream_v (unsigned int l_value_ui)
{
	cout << "Decoded Bit Stream is : ";

	for(int i = 0; i < xTestArraySize; i++)
	{
		cout << ((l_value_ui >> i) & 1)  << " ";
	}
}
