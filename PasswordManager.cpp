/* This program converts a entered password into morse code*/

#include <bits/stdc++.h> // Include all C++ STL
using namespace std;

// Morse code list
struct MorseCode {
  const char *letters[26] = {
      ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....",
      "..", // A-I
      ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-",
      ".-.",                                                        // J-R
      "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.." // S-Z
  };
};

// Password entry structure
struct PasswordEntry {
  char text[50];
  char morse[200];
};

// Binary Tree Implementation
struct BinaryTree {
  PasswordEntry *entries;
  int size;
  int capacity;

  // Constructor
  void init(int cap) {
    capacity = cap;
    entries = new PasswordEntry[capacity];
    size = 0;
  }
  // Function to insert a text
  int insert(const char *text, const char *morse) {
    if (size >= capacity) {
      cout << "\nTree is full!";
      return -1;
    }
    // Copies the text with length limit
    strncpy(entries[size].text, text, 49);
    strncpy(entries[size].morse, morse, 199);
    size++;
    return 0;
  }
  // Function to display all stored passwords
  void display() {
    if (size == 0) {
      cout << "No passwords stored.\n";
      return;
    }
    cout << "\nStored Passwords (Binary Tree):\n";
    for (int i = 0; i < size; i++) {
      cout << "Index " << i << ": " << entries[i].text
           << " (Morse: " << entries[i].morse << ")\n";
    }
  }

  // Function to delete password
  int remove(int index) {
    if (index >= size) {
      cout << "\nInvalid index!";
      return -1;
    }
    for (int i = index; i < size - 1; i++) {
      entries[i] = entries[i + 1];
    }
    size--;
    return 0;
  }
};

// Binary Search Tree Implementation
struct BST {
  PasswordEntry *entries;
  int size;
  int capacity;
  // Constructor
  void init(int cap) {
    capacity = cap;
    entries = new PasswordEntry[capacity];
    size = 0;
  }

  int insert(const char *text, const char *morse) {
    if (size >= capacity) {
      cout << "\nBST is full!\n";
      return -1;
    }

    int pos = 0;
    while (pos < size) {
      if (strcmp(text, entries[pos].text) < 0) {
        pos = 2 * pos + 1;
      } else {
        pos = 2 * pos + 2;
      }
    }

    if (pos < capacity) {
      strncpy(entries[pos].text, text, 49);
      strncpy(entries[pos].morse, morse, 199);
      size++;
      return 0;
    }
    return -1;
  }
  // Display function
  void display() {
    bool isEmpty = true;
    cout << "\nStored Passwords (BST):\n";
    for (int i = 0; i < capacity; i++) {
      if (entries[i].text[0] != '\0') {
        isEmpty = false;
        cout << "Index " << i << ": " << entries[i].text
             << " (Morse: " << entries[i].morse << ")\n";
      }
    }
    if (isEmpty) {
      cout << "No passwords stored.\n";
    }
  }

  // Function to remove a password
  int remove(const char *text) {
    int pos = 0;
    while (pos < capacity) {
      if (entries[pos].text[0] == '\0')
        return -1;
      if (strcmp(text, entries[pos].text) == 0) {
        entries[pos].text[0] = '\0';
        size--;
        return 0;
      }
      if (strcmp(text, entries[pos].text) < 0) {
        pos = 2 * pos + 1;
      } else {
        pos = 2 * pos + 2;
      }
    }
    return -1;
  }
};

