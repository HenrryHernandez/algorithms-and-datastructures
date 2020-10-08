#include <bits/stdc++.h>

/*
AVL Tree: AVL Tree is defined as the balanced Binary Search Tree. Here Balance
means at every node the difference in the height of Left SubTree and the Right
SubTree is -1, 0 or 1. If the balance factor is other than these three values
then the tree is not called a balanced tree.

Propeties:
    -2 children at most
    -self-balancing tree
    -Smaller or equal values go to left of root.
    -Bigger values go to right of root.
    -The difference between the height of left and right subtree has to be smaller or equal to 1.

*What are the differences between AVL Trees and BTS?
The only difference between AVL Tree and Binary Search Tree is that AVL Tree is a self-balancing tree BST.

            Average     Worst case
Space		O(n)	    O(n)
Search		O(log n)	O(log n)
Insert		O(log n)	O(log n)
Delete		O(log n)	O(log n)
*/

using namespace std;


struct Node{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
};

void rotateLeft(Node** root){
    Node* temp = (*root)->right;
    (*root)->right = temp->left;
    temp->left = (*root);
    temp->parent = (*root)->parent;
    (*root)->parent->left = temp;
    (*root)->parent = temp;
}

void rotateRight(Node** root){
    Node* temp = (*root)->left;
    (*root)->left = temp->right;
    temp->right = (*root);
    temp->parent = (*root)->parent;
    (*root)->parent->right = temp;
    (*root)->parent = temp;
}

void rebalanceTree(Node** root){
    if(root == NULL) return;

    if((*root)->left->height < (*root)->right->height){
        rebalanceTree(&(*root)->right);
    }else{
        rebalanceTree(&(*root)->left);
    }

    if((*root)->left == NULL && (*root)->right == NULL){
        return;
    }else if((*root)->left == NULL){
        rotateLeft(root);
    }else if((*root)->right == NULL){
        rotateRight(root);
    }
}

void insertNode(Node** root, Node** parent, int data){
    if(*root == NULL){
        Node* newNode = new Node();
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        newNode->parent = *parent;
        newNode->height = 0;
        *root = newNode;
        return;
    }


    if(data <= (*root)->data){
        insertNode(&(*root)->left, root, data);
    }else{
        insertNode(&(*root)->right, root, data);
    }

    if((*root)->left == NULL)
        (*root)->height = (*root)->right->height + 1;
    else if((*root)->right == NULL)
        (*root)->height = (*root)->left->height + 1;
    else
        (*root)->height = max((*root)->left->height, (*root)->right->height) + 1;

    if((*root)->height == 0){
        return;
    }else if((*root)->left == NULL && (*root)->right->height + 1 > 1){
        rebalanceTree(root);
    }else if((*root)->right == NULL && (*root)->left->height + 1 > 1){
        rebalanceTree(root);
    }else if(abs((*root)->left->height - (*root)->right->height) > 1){
        rebalanceTree(root);
    }
}

void printTree(Node* root){
    if(root == NULL) return;

    if(root->left == NULL)
        cout << "NULL";
    else
        cout << root->left->data;

    cout << " <= " << root->data << "." << root->height << " => ";

    if(root->right == NULL)
        cout << "NULL" << endl;
    else
        cout << root->right->data << endl;

    printTree(root->left);
    printTree(root->right);
}

int main(){
    Node* root = NULL;

    insertNode(&root, &root, 14);
    insertNode(&root, &root, 9);
    insertNode(&root, &root, 7);

    printTree(root);

    return 0;
}