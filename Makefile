CPP = g++
CPPFLAGS = -Iheader -ITokenDir -IParserDir -std=c++17

base: sdiybt
	$(CPP) $(CPPFLAGS) main.cpp -o test.k
	

test:
	$(CPP) -E -P $(CPPFLAGS) header/Tokens.h > output_tests/Tokens.ii
	$(CPP) -E -P $(CPPFLAGS) header/Parser.h > output_tests/Parser.ii
	

sdiybt:
	echo "Start digging in yo butt twin"

