#include <iostream>
#include <vector>
#pragma once

using namespace std;
template <typename T>

class LinkedList {
public:
    struct Node {
        Node *next;
        Node *prev;
        T data;
    };

    /*==== Behaviors ====*/
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

    /*==== Accessors ====*/
    unsigned int NodeCount() const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    const Node* GetNode(unsigned int index) const;
    Node* Head();
    Node* Tail();

    /*==== Insertion ====*/
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);

    /*==== Removal ====*/
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T&data);
    bool RemoveAt(unsigned int index);
    void Clear();

    /*==== Operators ====*/
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    bool operator==(const LinkedList<T>& rhs) const;
    LinkedList<T>& operator=(const LinkedList<T>& rhs);

    /*==== Construction / Destruction ====*/
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();

private:
    Node *head = nullptr;
    Node *tail = nullptr;
    unsigned int nodeCount = 0;
};
// ==== Add Head ==== //
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
    Node* newNode = new Node(); // Create new node
    newNode->data = data; // Assigns passed data to new node
    if(head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    nodeCount++; // Increment total node count
}
// ==== Add Tail ==== //
template <typename T>
void LinkedList<T>::AddTail(const T& data) {
    Node* newNode = new Node(); // Create new node
    newNode->data = data; // Assigns passed data to new node
    if(tail == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    nodeCount++; // Increment total node count
}

// ==== Add Nodes Head ==== //
template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
    int adjustIndex = (int)count - 1; // Adjust index to that of an array
    for(int i = adjustIndex; i >= 0; --i) { // Loop through array
        AddHead(data[i]); // Assign each index
    }
}

// ==== Add Nodes Head ==== //
template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    for(unsigned int i = 0; i < count; i++) { // Loop through array
        this->AddTail(data[i]); // Assign each index
    }
}

// ==== Node Count ==== //
template <typename T>
unsigned int LinkedList<T>::NodeCount() const{
    return nodeCount; // Getter
}

// ==== Print Forward ==== //
template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* index = head; // Assign index to head node
    while(index != nullptr) { // Iterate through nodes
        cout << index->data << endl; // Print value
        index = index->next; // Go to next node
    }
}

// ==== Print Reverse ==== //
template <typename T>
void LinkedList<T>::PrintReverse() const {
    Node* index = tail; // Assign index to head node
    while(index != nullptr) { // Iterate through nodes
        cout << index->data << endl; // Print value
        index = index->prev; // Go to previous node
    }
}

// ==== Destructor ==== //
template<typename T>
LinkedList<T>::~LinkedList() {
    Node *temp;
    Node *ptr = head;
    while(ptr != nullptr) { // Iterate nodes with data
        temp = ptr->next; // Next node
        delete ptr; // Deallocate memory
        ptr = temp;
    }
    head = nullptr;
    tail = nullptr;
    nodeCount = 0; // Reset node count
}

// ==== Head ==== //
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head; // Getter
}

// ==== Tail ==== //
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail; // Getter
}

// ==== Get Node == //
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    if(index >= nodeCount) { // Catch invalid input
        throw out_of_range("Out of Range");
    }
    Node* node = head;
    for(unsigned int i = 0; i < index; i++) { // Find node corresponding to index
        node = node->next;
    }
    return node;
}

// ==== Operator ==== //
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
    if(nodeCount == 0 || index > nodeCount - 1) { // Catch invalid input
        throw out_of_range("Out of range");
    }
    if (index == 0) {
        return head->data;
    }
    Node* n = head;
    for(int i = 1; i < index; i++) { // Takes an index and returns data from the i-th node
        n = n->next;
    }
    return n->data;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index)  {
    if(nodeCount == 0 || index > nodeCount - 1) { // Catch invalid input
        throw out_of_range("Out of range");
    }
    if (index == 0) {
        return head->data;
    }
    Node* n = head;
    for(int i = 1; i < index; i++) { // Takes an index and returns data from the i-th node
        n = n->next;
    }
    return n->data;
}

// ==== Find ==== //
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
    Node* node = head; // Start at head
    while(node != nullptr) { // Iterate to find node with matching data
        if(node->data == data) {
            return node;
        }
        node = node->next;
    }
    return nullptr; // Return nullptr if none match
}

// ==== Find ==== //
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) const {
    Node* node = head;
    while (node != nullptr) { // Iterate to find node with matching data
        if(node->data == data) {
            return node;
        }
        node = node->next;
    }
    return nullptr; // Return nullptr if none match
}

// ==== Find All ==== //
template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
    Node* node = head;
    while(node != nullptr) {
        if(node->data == value) { // If data matches
            outData.push_back(node); // Add to vector
        }
        node = node->next;
    }
}

// ==== Default Constructor ==== //
template<typename T>
LinkedList<T>::LinkedList() {
    this->nodeCount = 0;
    head = nullptr;
    tail = nullptr;
}

// ==== Copy Constructor ==== //
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    nodeCount = 0;
    head = nullptr;
    tail = nullptr;
    for(unsigned int i = 0; i < list.NodeCount(); i++) {
        this->AddTail(list.GetNode(i)->data);
    }
}

