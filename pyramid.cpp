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
int Pyramid::previous(int index, int mask) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	if(index < TOTAL_PYRAMID_CARDS - 1 || index >= TOTAL_CARDS) return NO_CARD;
	do {
		index--;
		if(index < TOTAL_PYRAMID_CARDS - 1) return NO_CARD;
	} while(!get_deck_waste_mask_value(index, mask));
	return index;
}

// Next card
int Pyramid::next(int index, int mask) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	if(index < TOTAL_PYRAMID_CARDS - 1 || index >= TOTAL_CARDS) return NO_CARD;
	do {
		index++;
		if(index >= TOTAL_CARDS) return NO_CARD;
	} while(!get_deck_waste_mask_value(index, mask));
	return index;
}

// Check card on (row, col) is covered or not
bool Pyramid::check_covered(int row, int col, int mask) {
	if(row > 7 || row < 1 || col > row || col < 1) return true;
	if(row == 7 && col <= row) return false;
	if(mask == NO_MASK) mask = pyramid_mask;
	int index = row * (row + 1) / 2 + col - 1;
	return get_pyramid_mask_value(index, mask) || get_pyramid_mask_value(index + 1, mask);
}

// Set pyramid mask
void Pyramid::set_pyramid_mask_value(int n, int *mask, bool bit_value) {
	if(mask == NULL) mask = &pyramid_mask;
	(*mask) = (*mask) ^ ((!bit_value) << (TOTAL_PYRAMID_CARDS - n - 1));
}

// Get pyramid mask
bool Pyramid::get_pyramid_mask_value(int n, int mask) {
	if(mask == NO_MASK) mask = pyramid_mask;
	return (mask >> (TOTAL_PYRAMID_CARDS - n - 1)) & 1;
}

// Set deck and waste mask
void Pyramid::set_deck_waste_mask_value(int n, int *mask, bool bit_value) {
	if(mask == NULL) mask = &deck_waste_mask;
	(*mask) = (*mask) ^ ((!bit_value) << (TOTAL_CARDS - n - 1));
}

// Get pyramid mask
bool Pyramid::get_deck_waste_mask_value(int n, int mask) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	return (mask >> (TOTAL_CARDS - n - 1)) & 1;
}

// Constructor
Pyramid::Pyramid() {
	srand(time(NULL) * time(NULL));
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
	pyramid_mask = PYRAMID_MASK_DEFAULT;
	deck_waste_mask = DECK_WASTE_MASK_DEFAULT;
}

Pyramid::Pyramid(Pyramid *_pyramid) {
	for(int i=0; i<TOTAL_CARDS; i++) pyramid[i] = _pyramid->pyramid[i];
	top_deck = _pyramid->top_deck;
	top_waste = _pyramid->top_waste;
	total_reset_deck = _pyramid->total_reset_deck;
	pyramid_mask = _pyramid->pyramid_mask;
	deck_waste_mask = _pyramid->deck_waste_mask;
}

Pyramid::Pyramid(int *pyramid_and_deck) {
	for(int i=0; i<TOTAL_CARDS; i++) pyramid[i] = pyramid_and_deck[i];
	top_deck = TOTAL_PYRAMID_CARDS;
	top_waste = NO_CARD;
	total_reset_deck = 0;
	pyramid_mask = PYRAMID_MASK_DEFAULT;
	deck_waste_mask = DECK_WASTE_MASK_DEFAULT;
}

// Destructor
Pyramid::~Pyramid() {}

// Functions
// Get state of pyramid
State Pyramid::get_state() {
	State current_state;
	current_state.pyramid_mask = pyramid_mask;
	current_state.deck_waste_mask = deck_waste_mask;
	current_state.top_deck_index = top_deck;
	current_state.top_waste_index = top_waste;
	current_state.total_reset_deck_count = total_reset_deck;
	current_state.recalculate();
	return current_state;
}

