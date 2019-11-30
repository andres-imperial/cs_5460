# Sql Scanner README:  
  
### How to compile:  
`g++ main.cpp sql_scanner.cpp -o sqlScanner`  

### How to run:
`sqlScanner <username> <password>`  
__Ex.__  
`sqlScanner "mr scammer" "admin`  
__OR__  
`sqlScanner` //Then the program will query you for the info    

### Adding Tests:
1. Go to sql_scanner.hpp and declare your test under the comment 'Tests'  
2. Go to sql_scanner.cpp and define your test  
3. If your test is positive increment m_score  
4. Increment m_NUM_TESTS in sql_scanner.hpp  

### How to run unit tests:
You will need boost, can be installed on linux with `sudo apt install libboost-test-dev`
Compile and run: `g++ sql_scanner_tests.cpp sql_scanner.cpp -lboost_unit_test_framework -o test && ./test`
