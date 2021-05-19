#pragma once

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

#include "IDatabase.h"

using namespace std;

class CThesaurus
{
public:
    CThesaurus();
    ~CThesaurus();

    void AddDatabase(IDatabase *database);
    void UnlinkDatabase();

    /**
     * @brief Adds the given vector of string synonyms to the thesaurus
     * 
     * @param pSynonyms Vector of string synonyms
     * 
     * This function has return value void, but it throws exceptions in some specific cases.
     * When database is not initialized/added, function throws CDatabaseInitException("Database is not initialized").
     * When input vector is NULL, function throws CInputParameterException("Input parameter is NULL").
     * When input vector contains less than two entries, function throws CInputParameterException("Invalid parameter, there should be at least two words as synonyms").
     * If any of the vector elements doesn't comply to the established rules function throws CInputParameterException type exception.
     * At the moment there are only two check and two exceptions are thrown:
     * When length of element in vector is not between 1 and 42, function throws CInputParameterException("Invalid parameter, length should be between [1 and 42]").
     * When element in vector has characters that are not alphanumeric, function throws CInputParameterException("Invalid parameter, string should contain only alfanumeric characters").
     */
    void AddSynonyms(vector<string> *pSynonyms);

    /**
     * @brief Gets vector of string synonyms for a given word
     * 
     * @param word String for which synonyms are searched in thesaurus
     * 
     * @return Vector of synonyms, caller/user needs to handle deletion of vector himself.
     * 
     * This function can throw exceptions in some specific cases.
     * When database is not initialized/added, function throws CDatabaseInitException("Database is not initialized").
     * When length of input string is not between 1 and 42, function throws CInputParameterException("Invalid parameter, length should be between [1 and 42]").
     * When input string has characters that are not alphanumeric, function throws CInputParameterException("Invalid parameter, string should contain only alfanumeric characters").
     */
    vector<string> *GetSynonyms(string word);

    /**
     * @brief Gets all existing words from the thesaurus
     * 
     * @return Vector of all existing words, caller/user needs to handle deletion of vector himself.
     * 
     * This function can throw exceptions in some specific cases.
     * When database is not initialized/added, function throws CDatabaseInitException("Database is not initialized").
     */
    vector<string> *GetAllWords();

    /**
     * @brief Print all existing words with their synonyms from the thesaurus
     * 
     * This function is used mostly for development and verification purpose.
     * This function has return value void, but it throws exceptions in some specific cases.
     * When database is not initialized/added, function throws CDatabaseInitException("Database is not initialized").
     */
    void PrintAllEntries();

private:
    /**
     * @brief Verification of input string
     * 
     * @param word String for which synonyms are searched in thesaurus
     * 
     * This function has return value void, but it throws exceptions in some specific cases.
     * If any of the vector elements doesn't comply to the established rules function throws CInputParameterException type exception.
     * At the moment there are only two check and two exceptions are thrown:
     * When length of input string is not between 1 and 42, function throws CInputParameterException("Invalid parameter, length should be between [1 and 42]").
     * When input string has characters that are not alphanumeric, function throws CInputParameterException("Invalid parameter, string should contain only alfanumeric characters").
     */
    void VerifyWord(string word);

    /**
     * @brief Verification of input vector
     * 
     * @param pSynonyms Pointer to a vector of strings containing synonyms
     * 
     * This function has return value void, but it throws exceptions in some specific cases.
     * When input vector is NULL, function throws CInputParameterException("Input parameter is NULL").
     * When input vector contains less than two entries, function throws CInputParameterException("Invalid parameter, there should be at least two words as synonyms").
     * If any of the vector elements doesn't comply to the established rules function throws CInputParameterException type exception.
     * At the moment there are only two check and two exceptions are thrown:
     * When length of element in vector is not between 1 and 42, function throws CInputParameterException("Invalid parameter, length should be between [1 and 42]").
     * When element in vector has characters that are not alphanumeric, function throws CInputParameterException("Invalid parameter, string should contain only alfanumeric characters").
     */
    void VerifySynonyms(vector<string> *pSynonyms);

    /**
     * @brief Database instance
     */
    IDatabase *m_Database;
};