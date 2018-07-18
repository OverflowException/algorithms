#include "node.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

void bt_iterate(Node<int>* root)
{
  if(root == NULL)
    return;

  bt_iterate(root->left);
  std::cout << root->val << " ";
  bt_iterate(root->right);  
}


int main(int argc, char** argv)
{
  std::vector<int> vec(20, 0);

  std::srand(std::time(nullptr));

  for(int& ele : vec)
    ele = std::rand() % 20;

  for(int ele : vec)
    std::cout << ele << " ";
  std::cout << std::endl;


  //Construct bunary tree
  Node<int>* root = new Node<int>(vec[0]);
  Node<int>* head;
  for(std::vector<int>::iterator it = ++vec.begin(); it != vec.end(); ++it, head = root)
    {
      head = root;
      while(true)
	if(*it < head->val)
	  if(head->left == NULL)
	    {
	      head->left = new Node<int>(*it);
	      break;
	    }
	  else
	    {
	      head = head->left;
	      continue;
	    }

	else
	  if(head->right == NULL)
	    {
	      head->right = new Node<int>(*it);
	      break;
	    }
	  else
	    {
	      head = head->right;
	      continue;
	    }
    }

  bt_iterate(root);

  std::cout << std::endl;
}
