/* - This system is a password manager that utilizes different tree data
   structures
   - Implements different tree operations*/

#include <bits/stdc++.h> // Include all c++ library
using namespace std;

// ANSI color codes for styling
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

// Morse code list
struct MorseCode {
  const char *letters[26] = {
      ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
      ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
      "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.."};
};

// Password entry structure
struct PasswordEntry {
  char text[50];
  char morse[200];
};

// Binary Tree Implementation
struct BinaryTree {
  vector<PasswordEntry> entries;

  // Function to insert a password
  void insert(const char *text, const char *morse) {
    PasswordEntry entry;
    strncpy(entry.text, text, 49);
    strncpy(entry.morse, morse, 199);
    entries.push_back(entry);
  }

  // Preorder traversal
  void preorder(int index) {
    if (index >= entries.size())
      return;
    cout << entries[index].text << " (Morse: " << entries[index].morse << ")\n";
    preorder(2 * index + 1);
    preorder(2 * index + 2);
  }
  // Inorder traversal
  void inorder(int index) {
    if (index >= entries.size())
      return;
    inorder(2 * index + 1);
    cout << entries[index].text << " (Morse: " << entries[index].morse << ")\n";
    inorder(2 * index + 2);
  }
  // Post order traversal
  void postorder(int index) {
    if (index >= entries.size())
      return;
    postorder(2 * index + 1);
    postorder(2 * index + 2);
    cout << entries[index].text << " (Morse: " << entries[index].morse << ")\n";
  }
  // Function to display passwords based on traversal selection
  void display(const string &traversal) {
    if (entries.empty()) {
      cout << "No passwords stored.\n";
      return;
    }
    cout << "Passwords (Binary Tree, " << traversal << "):\n";
    if (traversal == "preorder")
      preorder(0);
    else if (traversal == "inorder")
      inorder(0);
    else if (traversal == "postorder")
      postorder(0);
  }
};

// Binary Search Tree Implementation
struct BST {
  // BST Node structure
  struct Node {
    PasswordEntry entry;
    Node *left, *right;
  };
  Node *root = nullptr;

  // Function to create a new node
  Node *createNode(const char *text, const char *morse) {
    Node *node = new Node(); // Creates new node
    strncpy(node->entry.text, text,
            49); // Copies the text into entry.text with limit size of 49
    strncpy(node->entry.morse, morse, 199);
    node->left = node->right = nullptr; // Set the left and right node to null
    return node;
  }
  // Function to insert a morse
  Node *insert(Node *root, const char *text, const char *morse) {
    if (!root)
      return createNode(text,
                        morse); // Call the createNode if a  node doesn't exist
    // Compares the text to the entry.text
    if (strcmp(text, root->entry.text) < 0)
      // If < 0 insert to left
      root->left = insert(root->left, text, morse);
    else
      // If > 0 insert to right
      root->right = insert(root->right, text, morse);
    return root;
  }
  // Preorder traversal
  void preorder(Node *node) {
    if (!node)
      return;
    cout << node->entry.text << " (Morse: " << node->entry.morse << ")\n";
    preorder(node->left);
    preorder(node->right);
  }

  // Inorder traversal
  void inorder(Node *node) {
    if (!node)
      return;
    inorder(node->left);
    cout << node->entry.text << " (Morse: " << node->entry.morse << ")\n";
    inorder(node->right);
  }
  // Post order traversal
  void postorder(Node *node) {
    if (!node)
      return;
    postorder(node->left);
    postorder(node->right);
    cout << node->entry.text << " (Morse: " << node->entry.morse << ")\n";
  }

  // Function to display the passwords based on traversal selection
  void display(const string &traversal) {
    if (!root) {
      cout << "No passwords stored.\n";
      return;
    }
    cout << "Passwords (Binary Search Tree, " << traversal << "):\n";
    if (traversal == "preorder")
      preorder(root);
    else if (traversal == "inorder")
      inorder(root);
    else if (traversal == "postorder")
      postorder(root);
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

    if (left < entries.size() &&
        compare(entries[largestOrSmallest], entries[left]))
      largestOrSmallest = left;

    if (right < entries.size() &&
        compare(entries[largestOrSmallest], entries[right]))
      largestOrSmallest = right;

    if (largestOrSmallest != index) {
      swap(entries[index], entries[largestOrSmallest]);
      heapifyDown(largestOrSmallest);
    }
  }

