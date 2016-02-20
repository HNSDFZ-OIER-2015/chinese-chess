//
// Copyright 2016 HNSDFZ-OIER
//

#include <cassert>
#include <queue>

#include "PythonAPI.hpp"

static bool requested = false;
static std::queue<MoveEvent> events;

void Request() {
    assert(requested == false);

    requested = true;
}

auto PullEvent() -> MoveEvent {
    MoveEvent event = events.front();
    events.pop();

    return event;
}

bool is_requested() {
    return requested;
}

void push_move_event(int from_x, int from_y, int to_x, int to_y) {
    events.push(MoveEvent(from_x, from_y, to_x, to_y));
}
