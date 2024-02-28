#include <cs50.h>
#include <stdio.h>

//If you're reading this, I'm sorry. I finished college 8 years ago, in humanities, and english is not my native language, so bear with me while I try to brute force this code. The other problems on the set I did graceful code, but this is not how this is going to be.

int main(void)
{
//First, I will assume max digits from credit card is 16, so I will create an integer for each.

    int digit1;
    int digit2;
    int digit3;
    int digit4;
    int digit5;
    int digit6;
    int digit7;
    int digit8;
    int digit9;
    int digit10;
    int digit11;
    int digit12;
    int digit13;
    int digit14;
    int digit15;
    int digit16;

//Then, I will prompt user with the number. I will use long because the number can be higher than 2bi.

    long creditcard;
    do
    {

        creditcard = get_long("Insert your credit card number: ");
    }
    while (creditcard < 0); //Must be positive, I guess.

//So to eliminate one number from right to left we have to divide by 10, two number divide by 100, and so on (thanks for the modulo tip). To get last digit, we have to get the remainder of a division by 10, last two digits by 100, an so on. Combining the two we can isolate each of the numbers.
//For now, I will get the first set of numbers of the problem (every other multiply by 2). And, for safety, if the number ends up with two digits, I will sum the two. Worst case cenario it does not have a second digit, so it will be summed to 0 and it's all good.

    digit2 = ((creditcard % 100) / 10) * 2;
    digit2 = ((digit2 % 100) / 10) + (digit2 % 10);
    digit4 = ((creditcard % 10000) / 1000) * 2;
    digit4 = ((digit4 % 100) / 10) + (digit4 % 10);
    digit6 = ((creditcard % 1000000) / 100000) * 2;
    digit6 = ((digit6 % 100) / 10) + (digit6 % 10);
    digit8 = ((creditcard % 100000000) / 10000000) * 2;
    digit8 = ((digit8 % 100) / 10) + (digit8 % 10);
    digit10 = ((creditcard % 10000000000) / 1000000000) * 2;
    digit10 = ((digit10 % 100) / 10) + (digit10 % 10);
    digit12 = ((creditcard % 1000000000000) / 100000000000) * 2;
    digit12 = ((digit12 % 100) / 10) + (digit12 % 10);
    digit14 = ((creditcard % 100000000000000) / 10000000000000) * 2;
    digit14 = ((digit14 % 100) / 10) + (digit14 % 10);
    digit16 = ((creditcard % 10000000000000000) / 1000000000000000) * 2;
    digit16 = ((digit16 % 100) / 10) + (digit16 % 10);

    //After learning debug I used this to check with the example from the problem's description. Best ideia is to sum all. 4003600000000014 gives 13.
    //int sumeo;
    //sumeo = digit2 + digit4 + digit6 + digit8 + digit10 + digit12 + digit14 + digit16;

//Now that we have the sum of every other digit multiplied by two, we will have to get the sum of the remaining digits. Since we don't have to multiply by 2, we will not need the second operation I did earlier.

    digit1 = ((creditcard % 10) / 1);
    digit3 = ((creditcard % 1000) / 100);
    digit5 = ((creditcard % 100000) / 10000);
    digit7 = ((creditcard % 10000000) / 1000000);
    digit9 = ((creditcard % 1000000000) / 100000000);
    digit11 = ((creditcard % 100000000000) / 10000000000);
    digit13 = ((creditcard % 10000000000000) / 1000000000000);
    digit15 = ((creditcard % 1000000000000000) / 100000000000000);

    int sumtotal;
    sumtotal =  digit1 + digit2 + digit3 + digit4 + digit5 + digit6 + digit7 + digit8 + digit9 + digit10 + digit11 + digit12 + digit13 +
                digit14 + digit15 + digit16;

    //Ok, so now just get the remainder!!!

    sumtotal = sumtotal % 10;


    //Ok, now we will get "if" statements for each of the possibilites. First I will give invalid if it is not zero. I will create a second long (duplicate) because a I'm a newbie and I don't know how else to not lose the original value of the credit card number.

    int invalidation = 0;
    if (sumtotal != 0)
    {
        printf("INVALID\n");
        //Just learned that THIS ends the file
        return 0;
    }

    long creditcard2 = creditcard;
    int totaldigits = 0;
    while (creditcard2 > 0)
    {
        creditcard2 = creditcard2 / 10;
        totaldigits++;
    }
    //Now we will make a total logic mess, but basically if it has 16 digits, I will check if the first it is Mastercard (51 to 55). If it's not, I will check AGAIN if it's in the 40s range.
    if (totaldigits == 16)
    {
        int fdcheck = creditcard / 100000000000000;
        if (fdcheck == 51 || fdcheck == 52 || fdcheck == 53 || fdcheck == 54 || fdcheck == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (fdcheck > 39 && fdcheck < 50)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //Ok, now if the card number is valid, have 16 digits and starts with 51 to 55 is Master. If it starts with 4 is Visa. Else, is not valid. Now, for the case of 15 digits:
    if (totaldigits == 15)
    {
        int fdcheck = creditcard / 10000000000000;
        if (fdcheck == 34 || fdcheck == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //Now, if the credit card number is valid, have 15 digits but does not begin with 34 and 37, it is invalid. If it does, it is AMEX. For our final case, if it have 13 digits.
    if (totaldigits == 13)
    {
        int fdcheck = creditcard / 1000000000000;
        if (fdcheck == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //Just to be sure, I'm gonna invalid all the other digits possibilities.
    if ((totaldigits == 14 || totaldigits < 13))
    {
        printf("INVALID\n");
    }
}