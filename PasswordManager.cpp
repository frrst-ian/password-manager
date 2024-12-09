#include <bits/stdc++.h>
using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

// Morse code list
struct MorseCode {
    const char *letters[26] = {
        ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....",
        "..", ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.",
        "--.-", ".-.", "...",  "-",    "..-", "...-", ".--", "-..-", "-.--", "--.."};
};

// Password entry structure
struct PasswordEntry {
    char text[50];
    char morse[200];
};

// Binary Tree Implementation
struct BinaryTree {
    vector<PasswordEntry> entries;

    void insert(const char *text, const char *morse) {
        PasswordEntry entry;
        strncpy(entry.text, text, 49);
        strncpy(entry.morse, morse, 199);
        entries.push_back(entry);
    }

    void preorder(int index) {
        if (index >= entries.size()) return;
        cout << entries[index].text << " (Morse: " << entries[index].morse << ")\n";
        preorder(2 * index + 1);
        preorder(2 * index + 2);
    }

    void inorder(int index) {
        if (index >= entries.size()) return;
        inorder(2 * index + 1);
        cout << entries[index].text << " (Morse: " << entries[index].morse << ")\n";
        inorder(2 * index + 2);
    }

    void postorder(int index) {
        if (index >= entries.size()) return;
        postorder(2 * index + 1);
        postorder(2 * index + 2);
        cout << entries[index].text << " (Morse: " << entries[index].morse << ")\n";
    }

    void display(const string &traversal) {
        if (entries.empty()) {
            cout << "No passwords stored.\n";
            return;
        }
        cout << "Passwords (Binary Tree, " << traversal << "):\n";
        if (traversal == "Preorder") preorder(0);
        else if (traversal == "Inorder") inorder(0);
        else if (traversal == "Postorder") postorder(0);
    }
};

// Binary Search Tree Implementation
struct BST {
    struct Node {
        PasswordEntry entry;
        Node *left, *right;
    };
    Node *root = nullptr;

    Node *createNode(const char *text, const char *morse) {
        Node *node = new Node();
        strncpy(node->entry.text, text, 49);
        strncpy(node->entry.morse, morse, 199);
        node->left = node->right = nullptr;
        return node;
    }

    Node *insert(Node *root, const char *text, const char *morse) {
        if (!root) return createNode(text, morse);
        if (strcmp(text, root->entry.text) < 0)
            root->left = insert(root->left, text, morse);
        else
            root->right = insert(root->right, text, morse);
        return root;
    }

    void preorder(Node *node) {
        if (!node) return;
        cout << node->entry.text << " (Morse: " << node->entry.morse << ")\n";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node *node) {
        if (!node) return;
        inorder(node->left);
        cout << node->entry.text << " (Morse: " << node->entry.morse << ")\n";
        inorder(node->right);
    }

    void postorder(Node *node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->entry.text << " (Morse: " << node->entry.morse << ")\n";
    }

    void display(const string &traversal) {
        if (!root) {
            cout << "No passwords stored.\n";
            return;
        }
        cout << "Passwords (Binary Search Tree, " << traversal << "):\n";
        if (traversal == "preorder") preorder(root);
        else if (traversal == "inorder") inorder(root);
        else if (traversal == "postorder") postorder(root);
    }
};

// Heap Implementation (Both Max and Min)
struct Heap {
    vector<PasswordEntry> entries;
    bool isMaxHeap; // True for max heap, false for min heap

    Heap(bool isMax) : isMaxHeap(isMax) {}

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && compare(entries[parent], entries[index])) {
            swap(entries[parent], entries[index]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int largestOrSmallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < entries.size() && compare(entries[largestOrSmallest], entries[left]))
            largestOrSmallest = left;

        if (right < entries.size() && compare(entries[largestOrSmallest], entries[right]))
            largestOrSmallest = right;

        if (largestOrSmallest != index) {
            swap(entries[index], entries[largestOrSmallest]);
            heapifyDown(largestOrSmallest);
        }
    }

    bool compare(PasswordEntry &a, PasswordEntry &b) {
        return isMaxHeap ? strcmp(a.text, b.text) < 0 : strcmp(a.text, b.text) > 0;
    }

    void insert(const char *text, const char *morse) {
        PasswordEntry entry;
        strncpy(entry.text, text, 49);
        strncpy(entry.morse, morse, 199);
        entries.push_back(entry);
        heapifyUp(entries.size() - 1);
    }

    void removeTop() {
        if (entries.empty()) {
            cout << "Heap is empty!\n";
            return;
        }
        cout << "Removed password: " << entries[0].text << "\n";
        entries[0] = entries.back();
        entries.pop_back();
        heapifyDown(0);
    }

    void display() {
        if (entries.empty()) {
            cout << "No passwords stored.\n";
            return;
        }
        cout << "Passwords (Heap, " << (isMaxHeap ? "Max" : "Min") << "):\n";
        for (auto &entry : entries) {
            cout << entry.text << " (Morse: " << entry.morse << ")\n";
        }
    }
};

// Function to convert text to Morse code
void textToMorse(const char *text, char *morse, MorseCode &mc) {
    morse[0] = '\0';
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char c = toupper(text[i]) - 'A';
            strcat(morse, mc.letters[c]);
            strcat(morse, " ");
        }
    }
}

int main() {
    BinaryTree bt;
    BST bst;
    Heap maxHeap(true), minHeap(false);
    MorseCode mc;

    int dsChoice;
    cout << "Choose Data Structure:\n";
    cout << "1. Binary Tree\n";
    cout << "2. Binary Search Tree\n";
    cout << "3. Max Heap\n";
    cout << "4. Min Heap\n";
    cin >> dsChoice;

    while (true) {
        cout << "\nMenu:\n1. Add Password\n2. Remove Password\n3. Display Passwords\n4. Exit\n";
        int choice;
        cin >> choice;
        if (choice == 4) break;

        char text[50], morse[200];
        switch (choice) {
            case 1:
                cout << "Enter password: ";
                cin >> text;
                textToMorse(text, morse, mc);
                if (dsChoice == 1) bt.insert(text, morse);
                else if (dsChoice == 2) bst.root = bst.insert(bst.root, text, morse);
                else if (dsChoice == 3) maxHeap.insert(text, morse);
                else minHeap.insert(text, morse);
                break;
            case 2:
                if (dsChoice == 3) maxHeap.removeTop();
                else if (dsChoice == 4) minHeap.removeTop();
                else cout << "Remove functionality not supported for this structure.\n";
                break;
            case 3: {
                string traversal;
                if (dsChoice == 1 || dsChoice == 2) {
                    cout << "Choose traversal (Preorder,Inorder, Postorder): ";
                    cin >> traversal;
                    
                }
                if (dsChoice == 1) bt.display(traversal);
                else if (dsChoice == 2) bst.display(traversal);
                else if (dsChoice == 3) maxHeap.display();
                else minHeap.display();
                break;
            }
        }
    }
    return 0;
}
