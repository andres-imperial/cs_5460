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
        SqlReport(std::string itemName);
        void print(void);
        void scan(void);
        void scanLogin(void);
        void scanItem(void);

        // Tests
        bool sampleTest(const std::string value, const std::string type);
        void commentsTest(const std::string value, const std::string type);
        void loginBypassTest(const std::string value, const std::string type);
        void tautologyTest(const std::string value, const std::string type);
        void contradictionTest(const std::string value, const std::string type);
        void logicallyIncorrectTest(const std::string value, const std::string type);
        void unionTest(const std::string value, const std::string type);
        void piggyBackTest(const std::string value, const std::string type);
        void storedProceduresTest(const std::string value, const std::string type);
        void inferenceTest(const std::string value, const std::string type);
        void alternateEncodingTest(const std::string value, const std::string type);

        std::vector<std::string> getAlerts() { return m_alerts; }
        int getScore() { return m_score; }

    private:
        std::string m_username;
        std::string m_password;
        std::string m_itemName;
        int m_score{0};
        std::vector<std::string> m_alerts;
    };

    SqlReport scanSql(std::string username, std::string password);
    SqlReport scanSql(std::string itemName);
}

#endif
