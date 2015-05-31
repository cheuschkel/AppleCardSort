# AppleCardSort
Apple card sorting exercise.

Summary
-------

This exercise calls to set up a deck of N cards in sequential order and perform
"rounds" of sorting until the deck is original order.

A "round" of sorting the deck works as follows:
  1. Take the top card and put it on a table.
  2. Take the next card and put it at the bottom of the hand stack.
  3. Take the next card and put it on top of the table stack.
  4. Repeat steps 2-3 until all cards are on the table.
 
After each round, the deck is checked to see if it is in original order.

Building
--------

To build, run `make` in a Unix shell with **make** support at the root 
directory.

`make clean` and `make rebuild` are also implemented.

To build with additional debug info containing the card links between rounds, 
enter the following command:
	
	make debug

Running
-------

To run, enter a number to determine the number of rounds the sort algorithm will 
run to get the original deck order.

	./cards.exe <N cards>
