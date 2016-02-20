//
// Copyright 2016 HNSDFZ-OIER
//

#ifndef BACKEND_EVENTS_HPP_
#define BACKEND_EVENTS_HPP_

enum class EventType {
    NullEvent,
    MoveEvent,
    RequestEvent
};  // enum class EventType

struct IEvent {
    IEvent();
    virtual ~IEvent();

    EventType type;
};  // struct IEvent

struct MoveEvent final : public IEvent {
    MoveEvent();
    MoveEvent(int _x, int _y, int x, int y);
    virtual ~MoveEvent();

    EventType type;
    int from_x;
    int from_y;
    int to_x;
    int to_y;
};  // struct MoveEvent

struct RequestEvent final : public IEvent {
    RequestEvent();
    virtual ~RequestEvent();

    EventType type;
};  // struct RequestEvent

#endif  // BACKEND_EVENTS_HPP_
