//
// Copyright 2016 HNSDFZ-OIER
//

#include <cassert>

#include "PythonAPI.hpp"

std::queue<MoveEvent> events;
std::queue<MoveEvent> messages;

static bool requested = false;

void Request() {
    assert(requested == false);

    requested = true;
}

void PushMoveEvent(int from_x, int from_y, int to_x, int to_y) {
    events.push(MoveEvent(from_x, from_y, to_x, to_y));
}

auto PullEvent() -> MoveEvent {
    MoveEvent event = events.front();
    events.pop();

    return event;
}

bool is_requested() {
    return requested;
}

void fix_request() {
    requested = false;
}

bool has_message() {
    return not messages.empty();
}

void pull_move_event(int *from_x, int *from_y, int *to_x, int *to_y) {
    MoveEvent event = messages.front();
    messages.pop();

    *from_x = event.from_x;
    *from_y = event.from_y;
    *to_x = event.to_x;
    *to_y = event.to_y;
}

void push_move_event(int from_x, int from_y, int to_x, int to_y) {
    PushMoveEvent(from_x, from_y, to_x, to_y);
}
