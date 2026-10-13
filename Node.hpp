#pragma once
#include <memory>
#include <utility>
/*
*Esta clase representa un nodo te tipo arbitrario T que es utilizado para implementar una lista 
*doblemente enlazada.
*@see DoubleList.hpp
@author Yahir Enriquez
@version 1.0
@since 1.0
*/

template<typename T> class Node{

    public:
/*
*El constructor para generar un nodo con un dato previamente declarado
*@param data T el  dato que va a almacenar el nodo
*debido a la manera en que funciona std::move(), la fuente de datos original que se use
*para inicializar el nodo va a volverse invalida
*/
    explicit Node(T data)
        : 
        data(std::move(data)), next(nullptr), prev(nullptr)
        {}
/*
**El constructor para generar un nodo que apunta a otro
*debido a la manera en que funciona std::move(), la fuente de datos original que se use
*para inicializar el nodo va a volverse invalida.
*el nodo next siempre va a transferir el ownership de su puntero a este nodo, por lo que se
*debe garantizar que este no sea utilizado por otro objeto
*@param data T el  dato que va a almacenar el nodo
*@paramstd::unique_ptr<Node<T>> next el puntero unico al nodo siguiente al que apunta este nodo
*/
    Node(T data, std::unique_ptr<Node<T>> next)
        : 
        data(std::move(data)), next(std::move(next)){

        if (this->next){

            this->next->prev = this;
        }
    }
/*
*Regresa la data contenida en el nodo
@return T& una referencia modificable hacia la data que contiene el nodo
@version 1.0
@since 1.0
*/
    T& getData(){

        return data;
    }
/*
*Modifica la data interna contenida por el nodo
@param d T la nueva data que va a contener el nodo
@version 1.0
@since 1.0
*data debe ser del mismo tipo con el que se creo el nodo originalmente
*data sera movida por lo cual la fuente original de la misma se volvera invalida
*/
    void setData(T d){

        data = std::move(d);
    }
/*
*Regresa un puntero modificable y non-owning a next
@return Node<T>*
@version 1.0
@since 1.0
*/
    Node<T>* getNext(){

        return next.get();
    }
/*
*Regresa un no modificable y non-owning a next
@return const Node<T>*
@version 1.0
@since 1.0
*/
    const Node<T>* getNext() const{

        return next.get();
    }
/*
*Regresa un puntero modificable y non-owning hacia prev
@return Node<T>*
@version 1.0
@since 1.0
*/
    Node<T>* getPrev(){

        return prev;
    }
/*
*Regresa un puntero no modificable y non-owning hacia prev
@return Node<T>*
@version 1.0
@since 1.0
*/
    const Node<T>* getPrev() const{

        return prev;
    }
/*
*Transfiere el ownership del puntero de otro nodo a next
@author Yahir Enriquez
@param next_ std::unique_ptr<Node<T>> el nodo siguiente
@version 1.0
@since 1.0
*/

    void setNext(std::unique_ptr<Node<T>> next_){

        next = std::move(next_);

        if (next){

            next->prev = this;
        }
    }

    private:

    T data{};
    std::unique_ptr<Node<T>> next{};
    Node<T>* prev{nullptr};

    template<typename> friend class List;
};