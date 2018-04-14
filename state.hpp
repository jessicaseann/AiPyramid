#ifndef __STATE__
#define __STATE__

struct State {
	int pyramid_mask;
	int deck_waste_mask;
	int top_deck_index;
	int top_waste_index;
	int total_reset_deck_count;
	
	State() {}
	State(const State &state) {
		pyramid_mask = state.pyramid_mask;
		deck_waste_mask = state.deck_waste_mask;
		top_deck_index = state.top_deck_index;
		top_waste_index = state.top_waste_index;
		total_reset_deck_count = state.total_reset_deck_count;
	}
};

#endif

