//=============================================================================
// Andres Imperial
// CS_5460
//=============================================================================
#include <vector>
#include <stdexcept>
#include <string> 
#include <iostream>
#include <bits/stdc++.h>

#include "email_scanner.hpp"

namespace es = email_scanner;

int main(int argc, char *argv[])
{
    std::string emailID;
    std::string emailBody;
    std::vector<std::string> alerts = {};

    if (argc != 3)
    {
        // Query user for arguments
        printf("Enter emailer's ID:");
        std::getline(std::cin, emailID);
        std::transform(emailID.begin(), emailID.end(), emailID.begin(), ::tolower);
        printf("Enter email's body:");
        std::getline(std::cin, emailBody);
        std::transform(emailBody.begin(), emailBody.end(), emailBody.begin(), ::tolower);
    }
    else
    {
        // store command line arguments
        emailID = argv[1];
        emailBody = argv[2];
    }

    // Send email arguments to be tested
    es::EmailReport report = es::scanEmail(emailID, emailBody);

    // Print findings
    report.print();

    return 0;
}
