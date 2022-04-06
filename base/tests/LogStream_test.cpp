#include "../LogStream.h"

#include <limits>
#include <stdint.h>

#include "gtest/gtest.h"

TEST(LogStreamTest, testLogStreamBooleans)
{
    cppl::LogStream os;
    const cppl::LogStream::Buffer &buf = os.buffer();
    EXPECT_EQ(buf.toString(), std::string(""));
    os << true;
    EXPECT_EQ(buf.toString(), std::string("1"));
    os << '\n';
    EXPECT_EQ(buf.toString(), std::string("1\n"));
    os << false;
    EXPECT_EQ(buf.toString(), std::string("1\n0"));
}

TEST(LogStreamTest, testLogStreamIntegers)
{
    cppl::LogStream os;
    const cppl::LogStream::Buffer &buf = os.buffer();
    EXPECT_EQ(buf.toString(), std::string(""));
    os << 1;
    EXPECT_EQ(buf.toString(), std::string("1"));
    os << 0;
    EXPECT_EQ(buf.toString(), std::string("10"));
    os << -1;
    EXPECT_EQ(buf.toString(), std::string("10-1"));
    os.resetBuffer();

    os << 0 << " " << 123 << 'x' << 0x64;
    EXPECT_EQ(buf.toString(), std::string("0 123x100"));
}

TEST(LogStreamTest, testLogStreamIntegerLimits)
{
    cppl::LogStream os;
    const cppl::LogStream::Buffer &buf = os.buffer();
    os << -2147483647;
    EXPECT_EQ(buf.toString(), std::string("-2147483647"));
    os << static_cast<int>(-2147483647 - 1);
    EXPECT_EQ(buf.toString(), std::string("-2147483647-2147483648"));
    os << ' ';
    os << 2147483647;
    EXPECT_EQ(buf.toString(), std::string("-2147483647-2147483648 2147483647"));
    os.resetBuffer();

    os << std::numeric_limits<int16_t>::min();
    EXPECT_EQ(buf.toString(), std::string("-32768"));
    os.resetBuffer();

    os << std::numeric_limits<int16_t>::max();
    EXPECT_EQ(buf.toString(), std::string("32767"));
    os.resetBuffer();

    os << std::numeric_limits<uint16_t>::min();
    EXPECT_EQ(buf.toString(), std::string("0"));
    os.resetBuffer();

    os << std::numeric_limits<uint16_t>::max();
    EXPECT_EQ(buf.toString(), std::string("65535"));
    os.resetBuffer();

    os << std::numeric_limits<int32_t>::min();
    EXPECT_EQ(buf.toString(), std::string("-2147483648"));
    os.resetBuffer();

    os << std::numeric_limits<int32_t>::max();
    EXPECT_EQ(buf.toString(), std::string("2147483647"));
    os.resetBuffer();

    os << std::numeric_limits<uint32_t>::min();
    EXPECT_EQ(buf.toString(), std::string("0"));
    os.resetBuffer();

    os << std::numeric_limits<uint32_t>::max();
    EXPECT_EQ(buf.toString(), std::string("4294967295"));
    os.resetBuffer();

    os << std::numeric_limits<int64_t>::min();
    EXPECT_EQ(buf.toString(), std::string("-9223372036854775808"));
    os.resetBuffer();

    os << std::numeric_limits<int64_t>::max();
    EXPECT_EQ(buf.toString(), std::string("9223372036854775807"));
    os.resetBuffer();

    os << std::numeric_limits<uint64_t>::min();
    EXPECT_EQ(buf.toString(), std::string("0"));
    os.resetBuffer();

    os << std::numeric_limits<uint64_t>::max();
    EXPECT_EQ(buf.toString(), std::string("18446744073709551615"));
    os.resetBuffer();

    int16_t a = 0;
    int32_t b = 0;
    int64_t c = 0;
    os << a;
    os << b;
    os << c;
    EXPECT_EQ(buf.toString(), std::string("000"));
}

