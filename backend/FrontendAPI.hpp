//
// Copyright 2016 HNSDFZ-OIER
//

#include <vector>

#include "Events.hpp"

void Initialize();
void Terminate();

auto HasEvents() -> bool;
auto PollEvent() -> IEvent *;

template <typename... Args>
void PushEvent(const EventType type, const Args &... args);

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
