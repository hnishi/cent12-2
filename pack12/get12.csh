#!/bin/csh
#Usage: ./get.csh (start_resnum) (end_resnum)


# check error
if($#argv == 0) then
	echo "ERROR: you did not input residue range "
	echo "Usage: ./get.csh (start_resnum) (end_resnum)"
	exit 1
endif

if(-d pdb)then
else
	echo "ERROR: No 'pdb' directory existing "
	exit 1
endif

date > time12.txt

#abstract specific residue data 
if(-d 'pdbtmp')then
else
mkdir pdbtmp
endif

set i=1
set k
set l
@ k=$argv[1]
@ l=$argv[2]
@ l++
while($k<$l)
@ i=1
grep CA ./pdb/$i.pdb | grep " $k   " > ./pdbtmp/$k
	if($? == 1 ) then
	echo "ERROR: grep cannot confirm residue$i of $k.pdb from original Data" > errorget$k.txt
	endif
@ i++
	while($i<5001)
	grep CA ./pdb/$i.pdb | grep " $k   " >> ./pdbtmp/$k   
		if($? == 1 ) then
	        echo "ERROR: grep cannot confirm residue$i of $k.pdb from original Data" >> errorget$k.txt
	        endif
	@ i++
	end
@ k++
end

date >> time12.txt
