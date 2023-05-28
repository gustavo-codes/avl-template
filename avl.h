#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <stack>
#include "node.h"
using namespace std;

//Declaração da classe
template <typename T, typename D>
class avl_tree {
public:
    avl_tree() = default;
    avl_tree(const avl_tree& t) = delete;
    avl_tree& operator=(const avl_tree& t) = delete;
    vector<Node<T,D>*> search(T min, T max);
    void add(T key, D* data); 
    void bshow() const;
    void clear();
    void remove(T key);
    ~avl_tree();
    
private:
    Node<T,D>* root {nullptr};
    int height(Node<T,D>* node);
    int balance(Node<T,D> *node);
    void searchSimilar(Node<T,D>* p, vector<Node<T,D>*> &vec, T min, T max);
    Node<T,D>* add(Node<T,D>*p, T key, D* data); 
    Node<T,D>* rightRotation(Node<T,D> *p);
    Node<T,D>* leftRotation(Node<T,D> *p);
    Node<T,D>* fixup_node(Node<T,D> *p, T key);
    void bshow(Node<T,D> *node, std::string heranca) const;
    Node<T,D>* clear(Node<T,D> *node);
    Node<T,D>* remove(Node<T,D> *node, T key); 
    Node<T,D>* remove_successor(Node<T,D> *root, Node<T,D> *node);
    Node<T,D>* fixup_deletion(Node<T,D> *node);
};

//Implementação da classe
// retorna a altura do nó.
// se a arvore for vazia ela tem altura 0
// caso contrario, retorna o valor que está no campo height
template <typename T, typename D>
int avl_tree<T,D>::height(Node<T,D> *node) {
    return (node == nullptr) ? 0 : node->height;
}

template <typename T, typename D>
int avl_tree<T,D>::balance(Node<T,D> *node) {
    return height(node->right) - height(node->left);
}

template <typename T, typename D>
Node<T,D>* avl_tree<T,D>::rightRotation(Node<T,D> *p) {
    Node<T,D> *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

template <typename T, typename D>
Node<T,D>* avl_tree<T,D>::leftRotation(Node<T,D> *p) {
    Node<T,D> *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->right),height(p->left));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

//Solução iterativa do algorítmo de insersão em
//Uma árvore AVL
// função pública que recebe uma chave e a insere
// somente se ela não for repetida
/*
A solução é de O(lg n), pois em uma árvore de n nós, ao inserirmos mais um nó
Não precisaremos percorer a árvore toda, somente seu caminho até o local onde
pretendemos inserir o nó, por exemplo, em uma árvore AVL com 16 nós, se quisermos adicionar mais um,
percorreremos no máximo 4 nós.

A verificação atravez da pilha também executa lg n vezes, pois o que é guardado na pilha é somente
os nós no caminho até o nó inserido, que sabemos que são lg n nós.
*/
template <typename T, typename D>
void avl_tree<T,D>::add(T key, D* data){
    root = add(root,key,data);
}
template <typename T, typename D>
Node<T,D>* avl_tree<T,D>::add(Node<T,D> *p, T key, D* data) {
    if(p == nullptr)
        return new Node<T,D>(key,data); 
    if(key < p->key)
        p->left = add(p->left, key,data);
    else if(key > p->key)
        p->right = add(p->right, key,data);
    else{
        if(p->right == nullptr){
            p->right = new Node<T,D>(key,data);
        }else if(p->right!=nullptr){
            p->right = add(p->right,key,data);
        }
    }
    p = fixup_node(p, key);

    return p;
}

//Função que preenche um vetor com os nodes entre o intervalo min e max
template <typename T, typename D>
void avl_tree<T,D>::searchSimilar(Node<T,D>* p, vector<Node<T,D>*> &vec, T min, T max){
    if(p==nullptr || p->key > max || p->key < min){
        return;
    }else{
        vec.push_back(p);
        searchSimilar(p->left,vec,min,max);
        searchSimilar(p->right,vec,min,max);
    }
}

