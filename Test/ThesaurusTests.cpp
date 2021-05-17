#include <gtest/gtest.h>

using namespace ::testing;

#include "Thesaurus.h"
#include "ThesaurusDatabase.h"
#include "ThesaurusMocks.h"

// The fixture for testing class Thesaurus.
class ThesaurusTest : public ::Test
{
protected:
    CThesaurus thesaurus;
    DatabaseMock database;
    vector<string> *result;
    vector<string> *words;

public:
    void SetUp() override
    {
        thesaurus.AddDatabase(&database);
        words = new vector<string>;
    }

    void TearDown() override
    {
        delete words;
    }
};

TEST_F(ThesaurusTest, UpdateSynonymsCalled)
{
    words->assign({"0", "1", "2", "3", "4", "5"});

    EXPECT_CALL(database, UpdateSynonyms(words))
        .Times(Exactly(1));

    thesaurus.AddSynonyms(words);
}

TEST_F(ThesaurusTest, GetAllWordsCalled)
{
    EXPECT_CALL(database, GetAllWords())
        .Times(Exactly(1));

    result = thesaurus.GetAllWords();
}

TEST_F(ThesaurusTest, GetAllWordsReturned)
{
    words->assign({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});

    EXPECT_CALL(database, UpdateSynonyms(words))
        .Times(Exactly(1));

    thesaurus.AddSynonyms(words);

    EXPECT_CALL(database, GetAllWords())
        .Times(Exactly(1))
        .WillOnce(Return(words));

    result = thesaurus.GetAllWords();
    ASSERT_EQ(words->size(), result->size()) << "Input and output vectors don't have the same size";
    EXPECT_EQ(words, result) << "Input and output vectors differ";
}
