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

INCLUDEPATH += $$PWD \
               $$PWD/common \
               $$PWD/image \
               $$PWD/music/wy \
               $$PWD/music/kg \
               $$PWD/music/kw \
               $$PWD/music/bd \
               $$PWD/music/qq \
               $$PWD/radio/fm \
               $$PWD/radio/dj \
               $$PWD/radio/mv

HEADERS  += \
    $$PWD/common/musicnetworkthread.h \
    $$PWD/common/musicnetworkproxy.h \
    $$PWD/common/musicnetworkoperator.h \
    $$PWD/common/musicdownloaddatarequest.h \
    $$PWD/common/musicdownloadtextrequest.h \
    $$PWD/common/musicdownloadtagdatarequest.h \
    $$PWD/common/musicdownloadsourcerequest.h \
    $$PWD/common/musicdownloadqueuerequest.h \
    $$PWD/common/musicidentifysongsrequest.h \
    $$PWD/common/musicsourceupdaterequest.h \
    $$PWD/common/musicdownloadcounterpvrequest.h \
    $$PWD/image/musicdownloadbackgroundrequest.h \
    $$PWD/image/musicdownloadskin.h \
    $$PWD/image/musicabstractdownloadskinrequest.h \
    $$PWD/image/musicdownloadbingskinrequest.h \
    $$PWD/image/musicdownloadthunderskinrequest.h \
    $$PWD/image/musicdownloadbirdskinrequest.h \
    $$PWD/music/wy/musicwyqueryinterface.h \
    $$PWD/music/wy/musicwyqueryrequest.h \
    $$PWD/music/wy/musicwyqueryalbumrequest.h \
    $$PWD/music/wy/musicwyqueryartistrequest.h \
    $$PWD/music/wy/musicwyqueryplaylistrequest.h \
    $$PWD/music/wy/musicwyquerytoplistrequest.h \
    $$PWD/music/wy/musicwyquerymovierequest.h \
    $$PWD/music/wy/musicwyqueryrecommendrequest.h \
    $$PWD/music/wy/musicwyqueryartistlistrequest.h \
    $$PWD/music/wy/musicwydownloadtextrequest.h \
    $$PWD/music/wy/musicwycommentsrequest.h \
    $$PWD/music/wy/musicwyartistsimilarrequest.h \
    $$PWD/music/wy/musicwysongsuggestrequest.h \
    $$PWD/music/wy/musicwytranslationrequest.h \
    $$PWD/music/wy/musicwydiscoverlistrequest.h \
    $$PWD/music/kg/musickgqueryinterface.h \
    $$PWD/music/kg/musickgqueryrequest.h \
    $$PWD/music/kg/musickgqueryalbumrequest.h \
    $$PWD/music/kg/musickgqueryartistrequest.h \
    $$PWD/music/kg/musickgqueryplaylistrequest.h \
    $$PWD/music/kg/musickgquerytoplistrequest.h \
    $$PWD/music/kg/musickgquerymovierequest.h \
    $$PWD/music/kg/musickgqueryrecommendrequest.h \
    $$PWD/music/kg/musickgqueryartistlistrequest.h \
    $$PWD/music/kg/musickgdiscoverlistrequest.h \
    $$PWD/music/kg/musickgcommentsrequest.h \
    $$PWD/music/kg/musickgsongsuggestrequest.h \
    $$PWD/music/kg/musickgartistsimilarrequest.h \
    $$PWD/music/kw/musickwqueryinterface.h \
    $$PWD/music/kw/musickwqueryrequest.h \
    $$PWD/music/kw/musickwqueryalbumrequest.h \
    $$PWD/music/kw/musickwqueryartistrequest.h \
    $$PWD/music/kw/musickwqueryplaylistrequest.h \
    $$PWD/music/kw/musickwquerytoplistrequest.h \
    $$PWD/music/kw/musickwquerymovierequest.h \
    $$PWD/music/kw/musickwqueryrecommendrequest.h \
    $$PWD/music/kw/musickwqueryartistlistrequest.h \
    $$PWD/music/kw/musickwdownloadtextrequest.h \
    $$PWD/music/kw/musickwdownloadimagerequest.h \
    $$PWD/music/kw/musickwdiscoverlistrequest.h \
    $$PWD/music/kw/musickwcommentsrequest.h \
    $$PWD/music/kw/musickwsongsuggestrequest.h \
    $$PWD/music/kw/musickwartistsimilarrequest.h \
    $$PWD/music/bd/musicbdqueryinterface.h \
    $$PWD/music/bd/musicbdquerylearnrequest.h \
    $$PWD/music/bd/musicbdtranslationrequest.h \
    $$PWD/music/qq/musicqqqueryinterface.h \
    $$PWD/music/qq/musicqqqueryrequest.h \
    $$PWD/music/qq/musicqqqueryalbumrequest.h \
    $$PWD/music/qq/musicqqqueryartistrequest.h \
    $$PWD/music/qq/musicqqqueryplaylistrequest.h \
    $$PWD/music/qq/musicqqquerytoplistrequest.h \
    $$PWD/music/qq/musicqqquerymovierequest.h \
    $$PWD/music/qq/musicqqqueryrecommendrequest.h \
    $$PWD/music/qq/musicqqqueryartistlistrequest.h \
    $$PWD/music/qq/musicqqdownloadtextrequest.h \
    $$PWD/music/qq/musicqqdownloadimagerequest.h \
    $$PWD/music/qq/musicqqdiscoverlistrequest.h \
    $$PWD/music/qq/musicqqcommentsrequest.h \
    $$PWD/music/qq/musicqqsongsuggestrequest.h \
    $$PWD/music/qq/musicqqartistsimilarrequest.h \
    $$PWD/radio/fm/musicfmradiochannelrequest.h \
    $$PWD/radio/fm/musicfmradiodownloadtextrequest.h \
    $$PWD/radio/fm/musicfmradiosongsrequest.h \
    $$PWD/radio/fm/musicabstractfmradiorequest.h \
    $$PWD/radio/dj/musicdjradiocategoryrequest.h \
    $$PWD/radio/dj/musicdjradioprogramrequest.h \
    $$PWD/radio/dj/musicdjradioprogramcategoryrequest.h \
    $$PWD/radio/dj/musicabstractdjradiorequest.h \
    $$PWD/radio/mv/musicmvradiocategoryrequest.h \
    $$PWD/radio/mv/musicmvradioprogramrequest.h \
    $$PWD/radio/mv/musicabstractmvradiorequest.h \
    $$PWD/musicnetworkdefines.h \
    $$PWD/musicabstractqueryrequest.h \
    $$PWD/musicabstractnetwork.h \
    $$PWD/musicabstractdownloadrequest.h \
    $$PWD/musicdownloadqueryfactory.h \
    $$PWD/musicdownloadmanager.h \
    $$PWD/musicdownloadimagerequest.h \
    $$PWD/musicpagequeryrequest.h \
    $$PWD/musicqueryalbumrequest.h \
    $$PWD/musicqueryartistrequest.h \
    $$PWD/musicqueryartistlistrequest.h \
    $$PWD/musicqueryplaylistrequest.h \
    $$PWD/musicquerytoplistrequest.h \
    $$PWD/musicqueryrecommendrequest.h \
    $$PWD/musicquerymovierequest.h \
    $$PWD/musicsongsuggestrequest.h \
    $$PWD/musicsimilarrequest.h \
    $$PWD/musictranslationrequest.h \
    $$PWD/musiccommentsrequest.h \
    $$PWD/musicdiscoverlistrequest.h


