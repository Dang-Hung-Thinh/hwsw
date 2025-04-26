# This script segment is generated automatically by AutoPilot

# clear list
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_begin
    cg_default_interface_gen_bundle_begin
    AESL_LIB_XILADAPTER::native_axis_begin
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 1 \
    name sel_V \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_sel_V \
    op interface \
    ports { sel_V { I 2 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 2 \
    name d0_V \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_d0_V \
    op interface \
    ports { d0_V { I 1 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 3 \
    name d1_V \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_d1_V \
    op interface \
    ports { d1_V { I 1 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 4 \
    name d2_V \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_d2_V \
    op interface \
    ports { d2_V { I 1 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 5 \
    name d3_V \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_d3_V \
    op interface \
    ports { d3_V { I 1 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 6 \
    name y_V \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_y_V \
    op interface \
    ports { y_V { O 1 vector } y_V_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -1 \
    name ap_ctrl \
    type ap_ctrl \
    reset_level 1 \
    sync_rst true \
    corename ap_ctrl \
    op interface \
    ports { ap_start { I 1 bit } ap_ready { O 1 bit } ap_done { O 1 bit } ap_idle { O 1 bit } } \
} "
}



# merge
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_end
    cg_default_interface_gen_bundle_end
    AESL_LIB_XILADAPTER::native_axis_end
}


