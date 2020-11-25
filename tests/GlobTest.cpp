#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include<gtest/gtest.h>

#include<Glob.h>

TEST(Glob, BasicTest){
    Glob glob = Glob();
    std::vector<Path>* result = glob.glob("/dummyTest/asd");
  ASSERT_EQ(result->size(), 0);
}

TEST(Glob, )


#pragma clang diagnostic pop