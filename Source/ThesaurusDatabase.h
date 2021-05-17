#pragma once

#include <set>
#include <unordered_map>

#include "IDatabase.h"

using namespace std;

class CThesaurusDatabase : public IDatabase
{
public:
    CThesaurusDatabase();
    virtual ~CThesaurusDatabase();

    void UpdateSynonyms(vector<string> *pSynonyms) override;
    vector<string> *GetSynonyms(string word) override;
    vector<string> *GetAllWords() override;
    void PrintAllEntries() override;

private:
    // Database with synonyms
    unordered_map<string, set<string>> m_ThesaurusDatabase;
};
