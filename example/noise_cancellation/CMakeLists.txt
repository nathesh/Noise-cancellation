project(noise_cancellation)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

find_package(PortAudio REQUIRED)
include_directories(${PORTAUDIO_INCLUDE_DIRS})

find_package(FFTW3 REQUIRED COMPONENTS fftw3f)
include_directories(${FFTW3_INCLUDE_DIR})

add_executable(portaudio_devices src/portaudio_devices.cc)
target_link_libraries(portaudio_devices ${PORTAUDIO_LIBRARIES})

add_executable(portaudio_test src/portaudio_test.cc)
target_link_libraries(portaudio_test ${PORTAUDIO_LIBRARIES})

add_executable(portaudio_test2 src/portaudio_test2.cc)
target_link_libraries(portaudio_test2 ${PORTAUDIO_LIBRARIES})

add_executable(test_fft src/test_fft.cc)
target_link_libraries(test_fft ${FFTW3_LIBRARIES})
