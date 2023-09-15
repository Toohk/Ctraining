#include "../../include/commands.h"
#include "../../include/Task.h"
#include "../../include/Board.h"
#include "../../include/DBManager.h"
#include <iomanip>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>

void cmd_quit() {
    std::cout << "Quitting...\n";
    exit(0);
}

void cmd_help() {
    std::cout << "Available commands: quit, help\n";
}

void cmd_unknown(const std::string& cmd) {
    std::cout << "Commande inconnue: " << cmd << "\n";
}

void cmd_create_board(){
std::string name;
    std::string columnsInput;
    std::vector<std::string> columns;

    std::cout << "\033[32mEnter Board Name:\033[0m ";
    std::getline(std::cin, name);

    std::cout << "\033[32mEnter Columns (separated by commas):\033[0m ";
    std::getline(std::cin, columnsInput);

    // Splitting the columns input string by commas and adding them to the columns vector
    std::istringstream ss(columnsInput);
    std::string column;
    while(std::getline(ss, column, ',')) {
        columns.push_back(column);
    }

    // Creating an empty tasks vector as we are just creating the board now
    std::vector<Task> tasks;

    // Creating a new Board instance
    Board newBoard(0 ,name, columns, tasks);

    // Inserting the new Board into the database
    if(insertBoard(newBoard)) {
        std::cout << "\033[34mBoard created successfully!\033[0m\n";
    } else {
        std::cout << "\033[31mFailed to create board.\033[0m\n";
    }
}

void cmd_list_boards() {
    std::vector<Board> boards = listBoards();

    if (!boards.empty()) {
        for (const auto& board : boards) {
            std::cout << "ID: " << board.getId() << ", Name: " << board.getName() << ", Columns: ";
            for (const auto& column : board.getColumns()) {
                std::cout << column << ", ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cerr << "Erreur lors de la récupération de la liste des boards ou liste vide.\n";
    }
}

void cmd_update_board(){
    return;
}

void cmd_delete_board(){
    return;
}

void cmd_select_board(){
    return;
}


void cmd_add_task() {
    std::string title;
    std::string description;
    std::string dueDateStr;
    
    std::cout << "\033[32mEnter Title :\033[0m ";
    std::getline(std::cin, title);

    std::cout << "\033[32mEnter a description :\033[0m ";
    std::getline(std::cin, description);

    std::cout << "\033[32mEnter Due Date :\033[0m ";
    std::getline(std::cin, dueDateStr);
   
    std::tm dueDate_tm = {};
    std::istringstream ss(dueDateStr);
    ss >> std::get_time(&dueDate_tm, "%d/%m/%Y");
    if (ss.fail()) {
        std::cerr << "Invalid date format: " << dueDateStr << "\n";
        return;
    }

    // Convert std::tm to std::time_t
    std::time_t dueDate_time_t = std::mktime(&dueDate_tm);

    // Convert std::time_t to std::chrono::system_clock::time_point
    std::chrono::system_clock::time_point newDueDate = std::chrono::system_clock::from_time_t(dueDate_time_t);
    
    Task newTask( title, description, "done", std::chrono::system_clock::now(), newDueDate);
    
    std::cout << "\033[34mTask created\033[0m\n";
}

void run_cli() {
    std::unordered_map<std::string, std::function<void()>> commands;
    commands["quit"] = cmd_quit;
    commands["help"] = cmd_help;
    commands["create"] = cmd_create_board;
    commands["add"] = cmd_add_task;
    commands["list"] = cmd_list_boards;

    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        // Split the input into command and arguments
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        auto it = commands.find(cmd);
        if (it != commands.end()) {
            it->second();
        } else {
            cmd_unknown(command);
        }
    }
}