// Get local pyramid mask
int Pyramid::get_local_pyramid_mask() {
	return pyramid_mask;
}

// Get local deck waste mask
int Pyramid::get_local_deck_waste_mask() {
	return deck_waste_mask;
}

// Retrieves the card on the top of the deck
char Pyramid::get_top_deck_card(int mask, int top_deck_index) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	if(top_deck_index == NO_CARD_INDEX) top_deck_index = top_deck;
	
	if(top_deck_index == NO_CARD || !get_deck_waste_mask_value(top_deck_index, mask)) return '-';
	return get_card(pyramid[top_deck_index]);
}

// Retrieves the card on the top of the waste
char Pyramid::get_top_waste_card(int mask, int top_waste_index) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	if(top_waste_index == NO_CARD_INDEX) top_waste_index = top_waste;
	
	if(top_waste_index == NO_CARD || !get_deck_waste_mask_value(top_waste_index, mask)) return '-';
	return get_card(pyramid[top_waste_index]);
}

// Retrieves the cards on pyramid
char * Pyramid::get_pyramid(int mask) {
	char * pyramid_cards = (char *)malloc(sizeof(char) * TOTAL_PYRAMID_CARDS);
	if(mask == NO_MASK) mask = pyramid_mask;
	for(int i = 0; i < TOTAL_PYRAMID_CARDS; i++) {
		if(get_pyramid_mask_value(i, mask)) {
			pyramid_cards[i] = get_card(pyramid[i]);
		} else {
			pyramid_cards[i] = get_card(NO_CARD);
		}
	}
	return pyramid_cards;
}

// Draw a card from deck
// If the deck is empty, the cards in the waste
// is going back to deck in order
void Pyramid::draw_deck(int mask, int *top_deck_index, int *top_waste_index, int *total_reset_deck_count) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	if(top_deck_index == NULL) top_deck_index = &top_deck;
	if(top_waste_index == NULL) top_waste_index = &top_waste;
	if(total_reset_deck_count == NULL) total_reset_deck_count = &total_reset_deck;
	
	int temporary;
	if(*top_deck_index == NO_CARD) {
		*top_deck_index = next(TOTAL_PYRAMID_CARDS - 1, mask);
		*top_waste_index = NO_CARD;
		(*total_reset_deck_count)++;
	} else {
		temporary = next(*top_deck_index, mask);
		*top_waste_index = *top_deck_index;
		*top_deck_index = temporary;
	}
}

// Pair 2 cards from pyramid
bool Pyramid::pair_cards_in_pyramid(int row1, int col1, int row2, int col2, int *mask) {
	if(mask == NULL) mask = &pyramid_mask;
	if(row1 == row2 && col1 == col2) return false;
	if(row1 > 7 || row1 < 1 || col1 > row1 || col1 < 1) return false;
	if(row2 > 7 || row2 < 1 || col2 > row2 || col2 < 1) return false;
	if(check_covered(row1, col1, *mask) || check_covered(row2, col2, *mask)) return false; 
	row1--; col1--; row2--; col2--;
	int index1, index2;
	index1 = row1 * (row1 + 1) / 2 + col1;
	index2 = row2 * (row2 + 1) / 2 + col2;

	if(get_pyramid_mask_value(index1, *mask) && get_pyramid_mask_value(index2, *mask) && pyramid[index1] + pyramid[index2] == 13) {
		set_pyramid_mask_value(index1, mask);
		set_pyramid_mask_value(index2, mask);
		return true;
	} else return false;
}

