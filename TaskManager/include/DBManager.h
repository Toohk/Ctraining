#ifndef DBManager
#define DBManager
#include <vector>
#pragma once

#include "Task.h"
#include "Board.h"

bool createDatabase();

bool insertBoard(const Board& board);

bool insertTask(const Task& task);

std::vector<Board> listBoards(); 

#endif // !DBManager
