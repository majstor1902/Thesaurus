#include <iostream>

#include "ThesaurusDatabase.h"

CThesaurusDatabase::CThesaurusDatabase()
{
    cout << "CThesaurusDatabase() constructor called." << endl;
}

CThesaurusDatabase::~CThesaurusDatabase()
{
    cout << "CThesaurusDatabase() destructor called." << endl;
}

void CThesaurusDatabase::UpdateSynonyms(vector<string> *pSynonyms)
{
    set<string> synonyms_set;
    string key;
    int i;
    synonyms_set.insert(pSynonyms->begin(), pSynonyms->end());
    for (i = 0; i < pSynonyms->size(); ++i)
    {
        key = pSynonyms->at(i);
        //cout << "Key [" << i << "] = " << key << endl;
        set<string> temp_set = synonyms_set;
        temp_set.erase(key);

        // Insert/Update entry in thesaurus
        unordered_map<string, set<string>>::iterator it;
        it = m_ThesaurusDatabase.find(key);
        if (it == m_ThesaurusDatabase.end())
        {
            // Add new entry with synonyms
            //cout << "Add new entry: " << key << endl;
            m_ThesaurusDatabase.emplace(key, temp_set);
        }
        else
        {
            // Update synonyms in existing entry
            //cout << "Update existing entry: " << key << endl;
            it->second.insert(temp_set.begin(), temp_set.end());
        }
    }
}

vector<string> *CThesaurusDatabase::GetSynonyms(string word)
{
    unordered_map<string, set<string>>::const_iterator it;
    it = m_ThesaurusDatabase.find(word);
    if (it == m_ThesaurusDatabase.end())
        throw invalid_argument("MyFunc argument too large.");

    vector<string> *results = new vector<string>;
    results->assign(it->second.begin(), it->second.end());

    return results;
}

vector<string> *CThesaurusDatabase::GetAllWords()
{
    set<string> sets;
    vector<string> *results = new vector<string>;
    for (auto x : m_ThesaurusDatabase)
        sets.insert(x.second.begin(), x.second.end());

    results->assign(sets.begin(), sets.end());

    return results;
}

void CThesaurusDatabase::PrintAllEntries()
{
    // Log all entries
    cout << "Thesaurus contains [" << m_ThesaurusDatabase.size() << "] elements" << endl;
    for (auto x : m_ThesaurusDatabase)
    {
        cout << "\t[" << x.first << "] -> ";
        for (auto i = x.second.begin(); i != x.second.end(); ++i)
            cout << *i << " ";
        cout << endl;
    }
}
