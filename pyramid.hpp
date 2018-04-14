#ifndef __PYRAMID__
#define __PYRAMID__

//--- Include dependencies ---
//----   NOT NEEDED YET   ----
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
	// Retrieves the card
	char get_card(int representation);
	// Previous card
	int previous(int index);
	// Next card
	int next(int index);
	// Check card on row and col is covered or not
	bool check_covered(int row, int col);
	
	public:
	// Constants
	static const int NO_CARD = -1;
	static const int TOTAL_PYRAMID_CARDS = 28;
	static const int TOTAL_CARDS = 52;
	static const int TOTAL_POSSIBLE_UNCOVERED_CARDS = 13;
	// Constructor
	Pyramid();
	Pyramid(Pyramid *pyramid);
	// Destructor
	~Pyramid();
	// Functions
	// Retrieves the card on the top of the deck
	char get_top_deck_card();
	// Retrieves the card on the top of the waste
	char get_top_waste_card();
	// Retrieves the cards on pyramid
	char * get_pyramid();
	// Draw a card from deck
	// If the deck is empty, the cards in the waste
	// is going back to deck in order
	void draw_deck();
	// Pair 2 cards from pyramid
	bool pair_cards_in_pyramid(int row1, int col1, int row2, int col2);
	// Pair card from top of deck and card from top of waste
	bool pair_cards_deck_and_waste();
	// Pair card from top of deck and card from pyramid
	bool pair_cards_deck_and_pyramid(int row, int col);
	// Pair card from top of waste and card from pyramid
	bool pair_cards_waste_and_pyramid(int row, int col);
	// Remove king from the pyramid
	bool remove_king(int row, int col);
	// Remove king from the top of the deck
	bool remove_king_from_deck();
	// Remove king from the top of the waste
	bool remove_king_from_waste();
	
	// Check any card to pair Action
	int check_pair();
	// Check Pair 2 cards from pyramid
	bool check_pair_cards_in_pyramid(int row1, int col1, int row2, int col2);
	// Check Pair card from top of deck and card from top of waste
	bool check_pair_cards_deck_and_waste();
	// Check Pair card from top of deck and card from pyramid
	bool check_pair_cards_deck_and_pyramid(int row, int col);
	// Check Pair card from top of waste and card from pyramid
	bool check_pair_cards_waste_and_pyramid(int row, int col);
	// Check Remove king from the pyramid
	bool check_remove_king(int row, int col);
	// Check Remove king from the top of the deck
	bool check_remove_king_from_deck();
	// Check Remove king from the top of the waste
	bool check_remove_king_from_waste();
	
	// Obtain the status of the game
	// Finished when the total_reset_deck equals to 3
	bool is_finished();
};

#endif
