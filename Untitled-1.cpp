//create a function that asks the user for a number and prints the multiplication table for that number

#include <iostream>
using namespace std;

void multiplication_table(int num)
{
    for (int i = 1; i <= 20; i++)
    {
        cout << num << " * " << i << " = " << num * i << endl;
    }
}

int main()
{
    int num;
    cout << "Enter a number: ";
    cin >> num;
    multiplication_table(num);
    return 0;
}