//=============================
// Up/Down Counter Header
//=============================
#ifndef UPDOWN_COUNTER_H
#define UPDOWN_COUNTER_H

#include <systemc.h>

SC_MODULE(UpDownCounter) {
    sc_in<bool> clk;
    sc_in<bool> pe;
    sc_in<bool> ud;
    sc_in<bool> bd;
    sc_in<sc_uint<4>> p;
    sc_out<sc_uint<4>> q;

    sc_uint<4> count;

    void process() {
        if (pe.read()) {
            count = p.read();
        } else if (clk.posedge()) {
            if (ud.read()) {
                // Count Up
                if (bd.read() == 0 && count < 9) count++;
                else if (bd.read() == 1 && count < 15) count++;
            } else {
                // Count Down
                if (count > 0) count--;
            }
        }
        q.write(count);
    }

    SC_CTOR(UpDownCounter) : count(0) {
        SC_METHOD(process);
        sensitive << clk.pos();
    }
};

#endif