// Max Heap Implementation
struct MaxHeap {
  PasswordEntry *entries;
  int size;
  int capacity;
  // Constructor
  void init(int cap) {
    capacity = cap;
    entries = new PasswordEntry[capacity];
    size = 0;
  }
  // Heapify up function
  void heapifyUp(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && strcmp(entries[parent].text, entries[index].text) < 0) {
      swap(entries[parent], entries[index]);
      index = parent;
      parent = (index - 1) / 2;
    }
  }
  // Function to insert a password
  int insert(const char *text, const char *morse) {
    if (size >= capacity) {
      cout << "\nHeap is full!";
      return -1;
    }

    strncpy(entries[size].text, text, 49);
    strncpy(entries[size].morse, morse, 199);
    heapifyUp(size);
    size++;
    return 0;
  }
  // Heapify down function
  void heapifyDown(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && strcmp(entries[left].text, entries[largest].text) > 0)
      largest = left;

    if (right < size && strcmp(entries[right].text, entries[largest].text) > 0)
      largest = right;

    if (largest != index) {
      swap(entries[index], entries[largest]);
      heapifyDown(largest);
    }
  }
  // Function to remove in the max heap
  int removeMax() {
    if (size == 0) {
      cout << "\nHeap is empty!";
      return -1;
    }

    cout << "\nRemoved password: " << entries[0].text;
    entries[0] = entries[size - 1];
    size--;
    heapifyDown(0);
    return 0;
  }
  // Display all max heap
  void display() {
    if (size == 0) {
      cout << "No passwords stored.\n";
      return;
    }
    cout << "\nStored Passwords (Max Heap):\n";
    for (int i = 0; i < size; i++) {
      cout << "Index " << i << ": " << entries[i].text
           << " (Morse: " << entries[i].morse << ")\n";
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

// Function to convert Morse to text
void morseToText(const char *morse, char *text, MorseCode &mc) {
  text[0] = '\0';
  char *morseCopy = strdup(morse);
  char *token = strtok(morseCopy, " ");
  int pos = 0;

  while (token != NULL) {
    for (int i = 0; i < 26; i++) {
      if (strcmp(token, mc.letters[i]) == 0) {
        text[pos++] = 'A' + i;
        break;
      }
    }
    token = strtok(NULL, " ");
  }
  text[pos] = '\0';
  free(morseCopy);
}

int main() {
  BinaryTree bt;
  BST bst;
  MaxHeap heap;
  MorseCode mc;

  bt.init(10);
  bst.init(10);
  heap.init(10);

  int dsChoice;
  // Menu
  cout << "Choose Data Structure for Password Manager:\n";
  cout << "1. Binary Tree\n";
  cout << "2. Binary Search Tree\n";
  cout << "3. Max Heap\n";
  cout << "Enter choice: ";
  cin >> dsChoice;

  // Menu for different Tree operations
  while (true) {
    cout << "\nPassword Manager Menu:\n";
    cout << "1. Add Password\n";
    cout << "2. Remove Password\n";
    cout << "3. Display Passwords\n";
    cout << "4. Convert Text to Morse\n";
    cout << "5. Convert Morse to Text\n";
    cout << "6. Exit\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input! Please enter a number.\n";
      continue;
    }

    if (choice == 6)
      break;

    char text[50], morse[200];

    switch (choice) {
    case 1:
      cout << "Enter password: ";
      cin >> text;
      textToMorse(text, morse, mc);

      switch (dsChoice) {
      case 1:
        bt.insert(text, morse);
        cout << "Password added successfully.\n";
        break;
      case 2:
        bst.insert(text, morse);
        cout << "Password added successfully.\n";
        break;
      case 3:
        heap.insert(text, morse);
        cout << "Password added successfully.\n";
        break;
      }
      break;

    case 2:
      if (dsChoice == 1) {
        cout << "Enter index to remove: ";
        int index;
        cin >> index;
        if (cin.fail()) {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input! Please enter a number.\n";
          break;
        }
        if (index >= bt.size || index < 0) {
          cout << "Error: Index does not exist!\n";
          break;
        }
        bt.remove(index);
      } else if (dsChoice == 2) {
        cout << "Enter password to remove: ";
        cin >> text;
        if (bst.remove(text) == -1) {
          cout << "Error: Password not found!\n";
        }
      } else {
        if (heap.size == 0) {
          cout << "Error: Heap is empty!\n";
          break;
        }
        heap.removeMax();
      }
      break;

    case 3:
      switch (dsChoice) {
      case 1:
        bt.display();
        break;
      case 2:
        bst.display();
        break;
      case 3:
        heap.display();
        break;
      }
      break;

    case 4:
      cout << "Enter text to convert: ";
      cin >> text;
      textToMorse(text, morse, mc);
      cout << "Morse code: " << morse << "\n";
      break;

    case 5:
      cout << "Enter Morse code (use spaces between letters): ";
      cin.ignore();
      cin.getline(morse, 200);
      morseToText(morse, text, mc);
      cout << "Text: " << text << "\n";
      break;

    default:
      cout << "Invalid choice!\n";
    }
  }
  return 0;
}