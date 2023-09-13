#include "../../include/Task.h"
#include <chrono>
#include <string>

Task::Task (
    const std::string& title,
    const std::string& description,
    const std::string& status,
    const std::chrono::system_clock::time_point& creationDate,
    const std::chrono::system_clock::time_point& dueDate
    ): title(title), description(description), status(status), creationDate(creationDate), dueDate(dueDate) {}


int Task::getId() const {
    return id;
}
void Task::setId(int newId){
    id = newId;
}

std::string Task::getTitle() const {
    return title;
}
void Task::setTitle(const std::string& newTitle) {
    title = newTitle;
}

std::string Task::getDescription() const{
    return description;
}
void Task::setDescription(const std::string& newDescription){
    description = newDescription;
}

std::string Task::getStatus() const{
    return status;
}
void Task::setStatus(const std::string& newStatus){
    status = newStatus;
}

std::chrono::system_clock::time_point Task::getCreationDate() const{
    return creationDate;
}
void Task::setCreationDate(const std::chrono::system_clock::time_point& newCreationDate){
    creationDate = newCreationDate;
}

std::chrono::system_clock::time_point Task::getDueDate() const{
    return dueDate;
}
void Task::setDueDate(const std::chrono::system_clock::time_point& newDueDate){
    dueDate = newDueDate;
}



