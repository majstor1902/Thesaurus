#include <iostream>

#include "Thesaurus.h"
#include "ThesaurusDatabase.h"

static void InsertCases(CThesaurus *thesaurus)
{
    vector<string> *words = new vector<string>;

    words->assign({"VW", "golf", "passat", "polo"});
    thesaurus->AddSynonyms(words);

    words->assign({"golf", "VW"});
    thesaurus->AddSynonyms(words);

    words->assign({"passat", "VW"});
    thesaurus->AddSynonyms(words);

    words->assign({"polo", "VW"});
    thesaurus->AddSynonyms(words);

    words->assign({"golf", "hatchback", "diesel", "blue"});
    thesaurus->AddSynonyms(words);

    words->assign({"hatchback", "golf"});
    thesaurus->AddSynonyms(words);

    words->assign({"diesel", "golf"});
    thesaurus->AddSynonyms(words);

    words->assign({"blue", "golf"});
    thesaurus->AddSynonyms(words);

    words->assign({"passat", "caravan", "petrol", "green"});
    thesaurus->AddSynonyms(words);

    words->assign({"caravan", "passat"});
    thesaurus->AddSynonyms(words);

    words->assign({"petrol", "passat"});
    thesaurus->AddSynonyms(words);

    words->assign({"green", "passat"});
    thesaurus->AddSynonyms(words);

    words->assign({"polo", "hatchback", "diesel", "red"});
    thesaurus->AddSynonyms(words);

    words->assign({"hatchback", "polo"});
    thesaurus->AddSynonyms(words);

    words->assign({"diesel", "polo"});
    thesaurus->AddSynonyms(words);

    words->assign({"red", "polo"});
    thesaurus->AddSynonyms(words);

    thesaurus->PrintAllEntries();

    delete words;
}

static void PrintEntries(const string &message, vector<string> *result)
{
    if (result != NULL)
    {
        cout << message << " : ";
        for (auto i = result->begin(); i != result->end(); ++i)
            cout << *i << " ";
        cout << endl;
    }
    else
    {
        cout << message << " : (empty)" << endl;
    }
}

int main()
{
    CThesaurus thesaurus;
    CThesaurusDatabase database;
    thesaurus.AddDatabase(&database);
    vector<string> *result;
    string word;

    InsertCases(&thesaurus);

    word = "golf";
    result = thesaurus.GetSynonyms(word);
    PrintEntries(word + " synonyms", result);
    delete result;

    word = "diesel";
    result = thesaurus.GetSynonyms(word);
    PrintEntries(word + " synonyms", result);
    delete result;

    word = "VW";
    result = thesaurus.GetSynonyms(word);
    PrintEntries(word + " synonyms", result);
    delete result;

    word = "red";
    result = thesaurus.GetSynonyms(word);
    PrintEntries(word + " synonyms", result);
    delete result;

    word = "polo";
    result = thesaurus.GetSynonyms(word);
    PrintEntries(word + " synonyms", result);
    delete result;

    result = thesaurus.GetAllWords();
    PrintEntries("All words", result);
    delete result;

    return 0;
}
