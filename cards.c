/**
 * @file   cards.c
 * @Author Cory Heuschkel (cory.heuschkel@gmail.com)
 * @date   May 30, 2015
 * @brief  Apple card sorting coding exercise module.
 *
 * The functions in this file set up a deck of N cards in sequential order
 * and performs a "round" of sorting per Apple's exercise requirements.
 *
 * A "round" of sorting the deck works as follows:
 *        1. Take the top card and put it on a table.
 *        2. Take the next card and put it at the bottom of the hand stack.
 *        3. Take the next card and put it on top of the table stack.
 *        4. Repeat steps 2-3 until all cards are on the table.
 * 
 * After each round, the deck is checked to see if it is in original order.
 *
 * The style I chose to use was a circular linked list with seperate lists
 * for the table and hand stacks.  This is obviously not the quickest method
 * but it has predictable behavior and models well the true human action of 
 * sorting and verifying.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Action taken for the current card in hand.
 */
typedef enum
{
    PUT_ON_TABLE,
    PUT_AT_DECK_BOTTOM,
} DRAW_STATE_E;

/**
 * Stores information for each card and their link to the next card.
 */
struct card
{
    uint32_t        card_number;            /**< Card number. */
    struct card *    next_card;             /**< Next card (hand or table). */
    struct card *    next_card_orig_deck;   /**< Next card in original hand. */
};

typedef struct card Card;

Card * OrigFirstCard;   /**< Top of the starting deck. */
Card * FirstCard;       /**< Top of the deck between rounds. */
Card * LastCard;        /**< Bottom of the deck between rounds. */

static uint32_t NumberCards = 0;

/**
 * Check if cards are sorted in original order.
 * @return True if cards have been sorted this round, false otherwise.
 */
static int are_cards_sorted()
{
    Card * current_card = FirstCard;
    bool are_cards_sorted = false;

    /* Cards can only be in order if the top of the deck is the first card. */
    if(OrigFirstCard != FirstCard)
    {
        return false;
    }
    
    /* Check if subsequent cards are in order. */
    while (current_card->next_card != FirstCard)
    {
        if(current_card->next_card_orig_deck != current_card->next_card)
        {
            return false;
        }
        
        current_card = current_card->next_card;
    }

    /* Cards are in original order. */
    return true;
}

/**
 * Prints card order between rounds.
 */
static void print_card_order()
{
    Card * card = FirstCard;
    while(card->next_card != FirstCard)
    {
        printf("Card %u->", card->card_number);
        card = card->next_card;
    }
    
    printf("Card %u\r\n", card->card_number);
}


/** 
 * Performs a round of "shuffling" and checks for original order.
 * @details "Shuffling" is alternating between putting a card on the table
 *          and on bottom of deck until all cards are on table.
 * @return True if cards are in the original order, false otherwise.
 */
bool cards_OneRound(void)
{
    Card * current_card = FirstCard;
    Card * table_stack_top = FirstCard;     /** First card goes on table. */
    Card * table_stack_bottom = FirstCard;  /** First is bottom of table stack. */
    Card * hand_bottom = LastCard;          /** Bottom of hand is the last card. */
    bool cards_are_sorted = false;
    DRAW_STATE_E draw_state = PUT_ON_TABLE;

    /* Run loop until no cards left in hand. */
    while (current_card->next_card != current_card)
    {
        switch (draw_state)
        {
            case PUT_ON_TABLE:
            {
                /* Fetch next card. */
                Card * next_card = current_card->next_card;

                /* Put card on table stack. */
                hand_bottom->next_card = current_card->next_card;
                current_card->next_card = table_stack_top;
                table_stack_top = current_card;

                /* Pick up next card and change state. */
                current_card = next_card;
                draw_state = PUT_AT_DECK_BOTTOM;
                break;
            }
            case PUT_AT_DECK_BOTTOM:
                /* Put card at bottom of stack in hand. */
                hand_bottom->next_card = current_card;
                hand_bottom = current_card;
                
                /* Pick up next card and change state. */
                current_card = current_card->next_card;
                draw_state = PUT_ON_TABLE;
                break;
            default:
                /* Should never occur. */
                break;
        }
    }

    /* Put last card on top of deck on table. */
    current_card->next_card = table_stack_top;
    table_stack_top = current_card;

    /* Set first and last cards. */
    LastCard = table_stack_bottom;
    table_stack_bottom->next_card = table_stack_top;
    FirstCard = table_stack_top;

    /* Check if cards are sorted. */
    cards_are_sorted = are_cards_sorted();

#if defined CARDS_DEBUG
    /* Print card order */
    print_card_order();
#endif

    return cards_are_sorted;
}

/**
 * Adds a card to the deck.  
 * @param card_number The card number of the appended card.
 * @param last_card Current card at the bottom of the deck.
 * @return Pointer to the card added to the bottom of the deck.
 */
static Card * add_card(uint32_t card_number, Card * last_card)
{
    Card * new_card = NULL;

    new_card = malloc(sizeof(Card));
    last_card->next_card_orig_deck = new_card;
    last_card->next_card = new_card;
    new_card->next_card_orig_deck = new_card;
    new_card->next_card = FirstCard;
    new_card->card_number = card_number;

    return new_card;
}

/**
 * Initializes the deck based on N cards.  
 * @details Creates a circular linked list of cards.
 * @param number The number of cards in the deck.
 */
void cards_Init(uint32_t number)
{
    uint32_t i;
    Card * last_card;

    NumberCards = number;           
    FirstCard = malloc(sizeof(Card));
    
    /* Initialize first card. */
    FirstCard->card_number = 1; /* One-indexed cards (easier for testing). */
    FirstCard->next_card_orig_deck = FirstCard;
    FirstCard->next_card = FirstCard;
    OrigFirstCard = FirstCard;
    last_card = FirstCard;
    
    /* Add all other cards. */
    for(i = 2; i < NumberCards + 1; i++)
    {
        last_card = add_card(i, last_card);
    }
    
    /* Set last card. */
    LastCard = last_card;
}
