/*!**************************************************************************/
/*	\file 		viterbi_decoder.cpp
 *
 *	\brief 		This file declares all functional  modules to
 *				realize viterbi in all n,k,m
 *
 *	\author		Arjun Haritsa
 *	\date		30-Jun-2019
 */
/***************************************************************************/

#include "viterbi_decoder_functions.h"

#include <systemc.h>
#include <iostream>
#include <bitset>
#include <string.h>

using namespace std;

void FUN_Calculate_StateTable_v(void);
bool FUN_XOR_IndividualBitsOfASingleInt_b(unsigned int l_value_i);
c_transitionNodes_N FUN_viterbiDecoder_wTrellis_v(unsigned int l_currentStreamValue_ui);
unsigned int FUN_CalculateHammingDistance_ui(unsigned int l_value1_i, unsigned int l_value2_i);
unsigned int FUN_CombineIndividualBits_ui(bool* l_bitValue_b, unsigned int l_size_ui);

/*!**************************************************************************
 * DECODER PREPROCESSING PARAMETERS
 * \ingroup viterbiDecoder_GlobalVariables @{
 ***************************************************************************/

/*! number of states that a decoder can have */
unsigned int g_numberOfStates_i = (1 << C_DECODER_M);

/*! Defined polynomials to generate state table */
const unsigned int gc_polynomialsG_i[C_MAX_DEGREE_POLY] = {
															C_POLYNOMIAL_G1_B,
															C_POLYNOMIAL_G2_B,
															C_POLYNOMIAL_G3_B,
															C_POLYNOMIAL_G4_B,
															C_POLYNOMIAL_G5_B,
															C_POLYNOMIAL_G6_B,
															C_POLYNOMIAL_G7_B,
															C_POLYNOMIAL_G8_B,
															C_POLYNOMIAL_G9_B
														  };

/* define the required number of states and transitions the encoder can have */
static c_stateTable_N g_decoderStateTable_N[1 << C_DECODER_M];

/* define node for a possible combination of inputs for a specific node in trellis diagram */
static c_transitionNodes_N g_bufferedTrellis_Nodes[1 << C_DECODER_M] = {{0}};

/* define node for a possible combination of minimum hamming distance after all accumulation for a specific node in trellis diagram */
static c_transitionNodes_N g_calculatedTrellis_Nodes[1 << C_DECODER_N] = {{0}};

/*!*************************************************************************
 * @}
 * *************************************************************************/

/*!*************************************************************************
 *
 *\brief	This function generates state table for the possible n,k,m
 *
 *\param 	void
 *\return	void
 *
 *\param[in]	n,k,m
 *\param[out]	g_decoderStateTable_N[]
 *
 *\ingroup 	viterbiDecoder_Functions
 ***************************************************************************/
void viterbi_decoder::FUN_Execute_ViterbiDecoder_v(void)
{
	memset(g_decoderStateTable_N, 0, (sizeof(c_stateTable_N) * (1 << C_DECODER_M)));
	memset(g_bufferedTrellis_Nodes, 0, (sizeof(c_transitionNodes_N) * (1 << C_DECODER_M)));
	memset(g_calculatedTrellis_Nodes, 0, (sizeof(c_transitionNodes_N) * (1 << C_DECODER_N)));

	input_ready.write(0);
	output_valid.write(0);
	decodedValue.write(0);
	wait();

	FUN_Calculate_StateTable_v();

	while(1)
	{
		input_ready.write(1);

		do
		{
			wait();
		}
		while(!input_valid.read());

		unsigned int l = encodedValue.read();

		input_ready.write(0);
		wait();

//		cout << "in decoder module input = " << l <<endl;

		c_transitionNodes_N l_outputValue_N = {0};

		l_outputValue_N = FUN_viterbiDecoder_wTrellis_v(l);

//		cout << "in decoder module output = " << l_outputValue_N.output <<endl;

		output_valid.write(1);
		decodedValue.write(l_outputValue_N.output);

		do
		{
			wait();
		}
		while(!output_ready.read());

		output_valid.write(0);
	}
}


/*!*************************************************************************
 *
 *\brief	This function generates state table for the possible n,k,m
 *
 *\param 	void
 *\return	void
 *
 *\param[in]	n,k,m
 *\param[out]	g_decoderStateTable_N[]
 *
 *\ingroup 	viterbiDecoder_Functions
 ***************************************************************************/

