QT -= gui
QT += widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target


TARGET = ImageEditor

# Define output directories
DESTDIR = ./release
OBJECTS_DIR = ./release/obj
CUDA_OBJECTS_DIR = ./release/cuda

HEADERS += \
    histograms.h \
    gradients.h \
    image_interface.h \
    myqlineedit.h \
    my_user_types.h \
    fouriertransform.h \
    fogeffect.h \
    cuda_methods.h \
    colortransform.h \
    threshold.h \
    graytransform.h \
    mergeimages.h \
    templatematching.h

# Source files
SOURCES += \
    main.cpp \
    histograms.cpp \
    gradients.cpp \
    image_interface.cpp \
    myqlineedit.cpp \
    fouriertransform.cpp \
    fogeffect.cpp \
    colortransform.cpp \
    threshold.cpp \
    graytransform.cpp \
    mergeimages.cpp \
    templatematching.cpp

DISTFILES += \
    fouriertransform.cu \
    fogeffect.cu \
    colortransform.cu \
    sobelfilter.cu \
    graytransform.cu \
    treshold.cu \
    histograms.cu \
    mergeimages.cu \
    image_interface.cu \
    templatematching.cu

CUDA_SOURCES += \
    colortransform.cu \
    fouriertransform.cu \
    fogeffect.cu \
    sobelfilter.cu \
    graytransform.cu \
    treshold.cu \
    histograms.cu \
    mergeimages.cu \
    image_interface.cu \
    templatematching.cu

# This makes the .cu files appear in your project
OTHER_FILES +=

# CUDA settings <-- may change depending on your system

#CUDA_SDK = "D:\opt\windows\nvidia\cuda\samples\v10.0"   # Path to cuda SDK install
CUDA_SDK = "/usr/local/cuda-10.1/samples"
#CUDA_DIR = "D:\opt\windows\nvidia\cuda\toolkit\v10.0"            # Path to cuda toolkit install
CUDA_DIR = "/usr/local/cuda-10.1/"
SYSTEM_NAME = unix         # Depending on your system either 'Win32', 'x64', or 'Win64'
SYSTEM_TYPE = 64            # '32' or '64', depending on your system
CUDA_ARCH = sm_61           # Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'
NVCC_OPTIONS = --use_fast_math

# include paths
INCLUDEPATH += $$CUDA_DIR/include \
               $$CUDA_SDK/common/inc/

# library directories
QMAKE_LIBDIR += $$CUDA_DIR/lib64
                $$CUDA_SDK/common/lib/$$SYSTEM_NAME

# Add the necessary libraries
LIBS += -lcuda -lcudart -lcufft

# The following library conflicts with something in Cuda
#QMAKE_LFLAGS_RELEASE += /NODEFAULTLIB:msvcrt.lib
QMAKE_CXXFLAGS_RELEASE = /MT

#QMAKE_LFLAGS_DEBUG   += /NODEFAULTLIB:msvcrtd.lib
#QMAKE_LFLAGS_DEBUG   += /NODEFAULTLIB:biblioteca.lib
#QMAKE_CXXFLAGS_DEBUG = /MTd
#QMAKE_CXXFLAGS += -Wmissing-field-initializers

# The following makes sure all path names (which often include spaces) are put between quotation marks
CUDA_INC = $$join(INCLUDEPATH,'" -I"','-I"','"')

# Configuration of the Cuda compiler
CONFIG(debug, debug|release) {
    # Debug mode
    cuda_d.input = CUDA_SOURCES
    cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
    cuda_d.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda_d.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda_d
}
else {
    # Release mode
    cuda.input = CUDA_SOURCES
    cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
    cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCC_OPTIONS $$CUDA_INC $$LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda
}