// ==== Insert Before ==== //
template<typename T>
void LinkedList<T>::InsertBefore(LinkedList<T>::Node* node, const T& data) {
    Node* newNode = head; // Create new node
    while(newNode) {
        if(node == head) {
            AddHead(data); // Add data to new node
            break;
        }
        if(newNode == node) { // Given a node, create a new node to store passed value before indicated node
            Node* temp = new Node;
            temp->data = data;
            temp->next = newNode;
            temp->prev = newNode->prev;
            newNode->prev->next =  temp;
            newNode->prev = temp;
        }
        newNode = newNode->next;
    }
}

// ==== Insert After ==== //
template<typename T>
void LinkedList<T>::InsertAfter(LinkedList<T>::Node* node, const T& data) {
    Node* newNode = head;
    while (newNode) {
        if(node == tail) {
            AddTail(data);
            break;
        }
        if(newNode == node) { // Given a node, create a new node to store passed value after indicated node
            Node* temp = new Node;
            temp->data = data;
            temp->prev = newNode;
            temp->next = newNode->next;
            newNode->next->prev = temp;
            newNode->next = temp;
        }
        newNode = newNode->next;
    }
}

// ==== Insert At ==== //
template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
    if(index > nodeCount || index < 0) {
        throw out_of_range("Index out of range");
    }
    if(index == 0) {
        AddHead(data);
        return;
    }
    else if (index == nodeCount) {
        AddTail(data);
        return;
    }
    else {
        Node* temp = head;
        Node* previous = nullptr;
        for(unsigned int i = 0; i < index; i++) {
            previous = temp;
            temp = temp->next;
        }

        Node* newNode = new Node;
        newNode->data = data;

        previous->next = newNode;
        temp->prev = newNode;

        newNode->next = temp;
        newNode->prev = previous;
    }
    nodeCount += 1;
}

// ==== Operator ==== //
template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    if(rhs.nodeCount != nodeCount) {
        return false;
    }
    Node* newNode = head;
    Node* temp = rhs.head;
    while (newNode){
        if(temp->data != newNode->data) {
            return false;
        }
        else {
            newNode = newNode->next;
            temp = temp->next;
        }
    }
    return true;
}

// ==== Remove Head ==== //
template<typename T>
bool LinkedList<T>::RemoveHead() {
    if(head != nullptr) {
        Node* newNode = head;
        head = head->next;
        if(head != nullptr) {
            head->prev = nullptr;
        }
        delete newNode;
        nodeCount--;
        if(nodeCount == 0) {
            head = tail = nullptr;
        }
        return true;
    }
    else {
        return false;
    }
}

// ==== Remove Tail ==== //
template<typename T>
bool LinkedList<T>::RemoveTail() {
    if(tail != nullptr) {
        Node* newNode = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        delete newNode;
        nodeCount--;
        if (nodeCount == 0) {
            head = tail = nullptr;
        }
        return true;
    }
    else {
        return false;
    }
}

// ==== Remove Head ==== //
template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
    Node* newNode = head;
    unsigned int remove_count = 0;
    Node* temp = nullptr;
    while(newNode) {
        if(newNode->data != data) {
            temp = newNode;
            newNode = newNode->next;
        }
        else {
            if(newNode == head) {
                newNode = newNode->next;
                RemoveHead();
            }
            else if(newNode == head) {
                newNode = nullptr;
                RemoveTail();
            }
            Node* temp2 = newNode;
            temp->next = newNode->next;
            if(newNode->next != nullptr) {
                newNode->next->prev = temp;
            }
            newNode = newNode->next;
            delete temp2;
            remove_count += 1;
        }
    }
    return remove_count;
}

// ==== Remove At ==== //
template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    Node* newNode = head;
    Node* temp = nullptr;
    if(index >= nodeCount) {
        return false;
    }
    for(unsigned int i = 0; i < index; i++) {
        temp = newNode;
        newNode = newNode->next;
    }
    temp->next = newNode->next;
    if(newNode->next != nullptr) {
        newNode->next->prev = temp;
    }
    delete newNode;
    nodeCount--;
    if(nodeCount == 0) {
        head = tail = nullptr;
    }
    return true;
}

// ==== Clear ==== //
template <typename T>
void LinkedList<T>::Clear() {
    Node* current = head;
    while(current != nullptr) {
        head = head->next;
        delete current;
        current = head;
    }
    nodeCount = 0;
    head = nullptr;
    tail = nullptr;
}

// ==== Print Forward Recursive ==== //
template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
    if(node != nullptr) {
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }
}

// ==== Print Reverse Recursive ==== //
template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
    if(node != nullptr) {
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }
}

// ==== Operator ==== //
template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs){
    Clear();
    nodeCount = 0;
    head = nullptr;
    tail = nullptr;
    for(unsigned int i = 0; i < rhs.NodeCount(); i++) {
        this->AddTail(rhs.GetNode(i)->data);
    }
    return *this;
}