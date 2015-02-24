#!/bin/csh
#USAGE: ./zenb.csh "first resnum" "end resnum"

icc ./pack12/exam12.c -o pack12/exam12 #compile
icc ./pack12/rslt12.c -o pack12/rslt12


./pack12/group12.csh $argv[1] $argv[2] 0 Rufile #make group
./pack12/group12.csh $argv[1] $argv[2] 1 Rufile
./pack12/group12.csh $argv[1] $argv[2] 2 Rufile
./pack12/group12.csh $argv[1] $argv[2] 3 Rufile 



./pack12/rslt12 $argv[1] $argv[2] 0 #make histogram
@ i=$argv[1]
@ j=$argv[2]
if(-d 'result12/graph1')then
else
mkdir result12/graph1
endif
if(-f './pack12/tmp.txt')then
rm ./pack12/tmp.txt
endif
cp ./result12/rslt/0_"$i"_"$j"A-B.dat ./pack12/tmp.txt
gnuplot ./pack12/eng12.plt


# make distribution map
set i 
set j
@ i=$argv[1]
@ j=$argv[2]
@ j++
while($i<$j)
if(-d 'result12/graph2/tmp')then
else
mkdir result12/graph2/tmp
endif
./pack12/exam12 "$i" "0.25"
paste ./result12/exam/"$i"_A_exam.dat ./result12/exam/"$i"_B_exam.dat > pack12/histo.txt
gnuplot ./pack12/fng12.plt
if(-d 'result12/graph2/'$i'')then
rm -r  ./result12/graph2/$i
endif
mv  ./result12/graph2/tmp  ./result12/graph2/$i
@ i++
end















