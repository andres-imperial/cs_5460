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
    const int LOW = 25;
    const int MED = 50;
    const int HIGH = 100;

    SqlReport::SqlReport(std::string username, std::string password)
        : m_username(username), m_password(password)
    {
    }

    SqlReport::SqlReport(std::string itemName)
        : m_itemName(itemName)
    {      
    }

    void SqlReport::print(void)
    {
        printf("This sql has a score of %i.\n"
               "Score Scale:\n"
               "Low malicious intent 0 - %i\n"
               "Med malicious intent %i - %i\n"
               "High malicious intent %i and greater\n"
               ,m_score,MED, MED, HIGH, HIGH);

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
        if (m_itemName.empty())
        {
            scanLogin();
        }
        else
        {
            scanItem();
        }
    }

    void SqlReport::scanLogin(void)
    {
        sampleTest(m_username, "Username");
        commentsTest(m_username, "Username");
        loginBypassTest(m_username, "Username");
        tautologyTest(m_username, "Username");
        logicallyIncorrectTest(m_username, "Username");
        unionTest(m_username, "Username");
        piggyBackTest(m_username, "Username");
        storedProceduresTest(m_username, "Username");
        inferenceTest(m_username, "Username");
        alternateEncodingTest(m_username, "Username");

        sampleTest(m_password, "Password");
        commentsTest(m_password, "Password");
        loginBypassTest(m_password, "Password");
        tautologyTest(m_password, "Password");
        logicallyIncorrectTest(m_password, "Password");
        unionTest(m_password, "Password");
        piggyBackTest(m_password, "Password");
        storedProceduresTest(m_password, "Password");
        inferenceTest(m_password, "Password");
        alternateEncodingTest(m_password, "Password");
    }

    void SqlReport::scanItem(void)
    {
        sampleTest(m_itemName, "Item name");
        commentsTest(m_itemName, "Item name");
        loginBypassTest(m_itemName, "Item name");
        tautologyTest(m_itemName, "Item name");
        logicallyIncorrectTest(m_itemName, "Item name");
        unionTest(m_itemName, "Item name");
        piggyBackTest(m_itemName, "Item name");
        storedProceduresTest(m_itemName, "Item name");
        inferenceTest(m_itemName, "Item name");
        alternateEncodingTest(m_itemName, "Item name");
    }

    bool SqlReport::sampleTest(const std::string value, const std::string type)
    {
        if (value.find("scam") != std::string::npos)
        {
            m_alerts.push_back(type + " contains word 'scam'.\n");
            return true;
        }

        return false;
    }

    // This test looks for potential injections with comments
     void SqlReport::commentsTest(const std::string value, const std::string type)
    {
        std::vector<std::string> keyWords = {"--", "/*", "*/"};
        for (std::string str : keyWords)
        {
            if (value.find(str) != std::string::npos)
            {
                m_score += MED;
                m_alerts.push_back(type + " contains possible sql comment '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential login bypass keywords
    /*Need to remove spaces in this one*/
     void SqlReport::loginBypassTest(const std::string value, const std::string type)
    {
        std::vector<std::string> keyWords = {"admin'--", "admin' #", "admin'/*", "' or 1=1--", "' or 1=1#", "' or 1=1/*", "') or '1'='1--", ") or ('1'='1--"};
        for (std::string str : keyWords)
        {
            if(value.find(str) != std::string::npos)
            {
                m_score += HIGH;
                m_alerts.push_back(type + " may contain a bypass login injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential tautologies in the username 'x=x' 
    void SqlReport::tautologyTest(const std::string value, const std::string type)
    {
        if (value.find("=") != std::string::npos)
        {
            int numEquals = std::count(value.begin(), value.end(), '=');

            std::string tempValue = value;
            for (int i = 0; i < numEquals; i++)
            {
                size_t found = tempValue.find("=");
                if (found == 0 || found == tempValue.length())
                {
                    return;
                }
                while (tempValue[found -1] == ' ')
                {
                    tempValue.erase(found - 1, 1);
                    --found;
                }
                while (tempValue[found +1] == ' ')
                {
                    tempValue.erase(found + 1, 1);
                }
                if(tempValue[found - 1] == tempValue[found + 1])
                {
                    //we should only count the score once if a tautology is found but still look for others
                    //if (i == 0)
                        m_score += MED;
                    std::string tautology = tempValue.substr((found - 1), 3);
                    m_alerts.push_back(type + " contains a tautology '" + tautology + "'.\n");
                }
                std::string smaller = tempValue.substr(found + 1, tempValue.length() - (found +1));
                tempValue = smaller;
                std::cout << "Smaller: " << smaller << std::endl;
            }
        }
    }

    // This test looks for potential illegal/logically incorrect injection keywords 
    void SqlReport::logicallyIncorrectTest(const std::string value, const std::string type)
    {
        std::vector<std::string> keyWords = {"sysobjects", "xtype='u'", "convert"};
        for (std::string str : keyWords)
        {
            if(value.find(str) != std::string::npos)
            {
                m_score += LOW;
                m_alerts.push_back(type + " may contain illegal or logically incorrect injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential union injection keywords
    void SqlReport::unionTest(const std::string value, const std::string type)
    {
        std::vector<std::string> keyWords = {"union", "=' '"};
        for (std::string str : keyWords)
        {
            if(value.find(str) != std::string::npos)
            {
                m_score += MED;
                m_alerts.push_back(type + " may contain union injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential piggy-back injection keywords
    void SqlReport::piggyBackTest(const std::string value, const std::string type)
    {
        std::vector<std::string> keyWords = {"; drop", "; select", "; alter", "; truncate", "; insert", "; update", "; where", "; delete", "; set", "; values"};
        std::string tempValue = value;
        //remove the spaces for this test only
        tempValue.erase(remove(tempValue.begin(), tempValue.end(), ' '), tempValue.end());
        for (std::string str : keyWords)
        {
            if(tempValue.find(str) != std::string::npos)
            {
                m_score += MED;
                m_alerts.push_back(type + " may contain piggy-back injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential stored procedures injection keywords 
    void SqlReport::storedProceduresTest(const std::string value, const std::string type)
    {
        std::vector<std::string> keyWords = {"exec", "shutdown"};
        for (std::string str : keyWords)
        {
            if(value.find(str) != std::string::npos)
            {
                m_score += HIGH;
                m_alerts.push_back(type + " may contain stored procedure injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential inference injection keywords
    void SqlReport::inferenceTest(const std::string value, const std::string type)
    {
        std::vector<std::string> keyWords = {"1=0--", "ascii(substring", "select top 1 name", "X WAITFOR"};
        for (std::string str : keyWords)
        {
            if(value.find(str) != std::string::npos)
            {
                m_score += LOW;
                m_alerts.push_back(type + " may contain inference injection '" + str + "'.\n");
            }
        }
    }

    // This test looks for potential inference injection keywords
    void SqlReport::alternateEncodingTest(const std::string value, const std::string type)
    {
        std::vector<std::string> keyWords = {"exec(char", "exec(shutdown"};
        for (std::string str : keyWords)
        {
            if(value.find(str) != std::string::npos)
            {
                m_score += HIGH;
                m_alerts.push_back(type + " may contain alternate encoding injection '" + str + "'.\n");
            }
        }
    }

    SqlReport scanSql(std::string username, std::string password)
    {
        SqlReport report(username, password);

        report.scan();

        return report;
    }

    SqlReport scanSql(std::string itemName)
    {
        SqlReport report(itemName);

        report.scan();

        return report;
    }
}
