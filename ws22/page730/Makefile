TEX2PDF=pdflatex
TEX2DVI=latex
DVI2PS=dvips
PS2PDF=ps2pdf
DVI2PDF=dvipdf

NAME=page730

PDFFAST=$(NAME).fast.pdf
PDF=$(NAME).pdf
PS=$(NAME).ps
DVI=$(NAME).dvi
TEX=$(NAME).tex

SRCDIR=./src
SRC=$(SRCDIR)/$(TEX)

.PHONY: clean cleanall

tex2pdf: $(PDFFAST)

$(PDFFAST): $(SRC)
	$(TEX2PDF) $<

ps2pdf: $(PDF)

$(PDF): $(PS)
	$(PS2PDF) $<

dvi2ps: $(PS)

$(PS): $(DVI)
	$(DVI2PS) $<

tex2dvi: $(DVI)

$(DVI): $(SRC)
	$(TEX2DVI) $<
	

	
cleanall: clean
	rm -rf $(PDF)
	rm -rf $(PDFFAST)
	rm -rf $(DVI)
	rm -rf $(PS)

clean:
	rm -rf $(NAME).aux
	rm -rf $(NAME).bbl
	rm -rf $(NAME).brf
	rm -rf $(NAME).blg
	rm -rf $(NAME).idx
	rm -rf $(NAME).ilg
	rm -rf $(NAME).ind
	rm -rf $(NAME).log
	rm -rf $(NAME).out
	rm -rf $(NAME).toc
	rm -rf $(NAME).nav
	rm -rf $(NAME).snm
