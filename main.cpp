#include <iostream>
#include <stdlib.h>
#include "pyramid.hpp"
using namespace std;

void print_rule();
void user_input_command();

int main() {
	Pyramid pyramid;
	char * pyramid_cards = pyramid.get_pyramid();

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

	while(true) {
		system("clear");
		print_rule();
		user_input_command();
		cin.get();
		cin.get();
	}

	free(pyramid_cards);

	return 0;
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
	cout << "+------------------------------------------------+" << endl;
}

void user_input_command() {
	int command;
	cout << "Please input command number in range of 1 to 8:" << endl;
	cin >> command;

	switch(command) {
		case 1:
			cout << "Draw" << endl;
			break;
		case 2:
			cout << "Remove king in pyramid" << endl;
			break;
		case 3:
			cout << "Remove king on top of deck" << endl;
			break;
		case 4:
			cout << "Remove king on top of waste" << endl;
			break;
		case 5:
			cout << "Pair 2 cards in pyramid" << endl;
			break;
		case 6:
			cout << "Pair card in pyramid with top deck" << endl;
			break;
		case 7:
			cout << "Pair card in pyramid with top waste" << endl;
			break;
		case 8:
			cout << "Pair card on top deck with top deck" << endl;
			break;
		default:
			cout << "Wrong command number. Please input a number in range 1 - 8" << endl;
	}
}
