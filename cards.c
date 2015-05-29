#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct card
{
	uint32_t		card_number;
	struct card *	next_card;
};

typedef struct card Card;

Card * FirstCard;
Card * LastCard;

static uint32_t NumberCards = 0;

/**
 *  Adds a card to the deck.  
 *  @param card_number The card number of the appended card.
 */
static void add_card(uint32_t card_number)
{
	Card * current_card = FirstCard;
	Card * last_card = NULL;

	while(current_card->next_card != LastCard)
	{
		current_card = current_card->next_card;
	}
	last_card = malloc(sizeof(Card));
	last_card->card_number = card_number;
	last_card->next_card = LastCard;
	current_card->next_card = last_card;
}

/**
 *  Initializes the deck.  
 *  @details Creates a linked list of cards.
 *  @param number The number of cards in the deck.
 */
void cards_Init(uint32_t number)
{
	uint32_t i;

	NumberCards = number;           
	FirstCard = malloc(sizeof(Card));
	LastCard = malloc(sizeof(Card));
	
	FirstCard->next_card = LastCard;
	LastCard->next_card = LastCard;
	
	FirstCard->card_number = 0;
	LastCard->card_number = 0;
	
	for(i = 1; i < NumberCards; i++)
	{
		add_card(i);
	}
}
