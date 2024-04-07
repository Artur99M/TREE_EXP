CC = g++
D = -DDEBUG
ALLFILES = obj/readfile.o obj/tree.o obj/main.o obj/Diff.o obj/SimpleTreeExp.o

all: $(ALLFILES)

run : $(ALLFILES)
	$(CC) $(ALLFILES) -o TREE_EXP.out

app :
	./TREE_EXP.out
obj/readfile.o : DEBUG/def.h Tree1/src/readfile.cpp Tree1/header/readfile.h Tree1/header/tree.h header/TREE_EXP.h
	$(CC) -c Tree1/src/readfile.cpp -o obj/readfile.o

obj/tree.o : DEBUG/def.h Tree1/src/tree.cpp Tree1/header/tree.h header/TREE_EXP.h
	$(CC) -c Tree1/src/tree.cpp -o obj/tree.o

obj/main.o : src/main.cpp Tree1/header/tree.h Tree1/header/readfile.h header/SimpleTreeExp.h
	$(CC) -c src/main.cpp -o obj/main.o

obj/Diff.o : DEBUG/def.h src/Diff.cpp header/Diff.h Tree1/src/tree.cpp Tree1/header/tree.h header/TREE_EXP.h
	$(CC) -c src/Diff.cpp -o obj/Diff.o

obj/SimpleTreeExp.o: DEBUG/def.h src/SimpleTreeExp.cpp header/SimpleTreeExp.h Tree1/header/tree.h
	$(CC) -c src/SimpleTreeExp.cpp -o obj/SimpleTreeExp.o

deb:
	$(CC) $(D) Tree1/src/readfile.cpp Tree1/src/tree.cpp src/main.cpp src/Diff.cpp src/SimpleTreeExp.cpp

clean :
	rm *.out obj/*.o
