#ifndef DATAPATH_H
#define DATAPATH_H

#include <systemc.h>
#include "Mux.h"
#include "Register.h"
#include "Comparator.h"
#include "Subtractor.h"

SC_MODULE(Datapath) {
    sc_in<bool> clk, reset;
    sc_in<bool> sel_x, sel_y;
    sc_in<bool> load_x, load_y, load_gcd;
    sc_in<sc_uint<4>> x_in, y_in;
    sc_out<bool> a_gt_b, a_lt_b, a_eq_b;
    sc_out<sc_uint<4>> gcd_out;

    sc_signal<sc_uint<4>> x, y, mux_x_out, mux_y_out, subtract_out;

    Mux *mux_x, *mux_y;
    Register *reg_x, *reg_y, *reg_gcd;
    Comparator *comp;
    Subtractor *sub;

    SC_CTOR(Datapath) {
        mux_x = new Mux("mux_x");
        mux_x->in0(x_in);
        mux_x->in1(subtract_out);
        mux_x->sel(sel_x);
        mux_x->out(mux_x_out);

        mux_y = new Mux("mux_y");
        mux_y->in0(y_in);
        mux_y->in1(subtract_out);
        mux_y->sel(sel_y);
        mux_y->out(mux_y_out);

        reg_x = new Register("reg_x");
        reg_x->d(mux_x_out);
        reg_x->load(load_x);
        reg_x->reset(reset);
        reg_x->clk(clk);
        reg_x->q(x);

        reg_y = new Register("reg_y");
        reg_y->d(mux_y_out);
        reg_y->load(load_y);
        reg_y->reset(reset);
        reg_y->clk(clk);
        reg_y->q(y);

        sub = new Subtractor("sub");
        sub->a(x);
        sub->b(y);
        sub->out(subtract_out);

        comp = new Comparator("comp");
        comp->a(x);
        comp->b(y);
        comp->a_gt_b(a_gt_b);
        comp->a_lt_b(a_lt_b);
        comp->a_eq_b(a_eq_b);

        reg_gcd = new Register("reg_gcd");
        reg_gcd->d(x);
        reg_gcd->load(load_gcd);
        reg_gcd->reset(reset);
        reg_gcd->clk(clk);
        reg_gcd->q(gcd_out);
    }
};

#endif