// Pair card from top of deck and card from top of waste
bool Pyramid::pair_cards_deck_and_waste(int *mask, int *top_deck_index, int *top_waste_index) {
	if(mask == NULL) mask = &deck_waste_mask;
	if(top_deck_index == NULL) top_deck_index = &top_deck;
	if(top_waste_index == NULL) top_waste_index = &top_waste;
	
	if(*top_deck_index == NO_CARD || *top_waste_index == NO_CARD) return false;
	if(get_deck_waste_mask_value(*top_deck_index, *mask) && get_deck_waste_mask_value(*top_waste_index, *mask) && pyramid[*top_deck_index] + pyramid[*top_waste_index] == 13) {
		set_deck_waste_mask_value(*top_deck_index, mask);
		set_deck_waste_mask_value(*top_waste_index, mask);
		*top_deck_index = next(*top_deck_index);
		*top_waste_index = previous(*top_waste_index);
		return true;
	} else return false;
}

// Pair card from top of deck and card from pyramid
bool Pyramid::pair_cards_deck_and_pyramid(int row, int col, int *mask, int *top_deck_index, int *deck_mask) {
	if(mask == NULL) mask = &pyramid_mask;
	if(top_deck_index == NULL) top_deck_index = &top_deck;
	if(deck_mask == NULL) deck_mask = &deck_waste_mask;
	
	if(row > 7 || row < 1 || col > row || col < 1) return false;
	if(*top_deck_index == NO_CARD || check_covered(row, col, *mask)) return false;
	row--; col--;
	int index;
	index = row * (row + 1) / 2 + col;

	if(get_pyramid_mask_value(index, *mask) && get_deck_waste_mask_value(*top_deck_index, *deck_mask) && pyramid[index] + pyramid[*top_deck_index] == 13) {
		set_pyramid_mask_value(index, mask);
		set_deck_waste_mask_value(*top_deck_index, deck_mask);
		*top_deck_index = next(*top_deck_index);
		return true;
	} else return false;
}

// Pair card from top of waste and card from pyramid
bool Pyramid::pair_cards_waste_and_pyramid(int row, int col, int *mask, int *top_waste_index, int *deck_mask) {
	if(mask == NULL) mask = &pyramid_mask;
	if(top_waste_index == NULL) top_waste_index = &top_waste;
	if(deck_mask == NULL) deck_mask = &deck_waste_mask;

	if(row > 7 || row < 1 || col > row || col < 1) return false;
	if(*top_waste_index == NO_CARD || check_covered(row, col, *mask)) return false;
	row--; col--;
	int index;
	index = row * (row + 1) / 2 + col;

	if(get_pyramid_mask_value(index, *mask) && get_deck_waste_mask_value(*top_waste_index, *deck_mask) && pyramid[index] + pyramid[*top_waste_index] == 13) {
		set_pyramid_mask_value(index, mask);
		set_deck_waste_mask_value(*top_waste_index, deck_mask);
		*top_waste_index = previous(*top_waste_index);
		return true;
	} else return false;
}

// Remove king from the pyramid
bool Pyramid::remove_king(int row, int col, int *mask) {
	if(mask == NULL) mask = &pyramid_mask;
	if(row > 7 || row < 1 || col > row || col < 1) return false;
	if(check_covered(row, col, *mask)) return false;
	row--; col--;
	int index;
	index = row * (row + 1) / 2 + col;
	if(get_pyramid_mask_value(index, *mask) && pyramid[index] == 13) {
		set_pyramid_mask_value(index, mask);
		return true;
	} else return false;
}

// Remove king from the top of the deck
bool Pyramid::remove_king_from_deck(int *mask, int *top_deck_index) {
	if(mask == NULL) mask = &deck_waste_mask;
	if(top_deck_index == NULL) top_deck_index = &top_deck;
	
	if(*top_deck_index != NO_CARD && get_deck_waste_mask_value(*top_deck_index, *mask) && pyramid[*top_deck_index] == 13) {
		set_deck_waste_mask_value(*top_deck_index, mask);
		*top_deck_index = next(*top_deck_index);
		return true;
	} else return false;
}

