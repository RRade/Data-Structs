CC=g++
CFLAGS=-c -Wall

all: compile

compile: Demonstration.o AVLTree.o BST.o SetAVL.o SetBST.o
	$(CC) Demonstration.o AVLTree.o Bst.o SetAVL.o SetBst.o -o DataStructs

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
