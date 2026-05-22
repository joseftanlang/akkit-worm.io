CFLAGS		+= -I./sources/app/game
CPPFLAGS	+= -I./sources/app/game

VPATH += sources/app/game

# CPP source files
SOURCES_CPP += sources/app/game/obj_border.cpp
SOURCES_CPP += sources/app/game/obj_apple.cpp
SOURCES_CPP += sources/app/game/obj_worm.cpp
SOURCES_CPP += sources/app/game/obj_score.cpp
SOURCES_CPP += sources/app/game/obj_lives.cpp
SOURCES_CPP += sources/app/game/obj_eating.cpp