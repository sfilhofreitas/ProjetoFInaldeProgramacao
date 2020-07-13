TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    DataHandler/data_handler.cpp \
    Utils/util_random.cpp \
    HypothesesGenerator/simple_random_hypotheses.cpp \
    Teachers/pac_teacher.cpp \
    Teachers/weights_theoretical_founded.cpp \
    Tests/unittests.cpp \
    Learners/random_learner.cpp\
    Learners/adversary_learner.cpp

HEADERS += \
    DataHandler/data_handler.h \
    Utils/util_random.h \
    HypothesesGenerator/simple_random_hypotheses.h \
    Teachers/pac_teacher.h \
    Teachers/weights_theoretical_founded.h \
    Teachers/teacher.h \
    Learners/learner.h \
    HypothesesGenerator/hypotheses_generator.h \
    Tests/unittests.h \
    Learners/random_learner.h \
    Learners/adversary_learner.h \
    Learners/adversary_learner
