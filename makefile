

.PHONY: clean release rapport

all: clean release

format: $(DEPS)
	cd 1/src/ && make format
	cd 2/src/ && make format

rapport: rapport.tex
	pdflatex rapport.tex

release: rapport clean
	tar -czvf ../tp3.tar.gz .

clean:
	cd 1/src && make clean
	cd 2/src && make clean
	rm -f *.aux *.log
