# Email Scanner README:  
  
### How to compile:  
`g++ main.cpp email_scanner.cpp -o emailScanner`

### How to run:
`emailScanner <emailID> <emailBody>`  
__Ex.__  
`emailScanner "my scamming cousin" "hey buddy"`  
__OR__  
`emailScanner` //Then the program will query you for the info  

### Adding Tests:
1. Go to email_scanner.hpp and declare your test under the comment 'Tests'  
2. Go to email_scanner.cpp and define your test  
3. If your test is positive increment m_score  
3. Increment m_NUM_TESTS in email_scanner.hpp  

### How to run unit tests:
You will need boost, can be installed on linux with `sudo apt install libboost-test-dev`
Compile and run: `g++ email_scanner_tests.cpp email_scanner.cpp -lboost_unit_test_framework -o test && ./test`
