#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* NewNode(int value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = value;
    temp->left =NULL;
    temp->right = NULL;
    return temp;
}
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return NewNode(data);   
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}
struct Node* createTree(int array[], int n) {
    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertNode(root, array[i]);
    }
    return root;
}
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with one or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        struct Node* temp = minValueNode(root->right);

        // Copy the inorder successor's data to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

int height(struct Node* node) {
    if (node == NULL) {
        return -1; // Height of an empty tree is -1
    } else {
        // Height of the left subtree
        int left_height_tree = height(node->left);
        // Height of the right subtree
        int right_height_tree = height(node->right);

        // Return the greater height
        return 1 + (left_height_tree > right_height_tree ? left_height_tree : right_height_tree);
    }
}

// Function to find the level of a node in the BST
int getLevel(struct Node* root, int data, int level) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == data) {
        return level;
    }
    if (data < root->data) {
        return getLevel(root->left, data, level + 1);
    } else {
        return getLevel(root->right, data, level + 1);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = createTree(arr, n);

    // Delete a node (replace 20 with the node you want to delete)
    root = deleteNode(root, 20);

   printf("Height of the Binarysearchtree: %d\n", height(root));

    int node_data = 15;
    int level = getLevel(root, node_data, 1);
    int node_height = height(root) - level + 1;
    printf("Level of node %d: %d\n", node_data, level);
    printf("Height of node %d\n from root: %d\n", node_data, node_height);

    return 0;
}