#include "pyramid.hpp"

#include <iostream>
#include <stdlib.h>
#include <time.h>

/*+- Card Representation -+
  |      -1   : -         |
  |      1    : Ace       |
  |      2-10 : 2-10      |
  |      11   : Jack      |
  |      12   : Queen     |
  |      13   : King      |
  +-----------------------+*/
// Retrieves the card
char Pyramid::get_card(int representation) {
	switch(representation) {
		case NO_CARD: return '-';
		case 1: return 'A';
		case 10: return 'T';
		case 11: return 'J';
		case 12: return 'Q';
		case 13: return 'K';
		default: return (char)(representation + '0');
	}
}

// Previous card
int Pyramid::previous(int index) {
	if(index < TOTAL_PYRAMID_CARDS || index >= TOTAL_CARDS) return NO_CARD;
	do {
		index--;
		if(index < TOTAL_PYRAMID_CARDS) return NO_CARD;
	} while(pyramid[index] == NO_CARD);
	return index;
}

// Next card
int Pyramid::next(int index) {
	if(index < TOTAL_PYRAMID_CARDS || index >= TOTAL_CARDS) return NO_CARD;
	do {
		index++;
		if(index >= TOTAL_CARDS) return NO_CARD;
	} while(pyramid[index] == NO_CARD);
	return index;
}

// Check card on (row, col) is covered or not
bool Pyramid::check_covered(int row, int col) {
	if(row > 7 || row < 1 || col > row || col < 1) return true;
	if(row == 7 && col <= row) return false;
	int index;
	index = row * (row + 1) / 2 + col - 1;
	std::cout << "Index check_covered: " << index << std::endl;
	return !(pyramid[index] == NO_CARD && pyramid[index + 1] == NO_CARD);
}

// Constructor
Pyramid::Pyramid() {
	srand(time(NULL));
	int cards[13], no_cards = 0, c, card_rep;
	for(int i=0; i<13; i++) cards[i] = 4;

	while(no_cards < 52) {
		c = rand() % (52 - no_cards) + 1;
		card_rep = 0;
		while(c > cards[card_rep]) {
			c -= cards[card_rep];
			card_rep++;
		}
		cards[card_rep]--;
		pyramid[no_cards] = card_rep + 1;
		no_cards++;
	}

	top_deck = TOTAL_PYRAMID_CARDS;
	top_waste = NO_CARD;
	total_reset_deck = 0;
}

Pyramid::Pyramid(Pyramid *_pyramid) {
	for(int i=0; i<TOTAL_CARDS; i++) pyramid[i] = _pyramid->pyramid[i];
	top_deck = _pyramid->top_deck;
	top_waste = _pyramid->top_waste;
	total_reset_deck = _pyramid->total_reset_deck;
}

// Destructor
Pyramid::~Pyramid() {
}

// Functions
// Retrieves the card on the top of the deck
char Pyramid::get_top_deck_card() {
	if(top_deck == NO_CARD) return '-';
	return get_card(pyramid[top_deck]);
}

// Retrieves the card on the top of the waste
char Pyramid::get_top_waste_card() {
	if(top_waste == NO_CARD) return '-';
	return get_card(pyramid[top_waste]);
}

// Retrieves the cards on pyramid
char * Pyramid::get_pyramid() {
	char * pyramid_cards = (char *)malloc(sizeof(char) * TOTAL_PYRAMID_CARDS);
	for(int i = 0; i < TOTAL_PYRAMID_CARDS; i++) {
		pyramid_cards[i] = get_card(pyramid[i]);
	}
	return pyramid_cards;
}

// Draw a card from deck
// If the deck is empty, the cards in the waste
// is going back to deck in order
void Pyramid::draw_deck() {
	int temporary;
	if(top_deck == NO_CARD) {
		top_deck = next(TOTAL_PYRAMID_CARDS - 1);
		top_waste = NO_CARD;
		total_reset_deck++;
	} else {
		temporary = next(top_deck);
		top_waste = top_deck;
		top_deck = temporary;
	}
}

// Pair 2 cards from pyramid
bool Pyramid::pair_cards_in_pyramid(int row1, int col1, int row2, int col2) {
	if(row1 == row2 && col1 == col2) return false;
	if(row1 > 7 || row1 < 1 || col1 > row1 || col1 < 1) return false;
	if(row2 > 7 || row2 < 1 || col2 > row2 || col2 < 1) return false;
	if(check_covered(row1, col1) || check_covered(row2, col2)) return false; 
	row1--; col1--; row2--; col2--;
	int index1, index2;
	index1 = row1 * (row1 + 1) / 2 + col1;
	index2 = row2 * (row2 + 1) / 2 + col2;

	if(pyramid[index1] + pyramid[index2] == 13) {
		pyramid[index1] = NO_CARD;
		pyramid[index2] = NO_CARD;
		return true;
	} else return false;
}

// Pair card from top of deck and card from top of waste
bool Pyramid::pair_cards_deck_and_waste() {
	if(pyramid[top_deck] + pyramid[top_waste] == 13) {
		pyramid[top_deck] = NO_CARD;
		pyramid[top_waste] = NO_CARD;
		top_deck = next(top_deck);
		top_waste = previous(top_waste);
		return true;
	} else return false;
}

// Pair card from top of deck and card from pyramid
bool Pyramid::pair_cards_deck_and_pyramid(int row, int col) {
	if(row > 7 || row < 1 || col > row || col < 1) return false;
	if(top_deck == NO_CARD || check_covered(row, col)) return false;
	row--; col--;
	int index;
	index = row * (row + 1) / 2 + col;

	if(pyramid[index] + pyramid[top_deck] == 13) {
		pyramid[index] = NO_CARD;
		pyramid[top_deck] = NO_CARD;
		top_deck = next(top_deck);
		return true;
	} else return false;
}

// Pair card from top of waste and card from pyramid
bool Pyramid::pair_cards_waste_and_pyramid(int row, int col) {
	if(row > 7 || row < 1 || col > row || col < 1) return false;
	if(top_waste == NO_CARD || check_covered(row, col)) return false;
	row--; col--;
	int index;
	index = row * (row + 1) / 2 + col;

	if(pyramid[index] + pyramid[top_waste] == 13) {
		pyramid[index] = NO_CARD;
		pyramid[top_waste] = NO_CARD;
		top_waste = previous(top_waste);
		return true;
	} else return false;
}

// Remove king from the pyramid
bool Pyramid::remove_king(int row, int col) {
	if(row > 7 || row < 1 || col > row || col < 1) return false;
	if(check_covered(row, col)) return false;
	row--; col--;
	int index;
	index = row * (row + 1) / 2 + col;
	if(pyramid[index] == 13) {
		pyramid[index] = NO_CARD;
		return true;
	} else return false;
}

// Remove king from the top of the deck
bool Pyramid::remove_king_from_deck() {
	if(top_deck != NO_CARD && pyramid[top_deck] == 13) {
		pyramid[top_deck] = NO_CARD;
		top_deck = next(top_deck);
		return true;
	} else return false;
}

// Remove king from the top of the waste
bool Pyramid::remove_king_from_waste() {
	if(top_waste != NO_CARD && pyramid[top_waste] == 13) {
		pyramid[top_waste] = NO_CARD;
		top_waste = previous(top_waste);
		return true;
	} else return false;
}

// Obtain the status of the game
// Finished when the total_reset_deck equals to 3
bool Pyramid::is_finished() {
	return total_reset_deck == 3;
}

