#include <iostream>
#include "queue.hpp"
#include "stack.hpp"

int main()
{
    Stack<int> stack(5);

    for (int i = 0; i < 10; i++)
        stack.push(i);

    Stack<int> stack2 = stack;
    stack.pop();
    stack2.push(12345);

    ErrorCode result;
    do
    {
        int item;
        result = stack.pop(item);
        if (result == Success)
            printf("%d ", item);

    } while (result == Success);

    do
    {
        int item;
        result = stack2.pop(item);
        if (result == Success)
            printf("%d ", item);

    } while (result == Success);

    Queue<int> queue;
    for (int i = 0; i < 10; i++)
        queue.enqueue(i);
    
    Queue<int> queue2 = queue;
    do
    {
        int item;
        result = queue2.dequeue(item);
        if (result == Success)
            printf("%d ", item);

    } while (result == Success);

    return 0;
}