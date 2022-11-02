#include <iostream>
#include <limits>
#include <queue>
#include <algorithm> // for max

using namespace std;

struct Node {
    Node *parent, *left, *right;
    int depth, data;

    Node(int depth, int data) :
            parent{nullptr}, left{nullptr}, right{nullptr},
            depth{depth}, data(data) {}

    Node(Node *parent, int depth, int data) :
            parent{parent}, left{nullptr}, right{nullptr},
            depth{depth}, data{data} {}
};

// O(tree height) (and the tree height is O(n))
Node *insert_helper(Node **proot, int x, Node *parent, int depth) {
    // Check if tree is empty (root pointer is null)
    // Dereference the pointer to the root pointer (checking if the pointer from main() itself is null)
    if (*proot == nullptr) {
        return *proot = new Node(parent, depth, x);
    }
    // value is already inserted, don't insert it again (no duplicates allowed)
    if ((*proot)->data == x) {
        return nullptr;
    }
    // recrusive search for where to insert the value
    if (x < (*proot)->data) {
        // giving the address of the left pointer, since this function wants a pointer of a pointer
        return insert_helper(&(*proot)->left, x, *proot, depth + 1);
    } else {
        return insert_helper(&(*proot)->right, x, *proot, depth + 1);
    }
}

// Takes in a pointer to a pointer (points to the pointer in main method that points to the root node)
Node *insert(Node **proot, int x) {
    return insert_helper(proot, x, nullptr, 0);
}

// Θ(n)
// Print the tree, rotated 90° counterclockwise (easier to print line by line) - right subtree becomes top subtree
void display_sideways(Node *node) {
    if (node != nullptr) {
        // recursively display right subtree
        display_sideways(node->right);
        // print value for the node itself
        if (node->depth == 0) { // root node
            cout << "-> ";
        } else {
            cout << "   ";
        }
        for (int i = 0; i < node->depth; ++i) { // the deeper the node is, the more spaces to print
            cout << "   ";
        }
        cout << node->data << endl; // actual data of the node

        // recursively display left subtree
        display_sideways(node->left);
    }
}

// O(tree height) (and the tree height is O(n))
Node *find(Node *root, int x) {
    // check if tree is empty
    if (root == nullptr) {
        // x is not in tree - search failed
        return nullptr;
    }
    if (root->data == x) { // found node -> return root
        return root;
    }
    // recursion
    if (x < root->data) {
        return find(root->left, x); // search left subtree
    } else {
        return find(root->right, x); // search right subtree
    }
}

// Sum all integers in the BST
// Θ(n)
int sum(Node *root) {
    if (root == nullptr) {
        return 0;
    } else {
        return root->data + sum(root->left) + sum(root->right);
    }
}

// Θ(n)
// decrease the depths of every node that has been shifted up
void decrement_depths(Node *root) {
//    if (root) {
    if (root != nullptr) {
        root->depth--;
        decrement_depths(root->left);
        decrement_depths(root->right);
    }
}

// Deletes and returns as result the minimum node in the non-empty tree.
// Since the tree is non-empty, such minimum node must exist.
// This code is similar to findMin except that we do not have to test
// the Null case since we know that the tree is non-empty.
// O(tree height) (and the tree height is O(n))
Node *delete_min(Node **proot) {
    if ((*proot)->left == nullptr) { // found smallest node when there is no left child
        // root is the minimum node, remove it from the tree and return it
        Node *min = *proot; //min we just found
        decrement_depths((*proot)->right);
        *proot = (*proot)->right; // bypassing the minimum, making the right substree the new child of the min's parent
        return min;
    } else {
        // Keep moving down-left
        return delete_min(&(*proot)->left);
    }
}

