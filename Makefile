# main file name
OBJECT = main.cpp engine.cpp engine/grid.cpp
# compiller flags
CFLAGS = -std=c++20
# linker flags
LFLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image
# end flags
DFLAGS = -g
# executable name
APP_NAME = fly_engine_template
# scripts
# build app
build : $(OBJECT)
	g++ $(OBJECT) $(CFLAGS) $(LFLAGS) -o $(APP_NAME)
# run app
run : $(OBJECT)
	$(CURDIR)/$(APP_NAME)
# build and run app
build_run : $(OBJECT)
	g++ $(OBJECT) $(CFLAGS) $(LFLAGS) -o $(APP_NAME)
	$(CURDIR)/$(APP_NAME)
build_win : $(OBJECT)
	x86_64-w64-mingw32-g++ $(OBJECT) $(CFLAGS) $(LFLAGS) -o $(APP_NAME)
# debug build
build_d : $(OBJECT)
	g++ $(OBJECT) $(CFLAGS) $(DFLAGS) $(LFLAGS) -o $(APP_NAME)
#debug
debug : $(OBJECT)
	g++ $(OBJECT) $(CFLAGS) $(DFLAGS) $(LFLAGS) -o $(APP_NAME)
	gdb $(CURDIR)/$(APP_NAME)
# clean builded app
clear : $(OBJECT)
	rm $(CURDIR)/$(APP_NAME)
