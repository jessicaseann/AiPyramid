#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <cassert>
#include "pyramid.hpp"
#include "bfs_pyramid.hpp"
using namespace std;

void print_game(Pyramid *pyramid);
void print_rule();
void user_input_command(Pyramid *pyramid);
void print_all_valid_moves(Pyramid *pyramid);
void print_action(pair<int, vector<int> > action);

int main() {
	int cards[Pyramid::TOTAL_CARDS];
	cout << "Input pyramid and deck: " << endl;
	for(int i = 0; i < Pyramid::TOTAL_CARDS; i++) cin >> cards[i];

	Pyramid pyramid(cards);
	vector< pair<int, vector<int> > > actions_taken;
	BFSPyramid solver;
	bool solvable = solver.bfs(&pyramid, &actions_taken);

	if(solvable) {
		cout << "SOLVABLE" << endl;
		for(int i = actions_taken.size() - 1; i >= 0; i--) {
			cout << "ACTION #" << actions_taken.size() - i << ":" << endl;
			print_action(actions_taken[i]);
			cout << endl;
		}
	} else {
		cout << "Impossible to solve" << endl;
	}
	
	print_game(&pyramid);

/*	while(!pyramid.is_finished()) {
		cout << solvable << " = " << (solvable? "CAN WIN" : "IMPOSSIBLE") << endl;
		print_game(&pyramid);
		print_rule();
		cout << "RECOMMENDATIONS:" << endl;
		print_all_valid_moves(&pyramid);
		user_input_command(&pyramid);
		cin.get();
		cin.get();
		system("cls");
	}
*/
	return 0;
}

void print_game(Pyramid *pyramid) {
	char * pyramid_cards = pyramid->get_pyramid();
	int level = 1;
	cout << level << " : ";
	for(int i=0; i<Pyramid::TOTAL_PYRAMID_CARDS; i++) {
		cout << pyramid_cards[i] << " ";
		if(i + 1 == level * (level + 1) / 2) {
			cout << endl;
			level++;
			if(level < 8) cout << level << " : ";
		}
	}
	
	cout << "Top deck: " << pyramid->get_top_deck_card() << endl;
	cout << "Top waste: " << pyramid->get_top_waste_card() << endl;
	free(pyramid_cards);
}

