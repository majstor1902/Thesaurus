#include <iostream>

#include "Thesaurus.h"

CThesaurus::CThesaurus() 
{

}

CThesaurus::~CThesaurus() 
{
    
}

void CThesaurus::AddSynonyms(vector<string>* pSynonyms) 
{
    set<string> synonyms_set;
    string key;

    // Insert synonyms from vector to set, but without first word
    // that should be the key
    for (auto i = pSynonyms->begin(); i != pSynonyms->end(); ++i) {
        if (*i == pSynonyms->at(0)) {
            key = *i;
            continue;
        }
        synonyms_set.insert(*i);
    }

    // Insert/Update entry in thesaurus
    unordered_map<string, set<string>>::iterator it;
    it = m_Thesaurus.find(key);
    if (it == m_Thesaurus.end()) {
        // Add new entry with synonyms
        cout << "Add new entry: " << key << endl;
        m_Thesaurus.emplace(key, synonyms_set);
    } else {
        // Update synonyms in existing entry
        cout << "Update existing entry: " << key << endl;
        it->second.insert(synonyms_set.begin(), synonyms_set.end());
    }
}

vector<string>* CThesaurus::GetSynonyms(string word) 
{
    unordered_map<string, set<string>>::const_iterator it;
    it = m_Thesaurus.find(word);
    if (it == m_Thesaurus.end())
        return NULL;

    vector<string>* results = new vector<string>;
    results->assign(it->second.begin(), it->second.end());

    return results;
}

vector<string>* CThesaurus::GetAllWords() 
{
    set<string> sets;
    vector<string>* results = new vector<string>;
    for (auto x: m_Thesaurus)
        sets.insert(x.second.begin(), x.second.end());

    results->assign(sets.begin(), sets.end());

    return results;
}

void CThesaurus::PrintAllEntries() 
{
    // Log all entries
    cout << "m_Thesaurus [" << m_Thesaurus.size() << "] " << "contains:" << endl;
    for (auto x: m_Thesaurus) {
        cout << "\t[" << x.first << "]" << " -> ";
        for (auto i = x.second.begin(); i != x.second.end(); ++i)
            cout << *i << " ";
        cout << endl;
    }
}
