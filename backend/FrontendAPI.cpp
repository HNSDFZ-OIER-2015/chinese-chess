//
// Copyright 2016 HNSDFZ-OIER
//

#include "FrontendAPI.hpp"
#include "PythonAPI.hpp"

std::queue<EventPointer> event_queue;

static ChessDataType data;

void Initialize() {
    data.resize(10);
    for (auto &line : data) {
        line.resize(9);
    }  // foreach in data
}

void Terminate() {
    data.clear();
}

auto HasEvents() -> bool {
    return not event_queue.empty();
}

auto PollEvent() -> EventPointer {
    EventPointer ptr = std::move(event_queue.front());
    event_queue.pop();

    return std::move(ptr);
}

auto GetChessData() -> ChessDataType & {
    return data;
}

auto GetChess(const int x, const int y) -> ChessType {
    return data[x - 1][y - 1];
}

void SetChess(const int x, const int y, const ChessType chess) {
    data[x - 1][y - 1] = chess;
}

void MoveChess(const int from_x, const int from_y, const int to_x,
               const int to_y) {
    SetChess(to_x, to_y, GetChess(from_x, from_y));
    SetChess(from_x, from_y, ChessType::None);
}

auto GetPlacable(const int /*x*/, const int /*y*/) -> std::vector<Point> {
    // TODO: Fixed it.
}
