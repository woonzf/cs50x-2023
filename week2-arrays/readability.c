#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Count letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Coleman-Liau index
    float l = letters / ((float) words / 100);
    float s = sentences / ((float) words / 100);
    float cli = round(0.0588 * l - 0.296 * s - 15.8);

    // Print "Grade X"
    if (cli < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (cli >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) cli);
    }

    return 0;
}

int count_letters(string text)
{
    int letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Count uppercase and lowercase
        if (text[i] >= 'A' && text[i] <= 'z')
        {
            letters++;
        }
    }

    return letters;
}

int count_words(string text)
{
    int count = 0;
    int words = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Tolerate multiple spaces before first char
        if (text[i] != ' ')
        {
            count = 1;
        }

        // Count space after first char
        if (text[i] == ' ' && count == 1)
        {
            words++;
        }
    }

    words++;
    return words;

    // Optional
    // Tolerate multiple spaces between words or indeed, no words!
    // Force first and last character to be non ' ' and count the number of series of ' '?
}

int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Count .?! as sentence
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }

    return sentences;
}