LATEX = latex
DVIPDF = dvipdfm
DVIPDFFLAGS = -r 1200 -p a4
DVIPS = dvips
DVIPSFLAGS = -r 1200 -p a4

RM = rm -f

PDFS = 01.pdf 02.pdf 03.pdf 04.pdf 06.pdf 07.pdf


all: $(PDFS)

01.pdf: 01.dvi

02.pdf: 02.dvi

03.pdf: 03.dvi

04.pdf: 03.dvi

06.pdf: 06.dvi

07.pdf: 07.dvi


%.pdf: %.dvi
	$(DVIPDF) $(DVIPDFFLAGS) -o $@ $<

%.pdf: %.ps
	$(PS2PDF) $(DVIPDFFLAGS) -o $@ $<

%.ps: %.dvi

%.dvi: %.tex
	$(LATEX) $<


clean:
	$(RM) *~ *.aux *.log

cleanall: clean
	$(RM) *.dvi *.ps *.pdf

.PHONY: clean cleanall
