TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

# compilation flags
QMAKE_CXXFLAGS += -fPIC -fopenmp
QMAKE_CXXFLAGS_DEBUG += -O3 -DDEBUG -D_GLIBCXX_DEBUG
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -UDEBUG -DNDEBUG -fstrict-aliasing

# uncomment when doing actual profiling
#QMAKE_CXXFLAGS_RELEASE += -pg
#QMAKE_LFLAGS += -pg

isEmpty(ENVIR) {
    ENVIR = "HOME"
}

# configure home
equals(ENVIR, "HOME") {
    LAL_DIR = /home/lluis/Documents/projects/linear-arrangement-library
	INCLUDEPATH += $$LAL_DIR

    # add definitions
	DEFINES += "__ENVIR=0"
}

# configure cluster
equals(ENVIR, "CLUSTER") {
    QMAKE_CXX = /home/soft/gcc-9.2.0/bin/g++
	QMAKE_LINK = /home/soft/gcc-9.2.0/bin/g++
	QMAKE_CXXFLAGS += -std=c++17

    LAL_DIR = /home/usuaris/lalemany/linear-arrangement-library
	INCLUDEPATH += $$LAL_DIR

    # add definitions
	DEFINES += "__ENVIR=1"
}

# add linkage
CONFIG(debug, debug|release) {
    LIBS += -L $$LAL_DIR/lal-debug/ -llaldebug
	PRE_TARGETDEPS += $$LAL_DIR/lal-debug/liblaldebug.so
}
CONFIG(release, debug|release) {
    LIBS += -L $$LAL_DIR/lal-release -llal
	PRE_TARGETDEPS += $$LAL_DIR/lal-release/liblal.so
}

# link against gmp and fopenmp
LIBS += -lgmp -fopenmp

SOURCES += \
    conversion.cpp \
    dir_to_undir_pp.cpp \
    generate.cpp \
    generate_arrangements_pp.cpp \
    generate_trees_pp.cpp \
    linarr_C.cpp \
    linarr_C_pp.cpp \
    linarr_Dmin.cpp \
    linarr_Dmin_pp.cpp \
	main.cpp \
    properties_centroid.cpp \
    properties_centroid_pp.cpp \
    utilities_tree_isomorphism.cpp

HEADERS += \
    dir_to_undir_pp.hpp \
    generate_arrangements_pp.hpp \
    generate_trees_pp.hpp \
    linarr_C_pp.hpp \
    linarr_Dmin_pp.hpp \
    properties_centroid_pp.hpp \
    time.hpp
