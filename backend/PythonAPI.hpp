//
// Copyright 2016 HNSDFZ-OIER
//

#ifndef BACKEND_PYTHON_API_HPP_
#define BACKEND_PYTHON_API_HPP_

#include "Events.hpp"

void Request();
auto PullEvent() -> MoveEvent;

extern "C" {
bool is_requested();
void push_move_event(int from_x, int from_y, int to_x, int to_y);
}

#endif  // BACKEND_PYTHON_API_HPP_
