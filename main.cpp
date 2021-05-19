#include <iostream>
#include <sstream>

#include "Thesaurus.h"
#include "ThesaurusDatabase.h"
#include "ThesaurusException.h"

static void PrintEntries(const string &message, vector<string> *result)
{
    if (result == NULL || result->size() == 0)
    {
        cout << message << " : (empty)" << endl;
    }
    else
    {
        cout << message << " : ";
        for (auto word = result->begin(); word != result->end(); ++word)
            cout << *word << " ";
        cout << endl;
    }
}

int main()
{
    string choice;
    CThesaurus thesaurus;
    CThesaurusDatabase database;
    thesaurus.AddDatabase(&database);
    vector<string> *result;
    vector<string> *words = new vector<string>;

    cout << "Input options: " << endl;
    cout << "[1]: AddSynonyms" << endl;
    cout << "[2]: GetSynonyms" << endl;
    cout << "[3]: GetAllWords" << endl;
    cout << "[4]: PrintAllWords" << endl;
    cout << "[q]: Quit" << endl;
    do
    {
        cout << "Enter selection: ";
        cin >> choice;
        if (choice == "1")
        {
            cout << "Enter all synonyms (divided by comma): ";
            string input;
            cin >> input;
            stringstream ss(input);

            while (ss.good())
            {
                string substr;
                getline(ss, substr, ',');
                cout << substr << endl;
                words->push_back(substr);
            }
            try
            {
                thesaurus.AddSynonyms(words);
            }
            catch (CInputParameterException &e)
            {
                cout << e.what() << endl;
            }
            catch (CDatabaseInitException &e)
            {
                cout << e.what() << endl;
            }
            words->clear();
        }
        else if (choice == "2")
        {
            string word;
            cout << "Enter word to find synonyms: ";
            cin >> word;
            try
            {
                result = thesaurus.GetSynonyms(word);
                PrintEntries(word + " synonyms: ", result);
                delete result;
            }
            catch (CDatabaseInitException &e)
            {
                cout << e.what() << endl;
            }
        }
        else if (choice == "3")
        {
            try
            {
                result = thesaurus.GetAllWords();
                PrintEntries("All words", result);
                delete result;
            }
            catch (CDatabaseInitException &e)
            {
                cout << e.what() << endl;
            }
        }
        else if (choice == "4")
        {
            thesaurus.PrintAllEntries();
        }
        else
        {
            cout << "Input options: " << endl;
            cout << "[1]: AddSynonyms" << endl;
            cout << "[2]: GetSynonyms" << endl;
            cout << "[3]: GetAllWords" << endl;
            cout << "[4]: PrintAllWords" << endl;
            cout << "[q]: Quit" << endl;
        }

    } while (choice != "q");

    delete words;

    return 0;
}
