#ifndef __STATE__
#define __STATE__

#include <iostream>

struct State {
	static const int NO_DRAW_DECK_INDEX = -200;
	int pyramid_mask;
	int deck_waste_mask;
	int top_deck_index;
	int top_waste_index;
	int total_reset_deck_count;
	int value;
	int draw_deck_index;
	int current_index;
	
	State() {
		draw_deck_index = NO_DRAW_DECK_INDEX;
		current_index = -1;
	}
	State(const State &state) {
		pyramid_mask = state.pyramid_mask;
		deck_waste_mask = state.deck_waste_mask;
		top_deck_index = state.top_deck_index;
		top_waste_index = state.top_waste_index;
		total_reset_deck_count = state.total_reset_deck_count;
		draw_deck_index = state.draw_deck_index;
		current_index = state.current_index;
		recalculate();
	}
	
	friend inline bool operator<(const State &a, const State &b) {
		return (a.value < b.value) ||
		(a.value == b.value && a.top_deck_index < b.top_deck_index) ||
		(a.value == b.value && a.top_deck_index == b.top_deck_index && a.top_waste_index < b.top_waste_index) ||
		(a.value == b.value && a.top_deck_index == b.top_deck_index && !(a.top_waste_index < b.top_waste_index) && a.total_reset_deck_count < b.total_reset_deck_count) ||
		(a.value == b.value && a.top_deck_index == b.top_deck_index && a.top_waste_index == b.top_waste_index && a.total_reset_deck_count == b.total_reset_deck_count && a.pyramid_mask < b.pyramid_mask) ||
		(a.value == b.value && a.top_deck_index == b.top_deck_index && a.top_waste_index == b.top_waste_index && a.total_reset_deck_count == b.total_reset_deck_count && a.pyramid_mask == b.pyramid_mask && a.deck_waste_mask < b.deck_waste_mask) ||
		(a.value == b.value && a.top_deck_index == b.top_deck_index && a.top_waste_index == b.top_waste_index && a.total_reset_deck_count == b.total_reset_deck_count && a.pyramid_mask == b.pyramid_mask && a.deck_waste_mask == b.deck_waste_mask && a.draw_deck_index < b.draw_deck_index);
	}
	
	friend inline bool operator==(const State &a, const State &b) {
		return a.value == b.value && a.pyramid_mask == b.pyramid_mask && a.deck_waste_mask == b.deck_waste_mask && a.top_deck_index == b.top_deck_index && a.top_waste_index == b.top_waste_index && a.total_reset_deck_count == b.total_reset_deck_count && a.draw_deck_index == b.draw_deck_index;
	}
	
	friend inline bool operator!=(const State &a, const State &b) {
		return !operator==(a, b);
	}
	
	friend inline bool operator>(const State &a, const State &b) {
		return operator<(b, a);
	}
	
	friend inline bool operator<=(const State &a, const State &b) {
		return !operator>(a, b);
	}

	friend inline bool operator>=(const State &a, const State &b) {
		return !operator<(a, b);
	}
	
	void recalculate() {
		int temporary = pyramid_mask;
		value = 0;
		while(temporary > 0) {
			value += temporary & 1;
			temporary >>= 1;
		}
	}
	
	void print() {
		std::cout << "value: " << value << " | " << top_deck_index << " | " << top_waste_index << " | " << total_reset_deck_count << " | " << pyramid_mask << " | " << deck_waste_mask << " | " << draw_deck_index << std::endl;
	}
};

struct ValueStateComparator {
	bool operator() (const State &a, const State &b) const {
		return a > b;
	}
};

#endif
