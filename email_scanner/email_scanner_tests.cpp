#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EmailScanner
#include <boost/test/unit_test.hpp>

#include "email_scanner.hpp"

namespace es = email_scanner;
 
BOOST_AUTO_TEST_CASE(personalInfoTest)
{
    es::EmailReport testAllPersonalInfo("", "It appears that your login information has been compromised. Please enter your name and email to reset your pin and password. This will ensure your social security number(ssn) and other info such as your address and phone number are secure.");
    es::EmailReport testBasicInfo("", "Click this link to access your email account. You will need to login with your full name and password.");
    es::EmailReport testSecureInfo("", "Thank you for your interest in Bank of America. To complete your sign up process, please provide you social security number(ssn) and a good phone number to reach you. To ensure a secure connection, please create a pin. This will be used to login in the future.");

    std::vector<std::string> allAlerts;
    std::vector<std::string> basicAlerts;
    std::vector<std::string> secureAlerts;

    std::vector<std::string> personalInfo = {"name", "login", "email", "pin", "password", "social security number", "ssn", "address", "phone number"};
    for (std::string str : personalInfo)
        allAlerts.push_back("Email may be asking for personal information '" + str + "'.\n");

    basicAlerts.push_back("Email may be asking for personal information 'name'.\n");
    basicAlerts.push_back("Email may be asking for personal information 'login'.\n");
    basicAlerts.push_back("Email may be asking for personal information 'email'.\n");
    basicAlerts.push_back("Email may be asking for personal information 'password'.\n");

    secureAlerts.push_back("Email may be asking for personal information 'login'.\n");
    secureAlerts.push_back("Email may be asking for personal information 'pin'.\n");
    secureAlerts.push_back("Email may be asking for personal information 'social security number'.\n");
    secureAlerts.push_back("Email may be asking for personal information 'ssn'.\n");
    secureAlerts.push_back("Email may be asking for personal information 'phone number'.\n");

    testAllPersonalInfo.personalInfoTest();
    auto allm_Alerts = testAllPersonalInfo.getAlerts();
    auto allm_Score = testAllPersonalInfo.getScore();

    testBasicInfo.personalInfoTest();
    auto basicm_Alerts = testBasicInfo.getAlerts();
    auto basicm_Score = testBasicInfo.getScore();

    testSecureInfo.personalInfoTest();
    auto securem_Alerts = testSecureInfo.getAlerts();
    auto securem_Score = testSecureInfo.getScore();
    
    BOOST_CHECK_EQUAL_COLLECTIONS(allAlerts.begin(), allAlerts.end(), allm_Alerts.begin(), allm_Alerts.end());
    BOOST_CHECK_EQUAL(allm_Score, 180);

    BOOST_CHECK_EQUAL_COLLECTIONS(basicAlerts.begin(), basicAlerts.end(), basicm_Alerts.begin(), basicm_Alerts.end());
    BOOST_CHECK_EQUAL(basicm_Score, 80);

    BOOST_CHECK_EQUAL_COLLECTIONS(secureAlerts.begin(), secureAlerts.end(), securem_Alerts.begin(), securem_Alerts.end());
    BOOST_CHECK_EQUAL(securem_Score, 100);
}

