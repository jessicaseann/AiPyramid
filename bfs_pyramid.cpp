#include "bfs_pyramid.hpp"
#include "state.hpp"
#include "action.hpp"
#include <queue>
#include <vector>
#include <utility>
#include <set>
#include <iostream>
#include <cassert>

void BFSPyramid::push_possible_actions(
	Pyramid *pyramid, 
	std::priority_queue<State, std::vector<State>, ValueStateComparator> *process_state, 
	const State &current_state, 
	int index, 
	std::set<State> &visited_state,
	std::vector< std::pair<int, int> > *actions_taken
	) {
	std::vector< std::pair<int, std::vector<int> > > moves = pyramid->get_all_possible_actions(current_state.pyramid_mask, current_state.deck_waste_mask, current_state.top_deck_index, current_state.top_waste_index, current_state.total_reset_deck_count);
	std::vector< std::pair<int, std::vector<int> > >::iterator it;
	bool remove_King = false;
	//system("cls");
//	if(index % 100000 == 0) std::cout << "Iteration #" << index << " | " << current_state.value << std::endl;

	for(it = moves.begin(); it != moves.end(); it++) {
		State next_state(current_state);
		//std::cout << "- ";
		switch(it->first) {
			case Pyramid::ACTION_DRAW:
				assert(it->second.size() == 0);
				//std::cout << "(1) Draw" << std::endl;
				if(next_state.draw_deck_index == State::NO_DRAW_DECK_INDEX) next_state.draw_deck_index = next_state.top_deck_index;
				pyramid->draw_deck(next_state.deck_waste_mask, &(next_state.top_deck_index), &(next_state.top_waste_index), &(next_state.total_reset_deck_count));
				break;
			case Pyramid::ACTION_REMOVE_KING_IN_PYRAMID:
				assert(it->second.size() == 2);
				//std::cout << "(2) Remove king in pyramid\n  === row: " << it->second[0] << ", col: " << it->second[1] << std::endl;
				pyramid->remove_king(it->second[0], it->second[1], &(next_state.pyramid_mask));
				next_state.draw_deck_index = State::NO_DRAW_DECK_INDEX;
				remove_King = true;
				break;
			case Pyramid::ACTION_REMOVE_KING_ON_DECK:
				assert(it->second.size() == 0);
				//std::cout << "(3) Remove king on top of deck" << std::endl;
				pyramid->remove_king_from_deck(&(next_state.deck_waste_mask), &(next_state.top_deck_index));
				next_state.draw_deck_index = State::NO_DRAW_DECK_INDEX;
				remove_King = true;
				break;
			case Pyramid::ACTION_REMOVE_KING_ON_WASTE:
				assert(it->second.size() == 0);
				//std::cout << "(4) Remove king on top of waste" << std::endl;
				pyramid->remove_king_from_waste(&(next_state.deck_waste_mask), &(next_state.top_deck_index));
				next_state.draw_deck_index = State::NO_DRAW_DECK_INDEX;
				remove_King = true;
				break;
			case Pyramid::ACTION_PAIR_CARDS_PYRAMID:
				assert(it->second.size() == 4);
				//std::cout << "(5) Pair cards in pyramid | row1: " << it->second[0] << ", col1: " << it->second[1] << std::endl;
				//std::cout << "                            | row2: " << it->second[2] << ", col2: " << it->second[3] << std::endl;
				pyramid->pair_cards_in_pyramid(it->second[0], it->second[1], it->second[2], it->second[3], &(next_state.pyramid_mask));
				next_state.draw_deck_index = State::NO_DRAW_DECK_INDEX;
				break;
			case Pyramid::ACTION_PAIR_CARD_PYRAMID_DECK:
				assert(it->second.size() == 2);
				//std::cout << "(6) Pair card in pyramid with top of deck\n  === row: " << it->second[0] << ", col: " << it->second[1] << std::endl;
				pyramid->pair_cards_deck_and_pyramid(it->second[0], it->second[1], &(next_state.pyramid_mask), &(next_state.top_deck_index), &(next_state.deck_waste_mask));
				next_state.draw_deck_index = State::NO_DRAW_DECK_INDEX;
				break;
			case Pyramid::ACTION_PAIR_CARD_PYRAMID_WASTE:
				assert(it->second.size() == 2);
				//std::cout << "(7) Pair card in pyramid with top of waste\n  === row: " << it->second[0] << ", col: " << it->second[1] << std::endl;
				pyramid->pair_cards_waste_and_pyramid(it->second[0], it->second[1], &(next_state.pyramid_mask), &(next_state.top_waste_index), &(next_state.deck_waste_mask));
				next_state.draw_deck_index = State::NO_DRAW_DECK_INDEX;
				break;
			case Pyramid::ACTION_PAIR_CARD_DECK_WASTE:
				assert(it->second.size() == 0);
				//std::cout << "(8) Pair card on top of deck with top of waste" << std::endl;
				pyramid->pair_cards_deck_and_waste(&(next_state.deck_waste_mask), &(next_state.top_deck_index), &(next_state.top_waste_index));
				next_state.draw_deck_index = State::NO_DRAW_DECK_INDEX;
				break;
			default: break;
		}
		//###########################################
		//##  P U S H   T O   N E X T   S T A T E  ##
		//###########################################
		next_state.recalculate();
		if(visited_state.find(next_state) == visited_state.end()) {
			if(actions_taken != NULL) {
				next_state.current_index = actions_taken->size();
				actions_taken->push_back(std::make_pair(current_state.current_index, get_action_value(*it)));
			}
			visited_state.insert(next_state);
			process_state->push(next_state);
		}
		if(remove_King) break;
	}
}

bool BFSPyramid::bfs(Pyramid *pyramid, std::vector< std::pair<int, std::vector<int> > > *actions_taken_result) {
	State starting_state = pyramid->get_state();
	starting_state.current_index = -1;
	starting_state.recalculate();
	int count = -1, winnable_index, unwinnable_count = 0;
	//std::vector< std::pair<int, std::pair<int, std::vector<int> > > > actions_taken;
	std::vector< std::pair<int, int> > actions_taken;
	bool win = false;
	std::set<State> visited_state;
	visited_state.clear();
	
	std::priority_queue<State, std::vector<State>, ValueStateComparator> process_state;
	process_state.push(starting_state);
	
	while(!process_state.empty()) {
		State current_state = process_state.top();
		process_state.pop();
		if(current_state.top_deck_index != current_state.draw_deck_index) {
			if(current_state.pyramid_mask == 0 || current_state.value == 0) {
				win = true;
				winnable_index = current_state.current_index;
				break;
			}
			if(pyramid->is_winnable_state(current_state)) {
				push_possible_actions(pyramid, &process_state, current_state, count, visited_state, &actions_taken);
				count++;
				if(count % 1000000 == 0) std::cout << "Iteration " << count << " has " << unwinnable_count << " unwinnable counts | size of pq = " << process_state.size() << std::endl;
			} else unwinnable_count++;
//			std::cin.get();
		}
	}
	
	if(win) {
//		std::cout << "Last index : " << winnable_index << std::endl;

		while(winnable_index > -1) {
//			std::cout << actions_taken[winnable_index].second << std::endl;
			actions_taken_result->push_back(get_action(actions_taken[winnable_index].second));
			winnable_index = actions_taken[winnable_index].first;
		}
	}

	return win;
}