TEST(LogStreamTest, testLogStreamFloats)
{
    cppl::LogStream os;
    const cppl::LogStream::Buffer &buf = os.buffer();

    os << 0.0;
    EXPECT_EQ(buf.toString(), std::string("0"));
    os.resetBuffer();

    os << 1.0;
    EXPECT_EQ(buf.toString(), std::string("1"));
    os.resetBuffer();

    os << 0.1;
    EXPECT_EQ(buf.toString(), std::string("0.1"));
    os.resetBuffer();

    os << 0.05;
    EXPECT_EQ(buf.toString(), std::string("0.05"));
    os.resetBuffer();

    os << 0.15;
    EXPECT_EQ(buf.toString(), std::string("0.15"));
    os.resetBuffer();

    double a = 0.1;
    os << a;
    EXPECT_EQ(buf.toString(), std::string("0.1"));
    os.resetBuffer();

    double b = 0.05;
    os << b;
    EXPECT_EQ(buf.toString(), std::string("0.05"));
    os.resetBuffer();

    double c = 0.15;
    os << c;
    EXPECT_EQ(buf.toString(), std::string("0.15"));
    os.resetBuffer();

    os << a + b;
    EXPECT_EQ(buf.toString(), std::string("0.15"));
    os.resetBuffer();

    EXPECT_TRUE(a + b != c);

    os << 1.23456789;
    EXPECT_EQ(buf.toString(), std::string("1.23456789"));
    os.resetBuffer();

    os << 1.234567;
    EXPECT_EQ(buf.toString(), std::string("1.234567"));
    os.resetBuffer();

    os << -123.456;
    EXPECT_EQ(buf.toString(), std::string("-123.456"));
    os.resetBuffer();
}

TEST(LogStreamTest, testLogStreamVoid)
{
    cppl::LogStream os;
    const cppl::LogStream::Buffer &buf = os.buffer();

    os << static_cast<void *>(0);
    EXPECT_EQ(buf.toString(), std::string("0x0"));
    os.resetBuffer();

    os << reinterpret_cast<void *>(8888);
    EXPECT_EQ(buf.toString(), std::string("0x22B8"));
    os.resetBuffer();
}

TEST(LogStreamTest, testLogStreamStrings)
{
    cppl::LogStream os;
    const cppl::LogStream::Buffer &buf = os.buffer();

    os << "Hello ";
    EXPECT_EQ(buf.toString(), std::string("Hello "));

    std::string test = "test";
    os << test;
    EXPECT_EQ(buf.toString(), std::string("Hello test"));
}

TEST(LogStreamTest, testLogStreamFmts)
{
    cppl::LogStream os;
    const cppl::LogStream::Buffer &buf = os.buffer();

    os << cppl::Fmt("%4d", 1);
    EXPECT_EQ(buf.toString(), std::string("   1"));
    os.resetBuffer();

    os << cppl::Fmt("%4.2f", 1.2);
    EXPECT_EQ(buf.toString(), std::string("1.20"));
    os.resetBuffer();

    os << cppl::Fmt("%4.2f", 1.2) << cppl::Fmt("%4d", 43);
    EXPECT_EQ(buf.toString(), std::string("1.20  43"));
    os.resetBuffer();
}

TEST(LogStreamTest, testLogStreamLong)
{
    cppl::LogStream os;
    const cppl::LogStream::Buffer &buf = os.buffer();
    for (int i = 0; i < 399; ++i)
    {
        os << "123456789 ";
        EXPECT_EQ(buf.length(), 10 * (i + 1));
        EXPECT_EQ(buf.avail(), 4000 - 10 * (i + 1));
    }

    os << "abcdefghi ";
    EXPECT_EQ(buf.length(), 3990);
    EXPECT_EQ(buf.avail(), 10);

    os << "abcdefghi";
    EXPECT_EQ(buf.length(), 3999);
    EXPECT_EQ(buf.avail(), 1);
}

