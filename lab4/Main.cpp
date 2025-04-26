#include <systemc.h>
#include "Top.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> clk, reset, go;
    sc_signal<sc_uint<4>> x_in, y_in;
    sc_signal<sc_uint<4>> gcd_out;
    sc_signal<sc_uint<2>> state_out;

    Top top("top");

    top.clk(clk);
    top.reset(reset);
    top.go(go);
    top.x_in(x_in);
    top.y_in(y_in);
    top.gcd_out(gcd_out);
    top.state_out(state_out);

    // VCD trace setup
    sc_trace_file *wf = sc_create_vcd_trace_file("gcd_waveform");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, reset, "reset");
    sc_trace(wf, go, "go");
    sc_trace(wf, x_in, "x_in");
    sc_trace(wf, y_in, "y_in");
    sc_trace(wf, gcd_out, "gcd_out");
    sc_trace(wf, state_out, "state_out");

    // Initialization
    reset.write(1);
    clk.write(0);
    go.write(0);
    x_in.write(9);
    y_in.write(6);
    sc_start(1, SC_NS);

    reset.write(0);
    sc_start(1, SC_NS);

    go.write(1);

    // Clock loop
    for (int i = 0; i < 30; ++i) {
        clk.write(0);
        sc_start(5, SC_NS);
        clk.write(1);
        sc_start(5, SC_NS);

        cout << "Time: " << sc_time_stamp()
             << " | State: " << state_out.read()
             << " | GCD: " << gcd_out.read()
             << endl;
    }

    // Close VCD
    sc_close_vcd_trace_file(wf);

    return 0;
}

