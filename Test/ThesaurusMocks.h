#include <gmock/gmock.h>

#include "Thesaurus.h"
#include "ThesaurusDatabase.h"

class DatabaseMock : public IDatabase
{
public:
    MOCK_METHOD(void, UpdateSynonyms, (vector<string> * pSynonyms), (override));
    MOCK_METHOD(vector<string> *, GetSynonyms, (string word), (override));
    MOCK_METHOD(vector<string> *, GetAllWords, (), (override));
    MOCK_METHOD(void, PrintAllEntries, (), (override));
};