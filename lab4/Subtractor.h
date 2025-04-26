#ifndef SUBTRACTOR_H
#define SUBTRACTOR_H

#include <systemc.h>

SC_MODULE(Subtractor) {
    sc_in<sc_uint<4>> a, b;
    sc_out<sc_uint<4>> out;

    void do_subtract() {
        if (a.read() > b.read())
            out.write(a.read() - b.read());
        else
            out.write(b.read() - a.read());
    }

    SC_CTOR(Subtractor) {
        SC_METHOD(do_subtract);
        sensitive << a << b;
    }
};

#endif

