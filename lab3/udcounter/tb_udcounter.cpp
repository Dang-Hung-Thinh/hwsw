//=============================
// Up/Down Counter Testbench
//=============================
#include <systemc.h>
#include "libudcounter.h"

SC_MODULE(UpDownCounterTB) {
    sc_signal<bool> clk, pe, ud, bd;
    sc_signal<sc_uint<4>> p;
    sc_signal<sc_uint<4>> q;

    UpDownCounter* counter;

    void clk_gen() {
        while (true) {
            clk.write(false);
            wait(5, SC_NS);
            clk.write(true);
            wait(5, SC_NS);
        }
    }

    void stim() {
        pe.write(1);
        p.write(0x3);
        wait(10, SC_NS);

        pe.write(0);
        ud.write(1);
        bd.write(0);
        for (int i = 0; i < 10; i++) wait(10, SC_NS);

        ud.write(0);
        for (int i = 0; i < 10; i++) wait(10, SC_NS);

        bd.write(1);
        ud.write(1);
        for (int i = 0; i < 20; i++) wait(10, SC_NS);

        sc_stop();
    }

    SC_CTOR(UpDownCounterTB) {
        counter = new UpDownCounter("counter");
        counter->clk(clk);
        counter->pe(pe);
        counter->ud(ud);
        counter->bd(bd);
        counter->p(p);
        counter->q(q);

        SC_THREAD(clk_gen);
        SC_THREAD(stim);
    }
};

int sc_main(int argc, char* argv[]) {
    UpDownCounterTB tb("tb");
    sc_trace_file* tf = sc_create_vcd_trace_file("updown_counter");

    sc_trace(tf, tb.clk, "clk");
    sc_trace(tf, tb.pe, "pe");
    sc_trace(tf, tb.ud, "ud");
    sc_trace(tf, tb.bd, "bd");
    sc_trace(tf, tb.p, "p");
    sc_trace(tf, tb.q, "q");

    sc_start();
    sc_close_vcd_trace_file(tf);
    return 0;
}

