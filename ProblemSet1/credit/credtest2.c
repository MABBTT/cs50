#include <cs50.h>
#include <stdio.h>

int digit(long number);
long remdigit(long num);

int main(void) 
{
   long n = 4003600000000014;
   long n0 = (n);
   long n1 = remdigit(n0);
   long n2 = remdigit(n1);
   long n3 = remdigit(n2);
   long n4 = remdigit(n3);
   long n5 = remdigit(n4);
   long n6 = remdigit(n5);
   long n7 = remdigit(n6);
   long n8 = remdigit(n7);
   long n9 = remdigit(n8);
   long n10 = remdigit(n9);
   long n11 = remdigit(n10);
   long n12 = remdigit(n11);
   long n13 = remdigit(n12);
   long n14 = remdigit(n13);
   long n15 = remdigit(n14);
   long n16 = remdigit(n15);

   int d0 = digit(n0);
   int d1 = digit(n1);
   int d2 = digit(n2);
   int d3 = digit(n3);
   int d4 = digit(n4);
   int d5 = digit(n5);
   int d6 = digit(n6);
   int d7 = digit(n7);
   int d8 = digit(n8);
   int d9 = digit(n9);
   int d10 = digit(n10);
   int d11 = digit(n11);
   int d12 = digit(n12);
   int d13 = digit(n13);
   int d14 = digit(n14);
   int d15 = digit(n15);
   int d16 = digit(n16);
   
   
//   for (int j = 0; j < 16; j++)
//   {
//      for (int m = 
//      long k = n / 10;
//      int i = digit(k);
//      if ((j % 2) == 0)
//      {
//         printf("%i\n", i);
//      }
//   } 
   printf("%i\n%i\n", d0 , d1);
}

int digit(long number)
{
   return number % 10; 
}

long remdigit(long num)
{
   return (num / 10) - (digit(num) / 10); 
}
