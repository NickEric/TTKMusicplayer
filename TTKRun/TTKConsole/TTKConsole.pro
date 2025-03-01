# ***************************************************************************
# * This file is part of the TTK Music Player project
# * Copyright (C) 2015 - 2022 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
#
# * You should have received a copy of the GNU General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# ***************************************************************************

QT       += core
include($$PWD/../../TTKVersion.pri)

TEMPLATE = app
DEFINES += TTK_LIBRARY

CONFIG += console


DESTDIR = $$OUT_PWD/../../bin/$$TTKMusicPlayer
TARGET = TTKConsole

LIBS += -L$$DESTDIR -lTTKCore
unix:LIBS += -L$$DESTDIR -lTTKqmmp -lTTKUi -lTTKExtras -lTTKWatcher -lTTKDumper -lzlib -lTTKZip

win32:msvc{
    CONFIG += c++11
}else{
    QMAKE_CXXFLAGS += -std=c++11
}

INCLUDEPATH += \
    $$PWD/../ \
    $$PWD/../../TTKCommon \
    $$PWD/../../TTKThirdParty/TTKDumper \
    $$PWD/../../TTKModule/TTKCore/musicCoreKits \
    $$PWD/../../TTKModule/TTKCore/musicPlaylistKits \
    $$PWD/../../TTKModule/TTKCore/musicUtilsKits

SOURCES += \
    musicconsolemain.cpp \
    musicconsolemodule.cpp

HEADERS += \
    musicconsolemodule.h

win32:RC_FILE = TTKConsole.rc
