#include <gtest/gtest.h>

using namespace ::testing;

#include "Thesaurus.h"
#include "ThesaurusDatabase.h"
#include "ThesaurusException.h"
#include "ThesaurusMocks.h"

namespace
{
    void CompareVectors(vector<string> *words, vector<string> *result)
    {
        ASSERT_EQ(words->size(), result->size()) << "Input and output vectors don't have the same size";
        for (int i = 0; i < result->size(); ++i)
        {
            EXPECT_EQ(words->at(i), result->at(i)) << "Vectors differ at index " << i;
        }
    }

    // The fixture for testing class Thesaurus.
    // Here we test with database mock functions
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

    // Verify that UpdateSynonyms() function is called once from AddSynonyms() function
    TEST_F(ThesaurusTest, UpdateSynonymsCalled)
    {
        words->assign({"0", "1", "2", "3", "4", "5"});

        EXPECT_CALL(database, UpdateSynonyms(words))
            .Times(Exactly(1));

        thesaurus.AddSynonyms(words);
    }

    // Verify that AddSynonyms() function throws CInputParameterException when input vector is NULL
    TEST_F(ThesaurusTest, UpdateSynonymsNull)
    {
        vector<string> *synonyms = NULL;
        EXPECT_THROW(thesaurus.AddSynonyms(synonyms), CInputParameterException);
    }

    // Verify that AddSynonyms() function throws CInputParameterException when input vector is empty
    TEST_F(ThesaurusTest, UpdateSynonymsEmpty)
    {
        EXPECT_THROW(thesaurus.AddSynonyms(words), CInputParameterException);
    }

    // Verify that AddSynonyms() function throws CInputParameterException when input vector has just one entry
    TEST_F(ThesaurusTest, UpdateSynonymsOneWord)
    {
        words->assign({"1"});
        EXPECT_THROW(thesaurus.AddSynonyms(words), CInputParameterException);
    }

    // Verify that database GetAllWords() function is called once from thesaurus GetAllWords() function
    TEST_F(ThesaurusTest, GetAllWordsCalled)
    {
        EXPECT_CALL(database, GetAllWords())
            .Times(Exactly(1));

        thesaurus.GetAllWords();
    }

    // Verify that database GetSynonyms() function is called once from thesaurus GetSynonyms() function
    TEST_F(ThesaurusTest, GetSynonymsCalled)
    {
        string word = "test";
        EXPECT_CALL(database, GetSynonyms(word))
            .Times(Exactly(1));

        thesaurus.GetSynonyms(word);
    }

    // Verify that database GetSynonyms() function is called once from thesaurus GetSynonyms() function
    // Verify that database GetSynonyms() function returns empty vector
    TEST_F(ThesaurusTest, GetSynonymsNotExist)
    {
        string word = "ThisWordShouldNotExist";
        EXPECT_CALL(database, GetSynonyms(word))
            .Times(Exactly(1))
            .WillOnce(Return(words));
        thesaurus.GetSynonyms(word);
    }

    // Verify that GetSynonyms() function throws CInputParameterException when input word is empty
    TEST_F(ThesaurusTest, GetSynonymsEmptyString)
    {
        string word = "";
        EXPECT_THROW(thesaurus.GetSynonyms(word), CInputParameterException);
    }

    // Verify that GetSynonyms() function throws CInputParameterException when input word is too long
    TEST_F(ThesaurusTest, GetSynonymsLongString)
    {
        string word = "ThisStringIsUsedForTestCaseWhereStringLengthIsVerified";
        EXPECT_THROW(thesaurus.GetSynonyms(word), CInputParameterException);
    }

    // Verify that GetSynonyms() function throws CInputParameterException when input word contains non alphanumeric characters
    TEST_F(ThesaurusTest, GetSynonymsAlphanumeric)
    {
        string word = "#abc#";
        EXPECT_THROW(thesaurus.GetSynonyms(word), CInputParameterException);
    }

