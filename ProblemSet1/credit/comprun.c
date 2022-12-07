#include <cs50.h>
#include <stdio.h>
//testing make files
int digit(long number);
long remdigit(long num);

int main(void)
{
   long n = get_long("Number: ");
   int totaldigits = 0;
   int nonmultiplieddigits = 0;
   int multiplieddigits = 0;
   long d1 = n;
   long d2 = n;
// count total digits
   for (long i = 1; i <= n; i = i * 10)
   {
      totaldigits++;
   }
// Get first digit
   for (int p = 1; p < totaldigits; p++)
   {
      d1 = remdigit(d1);
   }
// Get first two digits
   for (int p = 1; p < (totaldigits - 1); p++)
   {
      d2 = remdigit(d2);
   }
//Luhn's Algo
   for (int j = 1; j <= totaldigits; j++)
   {
      if (j % 2 == 0)
      {
         int k = digit(n) * 2;
         if (k >= 10)
         {
            int g = digit(k);
            int f = digit(remdigit(k));
            multiplieddigits = multiplieddigits + g + f;
         }
         else 
         {
            int u = digit(k);
            multiplieddigits = multiplieddigits + u;
         }
      }
      else
      {
         nonmultiplieddigits = nonmultiplieddigits + digit(n);
      }
      n = remdigit(n);
   }
   int m = nonmultiplieddigits + multiplieddigits;
//Luhn's validation and print card type
    if (m % 10 == 0)
   {
      if (d1 == 4 && (totaldigits == 13 || totaldigits == 16))
      {
         printf("VISA\n");
      }
      else if ((d2 == 34 || d2 == 37) && totaldigits == 15)
      {
         printf("AMEX\n");
      }
      else if ((d2 == 51 || d2 == 52 || d2 == 53 || d2 == 54 || d2 == 55) && totaldigits == 16)
      {
         printf("MASTERCARD\n");
      }
      else
      {
         printf("INVALID\n");
      }
   }
   else 
   {
      printf("INVALID\n");
   }
}

int digit(long number)
{
   return number % 10; 
}

long remdigit(long num)
{
   return (num / 10) - (digit(num) / 10); 
}
