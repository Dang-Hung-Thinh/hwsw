#include <systemc.h>
#include "libpalsres.h"

SC_MODULE(ShiftRegisterTB) {
    sc_signal<bool> clk;
    sc_signal<sc_uint<8>> input;
    sc_signal<sc_uint<2>> sh;
    sc_signal<sc_uint<8>> output;

    ShiftRegister* reg;

    void clk_gen() {
        while (true) {
            clk.write(false);
            wait(5, SC_NS);
            clk.write(true);
            wait(5, SC_NS);
        }
    }

    void stim() {
        input.write(0xA5); // 10100101
        sh.write(2); // load
        wait(10, SC_NS);

        sh.write(1); // shift left
        for (int i = 0; i < 3; i++) wait(10, SC_NS);

        sh.write(0); // shift right
        for (int i = 0; i < 3; i++) wait(10, SC_NS);

        sh.write(3); // hold
        for (int i = 0; i < 3; i++) wait(10, SC_NS);

        sc_stop();
    }

    SC_CTOR(ShiftRegisterTB) {
        reg = new ShiftRegister("shiftreg");
        reg->clk(clk);
        reg->input(input);
        reg->sh(sh);
        reg->output(output);

        SC_THREAD(clk_gen);
        SC_THREAD(stim);
    }
};

int sc_main(int argc, char* argv[]) {
    ShiftRegisterTB tb("tb");

    sc_trace_file* tf = sc_create_vcd_trace_file("shift_register");
    sc_trace(tf, tb.clk, "clk");
    sc_trace(tf, tb.input, "input");
    sc_trace(tf, tb.sh, "sh");
    sc_trace(tf, tb.output, "output");

    sc_start();
    sc_close_vcd_trace_file(tf);
    return 0;
}
