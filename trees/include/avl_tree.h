#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <algorithm>

template<typename _T>
int get_height(Node<_T>* n)
{
  if(n == NULL)
    return 0;
  return n->height;
}

template<typename _T>
void update_height(Node<_T>* n)
{
  n->height = std::max(get_height(n->left), get_height(n->right)) + 1;
}

template<typename _T>
Node<_T>* rotate_right(Node<_T>* root)
{
  pivot = root->left;
  root->left = pivot->right;
  pivot->right = root;

  update_height(root);
  update_height(pivot);

  return pivot;
}

template<typename _T>
Node<_T>* rotate_left(Node<_T>* root)
{
  pivot = root->right;
  root->right = pivot->left;
  pivot->left = root;

  update_height(root);
  update_height(pivot);
  
  return pivot;
}


template<typename _T>
Node<_T>* avl_insert(Node<_T>* root, _T key)
{
  if(root == NULL)
    return (new Node<_T>(key));

  if(key == root->key)
    return root;
  
  if(key < root->key)
    root->left = avl_insert(root->left, key);

  else if(key > root->key)
    root->right = avl_insert(root->right, key);

  update_height(root);

  //Check balance, left heavy is negative, right heavy is positive
  int balance = root->right->height - root->left->height;
  
  //Left heavy
  if(balance == -2)
    {
      //Left-right condition, left rotation on left subtree first
      if(key > root->left->key)
	root->left = rotate_left(root->left);
      //Both left-left and left-right conditions have to do this rotation
      root = rotate_right(root);
    }

  //Right heavy
  else if(balance == 2)
    {
      //Right-left condition, right rotation on right subtree first
      if(key < root->right->key)
	root->right = rotate_right(root->right);
      //Both right-right and right-left conditions have to do this rotation
      root = rotate_left(root);
    }

  return root;
  
}


#endif
