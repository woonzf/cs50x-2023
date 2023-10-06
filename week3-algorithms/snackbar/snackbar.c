// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    string item;
    string itemu;
    float price;
}
menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(string item);

// Uppercase the string
string uppercase(string input);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i]. price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first four items to the menu array
void add_items(void)
{
    menu[0].item = "BURGER";
    menu[0].price = 9.5;

    menu[1].item = "VEGAN BURGER";
    menu[1].price = 11;

    menu[2].item = "HOT DOG";
    menu[2].price = 5;

    menu[3].item = "CHEESE DOG";
    menu[3].price = 7;

    menu[4].item = "FRIES";
    menu[4].price = 5;

    menu[5].item = "CHEESE FRIES";
    menu[5].price = 6;

    menu[6].item = "COLD PRESSED JUICE";
    menu[6].price = 7;

    menu[7].item = "COLD BREW";
    menu[7].price = 3;

    menu[8].item = "WATER";
    menu[8].price = 2;

    menu[9].item = "SODA";
    menu[9].price = 2;

    return;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    item = uppercase(item);
    float cost;

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (strcmp(item, menu[i].item) == 0)
            cost = menu[i].price;
    }

    return cost;
}

string uppercase(string input)
{
    for (int i = 0, len = strlen(input); i < len; i++)
    {
        input[i] = toupper(input[i]);
    }

    return input;
}