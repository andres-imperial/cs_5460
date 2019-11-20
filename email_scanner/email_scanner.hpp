//=============================================================================
// Andres Imperial
// CS_5460
//=============================================================================

#ifndef EMAIL_SCANNER_HPP
#define EMAIL_SCANNER_HPP

#include <string>
#include <vector>

namespace email_scanner
{
    class EmailReport
    {
    public:
        EmailReport(std::string emailID, std::string emailBody);
        void print(void);
        void scan(void);
        inline int getScore(void)
        {
            return static_cast<int>(m_score/m_NUM_TESTS * 100);
        }

        // Tests
        bool sampleTest(void);


    private:
        std::string m_ID;
        std::string m_body;
        double m_score{0};
        std::vector<std::string> m_alerts;
        const static int m_NUM_TESTS = 1;
    };

    EmailReport scanEmail(std::string emailID, std::string emailBody);
}

#endif
