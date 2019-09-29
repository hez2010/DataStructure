#pragma once
#include "error_code.hpp"
#include "node.hpp"

template <typename T>
class Stack
{
private:
    Node<T> *current = nullptr;
    int count = 0;
    int max_size = 0;

    Node<T> *copy_stack(Node<T> *node, Stack<T> *result)
    {
        if (node == nullptr)
            return nullptr;

        Node<T> *next = copy_stack(node->next, result);
        result->current = new Node<T>();
        result->current->item = node->item;
        result->current->next = next;
        return result->current;
    }

public:
    inline ErrorCode top(T &item)
    {
        if (count == 0 || current == nullptr)
            return Underflow;

        item = current->item;
        return Success;
    }

    inline ErrorCode pop(T &item)
    {
        if (count == 0 || current == nullptr)
            return Underflow;

        item = current->item;

        Node<T> *last = current->next;
        delete current;
        current = last;

        count--;
        return Success;
    }

    inline ErrorCode pop()
    {
        T item;
        pop(item);

        return Success;
    }

    inline ErrorCode push(T item)
    {
        if (max_size != 0 && count >= max_size)
            return Overflow;
            
        Node<T> *node = new Node<T>();
        node->item = item;
        node->next = current;

        current = node;

        count++;
        return Success;
    }

    inline int size()
    {
        return count;
    }

    Stack<T> &operator=(const Stack<T> &stack)
    {
        return new Stack<T>(stack);
    }

    Stack(const Stack<T> &stack)
    {
        if (stack.count <= 0)
            return;

        copy_stack(stack.current, this);
        this->count = stack.count;
        this->max_size = stack.max_size;
    }

    Stack() {}
    Stack(int max_size) : max_size(max_size) {}
    ~Stack()
    {
        T item;
        while (pop(item) == Success)
            ;
    }
};