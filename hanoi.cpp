#include <iostream>
using namespace std;

void hanoi_move(int number, char a, char b, char c)
{
    if (number == 1)
    {
        printf("%c --> %c\n", a, c);
        return;
    }

    hanoi_move(number - 1, a, c, b);
    printf("%c --> %c\n", a, c);
    hanoi_move(number - 1, b, a, c);

}

int main()
{
    hanoi_move(10, 'A', 'B', 'C');
}