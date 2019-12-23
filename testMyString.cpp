#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <sstream>
#include "MyString.hpp"

using namespace std;

TEST_CASE("Constructors", "[ctors]") {
    SECTION("Successful initializations") {
        REQUIRE(MyString() == "");
        REQUIRE(MyString("asd") == "asd");
        REQUIRE(MyString(move("asd")) == "asd");
        REQUIRE(MyString(move(MyString("asd"))) == "asd");
    }
}

TEST_CASE("Check operator=", "[assign]") {
    SECTION("Successful assigns") {
        MyString a = "asd";
        REQUIRE((a = "bsd") == "bsd");
        REQUIRE(((a = "bsd") = "csd") == "csd");
        REQUIRE((a = MyString("asd")) == "asd");
        REQUIRE((a = move("mov")) == "mov");
        REQUIRE((a = move(MyString("smov"))) == "smov");
    }
}

TEST_CASE("Check operator+=", "[assignconc]") {
    SECTION("Successful assign concatenations") {
        MyString a = "kek";
        REQUIRE((a += 'a') == "keka");
        REQUIRE((a += "asd") == "kekaasd");
        REQUIRE((a += MyString("lulw")) == "kekaasdlulw");
    }
}

TEST_CASE("Check operator+", "[conc]") {
    SECTION("Successful concatenations") {
        MyString a = "kek";
        REQUIRE((a + 'a') == "keka");
        REQUIRE((a + "asd") == "kekasd");
        REQUIRE((a + MyString("lulw")) == "keklulw");
    }
}

TEST_CASE("Check operator==", "[equalto]") {
    SECTION("Successful equalto") {
        REQUIRE(MyString("ASD") == "ASD");
        REQUIRE(MyString() == "");
    }
}

TEST_CASE("Check operator!=", "[notequalto]") {
    SECTION("Successful notequalto") {
        REQUIRE(MyString("ASD ") != "ASD");
        REQUIRE(MyString() != " ");
        REQUIRE(MyString() != "kekw");
    }
}

TEST_CASE("Check operator[]", "[operator[]]") {
    SECTION("Successful operator[]") {
        MyString a("asdw");
        REQUIRE(a[0] == 'a');
        REQUIRE(a[4] == '\0');
        a[3] = 'l';
        REQUIRE(a[3] == 'l');
        a = "";
        REQUIRE(a[0] == '\0');
    }
}

TEST_CASE("Check function at", "[funcat]") {
    SECTION("Successful at()") {
        MyString a("asdw");
        REQUIRE(a[0] == 'a');
        REQUIRE(a[3] == 'w');
        a[3] = 'l';
        REQUIRE(a[3] == 'l');
    }

    SECTION("Failed at()") {
        MyString a("asdw");
        REQUIRE_THROWS_AS(a.at(-1), out_of_range);
        REQUIRE_THROWS_AS(a.at(4), out_of_range);
        REQUIRE_THROWS_AS(a.at(123123), out_of_range);
    }
}

TEST_CASE("Check function size", "[funcsize]") {
    SECTION("Successful size()") {
        REQUIRE(MyString("asd").size() == 3);
        REQUIRE(MyString().size() == 0);
    }
}

TEST_CASE("Check function empty", "[funcempty]") {
    SECTION("Successful empty()") {
        REQUIRE(MyString("asd").empty() != true);
        REQUIRE(MyString().empty() == true);
    }
}

TEST_CASE("Check operator<<", "[output]") {
    ostringstream out;

    SECTION("Case 1") {
        out << MyString();
        REQUIRE(out.str() == "");
    }
    SECTION("Case 2") {
        out << MyString("asd");
        REQUIRE(out.str() == "asd");
    }
    SECTION("Case 3") {
        out << MyString("asd   ads");
        REQUIRE(out.str() == "asd   ads");
    }
}

TEST_CASE("Check operator>>", "[input]") {
    MyString a;

    SECTION("Case 1") {
        istringstream inp("asd");
        inp >> a;
        REQUIRE(bool(inp.eof() && a == "asd"));
    }
    SECTION("Case 2") {
        istringstream inp("    asd");
        inp >> a;
        REQUIRE(bool(inp.eof() && a == "asd"));
    }
}

TEST_CASE("Check function c_str()", "[funccstr]") {
    MyString a;

    SECTION("Case 1") {
        a = "asd";
        REQUIRE(a.c_str()[0] == 'a');
        REQUIRE(a.c_str()[1] == 's');
        REQUIRE(a.c_str()[2] == 'd');
        REQUIRE(a.c_str()[3] == '\0');
    }
}

TEST_CASE("Check functions begin end", "[funcsbeginend]") {
    MyString a;

    SECTION("Case 1") {
        a = "asd";
        REQUIRE(a.end() - a.begin() == 3);
    }
    SECTION("Case 2") {
        a = "as";
        auto i = a.begin(); i++; i++;
        REQUIRE(i == a.end());
    }
    SECTION("Case 3") {
        a = "as";
        auto j = a.end(); j--; j--;
        REQUIRE(j == a.begin());
    }
}