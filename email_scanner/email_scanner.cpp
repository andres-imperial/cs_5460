//=============================================================================
// Andres Imperial
// CS_5460
//=============================================================================

#include <string>
#include "email_scanner.hpp"

namespace email_scanner
{
    EmailReport::EmailReport(std::string emailID, std::string emailBody)
        : m_ID(emailID), m_body(emailBody)
    {
    }

    void EmailReport::print(void)
    {
        printf("This email has a %i%% chance of being a phishing email.\n", getScore());

        if (m_score > 0)
        {
            printf("The following reason attributed to this emails phishing score:\n");
            int counter{1};
            for(auto alert : m_alerts)
            {
                printf("%i: %s\n", counter, alert.c_str()); 
                ++ counter;
            }
        }
    }

    void EmailReport::scan(void)
    {
        // Run email through tests and build score for it.
        sampleTest();
    }

    bool EmailReport::sampleTest(void)
    {
        if (m_ID.find("scam") != std::string::npos)
        {
            ++m_score;
            m_alerts.push_back("Sender's ID contains word 'scam'.\n");
            return true;
        }

        return false;
    }

    EmailReport scanEmail(std::string emailID, std::string emailBody)
    {
        EmailReport report(emailID, emailBody);

        report.scan();

        return report;
    }
}