void FUN_Calculate_StateTable_v(void)
{
	/* define local loop variables */
	unsigned int i = 0, j = 0, k = 0, l = 0;

	/* define array size */
	unsigned int l_arrayInputSize_i = 1 << C_DECODER_K;

	/* define number of inputs */
	unsigned int l_arrayInputValues[l_arrayInputSize_i];

	/* fill the combinations of inputs that an encoder can have */
	for(i = 0; i < l_arrayInputSize_i; i++)
		l_arrayInputValues[i] = i;

	/* form the state table */
	for(l = 0, i = 0, j = 0; j < g_numberOfStates_i; j++, i++)
	{
		/* Clear combination of input pointers and change the state (l) after all combination of inputs*/
		if(i >= l_arrayInputSize_i)
		{
			i = 0;
			l++;
		}

		/* Fill the state table with all possible states, input combinations, next state and outputs based on the polynomials */
		g_decoderStateTable_N[j].currentState_i = l;
		g_decoderStateTable_N[j].input_i = l_arrayInputValues[i];
		g_decoderStateTable_N[j].nextState_i = ((l >> C_DECODER_K) | (l_arrayInputValues[i] << (C_DECODER_M - C_DECODER_K - 1)));

		/* Outputs are kept separately as different vectors */
		for (k = 0; k < C_DECODER_N; k++)
		{
			g_decoderStateTable_N[j].output_i[k] = FUN_XOR_IndividualBitsOfASingleInt_b((l | (l_arrayInputValues[i] << (C_DECODER_M - C_DECODER_K))) & gc_polynomialsG_i[k]);
		}
	}

#if (C_DEBUGTRACE == C_DEBUGTRACE_ENABLE)

	cout << endl << endl;
	cout << "=============================================================" << endl;
	cout << "=============================================================" << endl;
	cout << "Calculating possible states for given n,k,m" << endl;
	cout << "=============================================================" << endl;

	/* Display the State table */
	for(i=0; i<g_numberOfStates_i; i++)
	{
		bitset<C_DECODER_M -1> l_currentstate_bs(g_decoderStateTable_N[i].currentState_i);
		bitset<C_DECODER_K> l_input_bs(g_decoderStateTable_N[i].input_i);
		bitset<C_DECODER_M -1> l_nextstate_bs(g_decoderStateTable_N[i].nextState_i);

		cout << "current state = " 	<< l_currentstate_bs
			 << " input = " 		<< l_input_bs
			 << " next state = " 	<< l_nextstate_bs
			 << "\t output = {";

		for(j = 0; j < C_DECODER_N; j++)
		{
			cout << g_decoderStateTable_N[i].output_i[j];

			if (j != C_DECODER_N - 1)
			cout << ",";

		}
		cout << "}" << endl;
	}
#endif
}

/*!*************************************************************************
 *
 *\brief	XOR's all the bits inside a variable and gives boolean output
 *
 *\param 	unsigned int 	: The value inside which XOR should be done
 *\return	boolean			: Final boolean value after XORing the bits
 *
 *\ingroup 	viterbiDecoder_Functions
 ***************************************************************************/

bool FUN_XOR_IndividualBitsOfASingleInt_b(unsigned int l_value_i)
{
	bool l_returnValue_b = 0;
	/* define local loop variables */
	unsigned int i = 0;

	std::bitset<sizeof(unsigned int)> bits(l_value_i);

	for(i = 0; i < sizeof(unsigned int); i++)
		l_returnValue_b ^=bits[i];

	return l_returnValue_b;
}

/*!*************************************************************************
 *
 *\brief	Function that realizes Viterbi decoding
 *
 *\param 	void
 *\return	void
 *
 *\param[in] n,k,m,encoded stream of data
 *\param[out] hamming distance and decoded data
 *
 *\ingroup 	viterbiDecoder_Functions
 ***************************************************************************/

