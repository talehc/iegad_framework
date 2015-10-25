#ifndef __STRING_TEST__
#define __STRING_TEST__


#include "gtest/gtest.h"
#include "common/iegad_string.h"



TEST(STR_UTEST_CASE, SUBSTR_TEST)
{
    std::string srcString = "0123456789";
    EXPECT_EQ("345678", iegad::string::substr(srcString, 3, 6));
    EXPECT_EQ("56789", iegad::string::substr(srcString, 5));
    EXPECT_EQ("456789", iegad::string::substr2(srcString, 4));
    EXPECT_EQ("4567", iegad::string::substr2(srcString, 4, 7));
}


TEST(STR_UTEST_CASE, TRIM_TEST)
{
    std::string srcString = "   01234   56789    \t\t";
    std::string srcString2 = ",,1, 2, 3, 4, 5, 6, 7, 8,,";
    EXPECT_EQ("0123456789", iegad::string::trim(srcString));
    EXPECT_EQ("01234   56789", iegad::string::ltrim(iegad::string::rtrim(srcString)));
    EXPECT_EQ("0123456789\t\t", iegad::string::trim(srcString, ' '));
    EXPECT_EQ("0123456789", iegad::string::trim(iegad::string::trim(srcString, ' '), '\t'));
    EXPECT_EQ("12345678", iegad::string::trim(iegad::string::trim(srcString2), ','));
}


TEST(STR_UTEST_CASE, REPLACE_TEST)
{
    std::string srcString = "iegad is my name, iegad is very clever";
    EXPECT_EQ("Xiaoqi is my name, Xiaoqi is very clever", iegad::string::replace(srcString, "iegad", "Xiaoqi"));
    EXPECT_EQ("Aizen is my name, Aizen is very clever", iegad::string::replace(srcString, "iegad ", "Aizen "));
    int n = iegad::string::fstchr(srcString, ',');
    EXPECT_EQ("iegad is my name", iegad::string::remove(srcString, n));
    n = iegad::string::find_str(srcString, " is");
    int end = iegad::string::lstchr(srcString, 'd');
    EXPECT_EQ("iegad is very clever", iegad::string::remove2(srcString, n, end));
}


TEST(STR_UTEST_CASE, FIND_TEST)
{
    std::string srcString = "iegad is my name, iegad is very clever";
    EXPECT_EQ(3, iegad::string::fstchr(srcString, 'a'));
    EXPECT_EQ(35, iegad::string::lstchr(srcString, 'v'));
    EXPECT_EQ(0, iegad::string::find_str(srcString, "iegad"));
    EXPECT_EQ(18, iegad::string::find_str(srcString, "iegad", 2));
    EXPECT_EQ(true, iegad::string::start_with(srcString, "iega"));
    EXPECT_EQ(false, iegad::string::start_with(srcString, "iegadd"));
    EXPECT_EQ(false, iegad::string::end_with(srcString, "ever "));
    EXPECT_EQ(true, iegad::string::end_with(srcString, ", iegad is very clever"));
}


TEST(STR_UTEST_CASE, SPLIT_TEST)
{
    std::string srcString = "Aizen, iegad, Xiaoqi, , XiaoQ";
    std::vector<std::string> strVct = std::move(iegad::string::split_vct(srcString, ", "));
    EXPECT_EQ(5, strVct.size());
    EXPECT_EQ("Aizen", strVct[0]);
    EXPECT_EQ("iegad", strVct[1]);
    EXPECT_EQ("Xiaoqi", strVct[2]);
    EXPECT_EQ("", strVct[3]);
    EXPECT_EQ("XiaoQ", strVct[4]);
    srcString = iegad::string::trim(srcString);
    strVct.clear();
    strVct = std::move(iegad::string::split_vct(srcString, ","));
    EXPECT_EQ("Aizen", strVct[0]);
    EXPECT_EQ("iegad", strVct[1]);
    EXPECT_EQ("Xiaoqi", strVct[2]);
    EXPECT_EQ("", strVct[3]);
    EXPECT_EQ("XiaoQ", strVct[4]);
    EXPECT_EQ("1 : , 2 : Aizen, 3 : XiaoQ", iegad::string::format("1 : {3}, 2 : {0}, 3 : {4}", strVct));
}


TEST(STR_UTEST_CAST, UPLOW_TEST)
{
    std::string srcString = "iegad, 1234567890, AAbbccDd, XIAOQi";
    EXPECT_EQ("IEGAD, 1234567890, AABBCCDD, XIAOQI", iegad::string::to_upr(srcString));
    EXPECT_EQ("iegad, 1234567890, aabbccdd, xiaoqi", iegad::string::to_lwr(srcString));
}


TEST(STR_UTEST_CAST, CONVERT_TEST)
{
    int si32 = 1345678911;
    unsigned int ui32 = 2876543210;
    short ss16 = -32567;
    unsigned short us16 = -1;
    long long sll64 = -987162.9;
    unsigned long long ull64 = 111987162.9;
    float r4 = 111.123456;
    double r8 = 11123.123456789;
    EXPECT_EQ("1345678911", iegad::string::to_str(si32));
    EXPECT_EQ("2876543210", iegad::string::to_str(ui32));
    EXPECT_EQ("-32567", iegad::string::to_str(ss16));
    EXPECT_EQ("65535", iegad::string::to_str(us16));
    EXPECT_EQ("-987162", iegad::string::to_str(sll64));
    EXPECT_EQ("111987162", iegad::string::to_str(ull64));
    EXPECT_EQ("111.1", iegad::string::to_str(r4, 4));
    EXPECT_EQ("11123.123456789", iegad::string::to_str(r8));
    EXPECT_EQ(-123456, iegad::string::to_int32("-123456"));
    EXPECT_EQ(2123456, iegad::string::to_uint32("2123456"));
    EXPECT_EQ(-12345, iegad::string::to_int16("-12345"));
    EXPECT_EQ(65535, iegad::string::to_uint16("-1"));
    EXPECT_EQ(-12341156, iegad::string::to_int64("-12341156"));
    EXPECT_EQ(123456789012, iegad::string::to_uint64("123456789012"));
    EXPECT_EQ(-123.456F, iegad::string::to_float("-123.456"));
    EXPECT_EQ(-1.23456789012345, iegad::string::to_double("-1.23456789012345"));
}


TEST(STR_UTEST_CAST, ENCODE_TEST)
{
    std::string srcString = "Hello world";
    int key = 0xaa;
    std::string enStr = iegad::string::en_cust("Hello world", key);
    EXPECT_EQ("Hello world", iegad::string::de_cust(enStr, key));
}


TEST(STR_UTEST_CAST, CONV_TEST)
{
    std::string srcString = "我是大天才";
    std::string utf8str = iegad::string::to_utf8("真几吧心烦");
    std::string str1 = iegad::string::from_utf8(utf8str);
    EXPECT_EQ(L"我是大天才", iegad::string::str_towstr(srcString));
    EXPECT_EQ("真几吧心烦", iegad::string::wstr_tostr(L"真几吧心烦"));
    EXPECT_EQ("真几吧心烦", str1);    
}



#endif // __STRING_TEST__