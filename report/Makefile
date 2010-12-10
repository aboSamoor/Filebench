file=report
all:
	latex $(file).tex
	bibtex $(file)
	latex $(file).tex
	latex $(file).tex
	dvips $(file).dvi
	ps2pdf $(file).ps
	evince $(file).pdf
