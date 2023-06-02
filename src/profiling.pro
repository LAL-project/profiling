TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17 -fPIC -fopenmp -flto -fno-fat-lto-objects -O3
QMAKE_CXXFLAGS_DEBUG += -DDEBUG -D_GLIBCXX_DEBUG
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -UDEBUG -DNDEBUG -fstrict-aliasing

# use Inter-Procedural Optimization (IPO)
QMAKE_LFLAGS += -fPIC -O3 -flto -fno-fat-lto-objects
QMAKE_LFLAGS_RELEASE += -DNDEBUG -UDEBUG
QMAKE_LFLAGS_DEBUG += -DDEBUG -D_GLIBCXX_DEBUG

LIBS += -lgmp -fopenmp -lpthread

# uncomment when doing actual profiling
#QMAKE_CXXFLAGS_RELEASE += -pg
#QMAKE_LFLAGS += -pg

isEmpty(ENVIR) {
    ENVIR = "HOME"
}

# configure home
equals(ENVIR, "HOME") {
	LAL_DIR = /home/lluis/Documents/projects/LAL-dev/latest/linear-arrangement-library
	INCLUDEPATH += $$LAL_DIR

    # add definitions
	DEFINES += "__ENVIR=0"
}

# configure cluster
equals(ENVIR, "CLUSTER") {
    QMAKE_CXX = /home/soft/gcc-11.2.0/bin/g++
	QMAKE_LINK = /home/soft/gcc-11.2.0/bin/g++

	LAL_DIR = /home/usuaris/lalemany/LAL-dev/latest/linear-arrangement-library
	INCLUDEPATH += $$LAL_DIR

	DEFINES += "__ENVIR=1"
}

# add linkage
CONFIG(debug, debug|release) {
	LIBS += -L $$LAL_DIR/lal-debug/ -llal
	PRE_TARGETDEPS += $$LAL_DIR/lal-debug/liblal.so
}
CONFIG(release, debug|release) {
	LIBS += -L $$LAL_DIR/lal-release -llaloptimized
	PRE_TARGETDEPS += $$LAL_DIR/lal-release/liblaloptimized.so
}

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
	linarr_DMax.cpp \
	linarr_DMax_pp.cpp \
	main.cpp \
    properties_centroid_centre.cpp \
    properties_centroid_centre_pp.cpp \
    utilities_tree_isomorphism.cpp

HEADERS += \
    dir_to_undir_pp.hpp \
    generate_arrangements_pp.hpp \
    generate_trees_pp.hpp \
    linarr_C_pp.hpp \
    linarr_Dmin_pp.hpp \
	linarr_DMax_pp.hpp \
    properties_centroid_centre_pp.hpp \
    time.hpp