// Remove king from the top of the waste
bool Pyramid::remove_king_from_waste(int *mask, int *top_waste_index) {
	if(mask == NULL) mask = &deck_waste_mask;
	if(top_waste_index == NULL) top_waste_index = &top_waste;

	if(*top_waste_index != NO_CARD && get_deck_waste_mask_value(*top_waste_index, *mask) && pyramid[*top_waste_index] == 13) {
		set_deck_waste_mask_value(*top_waste_index, mask);
		*top_waste_index = previous(*top_waste_index);
		return true;
	} else return false;
}

// Get all possible actions
std::vector< std::pair<int, std::vector<int> > > Pyramid::get_all_possible_actions(int mask, int deck_mask, int top_deck_index, int top_waste_index, int total_reset_deck_count) {
	if(mask == NO_MASK) mask = pyramid_mask;
	if(deck_mask == NO_MASK) deck_mask = deck_waste_mask;
	if(top_deck_index == NO_CARD_INDEX) top_deck_index = top_deck;
	if(top_waste_index == NO_CARD_INDEX) top_waste_index = top_waste;
	if(total_reset_deck_count == NO_CARD_INDEX) total_reset_deck_count = total_reset_deck;
	
	int row, col, index;
	std::vector< std::pair<int, int> > uncovered_card[TOTAL_POSSIBLE_UNCOVERED_CARDS + 1];
	std::vector< std::pair<int, std::vector<int> > > actions;
	if(!is_finished(mask, total_reset_deck_count)) {
		// Clear all uncovered card
		for(int i = 0; i <= TOTAL_POSSIBLE_UNCOVERED_CARDS; i++)
			uncovered_card[i].clear();

		for(row = 1; row <= TOTAL_ROW; row++) {
			for(col = 1; col <= row; col++) {
				index = (row - 1) * row / 2 + col - 1;
				if(get_pyramid_mask_value(index, mask) && !check_covered(row, col, mask)) {
					//-----------------------
					// Check King in pyramid
					//-----------------------
					if(check_remove_king(row, col, mask)) {
						std::vector<int> location;
						location.push_back(row);
						location.push_back(col);
						actions.push_back(std::make_pair(ACTION_REMOVE_KING_IN_PYRAMID, location));
					}
					//------------------------------------
					// Get all uncovered card except King
					//------------------------------------
					else {
						uncovered_card[pyramid[index]].push_back(std::make_pair(row, col));
					}
				}
			}
		}

		//----------------------------------------------------------
		// Check pair of uncovered cards in pyramid
		//----------------------------------------------------------
		int check_size = TOTAL_POSSIBLE_UNCOVERED_CARDS / 2;
		std::vector< std::pair<int, int> >::iterator fc, sc;
		for(int i = 1; i <= check_size; i++) {
			int pc = 13 - i;
			if(uncovered_card[i].size() > 0 && uncovered_card[pc].size() > 0) {
				std::vector<int> location;
				for(fc = uncovered_card[i].begin(); fc != uncovered_card[i].end(); fc++) {
					for(sc = uncovered_card[pc].begin(); sc != uncovered_card[pc].end(); sc++) {
						location.clear();
						location.push_back(fc->first);
						location.push_back(fc->second);
						location.push_back(sc->first);
						location.push_back(sc->second);
						actions.push_back(std::make_pair(ACTION_PAIR_CARDS_PYRAMID, location));
					}
				}
			}
		}

		//---------------------------
		// Check King on top of deck
		//---------------------------
		if(check_remove_king_from_deck(deck_mask, top_deck_index)) {
			std::vector<int> empty_vector;
			actions.push_back(std::make_pair(ACTION_REMOVE_KING_ON_DECK, empty_vector));
		}

		//---------------------------
		// Check King on top of waste
		//---------------------------
		if(check_remove_king_from_waste(deck_mask, top_waste_index)) {
			std::vector<int> empty_vector;
			actions.push_back(std::make_pair(ACTION_REMOVE_KING_ON_WASTE, empty_vector));
		}
		
		//----------------------------------------------------------
		// Check pair on top of deck with uncovered card in pyramid
		//----------------------------------------------------------
		if(get_top_deck_card(deck_mask, top_deck_index) != '-') {
			int pc = 13 - pyramid[top_deck_index];
			for(int i = 0; i < uncovered_card[pc].size(); i++) {
				std::vector<int> location;
				location.push_back(uncovered_card[pc][i].first);
				location.push_back(uncovered_card[pc][i].second);
				actions.push_back(std::make_pair(ACTION_PAIR_CARD_PYRAMID_DECK, location));
			}
		}

		//----------------------------------------------------------
		// Check pair on top of waste with uncovered card in pyramid
		//----------------------------------------------------------
		if(get_top_waste_card(deck_mask, top_waste_index) != '-') {
			int pc = 13 - pyramid[top_waste_index];
			for(int i = 0; i < uncovered_card[pc].size(); i++) {
				std::vector<int> location;
				location.push_back(uncovered_card[pc][i].first);
				location.push_back(uncovered_card[pc][i].second);
				actions.push_back(std::make_pair(ACTION_PAIR_CARD_PYRAMID_WASTE, location));
			}
		}

		//----------------------------------------------------------
		// Check pair on top of deck with waste
		//----------------------------------------------------------
		if(check_pair_cards_deck_and_waste(deck_mask, top_deck_index, top_waste_index)) {
			std::vector<int> empty_vector;
			actions.push_back(std::make_pair(ACTION_PAIR_CARD_DECK_WASTE, empty_vector));
		}
		
		//----------------------------------------------------------
		// Action draw card
		//----------------------------------------------------------
		std::vector<int> empty_vector;
		actions.push_back(std::make_pair(ACTION_DRAW, empty_vector));
	}
	return actions;
}

