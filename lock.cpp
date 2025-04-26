#include <systemc.h>

// Định nghĩa FSM mở khóa
SC_MODULE(lock_fsm) {
    sc_in<bool> clk, reset, b0, b1; // Input: Clock, Reset, Buttons
    sc_out<bool> unlock;            // Output: Unlock signal

    enum state_t { 
        S_RESET, S_1, S_10, S_101, S_1011, S_10110, S_101100, S_1011001, S_10110011 
    };
    sc_signal<state_t> state, next_state;

    // Xác định trạng thái tiếp theo
    void compute_next_state() {
        switch (state.read()) {
            case S_RESET:   next_state = b1.read() ? S_1 : (b0.read() ? S_RESET : S_RESET); break;
            case S_1:       next_state = b0.read() ? S_10 : S_RESET; break;
            case S_10:      next_state = b1.read() ? S_101 : S_RESET; break;
            case S_101:     next_state = b1.read() ? S_1011 : S_RESET; break;
            case S_1011:    next_state = b0.read() ? S_10110 : S_RESET; break;
            case S_10110:   next_state = b0.read() ? S_101100 : S_RESET; break;
            case S_101100:  next_state = b1.read() ? S_1011001 : S_RESET; break;
            case S_1011001: next_state = b1.read() ? S_10110011 : S_RESET; break;
            case S_10110011: next_state = S_RESET; break;
            default:        next_state = S_RESET; break;
        }
    }

    // Cập nhật trạng thái theo clk
    void update_state() {
        if (reset.read()) 
            state = S_RESET;
        else 
            state = next_state;
    }

    // Xuất tín hiệu mở khóa
    void output_logic() {
        unlock.write(state == S_10110011);
    }

    // Constructor
    SC_CTOR(lock_fsm) {
        SC_METHOD(compute_next_state);
        sensitive << state << b0 << b1;

        SC_METHOD(update_state);
        sensitive << clk.pos() << reset;

        SC_METHOD(output_logic);
        sensitive << state;
    }
};
