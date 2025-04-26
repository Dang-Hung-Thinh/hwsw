############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project decoder_sc
set_top decoder
add_files ss/decoder.h
add_files -tb ss/decoder_tb.cpp -cflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
config_sdx -optimization_level 0 -target xocc
config_schedule -effort medium -enable_dsp_full_reg
config_export -vivado_phys_opt none
config_compile -name_max_length 256 -pipeline_loops 64
config_bind -effort medium
config_rtl -auto_prefix  -register_reset_num 3
config_interface -m_axi_addr64
set_clock_uncertainty 27%
#source "./decoder_sc/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
