// ============================================================================
// Computer Security
// Assignment 1
// Group: Alice and the Foobars
// Andres Imperial
// Stephanie Gonzales
// Jake Hadley
// ============================================================================

#include <vector>
#include <map>
#include <bitset>
#include <iostream> 

#include "codec.hpp"

namespace codec
{
	std::string oneTimePadEncrypt(std::string key, std::string text)
	{
    std::string polyIndices = reversePolySquare(text);
    
    std::string encryptText;
    
    for (int i = 0; i < polyIndices.size(); i+=2)
    {
      std::string subStr = polyIndices.substr(i, 2);
      int subInt = std::stoi(subStr);
      std::bitset<6> xorBits = std::bitset<6>(subInt)^=std::bitset<6>(std::stoi(key));
      encryptText = encryptText + binaryToDecimal(xorBits.to_string());
    }
    return encryptText;
	}

	std::string oneTimePadDecrypt(std::string key, std::string text)
	{
    std::string intermediateText;
    std::string polyIndices;
    
    for (int i = 0; i < text.size(); i+=2)
    {
      std::string subStr = text.substr(i, 2);
      int subInt = std::stoi(subStr);
      std::bitset<6> xorBits = std::bitset<6>(subInt)^=std::bitset<6>(std::stoi(key));
      polyIndices = polyIndices + binaryToDecimal(xorBits.to_string());
    }
    
    intermediateText = ploySquare(polyIndices);
		
    return intermediateText;
	}

	std::string columnarTranspositionEncrypt(std::string key,
																					 std::string plaintext)
	{
		std::vector<std::string> columns(key.size());
		for (int i = 0; i < key.size(); ++i)
		{
			for (int j = 0; j < key.size(); ++j)
			{
				if (j * key.size() + i >= plaintext.size())
				{
					break;
				}
				columns[i].push_back(plaintext[j * key.size() + i]);
			}
		}

		std::map<char, std::string> orderedColumns;
		for (int index = 0; index < key.size(); ++index)
		{
			orderedColumns[key.at(index)] += columns[index];
		}

		std::string result;
		for (auto it = orderedColumns.begin(); it != orderedColumns.end(); ++it)
		{
			result.append(it->second);
		}

		return result;
	}

	std::string columnarTranspositionDecrypt(std::string derivedKey,
																					 std::string ciphertext)
	{
		// TODO:
		// Take ciphertext size divide by size of key (ceiling)
		// Check if index of key(alpha order) + size of key * prevResult >= size of
		// ciphertext
		//
		// if it is then take previousResult - 1 characters instead
		//
		// then reconstruct in result string by taking subsequent indices of each
		// substring with regard to key alpha order, assoc with map for easy work
		//
		// return plaintext
	}

	// Takes indices and gets letters
	std::string ploySquare(std::string key)
	{
		std::string result;
		result.resize(key.size() / 2);

		for (int index = 0; index < result.size(); ++index)
		{
			int i = (int)(key.at(index * 2)) - '0';
			int j = (int)(key.at((index * 2) + 1)) - '0';

			result[index] = polybiusSquare[i][j];
		}

		return result;
	}
	
	std::string reversePolySquare(std::string text)
	{
		std::string polyText;
    
    for (int i = 0; i < text.size(); ++i)
		{
      char c = text[i];
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					if (polybiusSquare[j][k] == c)
					{
						std::string indices = std::to_string(j) + std::to_string(k);
						polyText = polyText + indices;
					}

				}
			}
		}
    return polyText;
	}
	
	std::string binaryToDecimal(std::string bin)
	{
	int binNum = std::stoi(bin);
	int decvalue = 0; 
	
		int base = 1; 
	
		int temp = binNum; 
		while (temp) { 
				int lastDigit = temp % 10; 
				temp = temp / 10; 
	
				decvalue += lastDigit * base; 
	
				base = base * 2; 
		} 

	if(decvalue < 10)
	{
		return "0" + std::to_string(decvalue);
	}
	else
	{
		return std::to_string(decvalue);
	}
	}

	std::string encrypt(std::string plaintext,
											std::string firstKey,
											std::string secondKey)
	{
		auto derivedKey = ploySquare(firstKey);

		printf("derivedKey: %s\n", derivedKey.c_str());

		auto ciphertext = columnarTranspositionEncrypt(derivedKey, plaintext);
	
	printf("intermediate text: %s\n", ciphertext.c_str());

		ciphertext = oneTimePadEncrypt(secondKey, ciphertext);

		return ciphertext;
	}

	std::string decrypt(std::string ciphertext,
											std::string firstKey,
											std::string secondKey)
	{
		// DONE:
		 std::string intermediateText = oneTimePadDecrypt(secondKey, ciphertext);
	// TODO:
		//
		// auto derivedKey = polySquare(firstKey);
		// plaintext = columnarTranspositionDecrypt(intermediateText, derivedKey)
		//
		// return plaintext <-- correct return (below return is just for testing)
	return intermediateText;
	}
}
