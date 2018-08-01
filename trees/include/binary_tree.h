#include "node.h"
#include <iostream>

template<typename _T>
Node<_T>* bin_find(Node<_T>* root, _T key)
{
  //Short-circuit evaluation
  if(root == NULL || root->key == key)
    return root;

  if(key < root->key)
    return find(key->left);
      
  if(key > root->key)
    return find(key->right);
}

template<typename _T>
Node<_T>* bin_insert(Node<_T>* root, _T key)
{
  if(root == NULL)
    return (new Node<_T>(key));

  if(key < root->key)
    root->left = bin_insert(root->left, key);

  else if(key > root->key)
    root->right = bin_insert(root->right, key);

  //Ignore equal key

  return root;
}

template<typename _T>
Node<_T>* bin_find_min(Node<_T>* root)
{
  while(root->left != NULL)
    root = root->left;
  return root;
}


template<typename _T>
Node<_T>* bin_find_max(Node<_T>* root)
{
  while(root->right != NULL)
    root = root->right;
  return root;
}


template<typename _T>
Node<_T>* bin_delete(Node<_T>* root, _T key)
{
  if(root == NULL)
    return root;

  if(key < root->key)
    root->left = bin_delete(root->left, key);

  else if(key > root->key)
    root->right = bin_delete(root->right, key);

  //Found the node to be deleted
  else
    {
      Node<_T>* n_ptr = NULL;
      //no left child. No neither child included
      if(root->left == NULL)
	{
	  n_ptr = root->right;
	  delete root;
	  return n_ptr;
	}
      //no right child
      else if(root->right == NULL)
	{
	  n_ptr = root->left;
	  delete root;
	  return n_ptr;
	}
      //Have 2 children
      else
	{
	  //Find predecessor node in subtree
	  n_ptr = bin_find_max(root->left);
	  //Copy predecessor's key
	  root->key = n_ptr->key;
	  //Recursively delete predecessor's node
	  bin_delete(root->left, root->key);
	}
    }
  return root;
}


template<typename _T>
void bin_inorder(Node<_T>* root)
{
  if(root == NULL)
    return;

  bin_inorder(root->left);
  std::cout << root->key << std::endl;
  bin_inorder(root->right);
}

