#include "gtest/gtest.h"
#include "fstring.h"
#include "fstringstream.h"
#include <string_view>
#include <string>
#include <sstream>

TEST(Stream, stream_numbers)
{
    {
        fstr::fstr127 fs;
        fs << true;
        EXPECT_STREQ(fs.c_str(), "true");
        fs << false;
        EXPECT_STREQ(fs.c_str(), "truefalse");

        fstr::fstr_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << true;
        EXPECT_STREQ(fs_ref.c_str(), "true");
        fs_ref << false;
        EXPECT_STREQ(fs_ref.c_str(), "truefalse");
    }
    {
        fstr::fstr127 fs;
        fs << 'z';
        EXPECT_STREQ(fs.c_str(), "z");

        fstr::fstr_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << 'z';
        EXPECT_STREQ(fs_ref.c_str(), "z");
    }
    {
        fstr::fstr127 fs;
        fs << 17;
        EXPECT_STREQ(fs.c_str(), "17");

        fstr::fstr_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << 17;
        EXPECT_STREQ(fs_ref.c_str(), "17");
    }
    {
        fstr::fstr127 fs;
        fs << 18446744073709551615U;
        EXPECT_STREQ(fs.c_str(), "18446744073709551615");

        fstr::fstr_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << 18446744073709551615U;
        EXPECT_STREQ(fs_ref.c_str(), "18446744073709551615");
    }
}

