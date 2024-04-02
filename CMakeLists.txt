cmake_minimum_required(VERSION 3.29)
project(Project_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project_2 main.c
        Headers/Bitmap.h
        Headers/FileProcessing.h
        FileProcessing.c
        Bitmap.c
        Headers/Histogram.h
        Histogram.c
        Headers/GrayScale.h
        GrayScale.c
)
