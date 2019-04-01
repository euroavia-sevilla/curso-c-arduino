#!/bin/bash
SIZE_W=1000
SIZE_H=1200

for i in *.stl; do
  T=__tmp__$i
  b=`basename $i`
  echo import\(\"$i\"\)\; >$T
  COPTS="--imgsize=$SIZE_W,$SIZE_H"
  COPTS="${COPTS} --colorscheme=Nature"
  COPTS="${COPTS} --autocenter"
  COPTS="${COPTS} --viewall"
  COPTS="${COPTS} --render"
  COPTS="${COPTS} --render"
  openscad -o "${b}_315.png" $COPTS --camera=0,0,0,60,0,315,300 $T
  openscad -o "${b}_30.png" $COPTS --camera=0,0,0,60,0,30,300 $T
  convert "${b}_315.png" -trim -bordercolor White -border 10 "${b}_315.png"
  convert "${b}_30.png" -trim -bordercolor White -border 10 "${b}_30.png"
  rm $T
done
