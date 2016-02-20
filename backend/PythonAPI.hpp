//
// Copyright 2016 HNSDFZ-OIER
//

#ifndef BACKEND_PYTHON_API_HPP_
#define BACKEND_PYTHON_API_HPP_

#include <queue>

#include "Events.hpp"

extern std::queue<MoveEvent> events;
extern std::queue<MoveEvent> messages;

void Request();
void PushMoveEvent(int from_x, int from_y, int to_x, int to_y);
auto PullEvent() -> MoveEvent;

extern "C" {
bool is_requested();
void fix_request();
bool has_message();
void pull_move_event(int *from_x, int *from_y, int *to_x, int *to_y);
void push_move_event(int from_x, int from_y, int to_x, int to_y);
}

#endif  // BACKEND_PYTHON_API_HPP_