//This test matches "man in charge" and "woman in charge" on the testFemale
BOOST_AUTO_TEST_CASE(indirectAddressTest)
{
    es::EmailReport testMale("", "This is addressed to mister John Doe. Our records indicate that you are the man in charge of accounting at Bank of America. Your rapid response is requested, sir.");
    es::EmailReport testFemale("", "This is addressed to missus Jane Doe. Miss, Our records indicate that you, madam, are the woman in charge of accounting at Bank of America. Your rapid response is requested, ma'am.");
    es::EmailReport testOther("", "To whom it may concern, the user A5226vc2334 has received a credit of $40.");

    std::vector<std::string> maleIndirectAlerts;
    std::vector<std::string> femaleIndirectAlerts;
    std::vector<std::string> otherIndirectAlerts;

    maleIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'sir'.\n");
    maleIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'man in charge'.\n");
    maleIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'mister'.\n");

    femaleIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'madam'.\n");
    femaleIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'ma'am'.\n");
    femaleIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'woman in charge'.\n");
    femaleIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'man in charge'.\n");
    femaleIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'miss'.\n");
    femaleIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'missus'.\n");

    otherIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'whom it may concern'.\n");
    otherIndirectAlerts.push_back("Email may be indirectly addressing the recipient 'user'.\n");

    testMale.indirectAddressTest();
    auto malem_Alerts = testMale.getAlerts();
    auto malem_Score = testMale.getScore();

    testFemale.indirectAddressTest();
    auto femalem_Alerts = testFemale.getAlerts();
    auto femalem_Score = testFemale.getScore();

    testOther.indirectAddressTest();
    auto otherm_Alerts = testOther.getAlerts();
    auto otherm_Score = testOther.getScore();

    BOOST_CHECK_EQUAL_COLLECTIONS(maleIndirectAlerts.begin(), maleIndirectAlerts.end(), malem_Alerts.begin(), malem_Alerts.end());
    BOOST_CHECK_EQUAL(malem_Score, 30);

    BOOST_CHECK_EQUAL_COLLECTIONS(femaleIndirectAlerts.begin(), femaleIndirectAlerts.end(), femalem_Alerts.begin(), femalem_Alerts.end());
    BOOST_CHECK_EQUAL(femalem_Score, 60);

    BOOST_CHECK_EQUAL_COLLECTIONS(otherIndirectAlerts.begin(), otherIndirectAlerts.end(), otherm_Alerts.begin(), otherm_Alerts.end());
    BOOST_CHECK_EQUAL(otherm_Score, 20);
}

BOOST_AUTO_TEST_CASE(symbolsDomainTest)
{
    std::string domain1("!banks*@thi~ngs^to]give$where\\it>co=unts}).com");
    es::EmailReport test1("johndoe@" + domain1, "");

    std::string domain2("<banks+[thi(ngs,&to%give?where#it-co/unts{.com");
    es::EmailReport test2("johndoe@" + domain2, "");

    std::vector<std::string> symbolDomainAlerts1;
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols '@'.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols '!'.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols '$'.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols '^'.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols '*'.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols ')'.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols '}'.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols '\\'.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols ']'.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols '>'.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols '='.\n");
    symbolDomainAlerts1.push_back("Domain name " + domain1 + " contains suspicious symbols '~'.\n");

    std::vector<std::string> symbolDomainAlerts2;
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '#'.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '-'.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '%'.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '&'.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '('.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '{'.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '/'.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '['.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '<'.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '?'.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols '+'.\n");
    symbolDomainAlerts2.push_back("Domain name " + domain2 + " contains suspicious symbols ','.\n");

    test1.symbolsDomainTest();
    auto testm_Alerts1 = test1.getAlerts();
    auto testm_Score1 = test1.getScore();

    test2.symbolsDomainTest();
    auto testm_Alerts2 = test2.getAlerts();
    auto testm_Score2 = test2.getScore();


    BOOST_CHECK_EQUAL_COLLECTIONS(symbolDomainAlerts1.begin(), symbolDomainAlerts1.end(), testm_Alerts1.begin(), testm_Alerts1.end());
    BOOST_CHECK_EQUAL(testm_Score1, 480);

    BOOST_CHECK_EQUAL_COLLECTIONS(symbolDomainAlerts2.begin(), symbolDomainAlerts2.end(), testm_Alerts2.begin(), testm_Alerts2.end());
    BOOST_CHECK_EQUAL(testm_Score2, 480);
}

