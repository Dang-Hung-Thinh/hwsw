#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <systemc.h>

SC_MODULE(Controller) {
    sc_in<bool> clk, reset;
    sc_in<bool> a_gt_b, a_lt_b, a_eq_b;
    sc_out<bool> sel_x, sel_y;
    sc_out<bool> load_x, load_y, load_gcd;
    sc_out<sc_uint<2>> state;

    enum States {IDLE = 0, CALCULATE = 1, DONE = 2};
    sc_signal<States> current_state, next_state;

    void state_transition() {
        if (reset.read())
            current_state = IDLE;
        else if (clk.posedge())
            current_state = next_state;
    }

    void next_state_logic() {
        switch (current_state.read()) {
            case IDLE:
                next_state = CALCULATE;
                break;
            case CALCULATE:
                if (a_eq_b.read())
                    next_state = DONE;
                else
                    next_state = CALCULATE;
                break;
            case DONE:
                next_state = IDLE;
                break;
        }
        state.write(current_state.read());
    }

    void output_logic() {
        switch (current_state.read()) {
            case IDLE:
                sel_x.write(0);
                sel_y.write(0);
                load_x.write(1);
                load_y.write(1);
                load_gcd.write(0);
                break;
            case CALCULATE:
                if (a_gt_b.read()) {
                    sel_x.write(1);
                    sel_y.write(0);
                    load_x.write(1);
                    load_y.write(0);
                    load_gcd.write(0);
                } else if (a_lt_b.read()) {
                    sel_x.write(0);
                    sel_y.write(1);
                    load_x.write(0);
                    load_y.write(1);
                    load_gcd.write(0);
                } else {
                    sel_x.write(0);
                    sel_y.write(0);
                    load_x.write(0);
                    load_y.write(0);
                    load_gcd.write(1);
                }
                break;
            case DONE:
                sel_x.write(0);
                sel_y.write(0);
                load_x.write(0);
                load_y.write(0);
                load_gcd.write(0);
                break;
        }
    }

    SC_CTOR(Controller) {
        SC_METHOD(state_transition);
        sensitive << clk.pos();
        SC_METHOD(next_state_logic);
        sensitive << current_state << a_gt_b << a_lt_b << a_eq_b;
        SC_METHOD(output_logic);
        sensitive << current_state << a_gt_b << a_lt_b << a_eq_b;
    }
};

#endif

