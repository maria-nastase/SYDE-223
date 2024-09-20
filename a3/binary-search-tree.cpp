#include "binary-search-tree.h"
#include <iostream>
#include <queue>

BinarySearchTree::Node::Node(DataType newval) {
    left = nullptr;
    right = nullptr;
    val = newval;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if (n == nullptr)
        return -1;
    else if (n -> left == nullptr && n -> right == nullptr)
        return 0;
    else
        return 1 + std::max(getNodeDepth(n -> left), getNodeDepth(n -> right));
}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree() {
    if (root_ != nullptr) {
        std::queue<Node *> Q;
        Q.push(root_);
        while (!Q.empty()) {
            Node *temp = Q.front();
            Q.pop();
            if (temp->left != nullptr)
                Q.push(temp->left);
            if (temp->right != nullptr)
                Q.push(temp->right);
            delete temp;
            temp = nullptr;
        }
    }
}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    Node *temp = root_;
    DataType max = temp -> val;
    while (temp != nullptr) {
        if (max <= temp -> val) {
            max = temp -> val;
            temp = temp -> right;
        }
    }
    return max;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node *temp = root_;
    DataType min = temp -> val;
    while (temp != nullptr) {
        if (min >= temp -> val) {
            min = temp -> val;
            temp = temp -> left;
        }
    }
    return min;
}

int BinarySearchTree::height() const {
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const {
    if (root_ == nullptr) {
        std::cout << "Empty" << std::endl;
        return;
    }
    std::queue<Node*> Q;
    Q.push(root_);
    while (!Q.empty()) {
        Node *temp = Q.front();
        Q.pop();

        std::cout << temp->val << ", ";
        if (temp->left != nullptr)
            Q.push(temp->left);
        if (temp->right != nullptr)
            Q.push(temp->right);
    }
}

bool BinarySearchTree::exists(DataType val) const {
    Node *temp = root_;
    while (temp != nullptr) {
        if (temp -> val == val)
            return true;
        else if (val < temp -> val)
            temp = temp -> left;
        else
            temp = temp -> right;
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    Node* newNode = new Node(val);

    Node* temp = root_;

    if (root_ == nullptr) {
        root_ = newNode;
        size_++;
        return true;
    }

    while (temp != nullptr) {
        if (newNode -> val == temp -> val)
            return false;
        else if (newNode -> val < temp -> val) {
            if (temp -> left == nullptr) {
                temp -> left = newNode;
                size_++;
                return true;
            }
            else
                temp = temp -> left;
        }
        else {
            if (temp -> right == nullptr) {
                temp -> right = newNode;
                size_++;
                return true;
            }
            else
                temp = temp -> right;
        }
    }
}

bool BinarySearchTree::remove(DataType val) {
    if (!exists(val))
        return false;

    Node *temp = root_;
    Node *parent = nullptr;
    bool isLeftChild = false;
    while (temp != nullptr) {
        if (temp -> val == val)
            break;
        else if (val < temp -> val) {
            parent = temp;
            temp = temp->left;
            isLeftChild = true;
        }
        else {
            parent = temp;
            temp = temp->right;
            isLeftChild = false;
        }
    }

    if (temp -> left == nullptr && temp -> right == nullptr) {
        if (temp == root_) {
            delete root_;
            root_ = nullptr;
            size_--;
            return true;
        }
        delete temp;
        temp = nullptr;
        if (isLeftChild)
            parent -> left = nullptr;
        else
            parent -> right = nullptr;
        size_--;
        return true;
    }

    if (temp -> left == nullptr && temp -> right != nullptr) {
        if (temp == root_)
            root_ = temp -> right;
        else {
            if (isLeftChild)
                parent->left = temp->right;
            else
                parent->right = temp->right;
        }
        delete temp;
        temp = nullptr;
        size_--;
        return true;
    }
    else if (temp -> right == nullptr && temp -> left != nullptr) {
        if (temp == root_) {
            root_ = temp -> left;
        }
        else {
            if (isLeftChild)
                parent->left = temp->left;
            else
                parent->right = temp->left;
        }
        delete temp;
        temp = nullptr;
        size_--;
        return true;
    }

    Node *predecessorParent = temp;
    Node *predecessor = temp -> left;
    isLeftChild = true;

    while (predecessor -> right != nullptr) {
        predecessorParent = predecessor;
        predecessor = predecessor -> right;
        isLeftChild = false;
    }

    temp -> val = predecessor -> val;


    if (predecessor -> left == nullptr) {
        if (!isLeftChild) {
            predecessorParent -> right = nullptr;
        }
        else {
            predecessorParent->left = nullptr;
        }
    }
    else {
        if (!isLeftChild)
            predecessorParent->right = predecessor->left;
        else
            predecessorParent->left = predecessor->left;
    }
    delete predecessor;
    predecessor = nullptr;
    size_--;
    return true;

}
