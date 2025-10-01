CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = BookVault
SOURCES = main.cpp library.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)