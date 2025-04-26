############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project mux
set_top mux4to1
add_files mux44_11/mux_func.cpp
add_files mux44_11/mux_func.h
add_files mux44_11/mux_func.cpp
add_files mux44_11/mux_func.h
add_files -tb mux44_11/mux_tb.cpp
add_files -tb mux44_11/mux_tb.cpp
open_solution "solution1"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
#source "./mux/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
