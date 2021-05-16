#include <gtest/gtest.h>

#include "Thesaurus.h"

TEST(Thesaurus, AddSynonyms) {
    CThesaurus thesaurus;
    vector<string>* result;
    vector<string>* words = new vector<string>;
    words->insert(words->end(), {"VW", "golf", "passat", "polo"});
    thesaurus.AddSynonyms(words);
    thesaurus.PrintAllEntries();
    result = thesaurus.GetSynonyms(words->at(0));
    words->erase(words->begin());
    ASSERT_EQ(words->size(), result->size()) << "Input and output vectors don't have the same size";
    for (int i = 0; i < words->size(); ++i) {
        EXPECT_EQ(words->at(i), result->at(i)) << "Input and output vectors differ at index " << i;
    }

    delete words;
}
