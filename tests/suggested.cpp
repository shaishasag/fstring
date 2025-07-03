#include "gtest/gtest.h"
#include <string>
#include <random>
#include <algorithm>
#include <unordered_set>
#include "fstringstream.h"

// Asked ChatGPT to create test for std::string like functionality.
// after some negotiations this is what it came up with. I added
// some fstr_ref variations


#define ExpectEqualToStd(mystr, stdstr)                         \
    do {                                                        \
        std::string_view as_sv(stdstr);                         \
        EXPECT_EQ((mystr).size(), as_sv.size());                \
        EXPECT_EQ((mystr).empty(), as_sv.empty());              \
        EXPECT_EQ(std::string((mystr).begin(), (mystr).end()), as_sv); \
        EXPECT_STREQ((mystr).c_str(), as_sv.data());           \
    } while (0)

TEST(FStringEdgeTest, SelfAssignment)
{
    fstr::fstr31 s("selfie");
    s = s;
    ExpectEqualToStd(s, "selfie");
    
    fstr::fstr_ref s_ref(s);
    s_ref = s_ref;
    ExpectEqualToStd(s, "selfie");
    ExpectEqualToStd(s_ref, "selfie");

    s_ref = s;
    ExpectEqualToStd(s, "selfie");
    ExpectEqualToStd(s_ref, "selfie");

    s = s_ref;
    ExpectEqualToStd(s, "selfie");
    ExpectEqualToStd(s_ref, "selfie");
    
    // self assign with shorter size
    std::string_view shorter_sv(s.data(), 4);
    s = shorter_sv;
    ExpectEqualToStd(s, "self");
    ExpectEqualToStd(s_ref, "self");
    
    // self assign from the middle - will it work?
    fstr::fstr31 s1("birdie");
    fstr::fstr_ref s1_ref(s1);
    std::string_view middle_sv(s1.data()+2, 2);
    s1 = middle_sv;
    ExpectEqualToStd(s1, "rd");
    ExpectEqualToStd(s1_ref, "rd");
}

TEST(FStringEdgeTest, SelfAppend)
{
    fstr::fstr127 s("loop");
    s += s;
    ExpectEqualToStd(s, "looploop");
    
    fstr::fstr_ref s_ref(s);
    s += s_ref;
    ExpectEqualToStd(s, "looplooplooploop");
    s_ref += s;
    ExpectEqualToStd(s, "looplooplooplooplooplooplooploop");
    s_ref += s_ref;
    ExpectEqualToStd(s, "looplooplooplooplooplooplooplooplooplooplooplooplooplooplooploop");
}

TEST(FStringEdgeTest, InsertBoundary)
{
    fstr::fstr31 s("mid");
    s.insert(0, "A"); // Start
    s.insert(s.size(), "Z"); // End
    ExpectEqualToStd(s, "AmidZ");
}

TEST(FStringEdgeTest, EraseAll)
{
    fstr::fstr31 s("complete");
    s.erase(0, s.size());
    EXPECT_TRUE(s.empty());
}

TEST(FStringEdgeTest, ReplaceEmbeddedNulls)
{
    std::string raw("a\0b\0c", 5);
    fstr::fstr31 s(raw);
    EXPECT_EQ(s.size(), 5);
    EXPECT_EQ(std::string(s.begin(), s.end()), raw);
}

TEST(FStringEdgeTest, ResizeGrowShrink)
{
    fstr::fstr31 s("abc");
    s.resize(10, 'x');
    EXPECT_EQ(s.size(), 10);
    EXPECT_EQ(s[9], 'x');
    s.resize(2);
    ExpectEqualToStd(s, "ab");
}

TEST(FStringEdgeTest, IteratorRoundTrip)
{
    fstr::fstr31 s("hello");
    std::string ref(s.begin(), s.end());
    EXPECT_EQ(ref, "hello");
}

TEST(FStringEdgeTest, IteratorStability)
{
    fstr::fstr31 s("123456");
    [[maybe_unused]] auto it = s.begin();
    s += "789"; // Iterator may be invalidated if using dynamic buffer
    // Ensure iterator isn't used after invalidation
    EXPECT_EQ(*s.begin(), '1');
}

