
#include "driver.h"
#include "monitor.h"
#include "ViterbiEncoder.h"
#include "systemc.h"


int sc_main(int argc , char *argv[] )
	{
	sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated",
	                                           sc_core::SC_DO_NOTHING );

	sc_signal<sc_bit, SC_MANY_WRITERS> in,out1,out2;
	sc_clock clk("clock", 10, SC_NS, 0.5, 10, SC_NS, true);
	sc_trace_file *tf; 

	driver d1("driver");
	d1.in(in);

	Viterbi_Encoder e("ViterbiEncoder");
	e.in(in);
	e.clk(clk);
	e.op1(out1);
	e.op2(out2);


	monitor m1("monitor");
	m1.in(in);
	m1.clk(clk);
	m1.op1(out1);
	m1.op2(out2);

	tf = sc_create_vcd_trace_file("waves");
 	sc_trace(tf, clk, "Clock");
 	sc_trace(tf, in, "Input");
 	sc_trace(tf, out1, "Out1");
  sc_trace(tf, out2, "Out2");

	sc_start();/**< start the simulation and run indefinately */

	return 0;/**< Return Success */
	}
