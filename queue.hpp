#pragma once
#include "error_code.hpp"
#include "node.hpp"

template <typename T>
class Queue
{
private:
    Node<T> *current = nullptr;
    Node<T> *last = nullptr;
    int count = 0;
    int max_size = 0;

    inline void copy_queue(Node<T> *node, Queue<T> *result)
    {
        if (node == nullptr)
            return;

        Node<T> *last = nullptr;
        Node<T>* root = result->current = new Node<T>();
        while (node != nullptr)
        {
            result->current->next = last = new Node<T>();
            result->current->next->item = new T(*node->item);
            result->current = result->current->next;
            node = node->next;
        }

        result->last = last;

        result->current = root->next;
        delete root;
        
        return;
    }

    inline void place_node(Node<T> *node)
    {
        if (current == nullptr)
        {
            current = node;
        }
        else if (last == nullptr)
        {
            last = node;
            current->next = last;
        }
        else
        {
            last->next = node;
            last = node;
        }
    }

public:
    inline ErrorCode front(T &item)
    {
        if (count == 0 || current == nullptr)
            return Underflow;

        item = *current->item;
        return Success;
    }

    inline ErrorCode dequeue(T &item)
    {
        if (count == 0 || current == nullptr)
            return Underflow;

        item = *current->item;

        Node<T> *last = current->next;
        delete current;
        current = last;

        count--;
        return Success;
    }

    inline ErrorCode enqueue(T item)
    {
        if (max_size != 0 && count >= max_size)
            return Overflow;

        T *copy = new T(item);

        Node<T> *node = new Node<T>();
        node->item = copy;

        place_node(node);

        count++;
        return Success;
    }

    inline ErrorCode enqueue(T *item)
    {
        if (max_size != 0 && count >= max_size)
            return Overflow;

        Node<T> *node = new Node<T>();
        node->item = item;

        place_node(node);

        count++;
        return Success;
    }

    inline int size()
    {
        return count;
    }

    Queue<T> &operator=(const Queue<T> &queue)
    {
        return new Queue<T>(queue);
    }

    Queue(const Queue<T> &queue)
    {
        if (queue.count <= 0)
            return;

        copy_queue(queue.current, this);
        this->count = queue.count;
        this->max_size = queue.max_size;
    }

    Queue() {}
    Queue(int max_size) : max_size(max_size) {}
    ~Queue()
    {
        T item;
        while (dequeue(item) == Success)
            ;
    }
};