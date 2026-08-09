CPP = g++
CPPFLAGS = -Iheader -ITokenDir -IParserDir -Isrc -std=c++17

SRCDIRECTORIES = src
SRCS = $(foreach dir,$(SRCDIRECTORIES),$(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:.cpp=.o)

base: sdiybt objects
	
	python3 generate_productions.py
	$(CPP) $(OBJS) -o potassium
	

test:
	python3 generate_productions.py
	$(CPP) -E -P $(CPPFLAGS) header/Tokens.h > output_tests/Tokens.ii
	$(CPP) -E -P $(CPPFLAGS) header/Parser.h > output_tests/Parser.ii
	

objects: $(OBJS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

sdiybt:
	echo "------Start digging in yo butt twin------"

