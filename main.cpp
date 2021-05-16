#include <iostream>

#include "Thesaurus.h"

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
    vector<string> *result;

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
