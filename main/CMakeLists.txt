file(GLOB_RECURSE DEVICE_SRC "device/*.cpp")

idf_component_register(SRCS "System.cpp" "main.cpp" ${DEVICE_SRC}
                    INCLUDE_DIRS "include" "device/include")
