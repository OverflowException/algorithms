template<typename _T>
struct Node
{
  _T val;
  Node* left;
  Node* right;
  Node(_T v) : val(v), left(0), right(0){}
  Node(){}
};
