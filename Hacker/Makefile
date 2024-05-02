globalnorm: 
	g++ -g -std=c++17 -I includes GlobalNorm.cpp Alignment.cpp Context.cpp -o globalnorm -L link-dep -lfst -ldl

fst:
	./show_fst.sh alignment
	./show_fst.sh context

clean: 
	rm -rf *.fst
	rm -rf *.dot
	rm -rf *.pdf globalnorm
