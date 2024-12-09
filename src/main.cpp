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
    // Create a new PasswordEntry object
    PasswordEntry entry;
    // Copies text into entry.text
    strncpy(entry.text, text, 49);
    strncpy(entry.morse, morse, 199);
    // Adds to entries
    entries.push_back(entry);
    cout << GREEN << "\nPassword " << entry.text << " added successfully.\n"
         << RESET;
  }

  // Preorder traversal
  void preorder(int index) {
    // Checks if index is out of bounds
    if (index >= entries.size())
      return;

    // Visit root node
    cout << entries[index].text << " (Morse: " << entries[index].morse << ")\n";

    // Visit left node
    preorder(2 * index + 1);

    // Visit right node
    preorder(2 * index + 2);
  }

  // Inorder traversal
  void inorder(int index) {
    // Checks if index is out of bounds
    if (index >= entries.size())
      return;

    // Visit left node
    inorder(2 * index + 1);

    // Visit root node
    cout << entries[index].text << " (Morse: " << entries[index].morse << ")\n";

    // Visit right node
    inorder(2 * index + 2);
  }

  // Post order traversal
  void postorder(int index) {
    // Checks if index is out of bounds
    if (index >= entries.size())
      return;

    // Visit left node
    postorder(2 * index + 1);

    // Visit right node
    postorder(2 * index + 2);

    // Visit root node
    cout << entries[index].text << " (Morse: " << entries[index].morse << ")\n";
  }

  // Function to display passwords based on traversal selection
  void display(const string &traversal) {
    // Checks if entries is empty
    if (entries.empty()) {
      cout << "No passwords stored.\n";
      return;
    }
    // Display passwords based on conditions met
    cout << "Passwords (Binary Tree, " << traversal << "):\n";
    if (traversal == "preorder")
      preorder(0);
    else if (traversal == "inorder")
      inorder(0);
    else if (traversal == "postorder")
      postorder(0);
  }

  // Function to remove a password
  bool remove(const char *text) {
    //  Find the index of the password to remove
    for (int i = 0; i < entries.size(); i++) {
      if (strcmp(entries[i].text, text) == 0) {
        //  Replace with the last entry and remove the last entry
        entries[i] = entries.back();

        entries.pop_back();
        cout << GREEN << "\nPassword removed successfully.\n" << RESET;
        return true;
      }
    }
    cout << RED << "\nPassword not found.\n" << RESET;
    return false;
  }

  // Search function for Binary Tree
  bool search(const char *text) {
    // Search through all entries
    for (const auto &entry : entries) {
      // Compare current entry with search text
      if (strcmp(entry.text, text) == 0) {
        cout << GREEN << "\nPassword found: " << entry.text
             << "\nMorse code: " << entry.morse << RESET << endl;
        return true;
      }
    }
    cout << RED << "\nPassword not found.\n" << RESET;
    return false;
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
    if (!root) {
      // Create the new node when root is nullptr
      root = createNode(text, morse);
      cout << GREEN << "\nPassword " << root->entry.text
           << " added successfully.\n"
           << RESET;
      return root;
    }

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

  Node *search(Node *root, const char *text) {
    // Base case - if root is null or match found
    if (!root || strcmp(root->entry.text, text) == 0) {
      return root;
    }

    // Recursive search based on comparison
    if (strcmp(text, root->entry.text) < 0) {
      return search(root->left, text);
    }
    return search(root->right, text);
  }

  // Helper function to find minimum value node
  Node *minValueNode(Node *node) {
    Node *current = node;
    while (current && current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  // Remove function for BST
  Node *remove(Node *root, const char *text) {
    // Base case - if tree is empty
    if (!root) {
      return root;
    }

    // Find the node to delete
    if (strcmp(text, root->entry.text) < 0) {
      root->left = remove(root->left, text);
    } else if (strcmp(text, root->entry.text) > 0) {
      root->right = remove(root->right, text);
    } else {
      // Node with only one child or no child
      if (!root->left) {
        Node *temp = root->right;
        delete root;
        return temp;
      } else if (!root->right) {
        Node *temp = root->left;
        delete root;
        return temp;
      }

      // Node with two children
      Node *temp = minValueNode(root->right);
      strcpy(root->entry.text, temp->entry.text);
      strcpy(root->entry.morse, temp->entry.morse);
      root->right = remove(root->right, temp->entry.text);
    }
    return root;
  }
};

// Heap Implementation (Both Max and Min)
struct Heap {
  vector<PasswordEntry> entries;
  bool isMaxHeap; // True for max heap, false for min heap

  Heap(bool isMax) : isMaxHeap(isMax) {}

  // Repeatedly swap with parent until heap property is satisfied
  void heapifyUp(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && compare(entries[parent], entries[index])) {
      swap(entries[parent], entries[index]);
      index = parent;
      parent = (index - 1) / 2;
    }
  }
  // Repeatedly swap with higher priority child until heap property is satisfied
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
  // Function to perform heap comparison
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
    cout << GREEN << "\nPassword " << entry.text << " added successfully.\n"
         << RESET;
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

  // Function to display passwords
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

  bool search(const char *text) {
    // Step 1: Linear search through all entries
    for (const auto &entry : entries) {
      // Step 2: Compare current entry with search text
      if (strcmp(entry.text, text) == 0) {
        cout << GREEN << "\nPassword found: " << entry.text
             << "\nMorse code: " << entry.morse << RESET << endl;
        return true;
      }
    }
    cout << RED << "\nPassword not found.\n" << RESET;
    return false;
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

int main() {
  BinaryTree bt;
  BST bst;
  Heap maxHeap(true), minHeap(false);
  MorseCode mc;

  while (true) { // Main program loop
    cout << BLUE << "=================================================\n"
         << RESET;
    cout << RED << "        Welcome to Password Manager\n";
    cout << "     Select a data structure to get started!\n" << RESET;
    cout << BLUE << "=================================================\n"
         << RESET;

    int dsChoice;
    cout << "Select a Data Structure:\n";
    cout << "1. Binary Tree\n";
    cout << "2. Binary Search Tree\n";
    cout << "3. Max Heap\n";
    cout << "4. Min Heap\n";
    cout << "5. Exit Program\n";
    cout << "Select your choice: ";
    cin >> dsChoice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input! Please enter a number.\n";
      continue;
    }

    if (dsChoice == 5) { // Exit entire program
      cout << "\nThank you for using Password Manager!\n";
      break;
    }

    bool returnToMainMenu = false;
    while (!returnToMainMenu) { // Operations menu loop
      cout << "\nOperations Available:\n"
           << "1. Add Password\n"
           << "2. Remove Password\n"
           << "3. Display Passwords\n"
           << "4. Search Password\n"
           << "5. Return to Data Structure Selection\n";
      cout << "Select your choice: ";

      int choice;
      cin >> choice;
      // Input validation
      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number.\n";
        continue;
      }

      if (choice == 5) {
        returnToMainMenu = true;
        continue;
      }

      char text[50], morse[200];

      switch (choice) {
      case 1: {
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
      }

      case 2: {
        cout << "Enter password to remove: ";
        cin >> text;

        if (dsChoice == 1) {
          bt.remove(text);
        } else if (dsChoice == 2) {
          BST::Node *foundNode = bst.search(bst.root, text);
          if (foundNode) {
            bst.root = bst.remove(bst.root, text);
            cout << GREEN << "\nPassword removed successfully.\n" << RESET;
          } else {
            cout << RED << "\nPassword not found.\n" << RESET;
          }
        } else if (dsChoice == 3)
          maxHeap.removeTop();
        else
          minHeap.removeTop();
        break;
      }

      case 3: {
        string traversal;
        if (dsChoice == 1 || dsChoice == 2) {
          cout << "Choose traversal (preorder, inorder, postorder) "
                  "<lowercase>: ";
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

      case 4: {
        cout << "Enter password to search: ";
        cin >> text;

        if (dsChoice == 1) {
          bt.search(text);
        } else if (dsChoice == 2) {
          BST::Node *resultNode = bst.search(bst.root, text);
          if (resultNode) {
            cout << GREEN << "\nPassword found: " << resultNode->entry.text
                 << "\nMorse code: " << resultNode->entry.morse << RESET
                 << endl;
          } else {
            cout << RED << "\nPassword not found.\n" << RESET;
          }
        } else if (dsChoice == 3) {
          maxHeap.search(text);
        } else {
          minHeap.search(text);
        }
        break;
      }
      }
    }
  }
  return 0;
}