c_transitionNodes_N FUN_viterbiDecoder_wTrellis_v(unsigned int l_currentStreamValue_ui)
{
	/* declare local loop variables */
	unsigned int j =0, k = 0, l = 0;

#if (C_DEBUGTRACE == C_DEBUGTRACE_ENABLE)
	static unsigned int i = 0;
#endif
	/* final outputs */
	c_transitionNodes_N l_returnValue_N ={0};

	/* Step 1: - Calculate hamming distance for the given coded stream for every nodes
	 * 			 accumulated by previous node's hamming distance
	 * 			 Keep its output appended by the previous state's output
	 */
	for(j = 0, l = 0; l < (1 << (C_DECODER_M - C_DECODER_K)); l++)
	{
		for(k = 0; k < g_numberOfStates_i; k++)
		{
			if(g_decoderStateTable_N[k].nextState_i == l)
			{
				g_bufferedTrellis_Nodes[j].output = ((g_calculatedTrellis_Nodes[g_decoderStateTable_N[k].currentState_i].output << C_DECODER_K) | g_decoderStateTable_N[k].input_i);
				g_bufferedTrellis_Nodes[j].hammingDistance = g_calculatedTrellis_Nodes[g_decoderStateTable_N[k].currentState_i].hammingDistance + FUN_CalculateHammingDistance_ui((FUN_CombineIndividualBits_ui(g_decoderStateTable_N[k].output_i, C_DECODER_N)),l_currentStreamValue_ui);

				j++;
			}
		}
	}

	/* Step 2: - consider only the minimum path and save thier output and
	 * 			 hamming distance in the specific nodes
	 */
	for (l = 0; l < (1 << (C_DECODER_M - C_DECODER_K)); l++)
	{
		g_calculatedTrellis_Nodes[l].hammingDistance = g_bufferedTrellis_Nodes[l * (1 << C_DECODER_K)].hammingDistance;
		g_calculatedTrellis_Nodes[l].output = g_bufferedTrellis_Nodes[l * (1 << C_DECODER_K)].output;

		for(k = 1 ; k < (1 << C_DECODER_K); k++)
		{
			if(g_calculatedTrellis_Nodes[l].hammingDistance > g_bufferedTrellis_Nodes[(l * (1 << C_DECODER_K)) + k].hammingDistance)
			{
				g_calculatedTrellis_Nodes[l].hammingDistance = g_bufferedTrellis_Nodes[(l * (1 << C_DECODER_K)) + k].hammingDistance;
				g_calculatedTrellis_Nodes[l].output = g_bufferedTrellis_Nodes[(l * (1 << C_DECODER_K)) + k].output;
			}
		}
	}


	l_returnValue_N.hammingDistance = g_calculatedTrellis_Nodes[0].hammingDistance;
	l_returnValue_N.output = g_calculatedTrellis_Nodes[0].output;

	for(l = 1; l < (1 << (C_DECODER_M - C_DECODER_K)) ; l++)
	{
		if(l_returnValue_N.hammingDistance > g_calculatedTrellis_Nodes[l].hammingDistance)
		{
			l_returnValue_N.hammingDistance = g_calculatedTrellis_Nodes[l].hammingDistance;
			l_returnValue_N.output = g_calculatedTrellis_Nodes[l].output;
		}
	}

#if (C_DEBUGTRACE == C_DEBUGTRACE_ENABLE)

		cout << endl << endl;
		cout << "=============================================================" << endl;
		cout << "=============================================================" << endl;
		cout << "Calculating possible paths for each node at t" << i << endl;
		cout << "=============================================================" << endl;

		for(k = 0, l = 0; l < (1 << C_DECODER_M) ; l++)
		{
			cout << "-----------------------------------" << endl;
			cout << "Path " << ((l) % C_DECODER_N) << " for Node " << k << endl;
			cout << "Hamming Distance   = " << g_bufferedTrellis_Nodes[l].hammingDistance << endl;
			cout << "Accumulated output = " << g_bufferedTrellis_Nodes[l].output << endl;
			cout << endl;

			(((l + 1) % C_DECODER_N) == 0 ? k++ : 0);
		}
			cout << "-----------------------------------" << endl;

		cout << endl << endl;
		cout << "=============================================================" << endl;
		cout << "=============================================================" << endl;
		cout << "Calculating finalized paths for each node at t" << i << endl;
		cout << "=============================================================" << endl;

		for (l = 0; l < (1 << (C_DECODER_M - C_DECODER_K)); l++)
		{
			cout << "=============================================================" << endl;
			cout << "Node                     = " << l << endl;
			cout << "Minimum Hamming Distance = " << g_calculatedTrellis_Nodes[l].hammingDistance << endl;
			cout << "Traced output            = " << g_calculatedTrellis_Nodes[l].output << endl;
		}

		cout << "=============================================================" << endl;
		cout << endl;
		i++;
#endif

	return (l_returnValue_N);
}

/*!*************************************************************************
 *
 *\brief	Function that calculates hamming distance between 2 values
 *
 *\param 	unsigned int	1st value to the hamming distance calculator
 *\param 	unsigned int	2nd value to the hamming distance calculator
 *\return	unsigned int	hamming distance
 *
 *
 *\ingroup 	viterbiDecoder_Functions
 ***************************************************************************/
unsigned int FUN_CalculateHammingDistance_ui(unsigned int l_value1_i, unsigned int l_value2_i)
{
	unsigned int l_returnValue_i = 0;
	unsigned int i = 0;

	std::bitset<sizeof(unsigned int)> l_value1_bs(l_value1_i);
	std::bitset<sizeof(unsigned int)> l_value2_bs(l_value2_i);

	for(i = 0; i < (sizeof(unsigned int)) ;i++)
	{
		((l_value1_bs[i] != l_value2_bs[i]) ? l_returnValue_i++ : 0);
	}

	return l_returnValue_i;
}

/*!*************************************************************************
 *
 *\brief	Function that combines individual bits into one integer
 *
 *\param 	bool*			array of individual bits
 *
 *\return	unsigned int	combined bits
 *
 *
 *\ingroup 	viterbiDecoder_Functions
 ***************************************************************************/

unsigned int FUN_CombineIndividualBits_ui(bool* l_bitValue_b, unsigned int l_size_ui)
{
	/* Loop variables */
	unsigned int i = 0;

	/* return value */
	unsigned int l_returnValue_ui = 0;

	for (i = 0; i < l_size_ui; ++i)
	{
        l_returnValue_ui = ((l_returnValue_ui << 1 ) | l_bitValue_b[i]);
	}
    return l_returnValue_ui;
}
 /*End of module - viterbi_decoder*/
