//
// Copyright 2016 HNSDFZ-OIER
//

#include "Events.hpp"

IEvent::IEvent() : type(EventType::NullEvent) {}
IEvent::~IEvent() = default;

MoveEvent::MoveEvent() : type(EventType::MoveEvent) {}
MoveEvent::MoveEvent(int _x, int _y, int x, int y)
        : type(EventType::MoveEvent)
        , from_x(_x)
        , from_y(_y)
        , to_x(x)
        , to_y(y) {}
MoveEvent::~MoveEvent() = default;

RequestEvent::RequestEvent() : type(EventType::RequestEvent) {}
RequestEvent::~RequestEvent() = default;
