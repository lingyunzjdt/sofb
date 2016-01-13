#!/bin/bash

caput -a l:SR:APHLA:SOFB{BPM}Index 5 1 3 2 4 0
caput -a l:SR:APHLA:SOFB{BPM}Sel 5 1 1 1 0 0
caput -a l:SR:APHLA:SOFB{BPM}Index_ 5 5 5 5 5 5

caput l:SR:APHLA:SOFB{BPM}_shuffle_asub_.PROC 1
caget  l:SR:APHLA:SOFB{BPM}Index_
