#!/bin/bash
for filename in *.csv; do
	gnuplot -e "datafile='$filename';nolines=3;" gplot_final.plg 
done










