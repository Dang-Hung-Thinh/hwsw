#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

#include <systemc.h>

SC_MODULE(ShiftRegister) {
    sc_in<bool> clk;
    sc_in<sc_uint<8>> input;
    sc_in<sc_uint<2>> sh; // 00: shift right, 01: shift left, 10: load, 11: hold
    sc_out<sc_uint<8>> output;

    sc_uint<8> reg;

    void process();

    SC_CTOR(ShiftRegister) {
        SC_METHOD(process);
        sensitive << clk.pos();
        reg = 0;
    }
};

#endif
