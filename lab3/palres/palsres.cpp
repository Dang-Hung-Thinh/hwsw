#include "libpalsres.h"

void ShiftRegister::process() {
    switch (sh.read()) {
        case 0: // shift right
            reg = reg >> 1;
            break;
        case 1: // shift left
            reg = reg << 1;
            break;
        case 2: // load input
            reg = input.read();
            break;
        case 3: // hold
            // do nothing
            break;
    }
    output.write(reg);
}
