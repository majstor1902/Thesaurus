#pragma once

#include <string>
#include <vector>

using namespace std;

class CThesaurus
{
public:
    CThesaurus();
    ~CThesaurus();

    /**
     * @brief Adds the given synonyms to the thesaurus
     * 
     * @param pSynonyms List of synonyms
     */
    void AddSynonyms(vector<string>* pSynonyms);

    /**
     * @brief Gets the synonyms for a given word
     * 
     * @param word Word that is searched
     * @return List of synonyms 
     */
    vector<string>* GetSynonyms(string word);

    //Gets all words from the thesaurus
    /**
     * @brief Gets all words from the thesaurus
     * 
     * @return List of all words
     */
    vector<string>* GetAllWords();
};