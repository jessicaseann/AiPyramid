#ifndef __PYRAMID__
#define __PYRAMID__

//--- Include dependencies ---
#include <stdlib.h>
#include <vector>
#include <utility>
#include "state.hpp"
//----------------------------


class Pyramid
{
	// Store all card in pyramid, deck, and waste
	int pyramid[52];
	// Index to top of the deck
	int top_deck;
	// Index to top of the waste
	int top_waste;
	// How many times the deck is reset
	int total_reset_deck;
	// Pyramid mask
	int pyramid_mask;
	// Deck and waste mask
	int deck_waste_mask;
	// Retrieves the card
	char get_card(int representation);
	// Previous card
	int previous(int index, int mask = NO_MASK);
	// Next card
	int next(int index, int mask = NO_MASK);
	// Check card on row and col is covered or not
	bool check_covered(int row, int col, int mask = NO_MASK);
	// Set pyramid mask
	void set_pyramid_mask_value(int n, int *mask = NULL, bool bit_value = NO_CARD_MASK);
	// Get pyramid mask
	bool get_pyramid_mask_value(int n, int mask = NO_MASK);
	// Set deck and waste mask
	void set_deck_waste_mask_value(int n, int *mask = NULL, bool bit_value = NO_CARD_MASK);
	// Get pyramid mask
	bool get_deck_waste_mask_value(int n, int mask = NO_MASK);
	
	public:
	// Constants
	static const int NO_CARD = -1;
	static const int TOTAL_PYRAMID_CARDS = 28;
	static const int TOTAL_CARDS = 52;
	static const int TOTAL_POSSIBLE_UNCOVERED_CARDS = 13;
	static const int NO_MASK = -1;
	static const int NO_CARD_INDEX = -10;
	static const int NO_CARD_MASK = 0;
	static const int PYRAMID_MASK_DEFAULT = (1 << TOTAL_PYRAMID_CARDS) - 1;
	static const int DECK_WASTE_MASK_DEFAULT = (1 << (TOTAL_CARDS - TOTAL_PYRAMID_CARDS)) - 1;
	static const int TOTAL_ROW = 7;
	// Action Constants
	static const int ACTION_DRAW = 1;
	static const int ACTION_REMOVE_KING_IN_PYRAMID = 2;
	static const int ACTION_REMOVE_KING_ON_DECK = 3;
	static const int ACTION_REMOVE_KING_ON_WASTE = 4;
	static const int ACTION_PAIR_CARDS_PYRAMID = 5;
	static const int ACTION_PAIR_CARD_PYRAMID_DECK = 6;
	static const int ACTION_PAIR_CARD_PYRAMID_WASTE = 7;
	static const int ACTION_PAIR_CARD_DECK_WASTE = 8;
	
	// Constructor
	Pyramid();
	Pyramid(Pyramid *pyramid);
	Pyramid(int *pyramid_and_deck);
	// Destructor
	~Pyramid();
	// Functions
	// Get state of pyramid
	State get_state();
	// Get local pyramid mask
	int get_local_pyramid_mask();
	// Get local deck waste mask
	int get_local_deck_waste_mask();
	// Retrieves the card on the top of the deck
	char get_top_deck_card(int mask = NO_MASK, int top_deck_index = NO_CARD_INDEX);
	// Retrieves the card on the top of the waste
	char get_top_waste_card(int mask = NO_MASK, int top_waste_index = NO_CARD_INDEX);
	// Retrieves the cards on pyramid
	char * get_pyramid(int mask = NO_MASK);
	// Draw a card from deck
	// If the deck is empty, the cards in the waste
	// is going back to deck in order
	void draw_deck(int mask = NO_MASK, int *top_deck_index = NULL, int *top_waste_index = NULL, int *total_reset_deck_count = NULL);
	// Pair 2 cards from pyramid
	bool pair_cards_in_pyramid(int row1, int col1, int row2, int col2, int *mask = NULL);
	// Pair card from top of deck and card from top of waste
	bool pair_cards_deck_and_waste(int *mask = NULL, int *top_deck_index = NULL, int *top_waste_index = NULL);
	// Pair card from top of deck and card from pyramid
	bool pair_cards_deck_and_pyramid(int row, int col, int *mask = NULL, int *top_deck_index = NULL, int *deck_mask = NULL);
	// Pair card from top of waste and card from pyramid
	bool pair_cards_waste_and_pyramid(int row, int col, int *mask = NULL, int *top_waste_index = NULL, int *deck_mask = NULL);
	// Remove king from the pyramid
	bool remove_king(int row, int col, int *mask = NULL);
	// Remove king from the top of the deck
	bool remove_king_from_deck(int *mask = NULL, int *top_deck_index = NULL);
	// Remove king from the top of the waste
	bool remove_king_from_waste(int *mask = NULL, int *top_waste_index = NULL);
	
	// Get all possible actions
	std::vector< std::pair<int, std::vector<int> > > get_all_possible_actions(int mask = NO_MASK, int deck_mask = NO_MASK, int top_deck_index = NO_CARD_INDEX, int top_waste_index = NO_CARD_INDEX, int total_reset_deck_count = NO_CARD_INDEX);
	// Check any card to pair Action
	int check_pair(int mask = NO_MASK);
	// Check Pair 2 cards from pyramid
	bool check_pair_cards_in_pyramid(int row1, int col1, int row2, int col2, int mask = NO_MASK);
	// Check Pair card from top of deck and card from top of waste
	bool check_pair_cards_deck_and_waste(int mask = NO_MASK, int top_deck_index = NO_CARD_INDEX, int top_waste_index = NO_CARD_INDEX);
	// Check Pair card from top of deck and card from pyramid
	bool check_pair_cards_deck_and_pyramid(int row, int col, int mask = NO_MASK, int top_deck_index = NO_CARD_INDEX, int deck_mask = NO_MASK);
	// Check Pair card from top of waste and card from pyramid
	bool check_pair_cards_waste_and_pyramid(int row, int col, int mask = NO_MASK, int top_waste_index = NO_CARD_INDEX, int deck_mask = NO_MASK);
	// Check Remove king from the pyramid
	bool check_remove_king(int row, int col, int mask = NO_MASK);
	// Check Remove king from the top of the deck
	bool check_remove_king_from_deck(int mask = NO_MASK, int top_deck_index = NO_CARD_INDEX);
	// Check Remove king from the top of the waste
	bool check_remove_king_from_waste(int mask = NO_MASK, int top_waste_index = NO_CARD_INDEX);
	// Check if that state is winnable
	bool is_winnable_state(const State &state);
	// Obtain the status of the game
	// Finished when the total_reset_deck equals to 3
	bool is_finished(int mask = NO_MASK, int total_reset_deck_count = NO_CARD_INDEX);
};

#endif
