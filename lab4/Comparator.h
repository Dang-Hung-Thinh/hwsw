#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <systemc.h>

SC_MODULE(Comparator) {
    sc_in<sc_uint<4>> a, b;
    sc_out<bool> a_gt_b, a_lt_b, a_eq_b;

    void do_compare() {
        if (a.read() > b.read()) {
            a_gt_b.write(true);
            a_lt_b.write(false);
            a_eq_b.write(false);
        } else if (a.read() < b.read()) {
            a_gt_b.write(false);
            a_lt_b.write(true);
            a_eq_b.write(false);
        } else {
            a_gt_b.write(false);
            a_lt_b.write(false);
            a_eq_b.write(true);
        }
    }

    SC_CTOR(Comparator) {
        SC_METHOD(do_compare);
        sensitive << a << b;
    }
};

#endif

