#ifndef _NODE_H
#define _NODE_H

#define NULL 0

template<typename _T>
struct Node
{
  _T key;
  Node* left;
  Node* right;
  Node* parent;
  int color;
  int height;
  int balance;
  Node(_T k) : key(k), left(NULL), right(NULL), parent(NULL), color(0), height(1), balance(0){}
};

#endif
