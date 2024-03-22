/* Kaguchia Kago - SCT221-0522/2022
Katra Noor Soyan - sct221-0397/2022
SCT221-0181/2023 -- Brian Kyalo Kimanzi
*/
#include <stdio.h>
#include <stdlib.h>

// Structure for a node in BST
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a node into BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// Function to delete a node from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = root->right;
        while (temp && temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find the height of the BST
int height(struct Node* root) {
    if (root == NULL) return -1;
    int left_height = height(root->left);
    int right_height = height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

// Function to find level of a node
int level(struct Node* root, int data, int level_num) {
    if (root == NULL) return 0;
    if (root->data == data) return level_num;
    int downlevel = level(root->left, data, level_num + 1);
    if (downlevel != 0) return downlevel;
    downlevel = level(root->right, data, level_num + 1);
    return downlevel;
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    // Print height of the BST
    printf("Height of the BST is: %d\n", height(root));

    // Print level and height of any node
    int key = 25;
    printf("Level of %d is: %d\n", key, level(root, key, 1));
    printf("Height of %d is: %d\n", key, height(root));

    // Deleting a node
    int del_key = 20;
    root = deleteNode(root, del_key);
    printf("Node %d deleted\n", del_key);
    printf("Height of the BST after deletion: %d\n", height(root));

    return 0;
}
