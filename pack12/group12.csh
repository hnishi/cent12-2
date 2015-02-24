#!/bin/csh
#this script excute the "cent" from start_resnum to end_resnum
#USAGE: ./forgnu.csh (start_resnum) (end_resnum) (coefficient_sigma) (Rufile) 
  
icc ./pack12/cent12.c -o ./pack12/cent12

# CHECK ERROR
if($#argv == 0) then
        echo "ERROR: argument error"
        echo "Usage: ./group10.csh start_resnum end_resnum coefficient_sigma RuFile"
        exit 1
endif

if(-d 'pdbtmp')then
else
echo "ERROR: pdbtmp don't exist"
exit 1
endif

if(-d 'result12')then
else
mkdir result12
endif
if(-d 'result12/outpdb_cor')then
else
mkdir result12/outpdb_cor
endif
if(-d 'result12/outpdb_dis')then
else
mkdir result12/outpdb_dis
endif
if(-d 'result12/rslt')then
else
mkdir result12/rslt
endif
if(-d 'result12/exam')then
else
mkdir result12/exam
endif
if(-d 'result12/graph1')then
else
mkdir result12/graph1
endif
if(-d 'result12/graph2')then
else
mkdir result12/graph2
endif

# EXECUTE
set i
set j
@ i=$argv[1]
@ j=$argv[2]
@ j++
set k
@ k=$argv[3]
while($i<$j)
if(-d 'result12/outpdb_dis/'$k'')then
else
mkdir result12/outpdb_dis/$argv[3]
endif
if(-d 'result12/outpdb_cor/'$k'')then
else
mkdir result12/outpdb_cor/$argv[3]
endif
./pack12/cent12 $argv[4] $i $argv[3]
@ i++
end