TEST(Stream, stream_strs)
{
    {
        fstr::fstr127 fs;
        fs << "Potassium";
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fstr::fstr_ref fs_ref(fs);
        fs_ref << "Potassium";
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fstr::fstr127 fs;
        fs << fstr::fstr15("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fstr::fstr_ref fs_ref(fs);
        fs_ref << fstr::fstr15("Potassium");
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fstr::fstr127 fs;
        fstr::fstr15 ps("Potassium");
        fs << fstr::fstr_ref(ps);
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fstr::fstr_ref fs_ref(fs);
        fs_ref << fstr::fstr_ref(ps);
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fstr::fstr127 fs;
        fs << std::string_view("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fstr::fstr_ref fs_ref(fs);
        fs_ref << std::string_view("Potassium");
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fstr::fstr127 fs;
        fs << std::string("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fstr::fstr_ref fs_ref(fs);
        fs_ref << std::string("Potassium");
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
}

TEST(Stream, more_streaming)
{
    {   // stream to fstr with integer and boolean
        fstr::fstr31 vari;
        vari << "The" << ' ' << 3 << ' ' << "Musketeers? " << true;
        EXPECT_EQ(vari, "The 3 Musketeers? true");
    }
    {   // stream to fstr_ref with integer and boolean
        fstr::fstr31 vari;
        fstr::fstr_ref vari_ref{vari};
        vari_ref << "The" << ' ' << 3 << ' ' << "Musketeers? " << true;
        EXPECT_EQ(vari, "The 3 Musketeers? true");
        EXPECT_EQ(vari_ref, "The 3 Musketeers? true");
    }
    {   // stream to fstr with float and boolean
        fstr::fstr63 vari;
        vari << "The" << ' ' << 3.1415 << ' ' << "Musketeers? " << false;
        EXPECT_EQ(vari, "The 3.14150000000000018 Musketeers? false");
    }
    {   // stream to fstr_ref with float and boolean
        fstr::fstr63 vari;
        fstr::fstr_ref vari_ref{vari};
        vari_ref << "The" << ' ' << 3.1415 << ' ' << "Musketeers? " << false;
        EXPECT_EQ(vari, vari_ref);
        EXPECT_EQ(vari, "The 3.14150000000000018 Musketeers? false"sv);
        EXPECT_EQ(vari_ref, "The 3.14150000000000018 Musketeers? false"sv);
    }
}

TEST(Stream, quote_me)
{
    fstr::fstr63 vari;
    vari << fstr::quote_me("bananarama");
    EXPECT_EQ(vari, "\"bananarama\"");

}

TEST(Stream, quote_me_value_categories)
{
    // an lvalue must deduce as well as a temporary - this is what the explicit
    // deduction guide is for, without it only rvalues compiled
    {
        std::string_view lvalue_sv{"lvalue_sv"};
        fstr::fstr63 fs;
        fs << fstr::quote_me(lvalue_sv);
        EXPECT_EQ(fs.sv(), "\"lvalue_sv\""sv);
    }
    {
        const std::string_view const_lvalue_sv{"const_lvalue_sv"};
        fstr::fstr63 fs;
        fs << fstr::quote_me(const_lvalue_sv);
        EXPECT_EQ(fs.sv(), "\"const_lvalue_sv\""sv);
    }
    {   // prvalue returned from a function
        fstr::fstr63 fs;
        fs << fstr::quote_me(std::string_view("prvalue_sv"));
        EXPECT_EQ(fs.sv(), "\"prvalue_sv\""sv);
    }
    {   // a named quote_me, not just a temporary in the stream expression
        std::string_view lvalue_sv{"named"};
        const auto quoted = fstr::quote_me(lvalue_sv);
        fstr::fstr63 fs;
        fs << quoted;
        EXPECT_EQ(fs.sv(), "\"named\""sv);
    }
}

TEST(Stream, quote_me_types)
{
    {   // const char* variable, not a literal
        const char* c_str = "char_ptr";
        fstr::fstr63 fs;
        fs << fstr::quote_me(c_str);
        EXPECT_EQ(fs.sv(), "\"char_ptr\""sv);
    }
    {
        char char_array[] = "char_array";
        fstr::fstr63 fs;
        fs << fstr::quote_me(char_array);
        EXPECT_EQ(fs.sv(), "\"char_array\""sv);
    }
    {
        std::string std_str{"std_string"};
        fstr::fstr63 fs;
        fs << fstr::quote_me(std_str);
        EXPECT_EQ(fs.sv(), "\"std_string\""sv);
    }
    {   // fstring and a reference to one
        fstr::fstr31 inner("an_fstr");
        fstr::fstr63 fs;
        fs << fstr::quote_me(inner);
        EXPECT_EQ(fs.sv(), "\"an_fstr\""sv);

        fstr::fstr_ref inner_ref{inner};
        fs.clear();
        fs << fstr::quote_me(inner_ref);
        EXPECT_EQ(fs.sv(), "\"an_fstr\""sv);
    }
    {   // temporary fstring: the reference member must stay valid for the
        // whole full-expression
        fstr::fstr63 fs;
        fs << fstr::quote_me(fstr::fstr31("temporary"));
        EXPECT_EQ(fs.sv(), "\"temporary\""sv);
    }
    {   // non-string types go through the same streaming operators
        fstr::fstr63 fs;
        fs << fstr::quote_me('x');
        EXPECT_EQ(fs.sv(), "\"x\""sv);
        fs.clear();
        fs << fstr::quote_me(42);
        EXPECT_EQ(fs.sv(), "\"42\""sv);
        fs.clear();
        fs << fstr::quote_me(2.5);
        EXPECT_EQ(fs.sv(), "\"2.5\""sv);
        fs.clear();
        fs << fstr::quote_me(true);
        EXPECT_EQ(fs.sv(), "\"true\""sv);
    }
}

TEST(Stream, quote_me_empty_and_nested_quotes)
{
    {   // empty input still produces the two quotes
        fstr::fstr63 fs;
        fs << fstr::quote_me("");
        EXPECT_EQ(fs.sv(), "\"\""sv);
        EXPECT_EQ(fs.size(), 2);
    }
    {
        fstr::fstr63 fs;
        fs << fstr::quote_me(std::string_view{});
        EXPECT_EQ(fs.sv(), "\"\""sv);
    }
    {   // quote_me does not escape: quotes in the input are passed through
        fstr::fstr63 fs;
        fs << fstr::quote_me("say \"hi\"");
        EXPECT_EQ(fs.sv(), "\"say \"hi\"\""sv);
    }
}

TEST(Stream, quote_me_append_and_chain)
{
    {   // appends, does not replace
        fstr::fstr63 fs("pre:");
        fs << fstr::quote_me("mid") << "|" << fstr::quote_me("end");
        EXPECT_EQ(fs.sv(), "pre:\"mid\"|\"end\""sv);
    }
    {   // through an fstr_ref, and both views agree
        fstr::fstr63 fs;
        fstr::fstr_ref fs_ref{fs};
        fs_ref << fstr::quote_me("via_ref");
        EXPECT_EQ(fs.sv(), "\"via_ref\""sv);
        EXPECT_EQ(fs, fs_ref);
    }
}

TEST(Stream, quote_me_other_streams)
{
    {   // std::ostringstream, not only fstr streams
        std::ostringstream os;
        os << fstr::quote_me("ostringstream");
        EXPECT_EQ(os.str(), "\"ostringstream\"");
    }
    {   // an fstring as the quoted value, on a std stream
        fstr::fstr31 inner("inner_fstr");
        std::ostringstream os;
        os << fstr::quote_me(inner);
        EXPECT_EQ(os.str(), "\"inner_fstr\"");
    }
    {   // non-string values, and chaining around them
        std::ostringstream os;
        os << "pre:" << fstr::quote_me(42) << '|' << fstr::quote_me(2.5);
        EXPECT_EQ(os.str(), "pre:\"42\"|\"2.5\"");
    }
    {   // the std::ostream& return type is propagated, so << keeps chaining
        std::ostringstream os;
        static_assert(std::is_same_v<decltype(os << fstr::quote_me("x")), std::ostream&>);
        os << fstr::quote_me("a") << fstr::quote_me("b");
        EXPECT_EQ(os.str(), "\"a\"\"b\"");
    }
}

TEST(Stream, wrap_me_named_wrappers)
{
    std::string_view value{"val"};
    {
        fstr::fstr63 fs;
        fs << fstr::quote_me(value);
        EXPECT_EQ(fs.sv(), "\"val\""sv);
    }
    {
        fstr::fstr63 fs;
        fs << fstr::single_quote_me(value);
        EXPECT_EQ(fs.sv(), "'val'"sv);
    }
    {
        fstr::fstr63 fs;
        fs << fstr::brace_me(value);
        EXPECT_EQ(fs.sv(), "[val]"sv);
    }
    {
        fstr::fstr63 fs;
        fs << fstr::curly_brace_me(value);
        EXPECT_EQ(fs.sv(), "{val}"sv);
    }
    {
        fstr::fstr63 fs;
        fs << fstr::angle_brace_me(value);
        EXPECT_EQ(fs.sv(), "<val>"sv);
    }
    {
        fstr::fstr63 fs;
        fs << fstr::parenthesize_me(value);
        EXPECT_EQ(fs.sv(), "(val)"sv);
    }
    {   // the opening/closing characters are available without an instance
        static_assert(fstr::quote_me<int>::opening_char == '"');
        static_assert(fstr::brace_me<int>::closing_char == ']');
        static_assert(fstr::angle_brace_me<int>::opening_char == '<');
    }
}

TEST(Stream, wrap_me_arbitrary_chars)
{
    std::string_view value{"val"};
    {   // wrap() takes the characters explicitly and deduces the value type
        fstr::fstr63 fs;
        fs << fstr::wrap<'|', '|'>(value);
        EXPECT_EQ(fs.sv(), "|val|"sv);
    }
    {   // the closing character defaults to the opening one
        fstr::fstr63 fs;
        fs << fstr::wrap<'|'>(value);
        EXPECT_EQ(fs.sv(), "|val|"sv);
    }
    {   // asymmetric, still without naming the value type
        fstr::fstr63 fs;
        fs << fstr::wrap<'<', '>'>(value);
        EXPECT_EQ(fs.sv(), "<val>"sv);
    }
    {   // naming wrap_me itself: the value type is required, the closing
        // character is not
        fstr::fstr63 fs;
        fs << fstr::wrap_me<'#', std::string_view>(value);
        EXPECT_EQ(fs.sv(), "#val#"sv);
        static_assert(fstr::wrap_me<'#', std::string_view>::closing_char == '#');

        fs.clear();
        fs << fstr::wrap_me<'(', std::string_view, ')'>(value);
        EXPECT_EQ(fs.sv(), "(val)"sv);
    }
}

TEST(Stream, wrap_me_mixing_and_nesting)
{
    {   // different wrappers in one chain
        fstr::fstr63 fs;
        fs << fstr::brace_me("a") << fstr::curly_brace_me("b") << fstr::quote_me("c");
        EXPECT_EQ(fs.sv(), "[a]{b}\"c\""sv);
    }
    {   // a wrapped fstring that is itself wrapped
        fstr::fstr31 inner;
        inner << fstr::quote_me("in");
        fstr::fstr63 fs;
        fs << fstr::brace_me(inner);
        EXPECT_EQ(fs.sv(), "[\"in\"]"sv);
    }
    {   // non-string values, and on a std stream. The wrapped value is formatted
        // by the stream it is written to, not by wrap_me, so a bool comes out as
        // "true" on an fstr but as "1" on a std::ostream without boolalpha
        std::ostringstream os;
        os << fstr::angle_brace_me(42) << fstr::curly_brace_me(2.5) << fstr::brace_me(true);
        EXPECT_EQ(os.str(), "<42>{2.5}[1]");

        fstr::fstr63 fs;
        fs << fstr::brace_me(true);
        EXPECT_EQ(fs.sv(), "[true]"sv);
    }
}

TEST(Stream, quote_me_capacity_limits)
{
    {   // exactly enough room for the text plus both quotes
        fstr::fstring_base<12, char> fs;
        fs << fstr::quote_me("0123456789");
        EXPECT_EQ(fs.sv(), "\"0123456789\""sv);
        EXPECT_TRUE(fs.full());
    }
    {   // one char short: the closing quote is dropped rather than the text
        // being shortened, so the result is deliberately unbalanced
        fstr::fstring_base<11, char> fs;
        fs << fstr::quote_me("0123456789");
        EXPECT_EQ(fs.sv(), "\"0123456789"sv);
    }
    {   // room for the opening quote and one char only
        fstr::fstring_base<2, char> fs;
        fs << fstr::quote_me("abc");
        EXPECT_EQ(fs.sv(), "\"a"sv);
    }
    {   // room for nothing but the opening quote
        fstr::fstring_base<1, char> fs;
        fs << fstr::quote_me("abc");
        EXPECT_EQ(fs.sv(), "\""sv);
    }
    {   // already full: nothing is written and nothing overruns
        fstr::fstring_base<3, char> fs("abc");
        EXPECT_TRUE(fs.full());
        fs << fstr::quote_me("x");
        EXPECT_EQ(fs.sv(), "abc"sv);
    }
}
