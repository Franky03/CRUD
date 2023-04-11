CXX = gcc
CXXFLAGS = -Ifltk-1.3.8
LDFLAGS = -Lfltk-1.3.8/lib -lfltk -lX11 -lXfixes -lXext -ldl -lXrender -lXcursor -lfontconfig -lXft -lXinerama
OBJS = GUI.cpp
TARGET = hello_world


$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAGS) $(LDFLAGS)
