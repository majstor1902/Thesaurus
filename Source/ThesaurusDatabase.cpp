#include <iostream>

#include "ThesaurusDatabase.h"

CThesaurusDatabase::CThesaurusDatabase() {}

CThesaurusDatabase::~CThesaurusDatabase() {}

void CThesaurusDatabase::UpdateSynonyms(vector<string> *pSynonyms)
{
    set<string> synonyms;
    string key;
    // Copy values from input vector to set, if there was any duplicates in the vector
    // they won't be in the present in the set.
    synonyms.insert(pSynonyms->begin(), pSynonyms->end());
    for (int i = 0; i < pSynonyms->size(); ++i)
    {
        // Don't add current keyword to the list of its synonyms
        key = pSynonyms->at(i);
        set<string> intermediate_synonyms = synonyms;
        intermediate_synonyms.erase(key);

        // Insert/Update entry in thesaurus
        unordered_map<string, set<string>>::iterator it;
        it = m_ThesaurusDatabase.find(key);
        if (it == m_ThesaurusDatabase.end())
        {
            // Add new entry with synonyms
            m_ThesaurusDatabase.emplace(key, intermediate_synonyms);
        }
        else
        {
            // Update synonyms in existing entry
            it->second.insert(intermediate_synonyms.begin(), intermediate_synonyms.end());
        }
    }
}

vector<string> *CThesaurusDatabase::GetSynonyms(string word)
{
    // Find key in unordered_map that is equal to input word
    // If it is found, populate synonyms vector
    unordered_map<string, set<string>>::const_iterator it;
    vector<string> *results = new vector<string>;
    it = m_ThesaurusDatabase.find(word);
    if (it != m_ThesaurusDatabase.end())
        results->assign(it->second.begin(), it->second.end());

    return results;
}

vector<string> *CThesaurusDatabase::GetAllWords()
{
    // Go through database and add all words to std::set container.
    // No need to take care of duplicates since std::set container doesn't allow them to be added.
    set<string> words;
    vector<string> *results = new vector<string>;
    for (auto &entry : m_ThesaurusDatabase)
        words.insert(entry.second.begin(), entry.second.end());

    results->assign(words.begin(), words.end());

    return results;
}

void CThesaurusDatabase::PrintAllEntries()
{
    if (m_ThesaurusDatabase.size() == 0)
    {
        cout << "Thesaurus is empty, please add some synonyms." << endl;
    }
    else
    {
        cout << "Thesaurus contains [" << m_ThesaurusDatabase.size() << "] elements." << endl;
        for (auto &entry : m_ThesaurusDatabase)
        {
            cout << "\t[" << entry.first << "] -> ";
            for (auto &word : entry.second)
                cout << word << " ";
            cout << endl;
        }
    }
}
