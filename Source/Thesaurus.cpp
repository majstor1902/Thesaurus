#include <algorithm>
#include <iostream>

#include "Thesaurus.h"
#include "ThesaurusException.h"

#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 42

CThesaurus::CThesaurus() : m_Database(NULL) {}

CThesaurus::~CThesaurus()
{
    UnlinkDatabase();
}

void CThesaurus::AddDatabase(IDatabase *database)
{
    // Cannot initialize database with NULL parameter, notify user about that
    if (database == NULL)
        throw CInputParameterException("Input parameter is NULL");

    // Database is already initialized, notify user
    if (m_Database != NULL)
        throw CDatabaseInitException("Database was already added");

    m_Database = database;
}

void CThesaurus::UnlinkDatabase()
{
    // Unlink current database
    m_Database = NULL;
}

void CThesaurus::AddSynonyms(vector<string> *pSynonyms)
{
    // No point to continue if input vector is NULL, notify user
    if (pSynonyms == NULL)
        throw CInputParameterException("Input parameter is NULL");

    // If database is not initialized yet, notify user about that
    if (m_Database == NULL)
        throw CDatabaseInitException("Database is not initialized");

    // Verify input vector before adding it to database
    VerifySynonyms(pSynonyms);

    // Update database with new synonyms
    m_Database->UpdateSynonyms(pSynonyms);
}

vector<string> *CThesaurus::GetSynonyms(string word)
{
    // If database is not initialized yet, notify user about that
    if (m_Database == NULL)
        throw CDatabaseInitException("Database is not initialized");

    // Verify input string before calling database function
    VerifyWord(word);

    // Acquire all synonyms from the database for given string
    return m_Database->GetSynonyms(word);
}

vector<string> *CThesaurus::GetAllWords()
{
    // If database is not initialized yet, notify user about that
    if (m_Database == NULL)
        throw CDatabaseInitException("Database is not initialized");

    // Acquire all synonyms from the database
    return m_Database->GetAllWords();
}

void CThesaurus::PrintAllEntries()
{
    // If database is not initialized yet, notify user about that
    if (m_Database == NULL)
        throw CDatabaseInitException("Database is not initialized");

    // Show all entries from the database
    m_Database->PrintAllEntries();
}

void CThesaurus::VerifyWord(string word)
{
    // This is a small example of verification checks that will need to be added

    // Checking length restriction
    if (word.size() < MIN_WORD_LENGTH || word.size() > MAX_WORD_LENGTH)
    {
        throw CInputParameterException("Invalid parameter, length should be between [" + to_string(MIN_WORD_LENGTH) + " and " + to_string(MAX_WORD_LENGTH) + "]");
    }

    // Checking alphanumeric characters restriction
    if (count_if(word.begin(), word.end(), [](unsigned char c) { return !isalnum(c); }))
    {
        throw CInputParameterException("Invalid parameter, string should contain only alfanumeric characters");
    }
    // ... and many to come
}

void CThesaurus::VerifySynonyms(vector<string> *pSynonyms)
{
    // No point to continue if input vector is NULL, notify user to pay attention
    if (pSynonyms == NULL)
        throw CInputParameterException("Input parameter is NULL");

    // This is a small example of verification checks that will need to be added

    // We need at least two words to create synonym relation
    if (pSynonyms->size() < 2)
    {
        throw CInputParameterException("Invalid parameter, there should be at least two words as synonyms");
    }

    // Check each word in the vector
    for (auto word = pSynonyms->begin(); word != pSynonyms->end(); ++word)
    {
        VerifyWord(*word);
    }
}