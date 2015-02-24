
#set grid xtics ytics mxtics mytics
#set bar 0
#set pointsize 0.000001

#set terminal png font times 16
set terminal png

#set style line 1 linecolor black
#set palette model RGB maxcolors 4
#set palette defined ( 0 "blue", 1 "green", 2 "yellow", 3 "red" )

set xlabel "distance" 
set ylabel "data" 
#set yrange [0:1000]
#set xrange [-100:100]
#set xtics 1 

#set fontpath "C:\WINDOWS\Fonts"

#set style line 1 lt lc "black" lw 2 
#set style line 2 linetype lc "red" lw 2 
#set style line 3 linetype lc "gray" lw 2 

set title "AMOUNT OF DATA ( DISTANDE )"
set output 'result12/graph2/tmp/hist1.png'
p "pack12/histo.txt" index 0 using 1:2  w l lc rgb "black" title "GROUP A",\
  "pack12/histo.txt" index 0 using 3:4  w l lc rgb "red" title "GROUP B" 

set title "AMOUNT OF DATA ( 3DIMENSION )"
set output 'result12/graph2/tmp/hist2.png'
p "pack12/histo.txt" index 1 using 1:2  w l lc rgb "black" title "GROUP A",\
  "pack12/histo.txt" index 1 using 3:4  w l lc rgb "red" title "GROUP B"

set title "AMOUNT OF DATA ( x axis )"
set xlabel "x axis"
set output 'result12/graph2/tmp/hist3.png'
p "pack12/histo.txt" index 2 using 1:2  w l lc rgb "black" title "GROUP A",\
  "pack12/histo.txt" index 2 using 3:4  w l lc rgb "red" title "GROUP B"

set title "AMOUNT OF DATA ( y axis )"
set xlabel "y axis"
set output 'result12/graph2/tmp/hist4.png'
p "pack12/histo.txt" index 3 using 1:2  w l lc rgb "black" title "GROUP A",\
  "pack12/histo.txt" index 3 using 3:4  w l lc rgb "red" title "GROUP B"


set title "AMOUNT OF DATA ( z axis )"
set xlabel "z axis"
set output 'result12/graph2/tmp/hist5.png'
p "pack12/histo.txt" index 4 using 1:2  w l lc rgb "black" title "GROUP A",\
  "pack12/histo.txt" index 4  using 3:4  w l lc rgb "red" title "GROUP B"


reset

#p "backboneatoms_all.txt" using ($1*0.001):2 ls 3 w l, \
#  "allatoms_all.txt" using ($1* 0.001):2 ls 1 w l 
