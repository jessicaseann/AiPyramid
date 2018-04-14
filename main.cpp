#include <iostream>
#include <stdlib.h>
#include "pyramid.hpp"
using namespace std;

void print_game(Pyramid *pyramid);
void print_rule();
void user_input_command(Pyramid *pyramid);

int main() {
	Pyramid pyramid;

	while(true) {
		system("cls");
		print_game(&pyramid);
		print_rule();
		user_input_command(&pyramid);
		cin.get();
		cin.get();
	}

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
	int command2 = pyramid->check_pair();
	cout << "Recommend: "<<command2<<endl;
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
