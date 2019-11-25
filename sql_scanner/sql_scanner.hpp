//=============================================================================
// Andres Imperial
// CS_5460
//=============================================================================

#ifndef SQL_SCANNER_HPP
#define SQL_SCANNER_HPP

#include <string>
#include <vector>

namespace sql_scanner
{
    class SqlReport
    {
    public:
        SqlReport(std::string username, std::string password);
        void print(void);
        void scan(void);
        inline int getScore(void)
        {
            return static_cast<int>(m_score/m_NUM_TESTS * 100);
        }

        // Tests
        bool sampleTest(void);
        void commentsTest(void);
        void loginBypassTest(void);
        void usernameTautologyTest(void);
        void passwordTautologyTest(void);
        void logicallyIncorrectTest(void);
        void unionTest(void);
        void piggyBackTest(void);
        void storedProceduresTest(void);
        void inferenceTest(void);
        void alternateEncodingTest(void);


    private:
        std::string m_username;
        std::string m_password;
        double m_score{0};
        std::vector<std::string> m_alerts;
        const static int m_NUM_TESTS = 10; 
    };

    SqlReport scanSql(std::string username, std::string password);
}

#endif
