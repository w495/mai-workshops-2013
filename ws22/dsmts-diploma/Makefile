Name=presentation
Src=$(Name).tex
Res=$(Name).pdf
TeX=xelatex
Mi=makeindex
Bib=bibtex

Del=rm -f

Vec_C=dot
Vec_format=png
Vec_src=net-model
Vec_src_ext=dot
Vec_flags=-O -T
Vec_dir=./vec

double: pdf
	$(TeX) $(Src)

pdf: $(Res)
	
$(Res):$(Src)
	$(TeX) $<
	
cleanall: clean
	$(Del) $(Name).pdf

clean:
	$(Del) $(Name).aux
	$(Del) $(Name).bbl
	$(Del) $(Name).blg
	$(Del) $(Name).idx
	$(Del) $(Name).ilg
	$(Del) $(Name).ind
	$(Del) $(Name).log
	$(Del) $(Name).out
	$(Del) $(Name).toc

	$(Del) $(Name).nav
	$(Del) $(Name).snm