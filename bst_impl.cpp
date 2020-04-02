#include "bst_impl.hh"

using namespace std;

//defining all our sentinel nodes.
void initialConstruction()
{
  leaf1 = new node;
  leaf1->key = INT_MAX-2;
  leaf1->left.address = NULL;
  leaf1->right.address = NULL;

  leaf2 = new node;
  leaf2->key = INT_MAX-1;
  leaf2->left.address = NULL;
  leaf2->right.address = NULL;
 
  leaf3 = new node;
  leaf3->key = INT_MAX;
  leaf3->left.address = NULL;
  leaf3->right.address = NULL;

  S = new node;
  S->key = INT_MAX-1;
  S->left.address = leaf1;
  S->left.flag = false;
  S->left.tag = false;
  S->right.address = leaf1;
  S->right.flag = false;
  S->right.tag = false;

  R = new node;
  R->key = INT_MAX;
  R->left.address = S;
  R->left.flag = false;
  R->left.tag = false;
  R->right.address = leaf3;
  R->right.flag = false;
  R->right.tag = false;
}
void seek(int key, seekRecord *seekRecord)
{
//seekRecord initialization
 seekRecord->ancestor = R;
 seekRecord->successor = S;
 seekRecord->parent = S;
 seekRecord->leaf = S->left.address;

 //initialize other variables used in the traversal
  subNode parentField = (seekRecord->parent)->left;
  subNode currentField = (seekRecord->leaf)->left;
  node* current = currentField.address;
  while(!current)
  {
    //move down the tree
    //check if the edge from the (current) parent node in the access path is tagged
    if (!parentField.tag)
    {
     //found an untagged edge in the access path; advance ancestor and successor pointers
     seekRecord->ancestor = seekRecord->parent;
     seekRecord->successor = seekRecord->leaf;
    }
    //advance the parent and leaf pointers.
    seekRecord->parent = seekRecord->leaf;
    seekRecord->leaf = current;
    //update the other variables used in the traversal
    parentField = currentField;
    if (key < current->key)
        currentField = current->left;
    else
        currentField = current->right;
     current = currentField.address;
   //traversal complete
  }
  return;
}

bool search (int key)
{
  seekRecord* temp;
  temp = new seekRecord;
  seek(key, temp);
  if (((temp->leaf)->key)== key)
     return true;
  else
    return false;
}

int main()
{
 initialConstruction();
}
