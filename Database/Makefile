CXX = g++
LDFLAGS = -lsqlite3
OBJS = database.cpp Crud.cpp
TARGET = opendb


$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAGS) $(LDFLAGS)
