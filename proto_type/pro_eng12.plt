
#set grid xtics ytics mxtics mytics
#set bar 0
#set pointsize 0.000001

#set terminal png font times 16
set terminal png

#set style line 1 linecolor black
#set palette model RGB maxcolors 4
#set palette defined ( 0 "blue", 1 "green", 2 "yellow", 3 "red" )

set xlabel "residue number " 
set ylabel "A-B" 
#set yrange [-300:300]
#set xrange [110:130]
set xtics 1 

#set fontpath "C:\WINDOWS\Fonts"

#set style line 1 lt lc "black" lw 2 
#set style line 2 linetype lc "red" lw 2 
#set style line 3 linetype lc "gray" lw 2 

set title "A-B , 1SIGMA( THREE DIMENSION )"
set output './result12/graph1/A-B_1c.png'
p "./pack12/tmp.txt" using 1:2  w l lc rgb "black" title " sigmaA" , \
  "./pack12/tmp.txt" using 1:5  w l lc rgb "red" title " sigmaB" 
set title "A-B , 2SIGMA( THREE DIMENSION )"
set output './result12/graph1/A-B_2c.png'
p "./pack12/tmp.txt" using 1:3  w l  lc rgb "black" title "2sigmaA" ,\
  "./pack12/tmp.txt" using 1:6  w l  lc rgb "red" title "2sigmaB" 
set title "A-B , 3SIGMA( THREE DIMENSION )"
set output './result12/graph1/A-B_3c.png'
p "./pack12/tmp.txt" using 1:4  w l  lc rgb "black" title "3sigmaA" ,\
  "./pack12/tmp.txt" using 1:7  w l  lc rgb "red" title "3sigmaB" 


set title "A-B , 1SIGMA( DISTANCE )"
set output './result12/graph1/A-B_1d.png'
p "./pack12/tmp.txt" using 1:8  w l  lc rgb "black" title " sigmaA" ,\
  "./pack12/tmp.txt" using 1:11 w l  lc rgb "red" title " sigmaB" 
set title "A-B , 2SIGMA( DISTANCE )"
set output './result12/graph1/A-B_2d.png'
p "./pack12/tmp.txt" using 1:9  w l  lc rgb "black" title "2sigmaA" ,\
  "./pack12/tmp.txt" using 1:12 w l  lc rgb "red" title "2sigmaB" 
set title "A-B , 3SIGMA( DISTANCE )"
set output './result12/graph1/A-B_3d.png'
p "./pack12/tmp.txt" using 1:10 w l  lc rgb "black" title "3sigmaA" ,\
  "./pack12/tmp.txt" using 1:13 w l  lc rgb "red" title "3sigmaB" 

reset

#p "backboneatoms_all.txt" using ($1*0.001):2 ls 3 w l, \
#  "allatoms_all.txt" using ($1* 0.001):2 ls 1 w l 
