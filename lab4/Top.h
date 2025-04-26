// Top.h
#ifndef TOP_H
#define TOP_H

#include <systemc.h>

SC_MODULE(Top) {
    // Ports
    sc_in<bool> clk, reset, go;
    sc_in<sc_uint<4>> x_in, y_in;
    sc_out<sc_uint<4>> gcd_out;
    sc_out<sc_uint<2>> state_out;

    // Internal variables if needed
    sc_uint<4> x_reg, y_reg;
    sc_uint<2> state;

    void fsm() {
        if (reset.read()) {
            state = 0;
            gcd_out.write(0);
        } else {
            switch(state) {
                case 0: // Idle
                    if (go.read()) {
                        x_reg = x_in.read();
                        y_reg = y_in.read();
                        state = 1;
                    }
                    break;
                case 1: // Compare
                    if (x_reg > y_reg) {
                        x_reg = x_reg - y_reg;
                    } else if (y_reg > x_reg) {
                        y_reg = y_reg - x_reg;
                    } else {
                        state = 2;
                    }
                    break;
                case 2: // Done
                    gcd_out.write(x_reg); // or y_reg
                    break;
            }
        }
        state_out.write(state);
    }

    // Constructor
    SC_CTOR(Top) {
        SC_METHOD(fsm);
        sensitive << clk.pos(); // trigger on rising edge
    }
};

#endif // TOP_H

