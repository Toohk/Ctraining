#include "../../include/Board.h"
#include "../../include/Task.h"
#include <algorithm>
#include <chrono>
#include <string>
#include <vector>

Board::Board(
        int id,
        const std::string& name, 
        const std::vector<std::string>& columns, 
        const std::vector<Task>& tasks
        ): id(id), name(name), columns(columns), tasks(tasks) {}


int Board::getId() const {
    return id;
}
void Board::setId(int newId){
    id = newId;
}

std::string Board::getName() const{
    return name;
}
void Board::setName(const std::string& newName){
    name = newName;
}


std::vector<std::string> Board::getColumns() const {
    return columns;
}
void Board::setColumns(const std::vector<std::string>& newColumns){
    columns = newColumns;
}

std::vector<Task> Board::getTasks() const{
    return tasks;
}
void Board::setTasks(const std::vector<Task>& newTasks){
    tasks = newTasks;
}

void Board::addTask(const Task& newTask){
    tasks.push_back(newTask);
}

void Board::updateTask(int id, const std::string& newTitle, const std::string& newDescription, const std::chrono::system_clock::time_point& newDueDate){
    for(auto& task : tasks){ 
        if(task.getId() == id){
            task.setTitle(newTitle);
            task.setDescription(newDescription);
            task.setDueDate(newDueDate);
            return;
        }
    }
}

void Board::updateStatusTask(int id, const std::string& newStatus){
  for(auto& task : tasks){ 
        if(task.getId() == id){
            task.setStatus(newStatus);
            return;
        }
    }

}

void Board::removeTask(int id){
    auto it = std::remove_if(
            tasks.begin(), 
            tasks.end(),
            [&id](const Task& task){
                return task.getId() == id;
            }
        );
    if (it != tasks.end()){
        tasks.erase(it, tasks.end());
    }
}