void print_rule() {
	//------------------------------------------------//
	// Rule:                                          //
	// Read 1 string to know the command.             //
	// Retrieve input for specific command            //
	//------------------------------------------------//
	// Command:                                       //
	// 1. D - Draw                                    //
	// 2. RKP - Remove king in pyramid                //
	// 3. RKTD - Remove king on top of deck           //
	// 4. RKTW - Remove king on top of waste          //
	// 5. PP - Pair 2 cards in pyramid                //
	// 6. PTD - Pair card in pyramid with top deck    //
	// 7. PTW - Pair card in pyramid with top waste   //
	// 8. PTDW - Pair card on top deck with top waste //
	//------------------------------------------------//

	cout << "+------------------------------------------------+" << endl;
	cout << "| Rule:                                          |" << endl;
	cout << "| Read 1 string to know the command.             |" << endl;
	cout << "| Retrieve input for specific command            |" << endl;
	cout << "+------------------------------------------------+" << endl;
	cout << "| Command:                                       |" << endl;
	cout << "| 1. Draw                                        |" << endl;
	cout << "| 2. Remove king in pyramid                      |" << endl;
	cout << "| 3. Remove king on top of deck                  |" << endl;
	cout << "| 4. Remove king on top of waste                 |" << endl;
	cout << "| 5. Pair 2 cards in pyramid                     |" << endl;
	cout << "| 6. Pair card in pyramid with top deck          |" << endl;
	cout << "| 7. Pair card in pyramid with top waste         |" << endl;
	cout << "| 8. Pair card on top deck with top waste        |" << endl;
	cout << "|                                                |" << endl;
	cout << "| # Enter -1 in row and column to change command |" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void user_input_command(Pyramid *pyramid) {
	int command;
	cout << "Please input command number in range of 1 to 8:" << endl;
	cin >> command;

	switch(command) {
		case 1: {
			cout << "Draw" << endl;
			pyramid->draw_deck();
			break;
		}
		case 2: {
			int r, c;
			cout << "Remove king in pyramid" << endl;
			cout << "Enter row: "; cin >> r;
			cout << "Enter column: "; cin >> c;
			while(!(r == -1 && c == -1) && !pyramid->remove_king(r, c)) {
				cout << "Wrong input, please input again!" << endl;
				cout << "Enter row: "; cin >> r;
				cout << "Enter column: "; cin >> c;
			}
			break;
		}
		case 3: {
			cout << "Remove king on top of deck" << endl;
			if(!pyramid->remove_king_from_deck()) {
				cout << "Top of the deck is not King." << endl;
			}
			break;
		}
		case 4: {
			cout << "Remove king on top of waste" << endl;
			if(!pyramid->remove_king_from_waste()) {
				cout << "Top of the waste is not King." << endl;
			}
			break;
		}
		case 5: {
			int r1, r2, c1, c2;
			cout << "Pair 2 cards in pyramid" << endl;
			cout << "Enter first row: "; cin >> r1;
			cout << "Enter first column: "; cin >> c1;
			cout << "Enter first row: "; cin >> r2;
			cout << "Enter first column: "; cin >> c2;
			while(!(r1 == -1 && c1 == -1) && !pyramid->pair_cards_in_pyramid(r1, c1, r2, c2)) {
				cout << "Wrong input, please input again!" << endl;
				cout << "Enter first row: "; cin >> r1;
				cout << "Enter first column: "; cin >> c1;
				cout << "Enter first row: "; cin >> r2;
				cout << "Enter first column: "; cin >> c2;
			}
			break;
		}
		case 6: {
			int r, c;
			cout << "Pair card in pyramid with top deck" << endl;
			cout << "Enter row: "; cin >> r;
			cout << "Enter column: "; cin >> c;
			while(!(r == -1 && c == -1) && !pyramid->pair_cards_deck_and_pyramid(r, c)) {
				cout << "Wrong input, please input again!" << endl;
				cout << "Enter row: "; cin >> r;
				cout << "Enter column: "; cin >> c;
			}
			break;
		}
		case 7: {
			int r, c;
			cout << "Pair card in pyramid with top waste" << endl;
			cout << "Enter row: "; cin >> r;
			cout << "Enter column: "; cin >> c;
			while(!(r == -1 && c == -1) && !pyramid->pair_cards_waste_and_pyramid(r, c)) {
				cout << "Wrong input, please input again!" << endl;
				cout << "Enter row: "; cin >> r;
				cout << "Enter column: "; cin >> c;
			}
			break;
		}
		case 8: {
			cout << "Pair card on top deck with top waste" << endl;
			if(!pyramid->pair_cards_deck_and_waste()) {
				cout << "Sum of top of the waste and top of the deck is not 13." << endl;
			}
			break;
		}
		default: {
			cout << "Wrong command number. Please input a number in range 1 - 8" << endl;
		}
	}
}

void print_all_valid_moves(Pyramid *pyramid) {
	vector< pair<int, vector<int> > > moves = pyramid->get_all_possible_actions();
	vector< pair<int, vector<int> > >::iterator it;
	for(it = moves.begin(); it != moves.end(); it++) {
		cout << "- ";
		switch(it->first) {
			case Pyramid::ACTION_DRAW:
				assert(it->second.size() == 0);
				cout << "(1) Draw" << endl;
				break;
			case Pyramid::ACTION_REMOVE_KING_IN_PYRAMID:
				assert(it->second.size() == 2);
				cout << "(2) Remove king in pyramid\n  === row: " << it->second[0] << ", col: " << it->second[1] << endl;
				break;
			case Pyramid::ACTION_REMOVE_KING_ON_DECK:
				assert(it->second.size() == 0);
				cout << "(3) Remove king on top of deck" << endl;
				break;
			case Pyramid::ACTION_REMOVE_KING_ON_WASTE:
				assert(it->second.size() == 0);
				cout << "(4) Remove king on top of waste" << endl;
				break;
			case Pyramid::ACTION_PAIR_CARDS_PYRAMID:
				assert(it->second.size() == 4);
				cout << "(5) Pair cards in pyramid | row1: " << it->second[0] << ", col1: " << it->second[1] << endl;
				cout << "                            | row2: " << it->second[2] << ", col2: " << it->second[3] << endl;
				break;
			case Pyramid::ACTION_PAIR_CARD_PYRAMID_DECK:
				assert(it->second.size() == 2);
				cout << "(6) Pair card in pyramid with top of deck\n  === row: " << it->second[0] << ", col: " << it->second[1] << endl;
				break;
			case Pyramid::ACTION_PAIR_CARD_PYRAMID_WASTE:
				assert(it->second.size() == 2);
				cout << "(7) Pair card in pyramid with top of waste\n  === row: " << it->second[0] << ", col: " << it->second[1] << endl;
				break;
			case Pyramid::ACTION_PAIR_CARD_DECK_WASTE:
				assert(it->second.size() == 0);
				cout << "(8) Pair card on top of deck with top of waste" << endl;
				break;
			default: break;
		}
	}
}

void print_action(pair<int, vector<int> > action) {
	switch(action.first) {
		case Pyramid::ACTION_DRAW:
			assert(action.second.size() == 0);
			cout << "(1) Draw" << endl;
			break;
		case Pyramid::ACTION_REMOVE_KING_IN_PYRAMID:
			assert(action.second.size() == 2);
			cout << "(2) Remove king in pyramid\n  === row: " << action.second[0] << ", col: " << action.second[1] << endl;
			break;
		case Pyramid::ACTION_REMOVE_KING_ON_DECK:
			assert(action.second.size() == 0);
			cout << "(3) Remove king on top of deck" << endl;
			break;
		case Pyramid::ACTION_REMOVE_KING_ON_WASTE:
			assert(action.second.size() == 0);
			cout << "(4) Remove king on top of waste" << endl;
			break;
		case Pyramid::ACTION_PAIR_CARDS_PYRAMID:
			assert(action.second.size() == 4);
			cout << "(5) Pair cards in pyramid | row1: " << action.second[0] << ", col1: " << action.second[1] << endl;
			cout << "                          | row2: " << action.second[2] << ", col2: " << action.second[3] << endl;
			break;
		case Pyramid::ACTION_PAIR_CARD_PYRAMID_DECK:
			assert(action.second.size() == 2);
			cout << "(6) Pair card in pyramid with top of deck\n=== row: " << action.second[0] << ", col: " << action.second[1] << endl;
			break;
		case Pyramid::ACTION_PAIR_CARD_PYRAMID_WASTE:
			assert(action.second.size() == 2);
			cout << "(7) Pair card in pyramid with top of waste\n=== row: " << action.second[0] << ", col: " << action.second[1] << endl;
			break;
		case Pyramid::ACTION_PAIR_CARD_DECK_WASTE:
			assert(action.second.size() == 0);
			cout << "(8) Pair card on top of deck with top of waste" << endl;
			break;
		default: break;
	}
}
