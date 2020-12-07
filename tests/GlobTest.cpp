#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include<gtest/gtest.h>
#include<Glob.h>

using namespace gh;

void createFile(const std::string& filename){
    std::ofstream MyFile(filename);
    MyFile << "Files can be tricky, but it is fun enough!";
    MyFile.close();
}

bool createDirectory(const std::string& relativePath){
    return boost::filesystem::create_directory(Path(relativePath));
}

bool remove(const std::string& path){
    Path _path = path;
    boost::filesystem::remove_all(_path);
    return !boost::filesystem::exists(_path);
}

class Glob_OneFile : public ::testing::Test {
protected:
    void SetUp() override {
        createFile("file_1");
    }
    void TearDown() override {
        remove("file_1");
    }
};

TEST(Glob, BasicTest){
    Glob glob = Glob();
    ASSERT_THROW(glob.glob("./dummyTest/asd"), FileNotFoundException);
}

TEST(Glob, DirectoryExistsEmpty_NoGlobbing){
    Glob glob = Glob();
    std::vector<Path>* result = glob.glob(".");
    ASSERT_EQ(result->size(), 0);
}

TEST_F(Glob_OneFile, DirectoryExists_NoGlobbing){
    Glob glob = Glob();
    std::vector<Path>* result = glob.glob(".");
    ASSERT_EQ(result->size(), 0);
}

TEST_F(Glob_OneFile, DirectoryExists_DotSlash){
    Glob glob = Glob();
    std::vector<Path>* result = glob.glob("./");
    ASSERT_EQ(result->size(), 0);
}

TEST_F(Glob_OneFile, DirectoryExists_DotSlashStar){
    Glob glob = Glob();
    std::vector<Path>* result = glob.glob("./*");
    ASSERT_EQ(result->size(), 1);
    ASSERT_EQ(result->operator[](0).string(), "./file_1");
}

TEST_F(Glob_OneFile, DirectoryExists_DotSlashQuestionMark){
    Glob glob = Glob();
    std::vector<Path>* result = glob.glob("./?");
    ASSERT_EQ(result->size(), 0);
}

TEST_F(Glob_OneFile, DirectoryExists_DotSlashFile_QM){
    Glob glob = Glob();
    std::vector<Path>* result = glob.glob("./file_?");
    ASSERT_EQ(result->size(), 1);
    ASSERT_EQ(result->operator[](0).string(), "./file_1");
}


#pragma clang diagnostic pop