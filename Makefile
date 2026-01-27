CPP = g++
CPPFLAGS = -Iheader -ITokenDir

base: sdiybt
	$(CPP) $(CPPFLAGS) main.cpp -o test.k
	

test:
	$(CPP) -E -P $(CPPFLAGS) header/Tokens.h > output_tests/Tokens.ii

sdiybt:
	echo "Start digging in yo butt twin"

