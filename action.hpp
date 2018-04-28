#ifndef __ACTION__
#define __ACTION__

#include <utility>
#include <vector>

const int ACTION_NUMBER_BIT = 3;
const int ACTION_POSITION_BIT = 6;

int get_action_value(const std::pair<int, std::vector<int> > &action);
std::pair<int, std::vector<int> > get_action(const int &action);

#endif