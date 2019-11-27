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

        // Tests
        bool sampleTest(void);
        void personalInfoTest(void); 
        void indirectAddressTest(void); 
        void symbolsDomainTest(void);
        void badTopLevelDomainTest(void);
        void uncommonTopLevelDomainTest(void);
        void askForClickTest(void); 
        void attachmentTest(void);
        void fearWordsTest(void);
        void curiosityWordsTest(void);
        void commonPhishingWordsTest(void);


    private:
        std::string m_ID;
        std::string m_body;
        int m_score{0};
        std::vector<std::string> m_alerts;
    };

    EmailReport scanEmail(std::string emailID, std::string emailBody);
}

#endif
