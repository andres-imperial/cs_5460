//=============================================================================
// Andres Imperial
// CS_5460
//=============================================================================
#include <vector>
#include <stdexcept>
#include <string> 
#include <iostream>

#include "sql_scanner.hpp"

namespace sql = sql_scanner;

int main(int argc, char *argv[])
{
    std::string username;
    std::string password;
    std::vector<std::string> alerts = {};

    if (argc == 3)
    {
        // store command line arguments
        username = argv[1];
        password = argv[2];
    }
    else
    {
        // Query user for arguments
        printf("Enter username:");
        std::getline(std::cin, username);
        printf("Enter password:");
        std::getline(std::cin, password);
    }

    // Send sql arguments to be tested
    sql::SqlReport report = sql::scanSql(username, password);

    // Print findings
    report.print();

    return 0;
}
