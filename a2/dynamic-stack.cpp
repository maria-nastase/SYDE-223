#include "dynamic-stack.h"

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack() {
    init_capacity_ = 16;
    capacity_ = 16;
    items_ = new StackItem[capacity_];
    size_ = 0;
}

DynamicStack::DynamicStack(unsigned int capacity){
    if (capacity > 0) {
        init_capacity_ = capacity;
        capacity_ = capacity;
        items_ = new StackItem[capacity_];
        size_ = 0;
    }
}

DynamicStack::~DynamicStack() {
    delete [] items_;
    items_ = nullptr;
}

unsigned int DynamicStack::size() const {
    return size_;
}

bool DynamicStack::empty() const {
    if (size_ == 0) {
        return true;
    }
    else {
        return false;
    }
}

DynamicStack::StackItem DynamicStack::peek() const {
    if (size_ > 0) {
        return items_[size_ - 1];
    }
    else {
        return EMPTY_STACK;
    }
}

void DynamicStack::push(StackItem value) {
    if (size_ == capacity_) {
        StackItem* newItems = new StackItem[capacity_ * 2];
        capacity_ = capacity_ * 2;
        for (int i = 0; i < size_; i++) {
            newItems[i] = items_[i];
        }
        StackItem* temp = items_;
        items_ = newItems;
        delete [] temp;
        temp = nullptr;
    }
    items_[size_] = value;
    size_++;
}

DynamicStack::StackItem DynamicStack::pop() {
    if (size_ == 0) {
        return EMPTY_STACK;
    }
    else {
        StackItem poppedItem = items_[size_ -1];
        items_[size_ - 1] = NULL;
        size_--;
        if (size_ <= capacity_ / 4 && capacity_ / 2 >= init_capacity_){
            StackItem* newItems = new StackItem[capacity_ / 2];
            capacity_ = capacity_ / 2;
            for (int i = 0; i < size_; i++) {
                newItems[i] = items_[i];
            }
            StackItem* temp = items_;
            items_ = newItems;
            delete [] temp;
            temp = nullptr;
        }
        return poppedItem;
    }
}

void DynamicStack::print() const {
    if (size_ > 0) {
        for (int i = size_ - 1; i >= 0; i--) {
            std::cout << items_[i] << std::endl;
        }
    }
}
