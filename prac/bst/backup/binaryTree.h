//header file for binary tree implementation 
//peter kydd
//26/10

#define LINE "**************************************************************************\n"


typedef struct _treeRep *Tree;
typedef struct _treeNodeRep *TreeNode;

// creates a new tree
Tree createTree(void);

// dispose of tree and free malloc'd memory 
void disposeTree(Tree t);

// inserts a new node at the root of the tree
void insertAtRoot(Tree t, TreeNode newNode);

// inserters a new node at a balanced position in the tree
void insertOrdered(Tree t, TreeNode newNode);

//delete the node with the specified value
// if value is not discovered, print error message
void deleteNode(Tree t, int key);

// checks to see if the tree is degenerate 
int isDegenerate(Tree t);

// prints postFix order (L R N)
void printPostFix(Tree t);
   
// prints in inFix order (L N R)
void printInFix(Tree t);

// prints in preFix order (N L R)
void printPreFix(Tree t);

// checks to see if a value is in the tree (ie, search for value)
int inTree(Tree t);

// draw the tree in a tree-like way  
void drawTree(Tree t);

// return the height of the tree
int getHeight(Tree t);

//get the size of the tree - number of nodes, without using the size member
int getSize(Tree t);

// trim the tree below a certain level
void trimTree(Tree t, int depth);

// balance the tree
void balance(Tree t);


