#include <iostream>

using namespace std;

struct node;

struct subNode
{
  bool flag;
  bool tag;
  node* address;
};

struct node
{
 int key;
 subNode left;
 subNode right; 
};

struct seekRecord
{
 node* ancestor;
 node* successor;
 node* parent;
 node* leaf;
};

node* leaf1;

node* leaf2;

node* leaf3;


node* S;

node* R;

void seek(int key, seekRecord* record);
bool search (int key);

