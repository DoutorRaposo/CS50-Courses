#include <cs50.h>
#include <stdio.h>

bool triangle_check(int a, int b, int c);

int main(void)
{
    int x, y, z;
    x = get_int("Give side x of the triangle: ");
    y = get_int("Give side y of the triangle: ");
    z = get_int("Give side z of the triangle: ");

    if(triangle_check(x, y, z))
    {
        printf("This triangle is possible\n");
    }
    else
    {
        printf("This triangle is impossible\n");
    }
}

bool triangle_check(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <=0)
    {
        return false;
    }

    if(a + b <= c || b + c <= a || a + c <= b)
    {
        return false;
    }

    return true;
}