// Check if action valid
int Pyramid::check_pair(int mask) {
	int temp_i=0;
	int temp_j=0;
	
	if(check_remove_king_from_deck()) return 3;
	else if(check_remove_king_from_waste())return 4;
	for (int i=7; i>=1;i--){
		for(int j=i;j>=1;j--){
			i--;j--;
			int post = i * (i + 1) / 2 + j;
			//std::cout<<"Check "<<get_card(pyramid[post])<<"\n";
			i++;j++;
			if(!check_covered(i, j, mask)){
				if(get_card(pyramid[post])=='K') return 2;
				if(temp_i==0 && temp_j==0){
					temp_i=i;
					temp_j=j;
					for (int m=7; m>=1;m--){
						for(int n=7;n>=1;n--){
							if(!check_covered(m, n, mask))
								if(check_pair_cards_in_pyramid(temp_i, temp_j, m, n, mask)) return 5;
						}
					}
				if(check_pair_cards_deck_and_pyramid(temp_i, temp_j, mask)) return 6;
				if(check_pair_cards_waste_and_pyramid(temp_i, temp_j, mask)) return 7;
				temp_i=0;
				temp_j=0;		
				}
			}	
		}
	}
	if(check_pair_cards_deck_and_waste())return 8;
	else return 1;
}

// Check Pair 2 cards from pyramid
bool Pyramid::check_pair_cards_in_pyramid(int row1, int col1, int row2, int col2, int mask) {
	if(mask == NO_MASK) mask = pyramid_mask;

	if(row1 == row2 && col1 == col2) return false;
	if(row1 > 7 || row1 < 1 || col1 > row1 || col1 < 1) return false;
	if(row2 > 7 || row2 < 1 || col2 > row2 || col2 < 1) return false;
	if(check_covered(row1, col1, mask) || check_covered(row2, col2, mask)) return false; 
	row1--; col1--; row2--; col2--;
	int index1, index2;
	index1 = row1 * (row1 + 1) / 2 + col1;
	index2 = row2 * (row2 + 1) / 2 + col2;
	if(get_pyramid_mask_value(index1, mask) && get_pyramid_mask_value(index2, mask) && pyramid[index1] + pyramid[index2] == 13) {
		return true;
	} else return false;
}

