#pragma once
#include "Node.hpp"
#include <cstddef>
#include <memory>
#include <iostream>

/**
 * @author Gerardo David Ortega López
 * @version 1.0
 * @since v1.0
 * @see Node
 */
template<typename T> class CircularList{

    public:

    /**
     * Inserta un elemento al inicio de la lista.
     * @param data El dato que se va a insertar y su tipo.
     */
    void insertFirst(T data){

        auto node = std::make_unique<Node<T>>(std::move(data));

        node->next = std::move(head);

        if (node->next) node->next->prev = node.get();
        
        head = std::move(node);
        
        if (tail == nullptr) tail = head.get();
        

        size_++;
    }

    /**
     * Inserta un elemento al final de la lista.
     * @param data El dato que se va a insertar y su tipo.
     */
    void insertLast(T data){
        
        auto node = std::make_unique<Node<T>>(std::move(data));

        if (!head){

            head = std::move(node);
            tail = head.get();

        }else{

            node->prev = tail;
            tail->next = std::move(node);
            tail = tail->next.get();
        }

        size_++;
    }

    /**
     * Inserta un elemento despues de un nodo dado.
     * @param previous Nodo previo de referencia.
     * @param data El dato que se va a insertar y su tipo.
     */
    void insertAfter(Node<T>* previous, T data){

        if (!previous) return;

        if (previous == tail){

            insertLast(std::move(data));
            return;
        }

        auto node = std::make_unique<Node<T>>(std::move(data));

        node->next = std::move(previous->next);

        if (node->next){

            node->next->prev = node.get();
        }

        node->prev = previous;
        previous->next = std::move(node);

        size_++;
    }

    /**
     * Obtiene el ultimo nodo de la lista.
     * @return Puntero al ultimo nodo y su tipo.
     */
    Node<T>* getLast(){

        return tail;
    }

    /**
     * Obtiene el primer nodo de la lista.
     * @return Puntero al primer nodo y su tipo.
     */
    Node<T>* getFirst(){

        return head.get();
    }

    /**
     * Busca un elemento en la lista.
     * @param data Dato a buscar y su tipo.
     * @return Puntero al nodo encontrado o nulo si no existe.
     */
    Node<T>* search(const T& data){

        auto curr = head.get();
        
        while (curr != nullptr){

            if (curr->data == data) return curr;

            curr = curr->next.get();
        }

        return nullptr;
    }

    /**
     * Obtiene el nodo en una posicion especifica.
     * @param position Posicion del nodo.
     * @return Puntero al nodo en esa posicion.
     */
    Node<T>* get(std::size_t position){

        if (position >= size_) return nullptr;
        
        if (position < size_ / 2){

            auto curr = head.get();

            for (std::size_t x = 0; x < position; x ++){

                curr = curr->next.get();
            }

            return curr;

        }else{

            auto curr = tail;

            for (std::size_t x = size_ - 1; x > position; x --){

                curr = curr->prev;
            }

            return curr;
        }
    }

    /**
     * Elimina un nodo que contenga el dato especificado.
     * @param data Dato del nodo a eliminar y su tipo.
     * @return Verdadero si se elimino, falso en caso contrario.
     */
    bool deleteNode(const T& data){

        if (!head) return false;

        auto curr = head.get();

        while (curr != nullptr){

            if (curr->data == data){

                if (curr == head.get()){

                    head = std::move(head->next);

                    if (head){

                        head->prev = nullptr;

                    }else{

                        tail = nullptr;
                    }

                }else{

                    curr->prev->next = std::move(curr->next);

                    if (curr->prev->next){

                        curr->prev->next->prev = curr->prev;

                    }else{

                        tail = curr->prev;
                    }
                }

                size_--;
                return true;
            }

            curr = curr->next.get();
        }

        return false;
    }

    /**
     * Comprueba si la lista esta vacia.
     * @return Verdadero si esta vacia, falso si tiene elementos.
     */
    bool isEmpty() const{

        return size_ == 0;
    }

    /**
     * Elimina todos los elementos de la lista.
     */
    void deleteList(){

        head.reset();
        tail = nullptr;
        size_ = 0;
    }

    /**
     * Imprime los elementos de la lista.
     */
    void print() const{

        auto curr = head.get();

        while (curr != nullptr){

            std::cout << curr->data << "\n";
            curr = curr->next.get();
        }
    }

    /**
     * Imprime los elementos de la lista en orden inverso.
     */
    void printReverse() const{

        auto curr = tail;

        while (curr != nullptr){

            std::cout << curr->data << "\n";
            curr = curr->prev;
        }
    }

    /**
     * Obtiene el tamaño actual de la lista.
     * @return Numero de elementos en la lista y su tipo.
     */
    std::size_t size() const{

        return size_;
    }

    private:

    std::unique_ptr<Node<T>> head{};
    Node<T>* tail{nullptr};
    std::size_t size_{};
};