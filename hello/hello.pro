TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++17

TARGET = hello

DESTDIR = ../../bin

win32 {

    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

    } else {


    }

    INCLUDEPATH += $$(VSG_INCLUDE_PATH)
    INCLUDEPATH += $$(VULKAN_SDK)/Include

    LIBS += -L$(VSG_LIBRARY_PATH) -lvsg
}

unix {

    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

    } else {


    }
}

INCLUDEPATH += ./include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
