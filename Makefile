CXX := clang++
CXXFLAGS := -std=c++11 -stdlib=libc++ -Weverything -Wno-c++98-compat -Wno-missing-prototypes -Wno-unused-parameter
SOURCES := $(wildcard */*.cpp)
TARGETS := $(SOURCES:.cpp=)

all: $(TARGETS)

clean: FORCE
	@$(RM) $(TARGETS)

%: %.cpp FORCE
	$(CXX) $(CXXFLAGS) -o $@ $<
	$@

FORCE: