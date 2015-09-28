/*******************************************************************************
* Exceptions.h
*
* author: Rikk Anderson
* date created: 2015
* last updated: 9/28/2015
*
* This header file defines several Exception classes that can be thrown
*
*******************************************************************************/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


class TreeFullException {
  public:
    TreeFullException() {}
    char* getMsg() { return "TreeFullException: Failed to allocate memory for tree\n"; }
};

class TreeEmptyException {
  public:
    TreeEmptyException() {}
    char* getMsg() { return "TreeEmptyException: The tree is empty\n"; }
};


class DuplicateItemException {
  private:
    int data;
  public:
    DuplicateItemException(int data) { this->data = data; }
    char* getMsg() { return "DuplicateItemException: A duplicate item was found\n"; }
    int getData() { return data; }
};

class ItemNotFoundException {
  private:
    int data;
  public:
    ItemNotFoundException(int data) { this->data = data; }
    char* getMsg() { return "ItemNotFoundException: The search item was not found\n"; }
    int getData() { return data; }
};

#endif
