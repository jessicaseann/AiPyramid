#ifndef __BFS_PYRAMID__
#define __BFS_PYRAMID__

#include "pyramid.hpp"
#include "state.hpp"
#include <queue>

class BFSPyramid
{
	void push_possible_actions(Pyramid *pyramid, std::queue<State> &process_state, State current_state);
	
	public:
	bool bfs(Pyramid *pyramid);
};

#endif