#ifndef BOARD_H
#define BOARD_H

#include "Task.h"
#include <chrono>
#include <cstring>
#include <string>
#include <vector>

class Board {
    private:
        int id;
        std::string name;
        std::vector<std::string> columns;
        std::vector<Task> tasks;

    public:
        Board(
            int id,
            const std::string& name,
            const std::vector<std::string>& columns,
            const std::vector<Task>& tasks
        );
        
        int getId() const;
        void setId(int newId);

        std::string getName() const;
        void setName(const std::string& newName);

        std::vector<Task> getTasks() const;
        void setTasks(const std::vector<Task>& newTasks);

        std::vector<std::string> getColumns() const;
        void setColumns(const std::vector<std::string>& newColumns);
 
        void addTask(const Task& newTask);

        void updateTask(int id, const std::string& newTitle, const std::string& newDescription, const std::chrono::system_clock::time_point& newDueDate);
        
        void removeTask(int id);

        void updateStatusTask(int id, const std::string& newStatus);

};

#endif // !BOARD_H
