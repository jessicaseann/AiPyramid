#include "action.hpp"
#include "pyramid.hpp"

#include <utility>
#include <vector>
#include <cassert>

int get_action_value(const std::pair<int, std::vector<int> > &action) {
	int row, col, position;
	int action_value;
	// 3 last bit is the action number (ACTION CONSTANT - 1)
	action_value = action.first - 1;
//	std::cout << action.first;
	switch(action.first) {
		case Pyramid::ACTION_DRAW:
		case Pyramid::ACTION_REMOVE_KING_ON_DECK:
		case Pyramid::ACTION_REMOVE_KING_ON_WASTE:
		case Pyramid::ACTION_PAIR_CARD_DECK_WASTE:
			break;
		case Pyramid::ACTION_PAIR_CARDS_PYRAMID:
			assert(action.second.size() == 4);
			// next 6 bits contain first position of card (row, col)
			row = action.second[0];
			col = action.second[1];
			position = (row << 3) + col;
			action_value += (position << ACTION_NUMBER_BIT);
//			std::cout << ": (" << row << "," << col << "), ";
			// next 6 bits contain second position of card (row, col)
			row = action.second[2];
			col = action.second[3];
			position = (row << 3) + col;
			action_value += (position << (ACTION_NUMBER_BIT + ACTION_POSITION_BIT));
//			std::cout << "(" << row << "," << col << ") ";
			break;
		case Pyramid::ACTION_REMOVE_KING_IN_PYRAMID:
		case Pyramid::ACTION_PAIR_CARD_PYRAMID_DECK:
		case Pyramid::ACTION_PAIR_CARD_PYRAMID_WASTE:
			assert(action.second.size() == 2);
			// next 6 bits contain the position of card (row, col)
			row = action.second[0];
			col = action.second[1];
			position = (row << 3) + col;
			action_value += (position << ACTION_NUMBER_BIT);
//			std::cout << ": (" << row << "," << col << ") ";
			break;
		default: break;
	}
//	std::cout << std::endl;
//	for(int i=31; i>=0; i--) std::cout << ((action_value >> i) & 1);
//	std::cout << std::endl;
	return action_value;
}

std::pair<int, std::vector<int> > get_action(const int &action) {
	std::pair<int, std::vector<int> > action_value;
	int action_number = (action & ((1 << ACTION_NUMBER_BIT) - 1)) + 1;
//	std::cout << "ACTION: " << action_number << " | ";
	action_value.first = action_number;
	int position, row, col;
	switch(action_number) {
		case Pyramid::ACTION_DRAW:
		case Pyramid::ACTION_REMOVE_KING_ON_DECK:
		case Pyramid::ACTION_REMOVE_KING_ON_WASTE:
		case Pyramid::ACTION_PAIR_CARD_DECK_WASTE:
			break;
		case Pyramid::ACTION_PAIR_CARDS_PYRAMID:
			// next 6 bits contain first position of card (row, col)
			position = ((1 << ACTION_POSITION_BIT) - 1) & (action >> ACTION_NUMBER_BIT);
			row = position >> 3;
			col = position & 7;
//			std::cout << "(" << row << "," << col << ") ";
			action_value.second.push_back(row);
			action_value.second.push_back(col);
			// next 6 bits contain second position of card (row, col)
			position = ((1 << ACTION_POSITION_BIT) - 1) & (action >> (ACTION_NUMBER_BIT + ACTION_POSITION_BIT));
			row = position >> 3;
			col = position & 7;
//			std::cout << "(" << row << "," << col << ") ";
			action_value.second.push_back(row);
			action_value.second.push_back(col);
			break;
		case Pyramid::ACTION_REMOVE_KING_IN_PYRAMID:
		case Pyramid::ACTION_PAIR_CARD_PYRAMID_DECK:
		case Pyramid::ACTION_PAIR_CARD_PYRAMID_WASTE:
			// next 6 bits contain the position of card (row, col)
			position = ((1 << ACTION_POSITION_BIT) - 1) & (action >> ACTION_NUMBER_BIT);
			row = position >> 3;
			col = position & 7;
//			std::cout << "(" << row << "," << col << ") ";
			action_value.second.push_back(row);
			action_value.second.push_back(col);
			break;
		default: break;
	}
//	std::cout << std::endl;
	return action_value;
}