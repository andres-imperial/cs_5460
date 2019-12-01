#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SQLScanner
#include <boost/test/unit_test.hpp>

#include "sql_scanner.hpp"

namespace sql = sql_scanner;
 
BOOST_AUTO_TEST_CASE(commentsTest)
{
    std::string itemName("SELECT name from /* table1 where */ -- nothing here");
    sql::SqlReport test(itemName);

    std::vector<std::string> alerts;

    alerts.push_back("Item name contains possible sql comment '--'.\n");
    alerts.push_back("Item name contains possible sql comment '/*'.\n");
    alerts.push_back("Item name contains possible sql comment '*/'.\n");

    test.commentsTest(itemName, "Item name");
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();

    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 150);
}

BOOST_AUTO_TEST_CASE(loginBypassTest)
{
    std::string itemName("CREATE LOGIN admin' # or admin'-- or admin'/*\
        WITH PASSWORD = { 'password' | ') or ('1'='1-- | ' or 1=1/* | hashed_password HASHED } [ MUST_CHANGE ] \
        [ , SID = sid_value \
        | DEFAULT_DATABASE = database_name \
        | DEFAULT_LANGUAGE = language_name \
        | CHECK_EXPIRATION = { ON | OFF } \
        | CHECK_POLICY = { ON | OFF } \
        | CREDENTIAL = credential_name ];");
    sql::SqlReport test(itemName);

    std::vector<std::string> alerts;

    alerts.push_back("Item name may contain a bypass login injection 'admin'--'.\n");
    alerts.push_back("Item name may contain a bypass login injection 'admin' #'.\n");
    alerts.push_back("Item name may contain a bypass login injection 'admin'/*'.\n");
    alerts.push_back("Item name may contain a bypass login injection '\' or 1=1/*'.\n");
    alerts.push_back("Item name may contain a bypass login injection ') or (\'1\'=\'1--'.\n");

    test.loginBypassTest(itemName, "Item name");
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();

    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 500);
}

BOOST_AUTO_TEST_CASE(tautologyTest)
{
    std::string itemName("SELECT name from table1 where 1=1 and x=x and yellow=yellow");
    sql::SqlReport test(itemName);

    std::vector<std::string> alerts;

    alerts.push_back("Item name contains a tautology '1=1'.\n");
    alerts.push_back("Item name contains a tautology 'x=x'.\n");
    alerts.push_back("Item name contains a tautology 'yellow=yellow'.\n");

    test.tautologyTest(itemName, "Item name");
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();

    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 150);
}

BOOST_AUTO_TEST_CASE(contradictionTest)
{
    std::string itemName("SELECT name from table1 where 1=0 and table=tavel");
    sql::SqlReport test(itemName);

    std::vector<std::string> alerts;

    alerts.push_back("Item name contains a contradiction '1=0'.\n");
    alerts.push_back("Item name contains a contradiction 'table=tavel'.\n");

    test.contradictionTest(itemName, "Item name");
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();

    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 100);
}

BOOST_AUTO_TEST_CASE(logicallyIncorrectTest)
{
    std::string itemName("SELECT name from table1 convert table2 where sysobjects.call() or xtype='u'");
    sql::SqlReport test(itemName);

    std::vector<std::string> alerts;

    alerts.push_back("Item name may contain illegal or logically incorrect injection 'sysobjects'.\n");
    alerts.push_back("Item name may contain illegal or logically incorrect injection 'xtype='u''.\n");
    alerts.push_back("Item name may contain illegal or logically incorrect injection 'convert'.\n");

    test.logicallyIncorrectTest(itemName, "Item name");
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();

    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 75);
}

BOOST_AUTO_TEST_CASE(unionTest)
{
    std::string itemName("SELECT name from table1 union table2 =' ' table3");
    sql::SqlReport test(itemName);

    std::vector<std::string> alerts;

    alerts.push_back("Item name may contain union injection 'union'.\n");
    alerts.push_back("Item name may contain union injection '=' ''.\n");

    test.unionTest(itemName, "Item name");
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();

    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 100);
}

BOOST_AUTO_TEST_CASE(piggyBackTest)
{
    std::vector<std::string> keyWords = {"; drop", "; select", "; alter", "; truncate", "; insert", "; update", "; where", "; delete", "; set", "; values"};

    for (auto& keyWord : keyWords) 
    {
        std::string itemName("SELECT name from table1 " + keyWord);
        sql::SqlReport test(itemName);
        std::vector<std::string> alerts = {"Item name may contain piggy-back injection '" + keyWord + "'.\n"};

        test.piggyBackTest(itemName, "Item name");
        auto testm_Alerts = test.getAlerts();
        auto testm_Score = test.getScore();

        BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
        BOOST_CHECK_EQUAL(testm_Score, 50);
    }
}

BOOST_AUTO_TEST_CASE(storedProceduresTest)
{
    std::string itemName("SELECT name from table1 exec(new command); shutdown");
    sql::SqlReport test(itemName);

    std::vector<std::string> alerts;

    alerts.push_back("Item name may contain stored procedure injection 'exec'.\n");
    alerts.push_back("Item name may contain stored procedure injection 'shutdown'.\n");

    test.storedProceduresTest(itemName, "Item name");
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();

    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 200);
}

BOOST_AUTO_TEST_CASE(inferenceTest)
{
    std::string itemName("select top 1 name from table1 where name=ascii(substring of 1=0-- X WAITFOR 10");
    sql::SqlReport test(itemName);

    std::vector<std::string> alerts;

    alerts.push_back("Item name may contain inference injection '1=0--'.\n");
    alerts.push_back("Item name may contain inference injection 'ascii(substring'.\n");
    alerts.push_back("Item name may contain inference injection 'select top 1 name'.\n");
    alerts.push_back("Item name may contain inference injection 'X WAITFOR'.\n");

    test.inferenceTest(itemName, "Item name");
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();

    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 100);
}

BOOST_AUTO_TEST_CASE(alternateEncodingTest)
{
    std::string itemName("SELECT name from table1 exec(char); exec(shutdown)");
    sql::SqlReport test(itemName);

    std::vector<std::string> alerts;

    alerts.push_back("Item name may contain alternate encoding injection 'exec(char'.\n");
    alerts.push_back("Item name may contain alternate encoding injection 'exec(shutdown'.\n");

    test.alternateEncodingTest(itemName, "Item name");
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();

    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 200);
}
