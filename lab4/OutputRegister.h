// OutputRegister.h
#include <systemc.h>

SC_MODULE(OutputRegister) {
    sc_in<bool> clk, reset, enable;
    sc_in<sc_uint<4>> d_in;
    sc_out<sc_uint<4>> d_out;

    sc_uint<4> reg;

    void do_output() {
        if (reset.read())
            reg = 0;
        else if (clk.posedge()) {
            if (enable.read())
                reg = d_in.read();
        }
        d_out.write(reg);
    }

    SC_CTOR(OutputRegister) {
        SC_METHOD(do_output);
        sensitive << clk.pos();
    }
};
