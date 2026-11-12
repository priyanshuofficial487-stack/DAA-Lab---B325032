all: run graphs

run:
	cd Q1 && gcc -O2 -o prog code.c && ./prog
	cd Q2 && gcc -O2 -o prog code.c && ./prog
	cd Q3 && gcc -O2 -o prog code.c && ./prog

graphs:
	python3 generate_graphs.py

clean:
	rm -f Q1/prog Q2/prog Q3/prog
