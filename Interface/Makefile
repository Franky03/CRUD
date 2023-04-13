CXX = g++
CXXFLAGS = -Ifltk-1.3.8
LDFLAGS = -Lfltk-1.3.8/lib -lfltk -lX11 -lXfixes -lXext -ldl -lXrender -lXcursor -lfontconfig -lXft -lXinerama -lsqlite3 -lfltk_images -lpng
OBJS = GUI.cpp ../Database/Crud.cpp
TARGET = hello_world


$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAGS) $(LDFLAGS)
