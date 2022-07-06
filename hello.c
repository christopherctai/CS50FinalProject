#include <stdio.h>
#include <cs50.h>

int main(void)

{
    //ask for name
    string name = get_string("What's your name? ");

    //print hello, name
    printf("hello, %s\n", name);
}