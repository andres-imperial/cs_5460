//=============================================================================
// Andres Imperial
// CS_5460
//=============================================================================

#include <string>
#include "email_scanner.hpp"

namespace email_scanner
{
    const int LOW = 10;
    const int MED = 20;
    const int HIGH = 40;

    EmailReport::EmailReport(std::string emailID, std::string emailBody)
        : m_ID(emailID), m_body(emailBody)
    {
    }

    void EmailReport::print(void)
    {
        printf("This email has a score of %i.\n"
               "Score Scale:\n"
               "Low malicious intent 0 - %i\n"
               "Med malicious intent %i - %i\n"
               "High malicious intent %i and greater\n"
               ,m_score,50, 50, 100, 100);

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

    void EmailReport::scan(void)
    {
        // Run email through tests and build score for it.
        sampleTest();
        personalInfoTest();
        indirectAddressTest();
        symbolsDomainTest();
        badTopLevelDomainTest();
        uncommonTopLevelDomainTest();
        askForClickTest();
        attachmentTest();
        fearWordsTest();
        curiosityWordsTest();
        commonPhishingWordsTest();
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

    // This test looks for 9 potential phishing for personal information words/phrases
    void EmailReport::personalInfoTest(void)
    {
        std::vector<std::string> personalInfo = {"name", "login", "email", "pin", "password", "social security number", "ssn", "address", "phone number"};
        for (std::string str : personalInfo)
        {
            if(m_body.find(str) != std::string::npos)
            {
                m_score += MED;
                m_alerts.push_back("Email may be asking for personal information '" + str + "'.\n");
            }
        }
    }

    // This test looks for 10 potential words/phrases with an indirect or general address
    void EmailReport::indirectAddressTest(void)
    {
        std::vector<std::string> address = {"sir", "madam", "ma'am", "whom it may concern", "woman in charge", "man in charge", "miss", "missus", "mister", "user"};
        for (std::string str : address)
        {
            if(m_body.find(str) != std::string::npos)
            {
                m_score += LOW;
                m_alerts.push_back("Email may be indirectly addressing the recipient '" + str + "'.\n");
            }
        }
    }

    // This test looks for 24 symobols in the domain
    void EmailReport::symbolsDomainTest(void)
    {
        std::string domain = "";
        size_t atPosition = m_ID.find("@");
        if(atPosition != std::string::npos)
        {
            domain = m_ID.substr(atPosition + 1, m_ID.length());
        }
        else 
        {
            domain = m_ID;
        }

        std::vector<std::string> symbols = {"@", "#", "!", "-", "$", "%", "^", "&", "*", "(", ")", "{", "}", "/", "\\", "[", "]", "<", ">", "?", "=", "+", "~", ","};
        for (std::string str : symbols)
        {
            if(domain.find(str) != std::string::npos)
            {
                m_score += HIGH;
                m_alerts.push_back("Domain name " + domain + " contains suspicious symbols '" + str + "'.\n");
            }
        }
    }

    // This test looks for 20 known bad TLDs in the domain
    void EmailReport::badTopLevelDomainTest(void)
    {
        std::string domain = "";
        size_t atPosition = m_ID.find("@");
        if(atPosition != std::string::npos)
        {
            domain = m_ID.substr(atPosition + 1, m_ID.length());
        }
        else 
        {
            domain = m_ID;
        }

        std::vector<std::string> badTLDs = {".country", ".stream", ".download", ".xin", ".gdn", ".racing", ".jetzt", ".win", ".bid", ".vip", ".ren", ".kim", ".loan", ".mom", ".party", ".review", ".trade", ".date", ".wang", ".accountants"};
        for (std::string str : badTLDs)
        {
            if(domain.find(str) != std::string::npos)
            {
                m_score += HIGH;
                m_alerts.push_back("Domain name " + domain + " may contain a known shady top level domain '" + str + "'.\n");
            }
        }
    }

    // This test checks if the domain has a common TLD or multiple common TLDs
    void EmailReport::uncommonTopLevelDomainTest(void)
    {
        std::string domain = "";
        size_t atPosition = m_ID.find("@");
        if(atPosition != std::string::npos)
        {
            domain = m_ID.substr(atPosition + 1, m_ID.length());
        }
        else 
        {
            domain = m_ID;
        }

        std::vector<std::string> goodTLDs = {".com", ".org", ".ru", ".de", ".net", ".com.br", ".ir", ".co.uk", ".pl", ".it"};
        int foundGood = 0;
        for (std::string str : goodTLDs)
        {
            if(domain.find(str) != std::string::npos)
            {
                foundGood++;
            }
        }
        if (foundGood > 1)
        {
            m_score += MED;
            m_alerts.push_back("Domain name " + domain + " has multiple top level domains.\n");
        }
        else if (foundGood == 0)
        {
            m_score += LOW;
            m_alerts.push_back("Domain name " + domain + " doesn't contain a well known top level domain.\n");
        }
    }

    // This test looks for 9 potential phishing click bait words/phrases
    void EmailReport::askForClickTest(void)
    {
        std::vector<std::string> clickPrompts = {"click", "url", "website", "tell me more", "get it now", "get it here", "download"};
        for (std::string str : clickPrompts)
        {
            if(m_body.find(str) != std::string::npos)
            {
                m_score += MED;
                m_alerts.push_back("Email may be using click bait '" + str + "'.\n");
            }
        }
    }

    // This test looks for 8 potential attachment phishing words/phrases
    void EmailReport::attachmentTest(void)
    {
        std::vector<std::string> attachWords = {"attached", "attachment", "included", "pdf", "doc", "exe", "pif"};
        for (std::string str : attachWords)
        {
            if(m_body.find(str) != std::string::npos)
            {
                m_score += LOW;
                m_alerts.push_back("Email may contain an attachment '" + str + "'.\n");
            }
        }
    }

    // This test looks for 15 potential phishing words/phrases used to strike fear
    void EmailReport::fearWordsTest(void)
    {
        std::vector<std::string> fearWords = {"you must", "act now", "please help", "compromised", "caught", "trouble", "problem", "danger", "overdue", "unpaid", "delinquent", "criminal", "turn you in", "late", "if you don't"};
        for (std::string str : fearWords)
        {
            if(m_body.find(str) != std::string::npos)
            {
                m_score += HIGH;
                m_alerts.push_back("Email contains words or phrases used to strike fear '" + str + "'.\n");
            }
        }
    }

    // This test looks for 15 potential phishing words/phrases used to strike curiosity
    void EmailReport::curiosityWordsTest(void)
    {
        std::vector<std::string> curiousityWords = {"easy", "secret", "free", "win", "winner", "you won", "fool-proof", "faith", "research-backed", "guaranteed", "trustworthy", "trust me", "science"};
        for (std::string str : curiousityWords)
        {
            if(m_body.find(str) != std::string::npos)
            {
                m_score += MED;
                m_alerts.push_back("Email contains words or phrases used to spark curiosity '" + str + "'.\n");
            }
        }
    }

    // This test looks for 17 most common phishing words
    void EmailReport::commonPhishingWordsTest(void)
    {
        std::vector<std::string> phishingWords = {"label", "invoice", "post", "document", "postal", "calculations", "copy", "fedex", "statement", "financial", "dhl", "usps", "notification", "irs", "ups", "delivery", "ticket"};
        for (std::string str : phishingWords)
        {
            if(m_body.find(str) != std::string::npos)
            {
                m_score += LOW;
                m_alerts.push_back("Email contains common phishing word '" + str + "'.\n");
            }
        }
    }

    EmailReport scanEmail(std::string emailID, std::string emailBody)
    {
        EmailReport report(emailID, emailBody);

        report.scan();

        return report;
    }
}
