#ifndef NODE_H
#define NODE_H

template <typename T, typename D>
struct Node {
    // atributos
    T key;
    D* data;
    int height;
    Node* left;
    Node* right;

    // Construtor
    Node (T key,D* data = nullptr,Node<T,D> *left = nullptr, Node<T,D> *right = nullptr, int height = 1)
        : key(key), data(data),height(height), left(left), right(right)
    {
    }
};



#endif 