TEST(FStringExceptionTest, OutOfRange)
{
    fstr::fstr31 s("safe");
    EXPECT_THROW(s.at(999), std::out_of_range);
    EXPECT_NO_THROW(s.at(0));
}

TEST(FStringCompatibilityTest, HashWorksInUnorderedSet)
{
    std::unordered_set<fstr::fstr31, fstr::fstr_hasher> set;
    set.insert(fstr::fstr31("alpha"));
    set.insert(fstr::fstr31("beta"));
    EXPECT_EQ(set.count("alpha"), 1);
    EXPECT_EQ(set.count("gamma"), 0);
}

std::string RandomAsciiString(size_t len)
{
    static std::mt19937 rng(12345);
    static std::uniform_int_distribution<int> dist(32, 126); // Printable ASCII range

    std::string s;
    s.reserve(len);
    for (size_t i = 0; i < len; ++i)
        s.push_back(static_cast<char>(dist(rng)));
    return s;
}

TEST(FStringFuzzTest, RandomConstructionAndCopy)
{
    for (int i = 0; i < 1000; ++i)
    {
        auto raw = RandomAsciiString(i % 100);  // up to 100 chars
        fstr::fstr127 mine(raw);
        ExpectEqualToStd(mine, raw);

        fstr::fstr127 a_copy = mine;
        ExpectEqualToStd(a_copy, raw);
    }
}

TEST(FStringFuzzTest, RandomConcatenation)
{
    for (int i = 0; i < 500; ++i)
{
        std::string a = RandomAsciiString(i % 50);
        std::string b = RandomAsciiString(i % 50);

        fstr::fstr1023 m1(a), m2(b);
        m1 += m2;

        std::string ref = a + b;
        ExpectEqualToStd(m1, ref);
    }
}

TEST(FStringFuzzTest, RandomInsertAndErase)
{
    for (int i = 0; i < 300; ++i)
    {
        std::string base = RandomAsciiString(100);
        std::string insert = RandomAsciiString(10);

        fstr::fstr1023 m(base);
        size_t pos = rand() % (m.size() + 1);
        m.insert(pos, insert);

        std::string ref = base;
        ref.insert(pos, insert);
        ExpectEqualToStd(m, ref);

        size_t erase_pos = rand() % m.size();
        size_t erase_len = rand() % (m.size() - erase_pos + 1);
        m.erase(erase_pos, erase_len);
        ref.erase(erase_pos, erase_len);
        ExpectEqualToStd(m, ref);
    }
}

TEST(FStringFindTest, FindBasic)
{
    fstr::fstr127 s("hello world");

    EXPECT_EQ(s.sv().find("world"), 6);
    EXPECT_EQ(s.sv().find("lo"), 3);
    EXPECT_EQ(s.sv().find("x"), fstr::npos);
    EXPECT_EQ(s.sv().find("hello", 1), fstr::npos);
    EXPECT_EQ(s.sv().find("o", 5), 7);
}

TEST(FStringFindTest, RFindBasic)
{
    fstr::fstr127 s("abracadabra");

    EXPECT_EQ(s.sv().rfind("abra"), 7);
    EXPECT_EQ(s.sv().rfind("a"), 10);
    EXPECT_EQ(s.sv().rfind("z"), fstr::npos);
    EXPECT_EQ(s.sv().rfind("abra", 6), 0);
}

TEST(FStringFindTest, FindFirstOf)
{
    fstr::fstr127 s("alphabet soup");

    EXPECT_EQ(s.sv().find_first_of("aeiou"), 0);  // 'a'
    EXPECT_EQ(s.sv().find_first_of("xyz"), fstr::npos);
    EXPECT_EQ(s.sv().find_first_of("soup"), 2);   // 's'
}

TEST(FStringFindTest, FindLastOf)
{
    fstr::fstr127 s("foobar");

    EXPECT_EQ(s.sv().find_last_of("aeiou"), 4);   // 'o'
    EXPECT_EQ(s.sv().find_last_of("xyz"), fstr::npos);
}

TEST(FStringFindTest, FindFirstNotOf)
{
    fstr::fstr127 s("aaabbbcccXYZ");

    EXPECT_EQ(s.sv().find_first_not_of("abc"), 9); // 'X'
    EXPECT_EQ(s.sv().find_first_not_of("abcXYZ"), fstr::npos);
}

