
cmake_minimum_required(VERSION 3.22.1)

project("zerene")

add_library(${CMAKE_PROJECT_NAME} SHARED
        main.cpp
        Imgui/imgui.cpp
        Imgui/imgui_demo.cpp
        Imgui/imgui_draw.cpp
        Imgui/imgui_tables.cpp
        Imgui/imgui_widgets.cpp
        Imgui/imgui_impl_android.cpp
        Imgui/imgui_impl_opengl3.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        EGL
        GLESv3
        log)