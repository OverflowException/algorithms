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
  Node(_T k) : key(k), left(NULL), right(NULL), parent(NULL), color(0), height(0){}
};
