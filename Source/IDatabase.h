#pragma once

#include <vector>
#include <string>

using namespace std;

class IDatabase
{
public:
    virtual ~IDatabase() = default;

    virtual void UpdateSynonyms(vector<string> *pSynonyms) = 0;
    virtual vector<string> *GetSynonyms(string word) = 0;
    virtual vector<string> *GetAllWords() = 0;
    virtual void PrintAllEntries() = 0;
};
