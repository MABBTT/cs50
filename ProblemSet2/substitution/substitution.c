#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
   //validation and get plain text
   string key = argv[1];
   int testkey[26] = {0};
   if (argc != 2)
   {
      printf("You screwed up dummy, provide one and only one argument\n");
      return 1;
   }
   else if (strlen(key) != 26)
   {
      printf("Invalid key, must be 26 characters and include all alphabetical characters\n");
      return 1;
   }
   else
   {
      for (int i = 0; i < 26; i++)
      {
         if (isalpha(key[i]) == 0)
         {
            printf("Invalid key, all characters must be alphabetical characters\n");
            return 1;
         }
         testkey[tolower(key[i]) - 97] += 1;
      }
      for (int i = 0; i < 26; i++)
      {
         if (testkey[i] > 1)
         {
            printf("Invalid key, no duplicate characters\n");
            return 1;
         }
      }
   }
   string plaintext = get_string("plaintext: ");
   int sl = strlen(plaintext);
   int keylow[26] = {0};
   for (int i = 0; i < 26; i++)
   {
      keylow[i] = (tolower(key[i]));
   }
   //format plaintext
   char cyphertext[30] = {0};
   for (int i = 0; i <= sl; i++)
   {
      if (isalpha(plaintext[i]))
      {
         if (islower(plaintext[i]))
         {
            cyphertext[i] = keylow[plaintext[i] - 97];
         }
         else
         {
            cyphertext[i] = toupper(keylow[tolower(plaintext[i]) - 97]);
         }
      }
      else
      {
         cyphertext[i] = plaintext[i];
      }
   }
   printf("ciphertext: %s\n", cyphertext);
   return 0;
}
