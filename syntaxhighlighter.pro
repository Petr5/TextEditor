QT += widgets
QT += core5compat
HEADERS         = highlighter.h \
                  mainwindow.h \
    codeeditor.h \
    mytab.h
SOURCES         = highlighter.cpp \
                  mainwindow.cpp \
                  main.cpp \
    codeeditor.cpp \
    mytab.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/richtext/syntaxhighlighter
INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/usr/bin/ctags/release/ -lctags
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/usr/bin/ctags/debug/ -lctags
else:unix: LIBS += /usr/bin/ctags-universal #-lctags
message($${LIBS})
INCLUDEPATH += $$PWD/ctags-universals
#DEPENDPATH += $$PWD/home/peter/Lab-01/ctags
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/usr/bin/ctags/release/ctags.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/usr/bin/ctags/debug/ctags.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/libctags.a

wince {
   addFiles.files = main.cpp mainwindow.cpp
   addFiles.path = .
   INSTALLS += addFiles
}