BOOST_AUTO_TEST_CASE(badTopLevelDomainTest)
{
    std::vector<std::string> badTLDs = {".country", ".stream", ".download", ".xin", ".gdn", ".racing", ".jetzt", ".win", ".bid", ".vip", ".ren", ".kim", ".loan", ".mom", ".party", ".review", ".trade", ".date", ".wang", ".accountants"};

    for (auto& tld : badTLDs) 
    {        
        es::EmailReport test("johndoe@bankofamerica" + tld, "");
        std::vector<std::string> alerts = {"Domain name bankofamerica" + tld + " may contain a known shady top level domain '" + tld + "'.\n"};
        test.badTopLevelDomainTest();
        auto testm_Alerts = test.getAlerts();
        auto testm_Score = test.getScore();
        BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
        BOOST_CHECK_EQUAL(testm_Score, 40);
    }
}

BOOST_AUTO_TEST_CASE(noGoodUncommonTopLevelDomainTest)
{
    std::string notGoodDomain("bankofamerica.tl");
    std::vector<std::string> alerts = {"Domain name " + notGoodDomain + " doesn't contain a well known top level domain.\n"};
    es::EmailReport test("johndoe@" + notGoodDomain, "");
    test.uncommonTopLevelDomainTest();
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();
    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 10);
}

BOOST_AUTO_TEST_CASE(uncommonTopLevelDomainTest)
{
    std::vector<std::string> goodTLDs = {".com", ".org", ".ru", ".de", ".net", ".com.br", ".ir", ".co.uk", ".pl", ".it"};

    for (auto tld = 0; tld < goodTLDs.size() - 1; tld++)
    {
        std::string domain("bankofamerica" + goodTLDs[tld] + goodTLDs[tld + 1]);
        es::EmailReport test("johndoe@" + domain, "");
        std::vector<std::string> alerts = {"Domain name " + domain + " has multiple top level domains.\n"};
        test.uncommonTopLevelDomainTest();
        auto testm_Alerts = test.getAlerts();
        auto testm_Score = test.getScore();
        BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
        BOOST_CHECK_EQUAL(testm_Score, 20);
    }
}

BOOST_AUTO_TEST_CASE(askForClickTest)
{
    es::EmailReport test("", "click the link titled get it here below to navigate to the download page for your free website! You can get it now with the provided personal url.");

    std::vector<std::string> alerts;
    alerts.push_back("Email may be using click bait 'click'.\n");
    alerts.push_back("Email may be using click bait 'url'.\n");
    alerts.push_back("Email may be using click bait 'website'.\n");
    alerts.push_back("Email may be using click bait 'get it now'.\n");
    alerts.push_back("Email may be using click bait 'get it here'.\n");
    alerts.push_back("Email may be using click bait 'download'.\n");

    test.askForClickTest();
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();
    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 120);
}

BOOST_AUTO_TEST_CASE(attachmentTest)
{
    es::EmailReport test("", "Hi, please check the included pdf, doc, and pif items to view the desired attachment as requested by you on 4/6/18");

    std::vector<std::string> alerts;
    alerts.push_back("Email may contain an attachment 'attachment'.\n");
    alerts.push_back("Email may contain an attachment 'included'.\n");
    alerts.push_back("Email may contain an attachment 'pdf'.\n");
    alerts.push_back("Email may contain an attachment 'doc'.\n");
    alerts.push_back("Email may contain an attachment 'pif'.\n");

    test.attachmentTest();
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();
    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 50);
}