TEST(FStringFindTest, FindLastNotOf)
{
    fstr::fstr127 s("XYZccc");

    EXPECT_EQ(s.sv().find_last_not_of("c"), 2); // 'Z'
    EXPECT_EQ(s.sv().find_last_not_of("XYZc"), fstr::npos);
}

TEST(FStringFindTest, FindOnEmpty)
{
    fstr::fstr127 s("");

    EXPECT_EQ(s.sv().find("anything"), fstr::npos);
    EXPECT_EQ(s.sv().rfind("x"), fstr::npos);
    EXPECT_EQ(s.sv().find_first_of("abc"), fstr::npos);
}

TEST(FStringFindTest, FindEmptyNeedle)
{
    fstr::fstr127 s("abc");

    EXPECT_EQ(s.sv().find(""), 0);  // Per std::string rules
    EXPECT_EQ(s.sv().rfind(""), s.size());
    EXPECT_EQ(s.sv().find_first_of(""), fstr::npos);
    EXPECT_EQ(s.sv().find_first_not_of(""), 0);   // Everything is not in empty set
}

TEST(FStringFindTest, FindWithPositionBeyondEnd)
{
    fstr::fstr127 s("test");

    EXPECT_EQ(s.sv().find("e", 10), fstr::npos);
    EXPECT_EQ(s.sv().rfind("t", 100), 3);
}

// ---------- assign ----------
TEST(FStringApiTest, AssignBasic)
{
    fstr::fstr127 s;
    s.assign("hello");
    ExpectEqualToStd(s, "hello");

    s.assign("hi there", 2);
    ExpectEqualToStd(s, "hi");
}

// ---------- front / back ----------
TEST(FStringApiTest, FrontBackAccess)
{
    fstr::fstr127 s("abc");
    EXPECT_EQ(s.front(), 'a');
    EXPECT_EQ(s.back(), 'c');

    s.front() = 'x';
    s.back() = 'z';
    ExpectEqualToStd(s, "xbz");
}

// ---------- data + string_view ----------
TEST(FStringApiTest, DataAndStringView)
{
    fstr::fstr127 s("Joseph Stilwell");
    std::string_view sv = static_cast<std::string_view>(s);

    EXPECT_EQ(std::string(s.data(), s.size()), "Joseph Stilwell");
    EXPECT_EQ(sv, "Joseph Stilwell");
}

// ---------- iterators ----------
TEST(FStringApiTest, Iterators)
{
    fstr::fstr127 s("abcd");

    EXPECT_EQ(*s.begin(), 'a');
    EXPECT_EQ(*(s.end() - 1), 'd');
    EXPECT_EQ(*s.cbegin(), 'a');
    EXPECT_EQ(*(s.cend() - 1), 'd');

    EXPECT_EQ(*s.rbegin(), 'd');
    EXPECT_EQ(*(s.rend() - 1), 'a');
    EXPECT_EQ(*s.crbegin(), 'd');
    EXPECT_EQ(*(s.crend() - 1), 'a');

    std::string forward(s.begin(), s.end());
    std::string backward(s.rbegin(), s.rend());
    EXPECT_EQ(forward, "abcd");
    EXPECT_EQ(backward, "dcba");
}

// ---------- append / operator+= ----------
TEST(FStringApiTest, AppendAndPlusEqual)
{
    fstr::fstr127 s("foo");

    s.append("bar");
    ExpectEqualToStd(s, "foobar");

    s += "baz";
    ExpectEqualToStd(s, "foobarbaz");
}

// ---------- replace ----------
TEST(FStringApiTest, ReplaceSubstring)
{
    fstr::fstr127 s("I love cats");
    fstr::fstr_ref s_ref(s);
    s.replace(7, 4, "dogs");
    
    ExpectEqualToStd(s, "I love dogs");
    ExpectEqualToStd(s_ref, "I love dogs");
}

