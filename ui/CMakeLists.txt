set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -O3)

set(REQUIRED_LIBS_QUALIFIED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(ui_sources
        qt/MainWindow/MainWindow.hpp qt/MainWindow/MainWindow.cpp
        qt/Canvas/Canvas.hpp qt/Canvas/Canvas.cpp
        qt/ObjectsWidget/ObjectsWidget.cpp qt/ObjectsWidget/ObjectsWidget.hpp)

add_library(ui SHARED ${ui_sources})
target_include_directories(ui PUBLIC .)
target_link_libraries(ui ${REQUIRED_LIBS_QUALIFIED} engine)
