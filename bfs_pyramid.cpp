#include "bfs_pyramid.hpp"
#include "state.hpp"
#include <queue>
#include <vector>
#include <utility>
#include <iostream>
#include <cassert>
using namespace std;

void BFSPyramid::push_possible_actions(Pyramid *pyramid, std::queue<State> &process_state, State current_state) {
	vector< pair<int, vector<int> > > moves = pyramid->get_all_possible_actions(current_state.pyramid_mask, current_state.deck_waste_mask, current_state.top_deck_index, current_state.top_waste_index);
	vector< pair<int, vector<int> > >::iterator it;
	for(it = moves.begin(); it != moves.end(); it++) {
		State next_state(current_state);		
		cout << "- ";
		switch(it->first) {
			case Pyramid::ACTION_DRAW:
				assert(it->second.size() == 0);
				cout << "(1) Draw" << endl;
				pyramid->draw_deck(next_state.deck_waste_mask, &(next_state.top_deck_index), &(next_state.top_waste_index), &(next_state.total_reset_deck_count));
				break;
			case Pyramid::ACTION_REMOVE_KING_IN_PYRAMID:
				assert(it->second.size() == 2);
				cout << "(2) Remove king in pyramid\n  === row: " << it->second[0] << ", col: " << it->second[1] << endl;
				pyramid->remove_king(it->second[0], it->second[1], &(next_state.pyramid_mask));
				break;
			case Pyramid::ACTION_REMOVE_KING_ON_DECK:
				assert(it->second.size() == 0);
				cout << "(3) Remove king on top of deck" << endl;
				pyramid->remove_king_from_deck(&(next_state.deck_waste_mask), &(next_state.top_deck_index));
				break;
			case Pyramid::ACTION_REMOVE_KING_ON_WASTE:
				assert(it->second.size() == 0);
				cout << "(4) Remove king on top of waste" << endl;
				pyramid->remove_king_from_waste(&(next_state.deck_waste_mask), &(next_state.top_deck_index));
				break;
			case Pyramid::ACTION_PAIR_CARDS_PYRAMID:
				assert(it->second.size() == 4);
				cout << "(5) Pair cards in pyramid | row1: " << it->second[0] << ", col1: " << it->second[1] << endl;
				cout << "                            | row2: " << it->second[2] << ", col2: " << it->second[3] << endl;
				pyramid->pair_cards_in_pyramid(it->second[0], it->second[1], it->second[2], it->second[3], &(next_state.pyramid_mask));
				break;
			case Pyramid::ACTION_PAIR_CARD_PYRAMID_DECK:
				assert(it->second.size() == 2);
				cout << "(6) Pair card in pyramid with top of deck\n  === row: " << it->second[0] << ", col: " << it->second[1] << endl;
				pyramid->pair_cards_deck_and_pyramid(it->second[0], it->second[1], &(next_state.pyramid_mask), &(next_state.top_deck_index), &(next_state.deck_waste_mask));
				break;
			case Pyramid::ACTION_PAIR_CARD_PYRAMID_WASTE:
				assert(it->second.size() == 2);
				cout << "(7) Pair card in pyramid with top of waste\n  === row: " << it->second[0] << ", col: " << it->second[1] << endl;
				pyramid->pair_cards_waste_and_pyramid(it->second[0], it->second[1], &(next_state.pyramid_mask), &(next_state.top_waste_index), &(next_state.deck_waste_mask));
				break;
			case Pyramid::ACTION_PAIR_CARD_DECK_WASTE:
				assert(it->second.size() == 0);
				cout << "(7) Pair card on top of deck with top of waste" << endl;
				pyramid->pair_cards_deck_and_waste(&(next_state.deck_waste_mask), &(next_state.top_deck_index), &(next_state.top_waste_index));
				break;
			default: break;
		}
		process_state.push(next_state);
	}
}

bool BFSPyramid::bfs(Pyramid *pyramid) {
	State starting_state = pyramid->get_state();
	std::queue<State> process_state;
	process_state.push(starting_state);
	
	while(!process_state.empty()) {
		State current_state = process_state.front();
		if(current_state.pyramid_mask == 0) return true;
		push_possible_actions(pyramid, process_state, current_state);
		
		process_state.pop();
	}
	return false;
}