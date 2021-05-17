#include <iostream>

#include "Thesaurus.h"

CThesaurus::CThesaurus() {}

CThesaurus::~CThesaurus() {}

void CThesaurus::AddDatabase(IDatabase *database)
{
    m_Database = database;
}

void CThesaurus::AddSynonyms(vector<string> *pSynonyms)
{
    try
    {
        // TODO: Verify input vector
        m_Database->UpdateSynonyms(pSynonyms);
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
}

vector<string> *CThesaurus::GetSynonyms(string word)
{
    try
    {
        // TODO: Verify input word
        return m_Database->GetSynonyms(word);
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    return NULL;
}

vector<string> *CThesaurus::GetAllWords()
{
    return m_Database->GetAllWords();
}

void CThesaurus::PrintAllEntries()
{
    // Log all database entries
    m_Database->PrintAllEntries();
}
