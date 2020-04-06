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
  S->right.address = leaf2;
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

bool insert(int key)
{
  seekRecord* temp;
  temp = new seekRecord;
  while(1)
  {
    seek(key,temp);
    if(((temp->leaf)->key) != key)
    {
      //key is not present in the tree
      node* parent = temp->parent;
      node* leaf = temp->leaf;
      
      //obtain the address of the child field that needs to be modified
      subNode* childAddr;
      if(key < (parent->key))
        childAddr = &(parent->left);
      else
        childAddr = &(parent->right);

      node* newInternal = new node;
      node* newLeaf = new node;
      newLeaf->key = key;
      newInternal->key = std::max(key,leaf->key);

      if(key<leaf->key)
      {
        newInternal->left = newLeaf;
        newInternal->right = leaf;
      }
      else
      {
        newInternal->right = newLeaf;
        newInternal->left = leaf;
      }

      //trying to add the new nodes to the tree
      if(__sync_bool_compare_and_swap(childAddr->address, leaf, newInternal))
      {
        //insertion successful
        return true; 
      }        
      else
      {
        //insertion failed; help the conflicting delete operation
        if((childAddr->address == leaf) && (childAddr->flag || childAddr->tag))
        {
          //address if the child has not changed and either the leaf node
          //or its sibling has been flagged for deletion
          
          //Implemented as part of the delete operation
          //cleanup();
        } 
      }
    }
    else
    {
      //key is already present in the tree
      return false;
    }  
  }
}

int main()
{
 initialConstruction();
}
