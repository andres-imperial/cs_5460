//=============================================================================
// Andres Imperial
// CS_5460
//=============================================================================

#include <string>
#include <algorithm>
#include <iostream>
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
        commentsTest();
        loginBypassTest();
        usernameTautologyTest();
        passwordTautologyTest();
        logicallyIncorrectTest();
        unionTest();
        piggyBackTest();
        storedProceduresTest();
        inferenceTest();
        alternateEncodingTest();
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

    // This test looks for potential injections with comments
     void SqlReport::commentsTest(void)
    {
        std::vector<std::string> keyWords = {"--", "/*", "*/"};
        for (std::string str : keyWords)
        {
            if (m_username.find(str) != std::string::npos)
            {
                ++m_score;
                m_alerts.push_back("Username contains possible sql comment '" + str + "'.\n");
            }
            if (m_password.find(str) != std::string::npos)
            {
            ++m_score;
            m_alerts.push_back("Password contains possible comment '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential login bypass keywords
     void SqlReport::loginBypassTest(void)
    {
        std::vector<std::string> keyWords = {"admin'--", "admin' #", "admin'/*", "' or 1=1--", "' or 1=1#", "' or 1=1/*", "') or '1'='1--", ") or ('1'='1--"};
        for (std::string str : keyWords)
        {
            if(m_username.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Username may contain a bypass login injection '" + str + "'.\n");
            }
            if(m_password.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Password may contain a bypass login injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential tautologies in the username 'x=x' 
    void SqlReport::usernameTautologyTest()
    {
        if (m_username.find("=") != std::string::npos)
        {
            int numEquals = std::count(m_username.begin(), m_username.end(), '=');

            std::string tempUsername = m_username;
            for (int i = 0; i < numEquals; i++)
            {
                size_t found = tempUsername.find("=");
                if(tempUsername[found - 1] == tempUsername[found + 1])
                {
                    //we should only count the score once if a tautology is found but still look for others
                    if (i == 0)
                        ++m_score;
                    std::string tautology = tempUsername.substr((found - 1), 3);
                    m_alerts.push_back("Username contains a tautology '" + tautology + "'.\n");
                }
                std::string smaller = tempUsername.substr(found + 1, tempUsername.length());
                tempUsername = smaller;
            }
        }
    }

    // This test looks for potential tautologies in the password 'x=x' 
    void SqlReport::passwordTautologyTest()
    {
        if (m_password.find("=") != std::string::npos)
        {
            int numEquals = std::count(m_password.begin(), m_password.end(), '=');

            std::string tempPassword = m_password;
            for (int i = 0; i < numEquals; i++)
            {
                size_t found = tempPassword.find("=");
                if(tempPassword[found - 1] == tempPassword[found + 1])
                {
                    //we should only count the score once if a tautology is found but still look for others
                    if (i == 0)
                        ++m_score;
                    std::string tautology = tempPassword.substr((found - 1), 3);
                    m_alerts.push_back("Password contains a tautology '" + tautology + "'.\n");
                }
                std::string smaller = tempPassword.substr(found + 1, tempPassword.length());
                tempPassword = smaller;
            }
        }
    }

    // This test looks for potential illegal/logically incorrect injection keywords 
    void SqlReport::logicallyIncorrectTest()
    {
        std::vector<std::string> keyWords = {"sysobjects", "xtype='u'", "convert"};
        for (std::string str : keyWords)
        {
            if(m_username.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Username may contain illegal or logically incorrect injection '" + str + "'.\n");
            }
            if(m_password.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Password may contain illegal or logically incorrect injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential union injection keywords
    void SqlReport::unionTest()
    {
        std::vector<std::string> keyWords = {"union", "=' '"};
        for (std::string str : keyWords)
        {
            if(m_username.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Username may contain union injection '" + str + "'.\n");
            }
            if(m_password.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Password may contain union injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential piggy-back injection keywords
    void SqlReport::piggyBackTest()
    {
        std::vector<std::string> keyWords = {";drop", "; select", "; alter", "; truncate", "; insert", "; update", "; where", "; delete", "; set", "; values"};
        std::string tempUsername = m_username;
        std::string tempPassword = m_password;
        //remove the spaces for this test only
        tempUsername.erase(remove(tempUsername.begin(), tempUsername.end(), ' '), tempUsername.end());
        tempPassword.erase(remove(tempPassword.begin(), tempPassword.end(), ' '), tempPassword.end());
        for (std::string str : keyWords)
        {
            if(tempUsername.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Username may contain piggy-back injection '" + str + "'.\n");
            }
            if(tempPassword.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Password may contain piggy-back injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential stored procedures injection keywords 
    void SqlReport::storedProceduresTest()
    {
        std::vector<std::string> keyWords = {"exec", "shutdown"};
        for (std::string str : keyWords)
        {
            if(m_username.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Username may contain stored procedure injection '" + str + "'.\n");
            }
            if(m_password.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Password may contain stored procedure injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential inference injection keywords
    void SqlReport::inferenceTest()
    {
        std::vector<std::string> keyWords = {"1=0--", "ascii(substring", "select top 1 name", "X WAITFOR"};
        for (std::string str : keyWords)
        {
            if(m_username.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Username may contain inference injection '" + str + "'.\n");
            }
            if(m_password.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Password may contain inference injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential inference injection keywords
    void SqlReport::alternateEncodingTest()
    {
        std::vector<std::string> keyWords = {"exec(char", "exec(shutdown"};
        for (std::string str : keyWords)
        {
            if(m_username.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Username may contain alternate encoding injection '" + str + "'.\n");
            }
            if(m_password.find(str) != std::string::npos)
            {
                m_score++;
                m_alerts.push_back("Password may contain alternate encoding injection '" + str + "'.\n");
            }
        }
    }

    SqlReport scanSql(std::string username, std::string password)
    {
        SqlReport report(username, password);

        report.scan();

        return report;
    }
}
