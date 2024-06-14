TARGET = war_simulator
CXXFLAGS = -std=c++17 -Os -Wall -pedantic

SRCDIR = src
HEADERDIR = headers
OBJDIR = obj
BINDIR = bin

INCLUDES = -I $(HEADERDIR)

SRCS = $(wildcard *.cpp $(SRCDIR)/*.cpp)

HEADERS = $(wildcard $(HEADERDIR)/*.h )

OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRCS))

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

clean:
	$(RM) -r $(OBJDIR) $(BINDIR)