// O(tree height) (and the tree height is O(n))
// some pointers will be changed, which is why we use pointers to pointers
bool delete_node(Node **proot, int x) {
    if (*proot == nullptr) {
        // Cannot find x, deletion fails
        return false;
    }
    if ((*proot)->data == x) {
        // Case 1: the node is a leaf (no children)
        // Note: this case is in fact a special case of the next one (case 2-a
        // or case 2-b) so this code could be merged with the next case.
        // We keep this case separate here for clarity.
        if ((*proot)->left == nullptr && (*proot)->right == nullptr) {
            delete *proot; // delete the current node
            *proot = nullptr; // set the pointer that was pointing to this current node to be null
            return true;
        }
        // Case 2-a: the node has one left child
        if ((*proot)->left != nullptr && (*proot)->right == nullptr) {
            Node *tmp = *proot;
            decrement_depths((*proot)->left);
            *proot = (*proot)->left; // bypass this node
            delete tmp;
            return true;
        }
        // Case 2-b: the node has one right child
        if ((*proot)->left == nullptr && (*proot)->right != nullptr) {
            Node *tmp = *proot;
            decrement_depths((*proot)->right);
            *proot = (*proot)->right;
            delete tmp;
            return true;
        }
        // Case 3: the node has two children
        // We replace the root with the minimum node in the right subtree
        // (The maximum node in the left subtree would work too.)
        if ((*proot)->left != nullptr && (*proot)->right != nullptr) {
            Node *tmp = *proot;
            // Find the smallest node in the right subtree, and delete it from the right subtree:
            Node *min = delete_min(
                    &(*proot)->right); // already checked if right was null and at this point we know it can't be, so don't need to check again in delete)min
            // Replace the root with the min:
            min->parent = (*proot)->parent;
            min->depth = (*proot)->depth; // already updated the depth, delete_min will update the depths of everything in the old right subtree of previous min node
            min->left = (*proot)->left;
            min->right = (*proot)->right;
            // replace tmp with min
            *proot = min;
            delete tmp;
            return true;
        }
    }
    // root isn't x - recursively find x
    if ((*proot)->data > x) {
        // pass the address of the pointer to the left tree
        return delete_node(&(*proot)->left, x);
    } else {
        // pass the address of the pointer to the right tree
        return delete_node(&(*proot)->right, x);
    }
}

// Θ(n)
// delete the whole tree
void delete_bst(Node *root) {
    if (root != nullptr) {
        delete_bst(root->left);
        delete_bst(root->right);
        delete root;
    }
}

// Create a balanced BST from a sorted array.
// Θ(n)
Node *create_bst_helper(int data[], int low, int high, Node *parent, int depth) {
    if (low > high) {
        return nullptr;
    }
    int mid = low + (high - low) / 2;
    Node *new_node = new Node(parent, depth, data[mid]);
    new_node->left = create_bst_helper(data, low, mid - 1, new_node,
                                       depth + 1); // left half of the array becomes left subtree
    new_node->right = create_bst_helper(data, mid + 1, high, new_node,
                                        depth + 1); // right half of the array becomes right subtree
    return new_node;
}

Node *create_bst(int data[], int length) {
    // to make a more balanced tree, make the root the median of the array
    return create_bst_helper(data, 0, length - 1, nullptr, 0);
}

int main(int argc, const char *argv[]) {
    Node *bst1 = nullptr; // root pointer, initially null
    insert(&bst1, 3);
    insert(&bst1, 5);
    insert(&bst1, 2);
    display_sideways(bst1);
    cout << endl;
    cout << "finding " << find(bst1, 5)->data << endl;
    cout << "sum is " << sum(bst1) << endl;
    cout << "deleting 3:" << endl << endl;
    delete_node(&bst1, 3);
    display_sideways(bst1);
    cout << endl;
    cout << "deleting 5:" << endl << endl;
    delete_node(&bst1, 5);
    display_sideways(bst1);
    cout << endl;
    delete_bst(bst1);
    bst1 = nullptr; // set the root pointer to null, since we aren't passing the reference to the rot

    int data[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Node *bst2 = create_bst(data, 15);
    display_sideways(bst2);

    delete_bst(bst2);
    return 0;
}
