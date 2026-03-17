#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>  
#include <stddef.h> 
#include <stdlib.h> 
#include <time.h>   

struct Btree
{
    struct Btree* pLeft; // left and rightchildren
    struct Btree* pRight;
    int val; // value
};

typedef struct Btree Btree;

void init_rng(void) // random number generator
{
    time_t curtime; // using the current system time
    time(&curtime);
    srand((unsigned int)curtime);
}

int genRand(void)
{
    return rand() % 100 + 1; // range [1, 100]
}

int countNodes(Btree* node) // counts the total number of nodes in a subtree
{
    if (node == NULL) return 0;
    return 1 + countNodes(node->pLeft) + countNodes(node->pRight);
}

Btree* createNode(int val) // allocates and initializes a new tree node
{
    Btree* n = (Btree*)malloc(sizeof(Btree));
    if (!n) exit(1);

    n->val = val;
    n->pLeft = NULL;
    n->pRight = NULL;
    return n;
}

Btree* rotateRight(Btree* y) // right rotation
{
    Btree* x = y->pLeft;
    Btree* T = x->pRight;

    x->pRight = y;
    y->pLeft = T;

    return x;
}

Btree* rotateLeft(Btree* x) // left rotation
{
    Btree* y = x->pRight;
    Btree* T = y->pLeft;

    y->pLeft = x;
    x->pRight = T;

    return y;
}

void printTree(Btree* root, int level) // visualization of the tree
{
    int i;
    if (!root) return;

    printTree(root->pRight, level + 1);

    for (i = 0; i < level; i++)
    {
        printf("    ");
    }
    printf("%d\n", root->val);

    printTree(root->pLeft, level + 1);
}

// find the rightmost (maximum) node in subtree
Btree* findMax(Btree* node)
{
    while (node && node->pRight)
        node = node->pRight;
    return node;
}

// find the leftmost (minimum) node in subtree
Btree* findMin(Btree* node)
{
    while (node && node->pLeft)
        node = node->pLeft;
    return node;
}

Btree* balanceNode(Btree* node)
{
    if (!node)
        return node;

    int L = countNodes(node->pLeft);
    int R = countNodes(node->pRight);

    // LEFT-heavy case
    if (L - R > 1)
    {
        Btree* t2 = findMax(node->pLeft);

        //Bring t2 up by rotating its ancestors until it becomes the direct left child of node

        while (node->pLeft != t2)
        {
            node->pLeft = rotateLeft(node->pLeft);
        }

        // Final right rotation transfers mass to the right
        node = rotateRight(node);
    }

    // RIGHT-heavy case
    else if (R - L > 1)
    {
        Btree* t2 = findMin(node->pRight);

        // bring t2 up by rotating its ancestors until it becomes the direct right child of node

        while (node->pRight != t2)
        {
            node->pRight = rotateRight(node->pRight);
        }

        // final left rotation transfers mass to the left
        node = rotateLeft(node);
    }

    return node;
}

Btree* insert(Btree* root, int val)
{
    Btree* path[100];
    int top = 0;

    Btree* cur = root;
    Btree* parent = NULL;

    // find insertion position
    while (cur)
    {
        path[top++] = cur;
        parent = cur;

        if (val < cur->val)
            cur = cur->pLeft;
        else if (val > cur->val)
            cur = cur->pRight;
        else
            return root; // duplicate value
    }

    // insert new node
    if (!parent)
        root = createNode(val);
    else if (val < parent->val)
        parent->pLeft = createNode(val);
    else
        parent->pRight = createNode(val);

    printf("\nInserted %d\nBefore balancing:\n", val);
    printTree(root, 0);

    // bottom-up local balancing along the insertion path.
    while (top > 0)
    {
        Btree* node = path[--top];
        Btree* newNode = balanceNode(node);

        if (newNode != node)
        {
            if (top == 0)
                root = newNode;
            else if (path[top - 1]->pLeft == node)
                path[top - 1]->pLeft = newNode;
            else
                path[top - 1]->pRight = newNode;
        }
    }

    

    // Additional balancing of subtrees as new trees
    if (root)
    {
        Btree* nodes[100]; // for nodes to process
        Btree* processed[100]; // for processed nodes for avoiding infinity loops
        int nodesTop = 0;
        int processedTop = 0;

        // Start with root
        nodes[nodesTop++] = root;

        while (nodesTop > 0)
        {
            Btree* currentNode = nodes[--nodesTop];

            // Checking if node was already processed
            int alreadyProcessed = 0;
            for (int i = 0; i < processedTop; i++)
            {
                if (processed[i] == currentNode)
                {
                    alreadyProcessed = 1;
                    break;
                }
            }

            if (alreadyProcessed) continue;

            // Add to processed list
            processed[processedTop++] = currentNode;

            // Balance current node's subtree
            Btree* balancedNode = balanceNode(currentNode);

            // Update parents if needed
            if (balancedNode != currentNode)
            {
                // Find parent in processed
                Btree* parentNode = NULL;
                for (int i = 0; i < processedTop - 1; i++)
                {
                    if (processed[i]->pLeft == currentNode || processed[i]->pRight == currentNode)
                    {
                        parentNode = processed[i];
                        break;
                    }
                }

                if (parentNode)
                {
                    if (parentNode->pLeft == currentNode) parentNode->pLeft = balancedNode;
                    else if (parentNode->pRight == currentNode) parentNode->pRight = balancedNode;
                }
                else if (currentNode == root)
                {
                    root = balancedNode;
                }

                // Reset processing to start from balanced node
                nodesTop = 0;
                processedTop = 0;
                nodes[nodesTop++] = root;
                continue;
            }

            // Add children to stack for processing
            if (currentNode->pLeft) nodes[nodesTop++] = currentNode->pLeft;
            if (currentNode->pRight) nodes[nodesTop++] = currentNode->pRight;
        }
    }

    printf("After balancing:\n");
    printTree(root, 0);

    return root;
}

Btree* reverse(Btree* root) // reverses the tree by swapping left and right children at every node (mirror operation)
{
    if (!root) return root;

    Btree* stack[100];
    int top = 0;

    stack[top++] = root;

    while (top > 0)
    {
        Btree* node = stack[--top];

        Btree* tmp = node->pLeft;
        node->pLeft = node->pRight;
        node->pRight = tmp;

        if (node->pLeft)
            stack[top++] = node->pLeft;
        if (node->pRight)
            stack[top++] = node->pRight;
    }

    return root;
}

void freeTree(Btree* root) // frees all nodes in the tree
{
    if (!root) return;
    freeTree(root->pLeft);
    freeTree(root->pRight);
    free(root);
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    init_rng();

    Btree* root = NULL;

    // insert random values into the tree
    for (int i = 0; i < 15; i++)
        root = insert(root, genRand());

    /*
    root = insert(root, );
    root = insert(root, );
    root = insert(root, );
    root = insert(root, );
    root = insert(root, );
    root = insert(root, );
    root = insert(root, );
    */

    printf("\nFINAL TREE:\n");
    printTree(root, 0);

    // mirror the tree
    root = reverse(root);

    printf("\nREVERSED TREE:\n");
    printTree(root, 0);

    // print difference in subtree sizes
    printf("\nDifference: %d",
        abs(countNodes(root->pLeft) - countNodes(root->pRight)));

    freeTree(root);
    return 0;
}