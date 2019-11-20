//=============================================================================
// Andres Imperial
// CS_5460
//=============================================================================

#include <string>
#include "sql_scanner.hpp"

namespace sql_scanner
{
    SqlReport::SqlReport(std::string username, std::string password)
        : m_username(username), m_password(password)
    {
    }

    void SqlReport::print(void)
    {
        printf("This sql has a %i%% chance of being a malicious sql.\n", getScore());

        if (m_score > 0)
        {
            printf("The following reason(s) attributed to this sql's malicious score:\n");
            int counter{1};
            for(auto alert : m_alerts)
            {
                printf("%i: %s\n", counter, alert.c_str()); 
                ++ counter;
            }
        }
    }

    void SqlReport::scan(void)
    {
        // Run sql through tests and build score for it.
        sampleTest();
    }

    bool SqlReport::sampleTest(void)
    {
        if (m_username.find("scam") != std::string::npos)
        {
            ++m_score;
            m_alerts.push_back("Username contains word 'scam'.\n");
            return true;
        }

        return false;
    }

    SqlReport scanSql(std::string username, std::string password)
    {
        SqlReport report(username, password);

        report.scan();

        return report;
    }
}
