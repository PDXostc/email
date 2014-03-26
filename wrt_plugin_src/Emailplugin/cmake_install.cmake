# Install script for directory: /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src/Emailplugin

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin.so"
         RPATH "/usr/local/lib/wrt-plugins/tizen-tizen:/usr/local/lib/wrt-plugins/:/usr/local/lib/wrt-plugins/tizen-emailplugin")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin" TYPE SHARED_LIBRARY FILES "/prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src/Emailplugin/libwrt-plugins-tizen-emailplugin.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin.so")
    FILE(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin.so"
         OLD_RPATH "/prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src/Emailplugin::::::::::::::::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/usr/local/lib/wrt-plugins/tizen-tizen:/usr/local/lib/wrt-plugins/:/usr/local/lib/wrt-plugins/tizen-emailplugin")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin-impl.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin-impl.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin-impl.so"
         RPATH "/usr/local/lib/wrt-plugins/tizen-tizen:/usr/local/lib/wrt-plugins/:/usr/local/lib/wrt-plugins/tizen-emailplugin")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin" TYPE SHARED_LIBRARY FILES "/prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src/Emailplugin/libwrt-plugins-tizen-emailplugin-impl.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin-impl.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin-impl.so")
    FILE(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin-impl.so"
         OLD_RPATH ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/usr/local/lib/wrt-plugins/tizen-tizen:/usr/local/lib/wrt-plugins/:/usr/local/lib/wrt-plugins/tizen-emailplugin")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin/libwrt-plugins-tizen-emailplugin-impl.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/wrt-plugins/tizen-emailplugin" TYPE FILE FILES "/prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src/Emailplugin/config.xml")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/wrt-plugin-ivi/emailplugin" TYPE DIRECTORY FILES "/prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src/Emailplugin/" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/CMakeFiles$" EXCLUDE)
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