SOURCES += \
    $$PWD/common/musicnetworkthread.cpp \
    $$PWD/common/musicnetworkproxy.cpp \
    $$PWD/common/musicnetworkoperator.cpp \
    $$PWD/common/musicdownloaddatarequest.cpp \
    $$PWD/common/musicdownloadtextrequest.cpp \
    $$PWD/common/musicdownloadtagdatarequest.cpp \
    $$PWD/common/musicdownloadsourcerequest.cpp \
    $$PWD/common/musicdownloadqueuerequest.cpp \
    $$PWD/common/musicidentifysongsrequest.cpp \
    $$PWD/common/musicsourceupdaterequest.cpp \
    $$PWD/common/musicdownloadcounterpvrequest.cpp \
    $$PWD/image/musicdownloadbackgroundrequest.cpp \
    $$PWD/image/musicabstractdownloadskinrequest.cpp \
    $$PWD/image/musicdownloadbingskinrequest.cpp \
    $$PWD/image/musicdownloadthunderskinrequest.cpp \
    $$PWD/image/musicdownloadbirdskinrequest.cpp \
    $$PWD/music/wy/musicwyqueryinterface.cpp \
    $$PWD/music/wy/musicwyqueryrequest.cpp \
    $$PWD/music/wy/musicwyqueryalbumrequest.cpp \
    $$PWD/music/wy/musicwyqueryartistrequest.cpp \
    $$PWD/music/wy/musicwyqueryplaylistrequest.cpp \
    $$PWD/music/wy/musicwyquerytoplistrequest.cpp \
    $$PWD/music/wy/musicwyquerymovierequest.cpp \
    $$PWD/music/wy/musicwyqueryrecommendrequest.cpp \
    $$PWD/music/wy/musicwyqueryartistlistrequest.cpp \
    $$PWD/music/wy/musicwydownloadtextrequest.cpp \
    $$PWD/music/wy/musicwycommentsrequest.cpp \
    $$PWD/music/wy/musicwysongsuggestrequest.cpp \
    $$PWD/music/wy/musicwyartistsimilarrequest.cpp \
    $$PWD/music/wy/musicwytranslationrequest.cpp \
    $$PWD/music/wy/musicwydiscoverlistrequest.cpp \
    $$PWD/music/kg/musickgqueryinterface.cpp \
    $$PWD/music/kg/musickgqueryrequest.cpp \
    $$PWD/music/kg/musickgqueryalbumrequest.cpp \
    $$PWD/music/kg/musickgqueryartistrequest.cpp \
    $$PWD/music/kg/musickgqueryplaylistrequest.cpp \
    $$PWD/music/kg/musickgquerytoplistrequest.cpp \
    $$PWD/music/kg/musickgquerymovierequest.cpp \
    $$PWD/music/kg/musickgqueryrecommendrequest.cpp \
    $$PWD/music/kg/musickgqueryartistlistrequest.cpp \
    $$PWD/music/kg/musickgdiscoverlistrequest.cpp \
    $$PWD/music/kg/musickgcommentsrequest.cpp \
    $$PWD/music/kg/musickgsongsuggestrequest.cpp \
    $$PWD/music/kg/musickgartistsimilarrequest.cpp \
    $$PWD/music/kw/musickwqueryinterface.cpp \
    $$PWD/music/kw/musickwqueryrequest.cpp \
    $$PWD/music/kw/musickwqueryalbumrequest.cpp \
    $$PWD/music/kw/musickwqueryartistrequest.cpp \
    $$PWD/music/kw/musickwqueryplaylistrequest.cpp \
    $$PWD/music/kw/musickwquerytoplistrequest.cpp \
    $$PWD/music/kw/musickwquerymovierequest.cpp \
    $$PWD/music/kw/musickwqueryrecommendrequest.cpp \
    $$PWD/music/kw/musickwqueryartistlistrequest.cpp \
    $$PWD/music/kw/musickwdownloadtextrequest.cpp \
    $$PWD/music/kw/musickwdownloadimagerequest.cpp \
    $$PWD/music/kw/musickwdiscoverlistrequest.cpp \
    $$PWD/music/kw/musickwcommentsrequest.cpp \
    $$PWD/music/kw/musickwsongsuggestrequest.cpp \
    $$PWD/music/kw/musickwartistsimilarrequest.cpp \
    $$PWD/music/bd/musicbdquerylearnrequest.cpp \
    $$PWD/music/bd/musicbdtranslationrequest.cpp \
    $$PWD/music/qq/musicqqqueryinterface.cpp \
    $$PWD/music/qq/musicqqqueryrequest.cpp \
    $$PWD/music/qq/musicqqqueryalbumrequest.cpp \
    $$PWD/music/qq/musicqqqueryartistrequest.cpp \
    $$PWD/music/qq/musicqqqueryplaylistrequest.cpp \
    $$PWD/music/qq/musicqqquerytoplistrequest.cpp \
    $$PWD/music/qq/musicqqquerymovierequest.cpp \
    $$PWD/music/qq/musicqqqueryrecommendrequest.cpp \
    $$PWD/music/qq/musicqqqueryartistlistrequest.cpp \
    $$PWD/music/qq/musicqqdownloadtextrequest.cpp \
    $$PWD/music/qq/musicqqdownloadimagerequest.cpp \
    $$PWD/music/qq/musicqqdiscoverlistrequest.cpp \
    $$PWD/music/qq/musicqqcommentsrequest.cpp \
    $$PWD/music/qq/musicqqsongsuggestrequest.cpp \
    $$PWD/music/qq/musicqqartistsimilarrequest.cpp \
    $$PWD/radio/fm/musicfmradiochannelrequest.cpp \
    $$PWD/radio/fm/musicfmradiodownloadtextrequest.cpp \
    $$PWD/radio/fm/musicfmradiosongsrequest.cpp \
    $$PWD/radio/fm/musicabstractfmradiorequest.cpp \
    $$PWD/radio/dj/musicdjradiocategoryrequest.cpp \
    $$PWD/radio/dj/musicdjradioprogramrequest.cpp \
    $$PWD/radio/dj/musicdjradioprogramcategoryrequest.cpp \
    $$PWD/radio/dj/musicabstractdjradiorequest.cpp \
    $$PWD/radio/mv/musicmvradiocategoryrequest.cpp \
    $$PWD/radio/mv/musicmvradioprogramrequest.cpp \
    $$PWD/radio/mv/musicabstractmvradiorequest.cpp \
    $$PWD/musicabstractqueryrequest.cpp \
    $$PWD/musicabstractnetwork.cpp \
    $$PWD/musicabstractdownloadrequest.cpp \
    $$PWD/musicdownloadqueryfactory.cpp \
    $$PWD/musicdownloadmanager.cpp \
    $$PWD/musicdownloadimagerequest.cpp \
    $$PWD/musicpagequeryrequest.cpp \
    $$PWD/musicqueryalbumrequest.cpp \
    $$PWD/musicqueryartistrequest.cpp \
    $$PWD/musicqueryartistlistrequest.cpp \
    $$PWD/musicqueryplaylistrequest.cpp \
    $$PWD/musicquerytoplistrequest.cpp \
    $$PWD/musicqueryrecommendrequest.cpp \
    $$PWD/musicquerymovierequest.cpp \
    $$PWD/musicsongsuggestrequest.cpp \
    $$PWD/musicsimilarrequest.cpp \
    $$PWD/musictranslationrequest.cpp \
    $$PWD/musiccommentsrequest.cpp \
    $$PWD/musicdiscoverlistrequest.cpp
