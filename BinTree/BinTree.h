#pragma once
#include <iostream>

template <typename T>
struct BinNode {
    T data;
    BinNode<T>* left;
    BinNode<T>* right;
    BinNode(T d) : data(d), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinTree {
public:
    BinTree() : root(nullptr) {}
    ~BinTree() { clear(root); }
    void clear() { clear(root); root = nullptr; }
    bool empty() const { return root == nullptr; }
    void insert(const T& data) { insert(root, data); }
    void preOrder(void (*visit)(const T&)) const { preOrder(root, visit); }
    void inOrder(void (*visit)(const T&)) const { inOrder(root, visit); }
    void postOrder(void (*visit)(const T&)) const { postOrder(root, visit); }
protected:
    BinNode<T>* root;
    void clear(BinNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }
    void insert(BinNode<T>*& node, const T& data) {
        if (node == nullptr) {
            node = new BinNode<T>(data);
            return;
        }
        if (data < node->data) {
            insert(node->left, data);
        }
        else {
            insert(node->right, data);
        }
    }
    void preOrder(BinNode<T>* node, void (*visit)(const T&)) const {
        if (node == nullptr) {
            return;
        }
        visit(node->data);
        preOrder(node->left, visit);
        preOrder(node->right, visit);
    }
    void inOrder(BinNode<T>* node, void (*visit)(const T&)) const {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left, visit);
        visit(node->data);
        inOrder(node->right, visit);
    }
    void postOrder(BinNode<T>* node, void (*visit)(const T&)) const {
        if (node == nullptr) {
            return;
        }
        postOrder(node->left, visit);
        postOrder(node->right, visit);
        visit(node->data);
    }
};