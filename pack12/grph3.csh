#!/bin/csh
#USAGE: ./zenb.csh "first resnum" "end resnum"

# CHECK ERROR
if($#argv == 0) then
        echo "ERROR: argument error"
        echo "USAGE: ./zenb.csh (first resnum) (end resnum)"
        exit 1
endif


# MAKE DIRECTORY
if(-d 'result12/graph3')then
else
mkdir result12/graph3
endif
if(-d 'result12/graph3/tmp')then
else
mkdir result12/graph3/tmp
endif
if(-f './pack12/tmp.txt')then
rm ./pack12/tmp.txt
endif

icc ./pack12/grph3.c -o pack12/grph3 #compile

./pack12/grph3 $argv[1] $argv[2] 0 #make graph3

@ i=$argv[1]
@ j=$argv[2]

cp ./result12/rslt/0_"$i"_"$j"g3.dat ./pack12/tmp.txt

gnuplot ./pack12/gng12.plt

if(-d 'result12/graph3/'$i'_'$j'_g3')then # ARRANGEMENT
rm -r  ./result12/graph3/"$i"_"$j"_g3
endif
mv  ./result12/graph3/tmp  ./result12/graph3/"$i"_"$j"_g3 
