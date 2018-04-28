#ifndef __BFS_PYRAMID__
#define __BFS_PYRAMID__

#include "pyramid.hpp"
#include "state.hpp"
#include <queue>
#include <vector>
#include <utility>
#include <set>

class BFSPyramid
{
	void push_possible_actions(
		Pyramid *pyramid, 
		std::priority_queue<State, std::vector<State>, ValueStateComparator> *process_state, 
		const State &current_state, 
		int index, 
		std::set<State> &visited_state,
		std::vector< std::pair<int, int> > *actions_taken = NULL);
	
	public:
	bool bfs(Pyramid *pyramid, std::vector< std::pair<int, std::vector<int> > > *actions_taken_result = NULL);
};

#endif