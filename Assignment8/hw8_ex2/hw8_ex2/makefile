ex2: main.cpp bpn.o bpt.o BPlus_node.h BPlus_tree.h
	g++ main.cpp bpn.o bpt.o -o ex2
bpn.o: BPlus_node.cpp BPlus_node.h
	g++ -c BPlus_node.cpp -o bpn.o
bpt.o: BPlus_tree.cpp BPlus_tree.h
	g++ -c BPlus_tree.cpp -o bpt.o