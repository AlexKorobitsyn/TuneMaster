cmake_minimum_required(VERSION 3.16)

project(TuneMaster VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "D:/qt/qt5.15.2-install")

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Multimedia LinguistTools)
find_package(Qt5 REQUIRED COMPONENTS Multimedia)


set(TS_FILES TuneMaster_ru_RU.ts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.ui
    ${TS_FILES}

    audio/mic_input.h
    audio/mic_input.cpp
    audio/pitch_detector.h
    audio/pitch_detector.cpp
    audio/sine_wave_player.h
    audio/sine_wave_player.cpp


    tuner/string_tuner.h
    tuner/string_tuner.cpp

    theory/note_trainer.h
    theory/note_trainer.cpp
    theory/quiz_manager.h
    theory/quiz_manager.cpp
    theory/quiz_widget.h
    theory/quiz_widget.cpp
    theory/audio_quiz_widget.cpp
    theory/audio_quiz_widget.h

    ui/main_window.h
    ui/main_window.cpp
    ui/tuner_widget.h
    ui/tuner_widget.cpp
    ui/user_settings_dialog.h
    ui/user_settings_dialog.cpp
    ui/audio_wave_widget.h
    ui/audio_wave_widget.cpp
)

add_executable(TuneMaster
    ${PROJECT_SOURCES}
 )


target_link_libraries(TuneMaster PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::Multimedia
)


qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})


set_target_properties(TuneMaster PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
