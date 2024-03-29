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
    int height;
};
void printTree(Node* root);

int height(Node* root){
    if (root == NULL) return 0;
    else return root->height;
}

void rightRotation(Node*& root){
    Node* temp = root->left;
    root->left = temp->right;
    temp->right= root;
    root = temp;

    Node* prevRoot = root->right; //this is the node which we applied the rotation to

    prevRoot->height = max(height(prevRoot->left), height(prevRoot->right)) + 1;
    root->height = max(height(root->left), height(root->right)) + 1;
}

void leftRotation(Node*& root){
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root = temp;

    Node* prevRoot = root->left; //this is the node which we applied the rotation to

    prevRoot->height = max(height(prevRoot->right), height(prevRoot->left)) + 1;
    root->height = max(height(root->right), height(root->left)) + 1;
}

int checkBalance(Node* root){
    if(root == NULL) return 0;
    return height(root->left) - height(root->right);
}

Node* findMin(Node*& root){
    if(root == NULL) return root;

    Node* temp = root;
    while(temp->left != NULL)
        temp = temp->left;

    return temp;
}

Node* deleteNode(Node*& root, int data){
    if(root == NULL) return NULL;

    if(root->data < data){
        root->right = deleteNode(root->right, data);
    }else if(root->data > data){
        root->left = deleteNode(root->left, data);
    }else{
        if(root->right == NULL){
            Node* temp = root->left;
            delete(root);
            return temp;
        }else if(root->left == NULL){
            Node* temp = root->right;
            delete(root);
            return temp;
        }else{
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if(root == NULL) return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = checkBalance(root);

    if(balance > 1 && checkBalance(root->left) >= 0){ //LL
        rightRotation(root);
    }else if(balance > 1 && checkBalance(root->left) < 0){ //LR
        leftRotation(root->left);
        rightRotation(root);
    }else if(balance < -1 && checkBalance(root->right) <= 0){ //RR
        leftRotation(root);
    }else if(balance < -1 && checkBalance(root->right) > 0){ //RL
        rightRotation(root->right);
        leftRotation(root);
    }

    return root;

}

void insertNode(Node*& root, int data){
    if(root == NULL){
        Node* newNode = new Node();
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        root = newNode;
        return;
    }

    if(data <= root->data){
        insertNode(root->left, data);
    }else{
        insertNode(root->right, data);
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = checkBalance(root);

    if(balance > 1 && data <= root->left->data){ //LL
        rightRotation(root);
    }else if(balance > 1 && data > root->left->data){ //LR
        leftRotation(root->left);
        rightRotation(root);
    }else if(balance < -1 && data <= root->right->data){ //RL
        rightRotation(root->right);
        leftRotation(root);
    }else if(balance < -1 && data > root->right->data){ //RR
        leftRotation(root);
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

    insertNode(root, 50);
    insertNode(root, 25);
    insertNode(root, 55);
    insertNode(root, 10);
    insertNode(root, 30);
    insertNode(root, 54);
    insertNode(root, 1);
    insertNode(root, 15);
    insertNode(root, 29);
    insertNode(root, 35);
    printTree(root);
    cout << endl;

    deleteNode(root, 25);
    printTree(root);

    return 0;
}
