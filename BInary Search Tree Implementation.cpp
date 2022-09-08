// BInary Search Tree Implementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

struct BstNode {
    int data;
    BstNode* left;
    BstNode* right;
};


BstNode* getNewNode(int data) {
    BstNode* myNode = new BstNode();
    myNode->data = data;
    myNode->left = nullptr;
    myNode->right = nullptr;
    return myNode;
}


BstNode* insert(BstNode* root, int data) {
    if (root == nullptr) {
        root = getNewNode(data);
        return root;
    }
    else if (data <= root->data){
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }
    return root;
}


bool search(BstNode* root,int data) {
    if (root == nullptr) return false;  // empty
    if (root->data = data) return true;
    else if (data <= root->data) return search(root->left, data);
    else if (data >= root->data) return search(root->right, data);
}


//Function to visit nodes in Inorder
void printInOrder(BstNode* root) {
    if (root == NULL) return;

    printInOrder(root->left);       //Visit left subtree
    std::cout << root->data << " ";  //Print data
    printInOrder(root->right);      // Visit right subtree
    
}
int findHeight(BstNode* root) {
    if (root == nullptr) return 0;
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return std::max(leftHeight, rightHeight) + 1;
}


BstNode* findMin(BstNode* root) {
    if (root == nullptr) return nullptr;
    while (root->left != nullptr) root = root->left;
    return root;
}


BstNode* deleteNode(BstNode* root, int data) {
    if (root == nullptr) return nullptr;
    else if (data < root->data) root->left = deleteNode(root->left, data);  // key here is that function returns a node
    else if (data > root->data) root->right = deleteNode(root->right, data);
    else // gotcha bitch, get ready to be deleted
    {
     // Case 1: no child
        if (root->left == nullptr && root->right == nullptr) {
            delete root;    // deallocates memory, now a dangling pointer but still has address
            root = nullptr;
        }   // end case 1

        // Case 2: only one child
        else if (root->left == nullptr) {
            BstNode* temp = root;
            root = root->right;
            delete temp;
        }   
        else if (root->right == nullptr) {
            BstNode* temp = root;
            root = root->left;
            delete temp;
        }   // end case 2
        // Case 3: 2 children (harder)
            //find min in right subtree (or max in left subtree)
            //copy that value into node to be deletd
            //delete duplicate (reduced to case 1/2)
        else {
            BstNode* temp = findMin(root->right);   // finds min in right subtree
            root->data = temp->data;    // copies value into node to be deleted
            root->right = deleteNode(root->right, temp->data);  // delete duplicate(s) (reduced to case 1/2)
        }

    }   
    return root;    // returns new value returned by most recent recursive call fixing parent

}   // end deleteNode()

BstNode* root = nullptr; // empty tree


int main()
{
    /*
      Creating an example tree
                5
               / \
              3   10
             / \   \
            1   4   11
    */
    // inserts
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 3);
    root = insert(root, 4);
    root = insert(root, 1);
    root = insert(root, 11);

    // initial print
    printInOrder(root);
    std::cout << std::endl;

    // testing search
    int number;
    std::cout << "Enter value to search for: ";
    std::cin >> number;
    if (search(root, number) == true) std::cout << "found" << std::endl;
    else std::cout << "not found" << std::endl;
    
    // testing findHeight
    std::cout << "Height of tree: ";
    std::cout << findHeight(root) << std::endl;

    // deleting node with value 5
    root = deleteNode(root, 11);
    printInOrder(root); // reprint tree

}