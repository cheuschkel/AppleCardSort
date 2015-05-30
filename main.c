/**
 * @file   main.c
 * @Author Cory Heuschkel (cory.heuschkel@gmail.com)
 * @date   May 30, 2015
 * @brief  Apple card sorting coding exercise main application.
 *
 * This main file checks for acceptable user inputs and drives the card sorting
 * algorithm.  It prints the number of rounds taken to sort the cards as 
 * described in cards.c.
 * 
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "cards.h"

int main(int argc,  char* argv[])
{
    int32_t number_cards = 0;
    uint32_t number_rounds = 1;

    /* There should only be one arguemnt: number of cards. */
    if(argc != 2)
    {
        printf("usage: <N cards> (where N is 1 - 4294967295)\r\n");
        return 0;
    }

    /* Input must be a signed 32-bit integer. */
    if(sscanf(argv[1], "%ld", &number_cards) != 1) 
    { 
        printf("error - not an integer"); 
        return 0;
    }

    /* User must input at least 2 cards. */
    if(number_cards < 1 || number_cards > 0x7FFFFFFF)
    {
        printf("usage: <N cards> (where N is 1 - 2147483647)\r\n");
        return 0;
    }

    /* Create deck. */
    cards_Init((uint32_t)number_cards);
    
    /* Run sorting algorithm and measure number of rounds taken. */
    while(!cards_OneRound())
    {
        number_rounds++;
    }

    printf("Number of rounds: %lu\r\n", number_rounds);

    return 0;
}