#include "circular-queue.h"
#include <iostream>

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue() {
    capacity_ = 16;
    items_ = new QueueItem[capacity_];
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {
    capacity_ = capacity;
    items_ = new QueueItem[capacity_];
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}

CircularQueue::~CircularQueue() {
    delete [] items_;
    items_ = nullptr;
}

unsigned int CircularQueue::size() const {
    return size_;
}

bool CircularQueue::empty() const {
    if (size_ == 0)
        return true;
    else
        return false;
}

bool CircularQueue::full() const {
    if (size_ == capacity_)
        return true;
    else
        return false;
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if (size_ == 0)
        return EMPTY_QUEUE;
    else
        return items_[head_];
}

bool CircularQueue::enqueue(QueueItem value) {
    if (full()) {
        return false;
    }
    else {
        items_[tail_] = value;
        if (tail_ == capacity_ - 1) {
            tail_ = 0;
        }
        else {
            tail_++;
        }
        size_++;

        return true;
    }
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    if (empty()) {
        return EMPTY_QUEUE;
    }
    else {
        QueueItem value = items_[head_];
        items_[head_] = NULL;
        if (head_ == capacity_ - 1) {
            head_ = 0;
        }
        else {
            head_++;
        }
        size_--;

        return value;
    }
}

void CircularQueue::print() const {
    if (size_ > 0) {
        int i = head_;
        while (i != tail_) {
            std::cout << items_[i] << std::endl;
            if (i == capacity_ - 1) {
                i = 0;
            }
            else {
                i++;
            }
        }
    }
}
