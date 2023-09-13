#ifndef TASK_H
#define TASK_H

#include <string>
#include <chrono>

class Task {
    private:
        int id;
        std::string title;
        std::string description;
        std::string status;
        std::chrono::system_clock::time_point creationDate;
        std::chrono::system_clock::time_point dueDate;

    public:
        explicit Task(
           const std::string& title,
           const std::string& description,
           const std::string& status,
           const std::chrono::system_clock::time_point& creationDate,
           const std::chrono::system_clock::time_point& dueDate
        );
        
        int getId() const;
        void setId(int newId);
        
        std::string getTitle() const; 
        void setTitle(const std::string& newTitle);
        
        std::string getDescription() const;
        void setDescription(const std::string& newDescription);

        std::string getStatus() const;
        void setStatus(const std::string& newStatus);

        std::chrono::system_clock::time_point getCreationDate() const;
        void setCreationDate(const std::chrono::system_clock::time_point& newCreationDate);
        
        std::chrono::system_clock::time_point getDueDate() const;
        void setDueDate(const std::chrono::system_clock::time_point& newDueDate);
        
};

#endif 