    // Verify that database GetAllWords() function is called once from thesaurus GetAllWords() function
    // Verify that database GetAllWords() function returns vector entries that we expect
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
        CompareVectors(words, result);
    }

    // Verify that database GetAllWords() function is called once from thesaurus GetAllWords() function
    // Verify that database GetAllWords() function returns empty vector when nothing is added
    TEST_F(ThesaurusTest, GetAllWordsEmpty)
    {
        EXPECT_CALL(database, GetAllWords())
            .Times(Exactly(1))
            .WillOnce(Return(words));

        result = thesaurus.GetAllWords();
        ASSERT_EQ(0, result->size()) << "Database is not empty";
    }
}

namespace
{
    // The fixture for testing class Thesaurus.
    // Here we test without adding database
    class ThesaurusTestDatabase : public ::Test
    {
    protected:
        CThesaurus thesaurus;
        vector<string> *result;
        vector<string> *words;

    public:
        void SetUp() override
        {
            words = new vector<string>;
        }

        void TearDown() override
        {
            delete words;
        }
    };

    // Verify that AddSynonyms() function throws CDatabaseInitException when database is not yet added/initialized
    TEST_F(ThesaurusTestDatabase, UpdateSynonymsCalled)
    {
        words->assign({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});
        EXPECT_THROW(thesaurus.AddSynonyms(words), CDatabaseInitException);
    }

