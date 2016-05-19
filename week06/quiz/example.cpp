#include <cassert>
#include <cstdint>
#include <complex>
#include <string>
#include <iostream>

#include "lexical_cast.hpp"

int main() {
    assert(123 == lexical_cast<int>("123"));
    assert(-123 == lexical_cast<int>("-123"));
    assert(0 == lexical_cast<int>("0"));

    assert(32.0 == lexical_cast<double>("32.0"));
    assert(9e15 == lexical_cast<double>("9e+15"));

    assert('c' == lexical_cast<char>("c"));

    assert("123" == lexical_cast<std::string>(123));
    assert("-123" == lexical_cast<std::string>(-123));
    assert("0" == lexical_cast<std::string>(0));

    assert("0" == lexical_cast<std::string>(0ull));
    
    assert(42 == lexical_cast<int>(42l));

    std::complex<double> i(0.0, 1.0); // 0.0 + 1.0i
    assert(i == lexical_cast<std::complex<double>>("(0.0,1.0)"));
	
    try {
        lexical_cast<int>("abc"); // conversion failure
        assert(false); // should not reach here
    } catch (const bad_lexical_cast&) {}

    try {
        lexical_cast<int>(""); // empty
        assert(false);
    } catch (const bad_lexical_cast&) {}

    try {
        lexical_cast<int>("123abc"); // trailing characters
        assert(false);
    } catch (const bad_lexical_cast&) {}

    try {
        lexical_cast<int>("123 "); // trailing whitespace
        assert(false);
    } catch (const bad_lexical_cast&) {}

    try {
        lexical_cast<char>("ab"); // trailing characters
        assert(false);
    } catch (const bad_lexical_cast&) {}

    try {
        lexical_cast<int>(" 123"); // leading whitespace
        assert(false);
    } catch (const bad_lexical_cast&) {}
    
    try {
        lexical_cast<short>("12345678901234567890"); // value too large
        assert(false);
    } catch (const bad_lexical_cast&) {}

    try {
        lexical_cast<std::uint32_t>(std::uint64_t(UINT32_MAX) + 1); // value too large
        assert(false);
    } catch (const bad_lexical_cast&) {}

    try {
        lexical_cast<int>(""); // empty
        assert(false);
    } catch (const std::bad_cast&) {} // catch by ref. to base class 
    cout<<"ok\n";
    return 0;
}
