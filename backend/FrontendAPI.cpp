//
// Copyright 2016 HNSDFZ-OIER
//

#include "FrontendAPI.hpp"
#include "PythonAPI.hpp"

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
    return not events.empty();
}

auto PollEvent() -> MoveEvent {
    MoveEvent event = events.front();
    events.pop();

    return event;
}

void PushRequestEvent() {
    Request();
}

void PushMoveEvent(int from_x, int from_y, int to_x, int to_y) {
    messages.push(MoveEvent(from_x, from_y, to_x, to_y));
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