// Check Pair card from top of deck and card from top of waste
bool Pyramid::check_pair_cards_deck_and_waste(int mask, int top_deck_index, int top_waste_index) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	if(top_deck_index == NO_CARD_INDEX) top_deck_index = top_deck;
	if(top_waste_index == NO_CARD_INDEX) top_waste_index = top_waste;
	
	if(top_deck_index == NO_CARD || top_waste_index == NO_CARD) return false;
	if(get_deck_waste_mask_value(top_deck_index, mask) && get_deck_waste_mask_value(top_waste_index, mask) && pyramid[top_deck_index] + pyramid[top_waste_index] == 13) {
		return true;
	} else return false;
}

// Check Pair card from top of deck and card from pyramid
bool Pyramid::check_pair_cards_deck_and_pyramid(int row, int col, int mask, int top_deck_index, int deck_mask) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	if(top_deck_index == NO_CARD_INDEX) top_deck_index = top_deck;
	if(deck_mask = NO_MASK) deck_mask = deck_waste_mask;
	
	if(row > 7 || row < 1 || col > row || col < 1) return false;
	if(top_deck_index == NO_CARD || check_covered(row, col, mask)) return false;
	row--; col--;
	int index;
	index = row * (row + 1) / 2 + col;
	if(get_pyramid_mask_value(index, mask) && get_deck_waste_mask_value(top_deck_index, deck_mask) && pyramid[index] + pyramid[top_deck_index] == 13) {
		return true;
	} else return false;
}

// Check Pair card from top of waste and card from pyramid
bool Pyramid::check_pair_cards_waste_and_pyramid(int row, int col, int mask, int top_waste_index, int deck_mask) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	if(top_waste_index == NO_CARD_INDEX) top_waste_index = top_waste;
	if(deck_mask = NO_MASK) deck_mask = deck_waste_mask;

	if(row > 7 || row < 1 || col > row || col < 1) return false;
	if(top_waste_index == NO_CARD || check_covered(row, col, mask)) return false;
	row--; col--;
	int index;
	index = row * (row + 1) / 2 + col;
	if(get_pyramid_mask_value(index, mask) && get_deck_waste_mask_value(top_waste_index, deck_mask) && pyramid[index] + pyramid[top_waste_index] == 13) {
		return true;
	} else return false;
}

// Check Remove king from the pyramid
bool Pyramid::check_remove_king(int row, int col, int mask) {
	if(row > 7 || row < 1 || col > row || col < 1) return false;
	if(check_covered(row, col)) return false;
	row--; col--;
	int index;
	index = row * (row + 1) / 2 + col;
	if(get_pyramid_mask_value(index, mask) && pyramid[index] == 13) {
		return true;
	} else return false;
}

// Check Remove king from the top of the deck
bool Pyramid::check_remove_king_from_deck(int mask, int top_deck_index) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	if(top_deck_index == NO_CARD_INDEX) top_deck_index = top_deck;

	if(top_deck_index != NO_CARD && get_deck_waste_mask_value(top_deck_index, mask) && pyramid[top_deck_index] == 13) {
		return true;
	} else return false;
}

// Check Remove king from the top of the waste
bool Pyramid::check_remove_king_from_waste(int mask, int top_waste_index) {
	if(mask == NO_MASK) mask = deck_waste_mask;
	if(top_waste_index == NO_CARD_INDEX) top_waste_index = top_waste;

	if(top_waste_index != NO_CARD && get_deck_waste_mask_value(top_waste_index, mask) && pyramid[top_waste_index] == 13) {
		return true;
	} else return false;
}

// Obtain the status of the game
// Finished when the total_reset_deck equals to 3
bool Pyramid::is_finished(int mask, int total_reset_deck_count) {
	if(mask == NO_MASK) mask = pyramid_mask;
	if(total_reset_deck_count == NO_CARD_INDEX) total_reset_deck_count = total_reset_deck;
	
	return total_reset_deck_count == 3 || mask == 0;
}

