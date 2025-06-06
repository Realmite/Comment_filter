#include "pch.h"
#include "CppUnitTest.h"
#include "../CommentFilter/comment_filter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommentFilterTests
{
    TEST_CLASS(RemoveMultilineCommentsTests)
    {
    public:

        TEST_METHOD(Test_MultilineCommentRemoved)
        {
            std::string input = "int a = 5; /* this is a comment */ int b = 6;";
            std::string expected = "int a = 5;  int b = 6;";
            Assert::AreEqual(expected, removeMultilineCommentsFromText(input));
        }

        TEST_METHOD(Test_CommentInsideStringPreserved)
        {
            std::string input = "std::string s = \"text /* not a comment */\";";
            std::string expected = "std::string s = \"text /* not a comment */\";";
            Assert::AreEqual(expected, removeMultilineCommentsFromText(input));
        }

        TEST_METHOD(Test_MultipleMultilineComments)
        {
            std::string input = "int a; /* comment1 */ int b; /* comment2 */ int c;";
            std::string expected = "int a;  int b;  int c;";
            Assert::AreEqual(expected, removeMultilineCommentsFromText(input));
        }

        TEST_METHOD(Test_StringWithEscapedQuotes)
        {
            std::string input = "std::string s = \"value with \\\"quote\\\" inside\";";
            std::string expected = "std::string s = \"value with \\\"quote\\\" inside\";";
            Assert::AreEqual(expected, removeMultilineCommentsFromText(input));
        }

        TEST_METHOD(Test_SingleLineCommentPreserved)
        {
            std::string input = "int x = 0; // this is a comment\nx++;";
            std::string expected = "int x = 0; // this is a comment\nx++;";
            Assert::AreEqual(expected, removeMultilineCommentsFromText(input));
        }

        TEST_METHOD(Test_NoComments)
        {
            std::string input = "int main() { return 0; }";
            std::string expected = "int main() { return 0; }";
            Assert::AreEqual(expected, removeMultilineCommentsFromText(input));
        }

        TEST_METHOD(Test_MultilineCommentWithNewlines)
        {
            std::string input =
                "int a = 5;\n/* this is\na multiline\ncomment */\nint b = 6;";

            std::string expected =
                "int a = 5;\n\nint b = 6;";

            Assert::AreEqual(expected, removeMultilineCommentsFromText(input));
        }
    };
}
