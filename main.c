#include <stdint.h>
#include <stdio.h>
#include "cards.h"

int main(int argc,  char* argv[])
{
	uint32_t number_cards = 0;

	if(argc != 2)
	{
		printf("usage: <N cards>\r\n");
		return 0;
	}

	if(sscanf(argv[1], "%u", &number_cards) != 1) 
	{ 
		printf("error - not an integer"); 
		return 0;
	}

	cards_Init(number_cards);

	return 0;
}