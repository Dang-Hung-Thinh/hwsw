#ifndef MUX_H
#define MUX_H

#include <systemc.h>

SC_MODULE(Mux) {
    sc_in<sc_uint<4>> in0, in1;
    sc_in<bool> sel;
    sc_out<sc_uint<4>> out;

    void do_mux() {
        if (sel.read() == 0)
            out.write(in0.read());
        else
            out.write(in1.read());
    }

    SC_CTOR(Mux) {
        SC_METHOD(do_mux);
        sensitive << in0 << in1 << sel;
    }
};

#endif

