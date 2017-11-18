all:
	gcc test.c -o test.out -lm && ./test.out
clean:
	rm test.out gauss.png test.csv
plot:
	gnuplot -e "load 'plot.gb'" && eog gauss.png
