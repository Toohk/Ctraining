#include "../../include/DBManager.h"
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>
#include "../../include/Task.h"
#include "../../include/Board.h"
#include <sstream>
#include <optional>

// Fonction d'assistance pour joindre un vector<string> en une seule string
std::string join(const std::vector<std::string>& vec, const std::string& delim) {
    std::string result;
    for (const auto& str : vec) {
        if (!result.empty()) {
            result += delim;
        }
        result += str;
    }
    return result;
}


bool createDatabase(){
    sqlite3* db;
    int rc = sqlite3_open("task_manager.db", &db);

    if(rc) {
        std::cerr << "Erreur lors de l'ouverture de la base de données : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    char* errMsg = 0;
    const char* sql = "CREATE TABLE IF NOT EXISTS Boards("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "name TEXT NOT NULL,"
                      "columns TEXT NOT NULL"
                      ");"
                      "CREATE TABLE IF NOT EXISTS Tasks("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "board_id INTEGER,"
                      "title TEXT,"
                      "description TEXT,"
                      "status TEXT,"
                      "creationDate TEXT,"
                      "dueDate TEXT,"
                      "FOREIGN KEY(board_id) REFERENCES Boards(id)"
                      ");";

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if(rc) {
        std::cerr << "Erreur SQL : " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return false;
    }

    rc = sqlite3_close(db);
    if(rc) {
        std::cerr << "Erreur lors de la fermeture de la base de données : " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    return true;
}

bool insertBoard(const Board& board){
    sqlite3* db;
    int rc = sqlite3_open("task_manager.db", &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de l'ouverture de la base de données : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    std::string sql = "INSERT INTO Boards (name, columns) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de préparation de la requête SQL : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    // Convertir le vector<string> en une seule string séparée par des virgules
    std::string columnsStr = join(board.getColumns(), ", ");

    sqlite3_bind_text(stmt, 1, board.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, columnsStr.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Erreur d'insertion : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}



std::vector<std::string> deserializeColumns(const std::string& columnsStr) {
    std::vector<std::string> columns;
    std::stringstream ss(columnsStr);
    std::string column;
    
    while (std::getline(ss, column, ',')) {
        columns.push_back(column);
    }
    
    return columns;
}


std::vector<Board> listBoards() {
    sqlite3* db;
    std::vector<Board> boards;
    int rc;

    rc = sqlite3_open("task_manager.db", &db);
    if(rc) {
        std::cerr << "Erreur lors de l'ouverture de la base de données : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return boards; // Retourne un vecteur vide en cas d'erreur
    }

    const char* sql = "SELECT id, name, columns FROM Boards;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de préparation de la requête SQL : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return boards;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string columnsStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        
        std::vector<std::string> columns = deserializeColumns(columnsStr);
        
        // Ajout des tâches ici (actuellement vide)
        std::vector<Task> tasks; 
        
        boards.push_back(Board(id, name, columns, tasks));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return boards;
}

std::optional<Board> selectBoard(int id) {
    sqlite3* db;
    int rc = sqlite3_open("task_manager.db", &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de l'ouverture de la base de données : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return std::nullopt;
    }

    const char* sql = "SELECT id, name, columns FROM Boards WHERE id = ?;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur de préparation de la requête SQL : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return std::nullopt;
    }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string columnsStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        
        std::vector<std::string> columns = deserializeColumns(columnsStr);
        
        // Ajout des tâches ici (actuellement vide)
        std::vector<Task> tasks; 
        
        Board board(id, name, columns, tasks);
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return board;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return std::nullopt;
}

bool insertTask(const Task &task){
    return true;
}