TEST(LogStreamTest, testFormatSI)
{
    EXPECT_EQ(cppl::formatSI(0), std::string("0"));
    EXPECT_EQ(cppl::formatSI(999), std::string("999"));
    EXPECT_EQ(cppl::formatSI(1000), std::string("1.00k"));
    EXPECT_EQ(cppl::formatSI(9990), std::string("9.99k"));
    EXPECT_EQ(cppl::formatSI(9994), std::string("9.99k"));
    EXPECT_EQ(cppl::formatSI(9995), std::string("10.0k"));
    EXPECT_EQ(cppl::formatSI(10000), std::string("10.0k"));
    EXPECT_EQ(cppl::formatSI(10049), std::string("10.0k"));
    EXPECT_EQ(cppl::formatSI(10050), std::string("10.1k"));
    EXPECT_EQ(cppl::formatSI(99900), std::string("99.9k"));
    EXPECT_EQ(cppl::formatSI(99949), std::string("99.9k"));
    EXPECT_EQ(cppl::formatSI(99950), std::string("100k"));
    EXPECT_EQ(cppl::formatSI(100499), std::string("100k"));
    // FIXME:
    // EXPECT_EQ(cppl::formatSI(100500), string("101k"));
    EXPECT_EQ(cppl::formatSI(100501), std::string("101k"));
    EXPECT_EQ(cppl::formatSI(999499), std::string("999k"));
    EXPECT_EQ(cppl::formatSI(999500), std::string("1.00M"));
    EXPECT_EQ(cppl::formatSI(1004999), std::string("1.00M"));
    // EXPECT_EQ(cppl::formatSI(1005000), string("1.01M"));
    EXPECT_EQ(cppl::formatSI(1005001), std::string("1.01M"));
    EXPECT_EQ(cppl::formatSI(INT64_MAX), std::string("9.22E"));
}

TEST(LogStreamTest, testFormatIEC)
{
    EXPECT_EQ(cppl::formatIEC(0), std::string("0"));
    EXPECT_EQ(cppl::formatIEC(1023), std::string("1023"));
    EXPECT_EQ(cppl::formatIEC(1024), std::string("1.00Ki"));
    EXPECT_EQ(cppl::formatIEC(10234), std::string("9.99Ki"));
    EXPECT_EQ(cppl::formatIEC(10235), std::string("10.0Ki"));
    EXPECT_EQ(cppl::formatIEC(10240), std::string("10.0Ki"));
    EXPECT_EQ(cppl::formatIEC(10291), std::string("10.0Ki"));
    EXPECT_EQ(cppl::formatIEC(10292), std::string("10.1Ki"));
    EXPECT_EQ(cppl::formatIEC(102348), std::string("99.9Ki"));
    EXPECT_EQ(cppl::formatIEC(102349), std::string("100Ki"));
    EXPECT_EQ(cppl::formatIEC(102912), std::string("100Ki"));
    EXPECT_EQ(cppl::formatIEC(102913), std::string("101Ki"));
    EXPECT_EQ(cppl::formatIEC(1022976), std::string("999Ki"));
    EXPECT_EQ(cppl::formatIEC(1047552), std::string("1023Ki"));
    EXPECT_EQ(cppl::formatIEC(1047961), std::string("1023Ki"));
    EXPECT_EQ(cppl::formatIEC(1048063), std::string("1023Ki"));
    EXPECT_EQ(cppl::formatIEC(1048064), std::string("1.00Mi"));
    EXPECT_EQ(cppl::formatIEC(1048576), std::string("1.00Mi"));
    EXPECT_EQ(cppl::formatIEC(10480517), std::string("9.99Mi"));
    EXPECT_EQ(cppl::formatIEC(10480518), std::string("10.0Mi"));
    EXPECT_EQ(cppl::formatIEC(INT64_MAX), std::string("8.00Ei"));
}

using testing::InitGoogleTest;

int main(int argc, char **argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
