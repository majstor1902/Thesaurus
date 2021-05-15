#include <iostream>

#include "Thesaurus.h"

static void InsertCases(CThesaurus *thesaurus) {
    vector<string>* words = new vector<string>;

    words->insert(words->end(), {"VW", "golf", "passat", "polo"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"golf", "VW"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"passat", "VW"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"polo", "VW"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"golf", "hatchback", "diesel", "blue"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"hatchback", "golf"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"diesel", "golf"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"blue", "golf"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"passat", "caravan", "petrol", "green"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"caravan", "passat"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"petrol", "passat"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"green", "passat"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"polo", "hatchback", "diesel", "red"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"hatchback", "polo"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"diesel", "polo"});
    thesaurus->AddSynonyms(words);
    words->clear();

    words->insert(words->end(), {"red", "polo"});
    thesaurus->AddSynonyms(words);
    words->clear();

    thesaurus->PrintAllEntries();

    delete words;
}

static void PrintEntries(string message, vector<string>* result) {
    if (result != NULL) {
        cout << message << " : ";
        for (auto i = result->begin(); i != result->end(); ++i)
            cout << *i << " ";
        cout << endl;
    } else {
        cout << message << " : (empty)" << endl;
    }
}

int main() {
    CThesaurus thesaurus;
    vector<string>* result;

    InsertCases(&thesaurus);
    result = thesaurus.GetSynonyms("golf");
    PrintEntries("golf synonyms", result);
    delete result;
    result = thesaurus.GetSynonyms("diesel");
    PrintEntries("diesel synonyms", result);
    delete result;
    result = thesaurus.GetSynonyms("VW");
    PrintEntries("VW synonyms", result);
    delete result;
    result = thesaurus.GetSynonyms("red");
    PrintEntries("red synonyms", result);
    delete result;
    result = thesaurus.GetSynonyms("polo");
    PrintEntries("polo synonyms", result);
    delete result;
    result = thesaurus.GetAllWords();
    PrintEntries("All words", result);
    delete result;

    return 0;
}
