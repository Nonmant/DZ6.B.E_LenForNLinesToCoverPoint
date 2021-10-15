#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<"6 2\n"
                  "1 2 3 9 8 7";
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();
    
    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() == "2\n");
}

TEST_CASE("file 017", ""){
    BENCHMARK("Can cover with 0 len"){
        std::ifstream input( "../017", std::ofstream::in);
        std::stringstream output;
        parseFile(input,output);
        input.close();
        REQUIRE(output.str() == "0\n");
    };
}

TEST_CASE("file 018", ""){
    BENCHMARK("Should cover with 1 line"){
    std::ifstream input( "../018", std::ofstream::in);
    std::stringstream output;
    parseFile(input,output);
    input.close();
    REQUIRE(output.str() == "1999975600\n");
    };
}

TEST_CASE("one digit, one line", ""){
    std::stringstream input, output;
    input<<"1 1\n"
           "3";
    parseFile(input,output);
    REQUIRE(output.str() == "0\n");
}

TEST_CASE("one digit, more lines", ""){
    std::stringstream input, output;
    input<<"1 123\n"
           "3";
    parseFile(input,output);
    REQUIRE(output.str() == "0\n");
}

TEST_CASE("one zero digit, more lines", ""){
    std::stringstream input, output;
    input<<"1 123\n"
           "0";
    parseFile(input,output);
    REQUIRE(output.str() == "0\n");
}

TEST_CASE("all negative", ""){
    std::stringstream input, output;
    input<<"6 2\n"
           "-1 -2 -3 -7 -8 -9";
    parseFile(input,output);
    REQUIRE(output.str() == "2\n");
}

TEST_CASE("both signs", ""){
    std::stringstream input, output;
    input<<"6 2\n"
           "-1 -2 -3 7 8 9";
    parseFile(input,output);
    REQUIRE(output.str() == "2\n");
}

TEST_CASE("range", ""){
    std::stringstream input, output;
    input<<"6 2\n"
           "-1000000000 -300000000 -200000000 700000000 800000000 1000000000";
    parseFile(input,output);
    REQUIRE(output.str() == "800000000\n");
}