//Busca os nodes com as chaves entre min e max
template <typename T, typename D>
vector<Node<T,D>*> avl_tree<T,D>::search(T min, T max) {
    Node<T,D>* aux = root;
    vector<Node<T,D>*> vec;
    while(aux!=nullptr){
        if(aux->key >= min && aux->key <= max){
            searchSimilar(aux,vec,min,max);
            return vec;
        }else{
            if(min < aux->key){
                aux = aux->left;
            }else{
                aux = aux->right;
            }
        }
    }
    return vec;
    
}




template <typename T, typename D>
Node<T,D>* avl_tree<T,D>::fixup_node(Node<T,D> *p, T key) { //Função que recebe um nó a ser ajustado e seu pai
    // recalcula a altura de p
    p->height = 1 + max(height(p->left),height(p->right));

    // calcula o balanço do p
    int bal = balance(p);

    if(bal >= -1 && bal <= 1) {
        return p;
    }
    if(bal < -1 && key < p->left->key) {
        p = rightRotation(p);
    }
    else if(bal < -1 && key > p->left->key) {
        p->left = leftRotation(p->left);
        p = rightRotation(p);
        
    }
    else if(bal > 1 && key >= p->right->key) {
        p = leftRotation(p);
    }
    else if(bal > 1 && key < p->right->key) {
        p->right = rightRotation(p->right);
        p = leftRotation(p);
    }
    return p;
}

template <typename T, typename D>
void avl_tree<T,D>::clear() {
    root = clear(root);
}

template <typename T, typename D>
Node<T,D> *avl_tree<T,D>::clear(Node<T,D> *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

template <typename T, typename D>
avl_tree<T,D>::~avl_tree() {
    clear();
}

template <typename T, typename D>
void avl_tree<T,D>::bshow() const {
    bshow(root, "");
}

template <typename T, typename D>
void avl_tree<T,D>::bshow(Node<T,D> *node, std::string heranca) const {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << *node->data << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}

template <typename T, typename D>
void avl_tree<T,D>::remove(T key) {
    root = remove(root, key);
}

template <typename T, typename D>
Node<T,D>* avl_tree<T,D>::remove(Node<T,D> *node, T key) {
    if(node == nullptr) // node nao encontrado
        return nullptr; /*L\pauseL*/
    if(key < node->key) 
        node->left = remove(node->left, key);
    else if(key > node->key)
        node->right = remove(node->right, key); /*L\pauseL*/
    // encontramos no node
    else if(node->right == nullptr) { // sem filho direito
        Node<T,D> *child = node->left;
        delete node;
        return child;
    }
    else // tem filho direito: troca pelo sucessor
        node->right = remove_successor(node, node->right); /*L\pauseL*/
    
    // Atualiza a altura do node e regula o node
    node = fixup_deletion(node); 
    return node;
}

template <typename T, typename D>
Node<T,D>* avl_tree<T,D>::remove_successor(Node<T,D> *root, Node<T,D> *node) {
    if(node->left != nullptr)
        node->left = remove_successor(root, node->left);
    else {
        root->key = node->key;
        Node<T,D> *aux = node->right;
        delete node;
        return aux;
    }
    // Atualiza a altura do node e regula o node
    node = fixup_deletion(node);
    return node;
}

template <typename T, typename D>
Node<T,D>* avl_tree<T,D>::fixup_deletion(Node<T,D> *node) {
    node->height = 1 + max(height(node->left),height(node->right));

    int bal = balance(node);

    // node pode estar desregulado, ha 4 casos a considerar
    if(bal > 1 && balance(node->right) >= 0) {
        return leftRotation(node);
    }
    else if(bal > 1 && balance(node->right) < 0) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }
    else if(bal < -1 && balance(node->left) <= 0) {
        return rightRotation(node);
    }
    else if(bal < -1 && balance(node->left) > 0) { 
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    return node;
}

#endif