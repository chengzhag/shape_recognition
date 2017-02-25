#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T09:50:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shape_recognition
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    CvxText.cpp \
    fourier_descriptor.cpp \
    matlab_fcn.cpp \
    my_fcn.cpp \
    shape_recognition.cpp

HEADERS  += \
    CvxText.h \
    foutier_descriptor.h \
    matlab_fcn.h \
    my_fcn.h \
    shape_recognition.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$quote(D:\Program Files\OpenCV_3_1_0\opencv\build\include\opencv2)\
    $$quote(D:\Program Files\OpenCV_3_1_0\opencv\build\include\opencv)\
    $$quote(D:\Program Files\OpenCV_3_1_0\opencv\build\include)\
    $$quote(D:\Program Files\OpenCV_3_1_0\freetype\include)\
    $$quote(D:\Program Files\OpenCV_3_1_0\freetype\lib)

win32:CONFIG(release, debug|release): LIBS += -L'D:/Program Files/OpenCV_3_1_0/opencv/build/x64/vc14/lib/' -lopencv_world310
else:win32:CONFIG(debug, debug|release): LIBS += -L'D:/Program Files/OpenCV_3_1_0/opencv/build/x64/vc14/lib/' -lopencv_world310d
else:unix: LIBS += -L'D:/Program Files/OpenCV_3_1_0/opencv/build/x64/vc14/lib/' -lopencv_world310

INCLUDEPATH += 'D:/Program Files/OpenCV_3_1_0/opencv/build/x64/vc14'
DEPENDPATH += 'D:/Program Files/OpenCV_3_1_0/opencv/build/x64/vc14'

unix|win32: LIBS += -L'D:/Program Files/OpenCV_3_1_0/freetype/lib/' -lfreetype271MT

INCLUDEPATH += 'D:/Program Files/OpenCV_3_1_0/freetype/include'
DEPENDPATH += 'D:/Program Files/OpenCV_3_1_0/freetype/include'

