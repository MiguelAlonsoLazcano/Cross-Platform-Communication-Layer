macro(target_build)
        message("-- Target build")
        set(CMAKE_SYSTEM_NAME Generic)
        set(CMAKE_SYSTEM_PROCESSOR ARM)

        set(TOOLCHAIN_PREFIX arm-linux-gnueabihf-)

        set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
        set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
endmacro()


macro(host_build)
        message("-- Host build")
endmacro()
