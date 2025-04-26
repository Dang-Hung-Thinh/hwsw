#include "lock.cpp"

SC_MODULE(testbench) {
    sc_signal<bool> clk, reset, b0, b1, unlock;
    lock_fsm fsm;
    sc_trace_file *wf; // File VCD

    void clock_generator() {
        while (true) {
            clk = 0;
            wait(5, SC_NS);
            clk = 1;
            wait(5, SC_NS);
        }
    }

    void stimulus() {
        reset = 1;
        b0 = 0; b1 = 0;
        wait(10, SC_NS);
        reset = 0;

        // Nhập chuỗi 10110011
        sc_uint<8> sequence = 0b10110011;
        for (int i = 7; i >= 0; i--) {
            b0 = (sequence[i] == 0);
            b1 = (sequence[i] == 1);
            wait(10, SC_NS);
        } // ✅ Đã thêm dấu `}` để kết thúc vòng lặp

        // Giữ trạng thái sau unlock
        b0 = 0; b1 = 0;
        wait(20, SC_NS);

        // Thử sai dữ liệu
        reset = 1;
        wait(10, SC_NS);
        reset = 0;

        b0 = 1; b1 = 0; // Sai ngay từ đầu
        wait(10, SC_NS);
        b0 = 0; b1 = 1; // Reset và thử lại
        wait(10, SC_NS);

        sc_stop(); // Dừng mô phỏng
    } // ✅ Đã thêm dấu `}` để kết thúc hàm stimulus

    void vcd_trace() {
        wf = sc_create_vcd_trace_file("fsm_wave");
        sc_trace(wf, clk, "clk");
        sc_trace(wf, reset, "reset");
        sc_trace(wf, b0, "b0");
        sc_trace(wf, b1, "b1");
        sc_trace(wf, unlock, "unlock");
        sc_trace(wf, fsm.state, "state");

        while (true) wait(); // Chặn thread này chạy mãi
    } // ✅ Đã thêm dấu `}` để kết thúc hàm vcd_trace

    SC_CTOR(testbench) : fsm("FSM") {
        fsm.clk(clk);
        fsm.reset(reset);
        fsm.b0(b0);
        fsm.b1(b1);
        fsm.unlock(unlock);

        SC_THREAD(clock_generator);
        SC_THREAD(stimulus);
        SC_THREAD(vcd_trace);
    } // ✅ Đã thêm dấu `}` để kết thúc constructor
};

int sc_main(int argc, char* argv[]) {
    testbench tb("TB");
    sc_start();
    
    // Đóng file VCD đúng cách
    sc_close_vcd_trace_file(tb.wf);

    return 0;
} // ✅ Đã thêm dấu `}` để kết thúc `sc_main`

