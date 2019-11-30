//=============================================================================
// Andres Imperial
// CS_5460
//=============================================================================
#include <vector>
#include <stdexcept>
#include <string> 
#include <iostream>
#include <climits>

#include "sql_scanner.hpp"

namespace sql = sql_scanner;

int main(int argc, char *argv[])
{
    std::string username;
    std::string password;
    std::string itemName;
    std::vector<std::string> alerts = {};

    if (argc == 3)
    {
        // store command line arguments
        username = argv[1];
        password = argv[2];
    }
    else if (argc == 2)
    {
        // store command line arguments
        itemName = argv[1];
    }
    else
    {
        int userChoice;
        printf("Do you want to use login query(1) or item query(2)? ");
        std::cin >> userChoice;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        if (userChoice == 1)
        {
            // Query user for arguments
            printf("Enter username:");
            std::getline(std::cin, username);
            printf("Enter password:");
            std::getline(std::cin, password);
        }
        else if (userChoice == 2)
        {
            printf("Enter Item:");
            std::getline(std::cin, itemName);
        }
    }

    // Send sql arguments to be tested
    if (itemName.empty())
    {
        sql::SqlReport report = sql::scanSql(username, password);
        // Print findings
        report.print();
    }
    else
    {
        sql::SqlReport report = sql::scanSql(itemName);
        // Print findings
        report.print();
    }
    
    return 0;
}