  bool compare(PasswordEntry &a, PasswordEntry &b) {
    if (isMaxHeap) {
      // Condition to put larger value at the top of the heap
      if (strcmp(a.text, b.text) < 0) {
        return true; // a is smaller than b, so it should move down in the heap
      }
      return false; // a is larger or equal, so no need to swap
    } else {
      // Conditions to put smaller value at the top of the heap
      if (strcmp(a.text, b.text) > 0) {
        return true; // a is larger than b, so it should move down in the heap
      }
      return false; // a is smaller or equal, so no need to swap
    }
  }

  // Function to create a new password entry
  void insert(const char *text, const char *morse) {
    PasswordEntry entry;
    strncpy(entry.text, text, 49);
    strncpy(entry.morse, morse, 199);
    entries.push_back(entry);
    heapifyUp(entries.size() - 1);
  }
  // Function to remove top
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
    //  Check if the heap is empty.
    if (entries.empty()) {
      // If the heap is empty, print a message saying there are no passwords
      // stored
      cout << "No passwords stored.\n";
      return;
    }

    // Print the type of heap (Max or Min).
    if (isMaxHeap) {
      cout << "Passwords (Heap, Max):\n";
    } else {
      cout << "Passwords (Heap, Min):\n";
    }

    //  Loop through all entries in the heap and display each one.
    for (auto &entry : entries) {
      // For each entry, print the password and its Morse code.
      cout << entry.text << " (Morse: " << entry.morse << ")\n";
    }

    cout << "End of heap display.\n";
  }
};

// Function to convert text to Morse code
void textToMorse(const char *text, char *morse, MorseCode &mc) {

  // Initialize the Morse code string to an empty string
  morse[0] = '\0'; //  This sets the first character of the morse string to
                   //  the null terminator to clear any previous content

  //  Loop through each character of the input text string
  for (int i = 0; text[i]; i++) {

    // Check if the character is an alphabet letter (A-Z or a-z)
    if (isalpha(text[i])) {

      // Convert the letter to uppercase and then calculate its index
      char c = toupper(text[i]) - 'A';

      //  Append the corresponding Morse code for the character from the
      //  MorseCode object
      strcat(morse, mc.letters[c]);

      // Add a space between Morse code letters
      strcat(morse, " ");
    }
  }
}

// Main function
int main() {
  BinaryTree bt;
  BST bst;
  Heap maxHeap(true), minHeap(false);
  MorseCode mc;

  int dsChoice;
  // Menu for Data Structres selection
  cout << "Choose Data Structure:\n";
  cout << "1. Binary Tree\n";
  cout << "2. Binary Search Tree\n";
  cout << "3. Max Heap\n";
  cout << "4. Min Heap\n";
  cout << "Select your choice: ";
  cin >> dsChoice;

  while (true) {
    // Menu for operations
    cout << "\nMenu:\n1. Add Password\n2. Remove Password\n3. Display "
            "Passwords\n4. Exit\n";
    int choice;
    cin >> choice;
    if (choice == 4)
      break;

    char text[50], morse[200];
    switch (choice) {
    case 1:
      cout << "Enter password: ";
      cin >> text;
      textToMorse(text, morse, mc);
      if (dsChoice == 1)
        bt.insert(text, morse);
      else if (dsChoice == 2)
        bst.root = bst.insert(bst.root, text, morse);
      else if (dsChoice == 3)
        maxHeap.insert(text, morse);
      else
        minHeap.insert(text, morse);
      break;
    case 2:
      if (dsChoice == 3)
        maxHeap.removeTop();
      else if (dsChoice == 4)
        minHeap.removeTop();
      else
        cout << "Remove not supported for this structure.\n";
      break;
    case 3: {
      string traversal;
      if (dsChoice == 1 || dsChoice == 2) {
        cout << "Choose traversal (preorder,inorder, postorder) <lowercase>: ";
        cin >> traversal;
      }
      if (dsChoice == 1)
        bt.display(traversal);
      else if (dsChoice == 2)
        bst.display(traversal);
      else if (dsChoice == 3)
        maxHeap.display();
      else
        minHeap.display();
      break;
    }
    }
  }
  return 0;
}
