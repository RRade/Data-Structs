CC=g++
CFLAGS=-c -std=c++0x

all: compile

compile:  AVLTree.o BST.o SetAVL.o SetBST.o Demonstration.o
	$(CC) AVLTree.o Bst.o SetAVL.o SetBst.o Demonstration.o -o DataStructs

Demonstration.o: Demonstration.cpp
	$(CC) $(CFLAGS) Demonstration.cpp

AVLTree.o: AVLTree.cpp
	$(CC) $(CFLAGS) AVLTree.cpp

BST.o: Bst.cpp
	$(CC) $(CFLAGS) Bst.cpp

SetAVL.o: SetAVL.cpp
	$(CC) $(CFLAGS) SetAVL.cpp

SetBST.o: SetBst.cpp
	$(CC) $(CFLAGS) SetBst.cpp

clean:
	rm -rf *o DataStructs
