CC = g++
D = -DDEBUG
ALLFILES = obj/readfile.o obj/tree.o obj/main.o obj/Diff.o

deb:
	$(CC) $(D) Tree/src/readfile.cpp Tree/src/tree.cpp src/main.cpp src/Diff.cpp

all: $(ALLFILES)

start : $(ALLFILES)
	$(CC) $(ALLFILES) -o TREE_EXP.out

obj/readfile.o : DEBUG/def.h Tree/src/readfile.cpp Tree/header/readfile.h Tree/header/tree.h header/TREE_EXP.h
	$(CC) -c Tree/src/readfile.cpp -o obj/readfile.o

obj/tree.o : DEBUG/def.h Tree/src/tree.cpp Tree/header/tree.h header/TREE_EXP.h
	$(CC) -c Tree/src/tree.cpp -o obj/tree.o

obj/main.o : src/main.cpp Tree/header/tree.h Tree/header/readfile.h
	$(CC) -c src/main.cpp -o obj/main.o

obj/Diff.o : src/Diff.cpp header/Diff.h Tree/src/tree.cpp Tree/header/tree.h header/TREE_EXP.h

clean :
	rm *.out obj/*.o
