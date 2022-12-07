#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>


int count_letters(string text, int l);
int count_words(string text, int l);
int count_sentences (string text, int l);

int main(void)
{
   string text = get_string("Text: ");
   //printf("%s\n", text);
   int l = strlen(text);
   int let = count_letters(text, l);
   int wor = count_words(text, l);
   int sen = count_sentences(text, l);
   //printf("%i letters\n%i words\n%i sentences\n", let, wor, sen);
   double cl = (0.0588 * ((double)let / ((double)wor/100)) - 0.296 * ((double)sen / ((double)wor/100)) - 15.8);
   //printf("%f\n", cl);
   int grade = (int) round(cl);
   if (grade >= 1 && grade <=16)
   {
      printf("Grade %i\n", grade);
   }
   else if (grade <1)
   {
      printf("Before Grade 1\n");
   }
   else
   {
      printf("Grade 16+\n");
   }
}

int count_letters(string text, int l)
{
   int letters = 0;
   for (int i = 0; i <= l; i++)
   {
      if isalpha(text[i])
      {
         letters++;
      }
   }
   return letters;
}

int count_words(string text, int l)
{
   int words = 1;
   for (int i = 0; i <= l; i++)
   {
      if isblank(text[i])
      {
         words++;
      }
   }
   return words;
}

int count_sentences(string text, int l)
{
   int sentences = 0;
   for (int i = 0; i <= l; i++)
   {
      if (text[i] == '.' || text[i] == '!' || text[i] == '?')
      {
         sentences++;
      }
   }
   return sentences;
}
