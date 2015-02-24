#!/bin/csh
#USAGE: ./zenb.csh "first resnum" "end resnum"

# CHECK ERROR
if($#argv == 0) then
        echo "ERROR: argument error"
        echo "USAGE: ./zenb.csh (first resnum) (end resnum)"
        exit 1
endif



if(-d 'result12/graph3')then #make directory
else
mkdir result12/graph3
endif

icc ./pack12/grph3.c -o pack12/grph3 #compile

./pack12/grph3 $argv[1] $argv[2] 0 #make graph3

@ i=$argv[1]
@ j=$argv[2]

cp ./result12/rslt/0_"$i"_"$j"g3.dat ./pack12/tmp.txt

gnuplot ./pack12/gng12.plt

 