BOOST_AUTO_TEST_CASE(fearWordsTest)
{
    es::EmailReport test("", "It appears that you have a compromised balance that is overdue. If you have any delinquent accounts left unpaid by the end of the week, you are in danger of being caught and we will turn you in. you must act now, if you don't, we will be unable to help you.");

    std::vector<std::string> alerts;
    alerts.push_back("Email contains words or phrases used to strike fear 'you must'.\n");
    alerts.push_back("Email contains words or phrases used to strike fear 'act now'.\n");
    alerts.push_back("Email contains words or phrases used to strike fear 'compromised'.\n");
    alerts.push_back("Email contains words or phrases used to strike fear 'caught'.\n");
    alerts.push_back("Email contains words or phrases used to strike fear 'danger'.\n");
    alerts.push_back("Email contains words or phrases used to strike fear 'overdue'.\n");
    alerts.push_back("Email contains words or phrases used to strike fear 'unpaid'.\n");
    alerts.push_back("Email contains words or phrases used to strike fear 'delinquent'.\n");
    alerts.push_back("Email contains words or phrases used to strike fear 'turn you in'.\n");
    alerts.push_back("Email contains words or phrases used to strike fear 'if you don't'.\n");

    test.fearWordsTest();
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();
    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 400);
}

BOOST_AUTO_TEST_CASE(curiosityWordsTest)
{
    es::EmailReport test("", "You have win and are the winner of a new fool-proof research-backed treatment. It is from a trustworthy source that will cure your illness guaranteed. trust me, the science behind this is not based on faith, but on a new secret and easy yet simple procedure that not just anyone is able to acquire.");

    std::vector<std::string> alerts;
    alerts.push_back("Email contains words or phrases used to spark curiosity 'easy'.\n");
    alerts.push_back("Email contains words or phrases used to spark curiosity 'secret'.\n");
    alerts.push_back("Email contains words or phrases used to spark curiosity 'win'.\n");
    alerts.push_back("Email contains words or phrases used to spark curiosity 'winner'.\n");
    alerts.push_back("Email contains words or phrases used to spark curiosity 'fool-proof'.\n");
    alerts.push_back("Email contains words or phrases used to spark curiosity 'faith'.\n");
    alerts.push_back("Email contains words or phrases used to spark curiosity 'research-backed'.\n");
    alerts.push_back("Email contains words or phrases used to spark curiosity 'guaranteed'.\n");
    alerts.push_back("Email contains words or phrases used to spark curiosity 'trustworthy'.\n");
    alerts.push_back("Email contains words or phrases used to spark curiosity 'trust me'.\n");
    alerts.push_back("Email contains words or phrases used to spark curiosity 'science'.\n");

    test.curiosityWordsTest();
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();
    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 220);
}

BOOST_AUTO_TEST_CASE(commonPhishingWordsTest)
{
    es::EmailReport test("", "Included below is your invoice of $5000 payable to you via postal service or other common delivery services such as ups, fedex, dhl, or usps. Please view the document that contains the shipping label, and feel free to check the calculations before making a copy. Your ticket will be given from a post afterwords.");

    std::vector<std::string> alerts;
    alerts.push_back("Email contains common phishing word 'label'.\n");
    alerts.push_back("Email contains common phishing word 'invoice'.\n");
    alerts.push_back("Email contains common phishing word 'post'.\n");
    alerts.push_back("Email contains common phishing word 'document'.\n");
    alerts.push_back("Email contains common phishing word 'postal'.\n");
    alerts.push_back("Email contains common phishing word 'calculations'.\n");
    alerts.push_back("Email contains common phishing word 'copy'.\n");
    alerts.push_back("Email contains common phishing word 'fedex'.\n");
    alerts.push_back("Email contains common phishing word 'dhl'.\n");
    alerts.push_back("Email contains common phishing word 'usps'.\n");
    alerts.push_back("Email contains common phishing word 'ups'.\n");
    alerts.push_back("Email contains common phishing word 'delivery'.\n");
    alerts.push_back("Email contains common phishing word 'ticket'.\n");

    test.commonPhishingWordsTest();
    auto testm_Alerts = test.getAlerts();
    auto testm_Score = test.getScore();
    BOOST_CHECK_EQUAL_COLLECTIONS(alerts.begin(), alerts.end(), testm_Alerts.begin(), testm_Alerts.end());
    BOOST_CHECK_EQUAL(testm_Score, 130);
}
