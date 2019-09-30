// ============================================================================
// Computer Security
// Assignment 2 - Part 3
// Group: Alice and the Foobars
// Andres Imperial
// Stephanie Gonzales
// Jake Hadley
// Cole Buhman
// ============================================================================

#include <vector>
#include <iostream>
#include <string>

#include "FindKey.hpp"

namespace find_key
{
  std::string removeSpaces(std::string text)
  {
    for (int index=0; text[index]; index++)
    {
      if (text[index] == ' ') text.erase(index, 1);
    }
    return text;
  }

  int minKeyLength(std::string plaintext, std::string ciphertext)
  {
    char c = ciphertext[0]; 
    for (int index = 0; index < plaintext.length(); index++)
    {
      if(plaintext[index] == c)
      {
        return index + 1;
      }
    }
  }

  std::vector<std::string> setUpColumns(int keyLength, std::string plaintext)
  {
    int maxRows; 
    std::vector<std::string> setColumns;

    if (plaintext.length() % keyLength != 0)
    {
      maxRows = (plaintext.length() / keyLength) + 1;
    }
    else
    {
      maxRows = plaintext.length() / keyLength;
    }
    
    for (int row = 0, index = 0; row < maxRows; row++, index+=keyLength)
    {
      std::string tempString = plaintext.substr(index, keyLength);
      while (tempString.length() < keyLength)
      {
        tempString = tempString + '!';
      }
      setColumns.push_back(tempString); 
    }
    return setColumns;
  }

  std::string getColValues(std::vector<std::string> columns, int colNum)
  {
    std::string columnString = "";
    for (int row = 0; row < columns.size(); row++)
    {
      char temp = columns[row][colNum];
      columnString = columnString + temp;
    }
    return columnString; 
  }

  bool findColumns(std::vector<std::string> columns, std::string ciphertext, int testKey)
  {
    std::vector<int> indices = getCipherIndices(columns, ciphertext); 
    if((indices.size()) == testKey)
    {
      return true;
    }
    else
    {
      return false;
    }
  }


  std::string removePadding(std::string text)
  {
    for (int index = 0; index < text.length() ; index++)
    {
      if (text[index] == '!') text.erase(index, 1);
    }
    return text;
  }

  std::vector<int> getCipherIndices(std::vector<std::string> columns, std::string ciphertext)
  {
    std::vector<int> cipherIndices;
    for (int index = 0; index < columns[0].size(); index++)
    {
      std::string tempColumn = getColValues(columns, index);
      std::string text = removePadding(tempColumn);
      size_t found = ciphertext.find(text);
      if(found != std::string::npos)
      {
        cipherIndices.push_back(found);
      }
    }
    return cipherIndices;
  }

  void getKeyOutput(std::vector<std::string> columns, std::string ciphertext)
  {
    std::vector<int> cipherIndices = getCipherIndices(columns, ciphertext);
    std::vector<int> sortedIndices = cipherIndices;
    std::sort(sortedIndices.begin(), sortedIndices.end());
    std::vector<int> key;
    std::cout << "Key: ";
    for (int i = 0; i < cipherIndices.size(); i++)
    {
      for (int j = 0; j < sortedIndices.size(); j++)
      {
        if (cipherIndices[i] == sortedIndices[j])
        {
          key.push_back(j+1);
          std::cout << j+1;
        }
      }
    }
  }
}
