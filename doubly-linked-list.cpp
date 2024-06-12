#include "doubly-linked-list.h"

DoublyLinkedList::Node::Node(DataType data) {
    value = data;
    next = nullptr;
    prev = nullptr;
}


DoublyLinkedList::DoublyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}


DoublyLinkedList::~DoublyLinkedList() {

    Node* tempPtr;
    tempPtr = head_;
    while (tempPtr != nullptr) {
        Node* nextPtr = tempPtr -> next;
        delete tempPtr;
        tempPtr = nextPtr;
    }

    head_ = nullptr;
    tail_ = nullptr;
}


unsigned int DoublyLinkedList::size() const {
    return size_;
}


unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}


bool DoublyLinkedList::empty() const {
    if (size_ == 0) {
        return true;
    }
    else {
        return false;
    }
}


bool DoublyLinkedList::full() const {
    if (size_ == CAPACITY){
        return true;
    }
    else {
        return false;
    }
}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
    if (index == 0) {
        return head_ -> value;
    }
    else if (index >= size_ - 1) {
        return tail_ -> value;
    }
    Node* selectedNode = getNode(index);
    if (selectedNode == nullptr) {
        selectedNode = getNode(size_ - 1);
    }
    DataType selectedValue = selectedNode -> value;
    return selectedValue;
}


unsigned int DoublyLinkedList::search(DataType value) const {
    Node* tempPtr;
    tempPtr = head_;
    for (int i = 0; i < size_; i++) {
        if (tempPtr -> value == value) {
            return i;
        }
        tempPtr = tempPtr -> next;
    }
    return size_;
}


void DoublyLinkedList::print() const {
    if (head_ == nullptr){
        return;
    }
    Node* tempPtr;
    tempPtr = head_;
    for (int i = 0; i < size_; i++) {
        std::cout << tempPtr -> value << std::endl;
        tempPtr = tempPtr -> next;
    }
}


DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {
    if (index >= size_) {
        return nullptr;
    }
    else {
        Node* tempPtr;
        tempPtr = head_;
        for (int i = 0; i <= index; i++) {
            if (i == index) {
                return tempPtr;
            }
            tempPtr = tempPtr -> next;
        }
    }
}


bool DoublyLinkedList::insert(DataType value, unsigned int index) {
    if (index > size_ || size_ >= CAPACITY){
        return false;
    }
    else {
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode -> prev = nullptr;
            if (head_ == nullptr) {
                newNode -> next = nullptr;
                tail_ = newNode;
            }
            else {
                newNode -> next = head_;
                head_ -> prev = newNode;
            }
            head_ = newNode;
        }
        else if (index == size_){
            newNode -> next = nullptr;
            if (head_ == nullptr) {
                newNode -> prev = nullptr;
                head_ = newNode;
            }
            else {
                newNode -> prev = tail_;
                tail_ -> next = newNode;
            }
            tail_ = newNode;
        }
        else {
            Node* nextNode = getNode(index);
            newNode -> prev = nextNode -> prev;
            nextNode -> prev = newNode;
            newNode -> next = nextNode;
            newNode -> prev -> next = newNode;
        }
        size_++;
        return true;
    }
}


bool DoublyLinkedList::insert_front(DataType value) {
    if (size_ >= CAPACITY) {
        return false;
    }
    else {
        Node* newNode = new Node(value);
        newNode -> prev = nullptr;
        if (head_ == nullptr) {
            newNode -> next = nullptr;
            tail_ = newNode;
        }
        else {
            newNode -> next = head_;
            head_ -> prev = newNode;
        }
        head_ = newNode;
        size_++;
        return true;
    }
}


bool DoublyLinkedList::insert_back(DataType value) {
    if (size_ >= CAPACITY) {
        return false;
    }
    else {
        Node* newNode = new Node(value);
        newNode -> next = nullptr;
        if (head_ == nullptr) {
            newNode -> prev = nullptr;
            head_ = newNode;
        }
        else {
            newNode -> prev = tail_;
            tail_ -> next = newNode;
        }
        tail_ = newNode;
        size_++;
        return true;
    }
}


bool DoublyLinkedList::remove(unsigned int index) {
    if (index >= size_ || size_ == 0) {
        return false;
    }
    else {
        if (index == 0) {
            remove_front();
        }
        else if (index == size_ - 1) {
            remove_back();
        }
        else {
            Node* tempPtr;
            tempPtr = getNode(index);
            tempPtr -> prev -> next = tempPtr -> next;
            tempPtr -> next -> prev = tempPtr -> prev;
            tempPtr -> prev = nullptr;
            tempPtr -> next = nullptr;
            delete tempPtr;
            tempPtr = nullptr;
            size_--;
        }
        return true;
    }
}

bool DoublyLinkedList::remove_front() {
    if (size_ == 0) {
        return false;
    }
    else {
        Node *tempPtr;
        tempPtr = head_;
        if (size_ == 1) {
            head_ = nullptr;
            tail_ = nullptr;
        } else {
            head_ = tempPtr->next;
            head_->prev = nullptr;
            tempPtr -> next = nullptr;
        }
        delete tempPtr;
        tempPtr = nullptr;
        size_--;
        return true;
    }
}


bool DoublyLinkedList::remove_back() {
    if (size_ == 0) {
        return false;
    }
    else {
        Node *tempPtr;
        tempPtr = tail_;
        if (size_ == 1) {
            head_ = nullptr;
            tail_ = nullptr;
        } else {
            tempPtr-> prev -> next = nullptr;
            tail_ = tempPtr -> prev;
            tempPtr -> prev = nullptr;
        }
        delete tempPtr;
        tempPtr = nullptr;
        size_--;
        return true;
    }
}


bool DoublyLinkedList::replace(unsigned int index, DataType value) {
    if (index >= size_) {
        return false;
    }
    else {
        Node* tempPtr;
        tempPtr = getNode(index);
        tempPtr -> value = value;
        return true;
    }
}
