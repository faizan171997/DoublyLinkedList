#include <iostream>
#include <cassert>

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int data) : data(data), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void prepend(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    bool remove(int data) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == data) {
                if (temp->prev != nullptr) temp->prev->next = temp->next;
                if (temp->next != nullptr) temp->next->prev = temp->prev;
                if (temp == head) head = temp->next;
                if (temp == tail) tail = temp->prev;
                delete temp;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void displayForward() const {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void displayBackward() const {
        Node* temp = tail;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->prev;
        }
        std::cout << std::endl;
    }
};

void unitTests() {
    DoublyLinkedList list;

    // Test appending and prepending
    list.append(1);
    list.append(2);
    list.prepend(0);
    assert(list.head->data == 0 && "Head should be 0 after prepend");
    assert(list.tail->data == 2 && "Tail should be 2 after append");

    // Test removing a middle node
    list.remove(1);
    assert(list.head->next->data == 2 && "Next node should be 2 after removing 1");
    assert(list.head->data == 0 && "Head should remain 0 after removing 1");

    // Test removing the head
    list.prepend(-1);
    list.remove(-1);
    assert(list.head->data == 0 && "Head should be 0 after removing -1");

    // Test removing the tail
    list.append(3);
    list.remove(3);
    assert(list.tail->data == 2 && "Tail should be 2 after removing 3");

    // Test list with a single node
    list.remove(0);
    list.remove(2);
    list.append(4);
    assert(list.head->data == 4 && "Head should be 4 in a single-node list");
    assert(list.tail->data == 4 && "Tail should be 4 in a single-node list");
    list.remove(4);
    assert(list.head == nullptr && "List should be empty after removing the single node");

    // Test removing a non-existent node
    list.append(5);
    list.append(6);
    bool removed = list.remove(7);
    assert(!removed && "Remove should return false when node does not exist");
    assert(list.head->data == 5 && "Head should be 5 after attempting to remove a non-existent node");
    assert(list.tail->data == 6 && "Tail should be 6 after attempting to remove a non-existent node");

    // Test forward and backward traversal for consistency
    list.append(7);
    Node* temp = list.head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    assert(temp->data == list.tail->data && "Last node reached should be the tail");
    while (temp->prev != nullptr) {
        temp = temp->prev;
    }
    assert(temp->data == list.head->data && "First node reached backwards should be the head");

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    unitTests();
    return 0;
}
