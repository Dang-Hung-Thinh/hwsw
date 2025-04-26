#ifndef REGISTER_H
#define REGISTER_H

#include <systemc.h>

SC_MODULE(Register) {
    sc_in<sc_uint<4>> d;
    sc_in<bool> load, reset, clk;
    sc_out<sc_uint<4>> q;

    sc_uint<4> temp;

    void do_register() {
        if (reset.read()) {
            temp = 0;
        } else if (load.read() && clk.posedge()) {
            temp = d.read();
        }
        q.write(temp);
    }

    SC_CTOR(Register) {
        SC_METHOD(do_register);
        sensitive << clk.pos();
    }
};

#endif