// ---------- starts_with / ends_with / contains ----------
TEST(FStringApiTest, StartsEndsContains)
{
    fstr::fstr127 s("Barbara W. Tuchman");

    EXPECT_TRUE(s.starts_with("Barb"));
    EXPECT_TRUE(s.ends_with("man"));
    EXPECT_TRUE(s.contains("Tuch"));
    EXPECT_FALSE(s.starts_with("close"));
    EXPECT_FALSE(s.contains("xyz"));
    
    fstr::fstr_ref s_ref(s);
    EXPECT_TRUE(s_ref.starts_with("Barb"));
    EXPECT_TRUE(s_ref.ends_with("man"));
    EXPECT_TRUE(s_ref.contains("Tuch"));
    EXPECT_FALSE(s_ref.starts_with("close"));
    EXPECT_FALSE(s_ref.contains("xyz"));
}

// ---------- substr ----------
TEST(FStringApiTest, SubstrBasic)
{
    fstr::fstr127 s("abcdefg");

    fstr::fstr127 sub = s.sv().substr(2, 3);
    ExpectEqualToStd(sub, "cde");

    sub = s.sv().substr(5);
    ExpectEqualToStd(sub, "fg");

    sub = s.sv().substr(0, 100);  // Should clamp to end
    ExpectEqualToStd(sub, "abcdefg");
}

// ---------- compare ----------
TEST(FStringApiTest, CompareLexicographic)
{
    fstr::fstr127 a("apple");
    fstr::fstr127 b("banana");
    fstr::fstr127 c("apple");

    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
    EXPECT_EQ(a.compare(c), 0);
}

TEST(FStringMemoryCopyTest, MemcpyRoundTrip)
{
    char buffer[sizeof(fstr::fstr127)];
   
    {
        fstr::fstr127 original("hello memory");
        // Raw copy into buffer
        std::memcpy(buffer, &original, sizeof(fstr::fstr127));
    }

    // Reconstruct fstr::fstr127 from raw memory, original already destructed
    fstr::fstr127* copied = reinterpret_cast<fstr::fstr127*>(buffer);

    // Verify behavior
    ExpectEqualToStd(*copied, "hello memory");

    // Optional: create copy into actual object
    fstr::fstr127 safe_copy = *copied;
    std::fill(buffer, buffer+sizeof(fstr::fstr127), '\0'); // erase the buffer
    
    ExpectEqualToStd(safe_copy, "hello memory");
}

TEST(FStringMemoryCopyTest, MemmoveSafe)
{
    fstr::fstr127 original("abcdefg");
    alignas(fstr::fstr127) char storage[sizeof(fstr::fstr127)];

    std::memmove(storage, &original, sizeof(fstr::fstr127));

    fstr::fstr127* moved = reinterpret_cast<fstr::fstr127*>(storage);
    ExpectEqualToStd(*moved, "abcdefg");
}

TEST(FStringMemoryCopyTest, TriviallyCopyableCheck) {
#if defined(__cpp_lib_is_trivially_copyable)
    static_assert(std::is_trivially_copyable<fstr::fstr127>::value,
                  "fstr::fstr127 must be trivially copyable");
#endif
}

TEST(FStringIteratorTest, RangeBasedFor)
{
    fstr::fstr127 s("hello");
    std::string result;

    for (char c : s) {
        result.push_back(c);
    }

    EXPECT_EQ(result, "hello");
}

TEST(FStringIteratorTest, IteratorForLoop)
{
    fstr::fstr127 s("world");
    std::string result;

    for (fstr::fstr127::iterator it = s.begin(); it != s.end(); ++it) {
        result.push_back(*it);
    }

    EXPECT_EQ(result, "world");
}

TEST(FStringIteratorTest, ConstIteration)
{
    const fstr::fstr127 s("const");

    std::string result;
    for (auto it = s.cbegin(); it != s.cend(); ++it) {
        result.push_back(*it);
    }

    EXPECT_EQ(result, "const");
}

TEST(FStringIteratorTest, ReverseIteration)
{
    fstr::fstr127 s("abcd");
    std::string result;

    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        result.push_back(*it);
    }

    EXPECT_EQ(result, "dcba");
}

TEST(FStringIteratorTest, ConstReverseIteration)
{
    const fstr::fstr127 s("reverse");

    std::string result;
    for (auto it = s.crbegin(); it != s.crend(); ++it) {
        result.push_back(*it);
    }

    EXPECT_EQ(result, "esrever");
}
