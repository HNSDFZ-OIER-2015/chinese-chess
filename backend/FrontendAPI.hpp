//
// Copyright 2016 HNSDFZ-OIER
//

#include <vector>
#include <queue>
#include <memory>
#include <utility>

#include "Events.hpp"

#ifndef BACKEND_FRONTEND_API_HPP_
#define BACKEND_FRONTEND_API_HPP_

///////////////////////////////////
// Initialization & finalization //
///////////////////////////////////

void Initialize();
void Terminate();

//////////////////////
// Event processing //
//////////////////////

typedef std::unique_ptr<IEvent> EventPointer;

extern std::queue<EventPointer> event_queue;

auto HasEvents() -> bool;
auto PollEvent() -> EventPointer;

template <typename TEvent, typename... Args>
void PushEvent(const Args &... args) {
    EventPointer ptr = EventPointer(new TEvent(args...));
    event_queue.push(std::move(ptr));
}

//////////////////////
// Game controlling //
//////////////////////

enum class ChessType {
    None,  // TODO: fill here
};         // enum class ChessType

struct Point {
    int x;
    int y;
};  // struct Point

typedef std::vector<std::vector<ChessType>> ChessDataType;

auto GetChessData() -> ChessDataType &;
auto GetChess(const int x, const int y) -> ChessType;
void SetChess(const int x, const int y, const ChessType chess);

void MoveChess(const int from_x, const int from_y, const int to_x,
               const int to_y);
auto GetPlacable(const int x, const int y) -> std::vector<Point>;

#endif  // BACKEND_FRONTEND_API_HPP_