    /**
     * This test was added at the very begining.
     * It contains only numbers and below you can see the types of relations between numbers on which the synonyms were created.
     * This way it was easy to verify the output manually before googletest framework was even introduced in the project.
     * This use case was also used in initial analysis and basic implementation of the solution.
     * 
     * Possible inputs:
     * 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
     * 
     * single digits:
     * 0 1 2 3 4 5 6 7 8 9
     * double digits:
     * 10 11 12 13 14 15 16 17 18 19
     * 
     * last number is the same:
     * 0 10 20
     * 1 11
     * 2 12
     * 3 13
     * 
     * single digit odd numbers:
     * 1 3 5 7 9
     * double digit odd numbers:
     * 11 13 15 17 19
     * 
     * single digit even numbers:
     * 0 2 4 6 8
     * double digit even numbers:
     * 10 12 14 16 18
     * 
     * same sum of all digits of a number:
     * 1 10
     * 2 11 20
     * 3 12
     * 4 13
     * 5 14
     * 6 15
     * 7 16
     * 8 17
     * 9 18
     * 
     * numbers dividable by 5:
     * 5 10 15 20
     * numbers dividable by 7:
     * 7 14
     * 
     * Outputs:
     * [0] - 1 10 2 20 3 4 5 6 7 8 9
     * [1] - 0 10 11 2 3 4 5 6 7 8 9
     * [2] - 0 1 11 12 20 3 4 5 6 7 8 9
     * [3] - 0 1 12 13 2 4 5 6 7 8 9
     * [4] - 0 1 13 2 3 5 6 7 8 9
     * [5] - 0 1 10 14 15 2 20 3 4 6 7 8 9
     * [6] - 0 1 15 2 3 4 5 7 8 9
     * [7] - 0 1 14 16 2 3 4 5 6 8 9
     * [8] - 0 1 17 2 3 4 5 6 7 9
     * [9] - 0 1 18 2 3 4 5 6 7 8
     * [10] - 0 1 11 12 13 14 15 16 17 18 19 20 5
     * [11] - 1 10 12 13 14 15 16 17 18 19 2 20
     * [12] - 10 11 13 14 15 16 17 18 19 2 20 3
     * [13] - 10 11 12 14 15 16 17 18 19 3 4
     * [14] - 10 11 12 13 15 16 17 18 19 20 5 7
     * [15] - 10 11 12 13 14 16 17 18 19 20 5 6
     * [16] - 10 11 12 13 14 15 17 18 19 20 7
     * [17] - 10 11 12 13 14 15 16 18 19 8
     * [18] - 10 11 12 13 14 15 16 17 19 20 9
     * [19] - 10 11 12 13 14 15 16 17 18
     * [20] - 0 10 11 12 14 15 16 18 2 5
     * 
     */
    TEST_F(ThesaurusTestDatabase, AddSynonyms)
    {
        CThesaurusDatabase database;
        thesaurus.AddDatabase(&database);

        words->assign({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});
        thesaurus.AddSynonyms(words);

        words->assign({"10", "11", "12", "13", "14", "15", "16", "17", "18", "19"});
        thesaurus.AddSynonyms(words);

        words->assign({"0", "10", "20"});
        thesaurus.AddSynonyms(words);
        words->assign({"1", "11"});
        thesaurus.AddSynonyms(words);
        words->assign({"2", "12"});
        thesaurus.AddSynonyms(words);
        words->assign({"3", "13"});
        thesaurus.AddSynonyms(words);
        words->assign({"1", "3", "5", "7", "9"});
        thesaurus.AddSynonyms(words);
        words->assign({"11", "13", "15", "17", "19"});
        thesaurus.AddSynonyms(words);
        words->assign({"0", "2", "4", "6", "8"});
        thesaurus.AddSynonyms(words);
        words->assign({"10", "12", "14", "16", "18", "20"});
        thesaurus.AddSynonyms(words);
        words->assign({"1", "10"});
        thesaurus.AddSynonyms(words);
        words->assign({"2", "11", "20"});
        thesaurus.AddSynonyms(words);
        words->assign({"3", "12"});
        thesaurus.AddSynonyms(words);
        words->assign({"4", "13"});
        thesaurus.AddSynonyms(words);
        words->assign({"5", "14"});
        thesaurus.AddSynonyms(words);
        words->assign({"6", "15"});
        thesaurus.AddSynonyms(words);
        words->assign({"7", "16"});
        thesaurus.AddSynonyms(words);
        words->assign({"8", "17"});
        thesaurus.AddSynonyms(words);
        words->assign({"9", "18"});
        thesaurus.AddSynonyms(words);
        words->assign({"5", "10", "15", "20"});
        thesaurus.AddSynonyms(words);
        words->assign({"7", "14"});
        thesaurus.AddSynonyms(words);

        thesaurus.PrintAllEntries();

        result = thesaurus.GetSynonyms("0");
        words->assign({"1", "10", "2", "20", "3", "4", "5", "6", "7", "8", "9"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("1");
        words->assign({"0", "10", "11", "2", "3", "4", "5", "6", "7", "8", "9"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("2");
        words->assign({"0", "1", "11", "12", "20", "3", "4", "5", "6", "7", "8", "9"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("3");
        words->assign({"0", "1", "12", "13", "2", "4", "5", "6", "7", "8", "9"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("4");
        words->assign({"0", "1", "13", "2", "3", "5", "6", "7", "8", "9"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("5");
        words->assign({"0", "1", "10", "14", "15", "2", "20", "3", "4", "6", "7", "8", "9"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("6");
        words->assign({"0", "1", "15", "2", "3", "4", "5", "7", "8", "9"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("7");
        words->assign({"0", "1", "14", "16", "2", "3", "4", "5", "6", "8", "9"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("8");
        words->assign({"0", "1", "17", "2", "3", "4", "5", "6", "7", "9"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("9");
        words->assign({"0", "1", "18", "2", "3", "4", "5", "6", "7", "8"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("10");
        words->assign({"0", "1", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "5"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("11");
        words->assign({"1", "10", "12", "13", "14", "15", "16", "17", "18", "19", "2", "20"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("12");
        words->assign({"10", "11", "13", "14", "15", "16", "17", "18", "19", "2", "20", "3"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("13");
        words->assign({"10", "11", "12", "14", "15", "16", "17", "18", "19", "3", "4"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("14");
        words->assign({"10", "11", "12", "13", "15", "16", "17", "18", "19", "20", "5", "7"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("15");
        words->assign({"10", "11", "12", "13", "14", "16", "17", "18", "19", "20", "5", "6"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("16");
        words->assign({"10", "11", "12", "13", "14", "15", "17", "18", "19", "20", "7"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("17");
        words->assign({"10", "11", "12", "13", "14", "15", "16", "18", "19", "8"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("18");
        words->assign({"10", "11", "12", "13", "14", "15", "16", "17", "19", "20", "9"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("19");
        words->assign({"10", "11", "12", "13", "14", "15", "16", "17", "18"});
        CompareVectors(words, result);
        delete result;

        result = thesaurus.GetSynonyms("20");
        words->assign({"0", "10", "11", "12", "14", "15", "16", "18", "2", "5"});
        CompareVectors(words, result);
        delete result;
    }
}
