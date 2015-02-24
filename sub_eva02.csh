#!/bin/csh
#Usage: ./suv_eva02.csh <start_resnum> <end_resnum> <chain id> 
#Oct 25, 2013

# check error
if($#argv == 0) then
	echo "INPUT ERROR"
#	echo "Usage: ./get.csh start_residue_number end_residue_number "
	exit 1
endif

if(-d eva200_22)then
else
	echo "ERROR: eva200_22/ don't exist "
	exit 1
endif

date > Gtimelog.txt

#abstract specific residue data 
if(-d pdbtmp)then
else
mkdir pdbtmp
endif

set i=1
set k
set l 
@ k=$argv[1]
@ l=$argv[2]
@ l++

set m = "$argv[3]"

while($k<$l)
@ i=1
	if($k<10)then
	grep CA ./eva200_22/refine"$i"_1.pdb | grep "$m   $k " > ./pdbtmp/$k 
	else if($k<100)then
	grep CA ./eva200_22/refine"$i"_1.pdb | grep "$m  $k  " > ./pdbtmp/$k
	else
	grep CA ./eva200_22/refine"$i"_1.pdb | grep "$m $k   " > ./pdbtmp/$k
	endif 
@ i++
		while($i<5001)
			if($k<10)then
		        grep CA ./eva200_22/refine"$i"_1.pdb | grep "$m   $k " >> ./pdbtmp/$k
		        else if($k<100)then
		        grep CA ./eva200_22/refine"$i"_1.pdb | grep "$m  $k  " >> ./pdbtmp/$k
			else
		        grep CA ./eva200_22/refine"$i"_1.pdb | grep "$m $k   " >> ./pdbtmp/$k
		        endif 
		@ i++
		end
@ k++
end

date >> Gtimelog.txt
