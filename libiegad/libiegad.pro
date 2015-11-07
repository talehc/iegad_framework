TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += src/common/iegad_log.cpp \
    src/common/iegad_md5.cpp \
    src/common/iegad_string.cpp \
    test_common/test_common_main.cpp \
    src/sqlite/sqlite_helper.cpp \
    src/sqlite/sqlite3.c \
    src/data/iegad_dbrow.cpp \
    src/data/iegad_dbtab.cpp \
    src/nets/basic_proxy.cpp \
    src/nets/basic_svc.cpp \
    src/nets/tcp_mt_svr.cpp \
    src/nets/udp_puller.cpp \
    src/nets/udp_pusher.cpp \
    src/msg/basic_msg.pb.cc \
    src/msg/iegad_io_msg.cpp \
    #test_server/test_server_main.cpp \
    src/redis/iegad_redis.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    src/common/iegad_log.h \
    src/common/iegad_md5.h \
    src/common/iegad_string.h \
    src/common/job_queue.hpp \
    src/common/job_worker.hpp \
    test_common/job_test.hpp \
    test_common/string_test.hpp \
    src/iegad_define.h \
    test_common/log_test.hpp \
    src/sqlite/iegad_sqlite.h \
    src/sqlite/sqlite3.h \
    src/sqlite/sqlite3ext.h \
    src/sqlite/sqlite_helper.h \
    src/data/iegad_dbrow.h \
    src/data/iegad_dbtab.h \
    src/nets/basic_proxy.h \
    src/nets/basic_svc.h \
    src/nets/tcp_mt_svr.h \
    src/nets/udp_puller.h \
    src/nets/udp_pusher.h \
    src/msg/basic_msg.pb.h \
    src/msg/iegad_io_msg.h \
    test_server/echo_svc.hpp \
    src/redis/iegad_redis.h \
    src/common/iegad_map.hpp \
    src/common/iegad_singleton.hpp \
    src/common/iegad_timer.hpp

INCLUDEPATH += ./src


LIBS += -l dl
LIBS += -L/usr/local/lib/ -lglog
LIBS += -L/usr/local/lib/ -lgtest
LIBS += -L/usr/local/lib/ -lprotobuf
LIBS += -L/usr/local/lib/ -lboost_system-gcc48-mt-s-1_59
LIBS += -L/usr/local/lib/ -lboost_locale-gcc48-mt-s-1_59
LIBS += -L/usr/local/lib/ -lboost_thread-gcc48-mt-s-1_59
LIBS += -L$$PWD/third_party/lib/release/ -lhiredis


INCLUDEPATH += /usr/local/include/boost-1_59
INCLUDEPATH += /usr/local/include
INCLUDEPATH += $$PWD/third_party/include/redis
INCLUDEPATH += /usr/local/include/google


DEPENDPATH += /usr/local/include/boost-1_59
DEPENDPATH += /usr/local/include
DEPENDPATH += /usr/local/include/google
DEPENDPATH += $$PWD/third_party/include/redis


PRE_TARGETDEPS += /usr/local/lib/libboost_locale-gcc48-mt-s-1_59.a
PRE_TARGETDEPS += /usr/local/lib/libboost_system-gcc48-mt-s-1_59.a
PRE_TARGETDEPS += /usr/local/lib/libboost_thread-gcc48-mt-s-1_59.a
PRE_TARGETDEPS += /usr/local/lib/libglog.a
PRE_TARGETDEPS += /usr/local/lib/libgtest.a
PRE_TARGETDEPS += /usr/local/lib/libprotobuf.a
PRE_TARGETDEPS += $$PWD/third_party/lib/release/libhiredis.a


DISTFILES += \
    src/msg/basic_msg.proto





















