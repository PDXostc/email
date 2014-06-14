cmake_minimum_required(VERSION 2.8)
project(email)

add_definitions(-std=c++11)

include(FindPkgConfig)

PKG_CHECK_MODULES(dpl REQUIRED dpl-efl wrt-plugins-types wrt-plugins-tizen-common wrt-plugins-commons-javascript json-glib-1.0 gthread-2.0 vconf db-util uw-imap-toolkit contacts-service2 drm-client email-service)

INCLUDE_DIRECTORIES(
	${dpl_INCLUDE_DIRS}
	${wrt-plugins-types_INCLUDE_DIRS}
	${wrt-plugins-tizen-common_INCLUDE_DIRS}
	${wrt-plugins-commons-javascript_INCLUDE_DIRS}
	${json-glib_INCLUDE_DIRS}
	/usr/include/email-service	
)

SET(PKGCONFIG_DIR ${CMAKE_SOURCE_DIR}/pkgconfigs)

MACRO(configure_and_install_pkg PKG_FILE)
    CONFIGURE_FILE(${PKGCONFIG_DIR}/${PKG_FILE}.in
               ${PKGCONFIG_DIR}/${PKG_FILE} @ONLY)
    INSTALL(FILES ${PKGCONFIG_DIR}/${PKG_FILE} DESTINATION lib/pkgconfig)
ENDMACRO(configure_and_install_pkg)

#-----------------------------------------------------------------------
# Global vars
#-----------------------------------------------------------------------
SET(CMAKE_INSTALL_PREFIX "/usr")
SET(TARGET_NAME wrt-plugins-tizen-email)
SET(DESTINATION_NAME tizen-email)
SET(TARGET_IMPL_NAME wrt-plugins-tizen-email-impl)

SET(DESTINATION_LIB_PREFIX lib/wrt-plugins)
SET(DESTINATION_HEADER_PREFIX include/wrt-plugins-tizen/${PROJECT_NAME})
SET(LIBS_WIDGETDB ${wrt-plugins-widgetdb_LIBRARIES})

configure_and_install_pkg(wrt-plugins-tizen-email.pc)

SET(CMAKE_INSTALL_RPATH
	${CMAKE_INSTALL_RPATH}
	${CMAKE_INSTALL_PREFIX}/${DESTINATION_LIB_PREFIX}/${tizen_dest}
	${CMAKE_INSTALL_PREFIX}/${DESTINATION_LIB_PREFIX}/${DESTINATION_NAME}
)

SET(SRCS_IMPL
	src/JSEmailplugin.cpp
	src/Emailplugin.cpp
	src/email_stubs.cpp
)

ADD_LIBRARY(${TARGET_IMPL_NAME} SHARED ${SRCS_IMPL})

TARGET_LINK_LIBRARIES(${TARGET_IMPL_NAME}
	${dpl_LDFLAGS}
	${wrt-plugins-types_LDFLAGS}
	${wrt-plugins-tizen-common_LDFLAGS}
	${wrt-plugins-commons-javascript_LDFLAGS}
        ${json-glib_LDFLAGS}
	-L/usr/lib/wrt-plugins/tizen-tizen
)

SET(SRCS
	src/plugin_initializer.cpp
)

ADD_LIBRARY(${TARGET_NAME} SHARED ${SRCS})

TARGET_LINK_LIBRARIES(${TARGET_NAME}
	${TARGET_IMPL_NAME}
)

INSTALL(TARGETS ${TARGET_NAME} ${TARGET_IMPL_NAME} LIBRARY DESTINATION ${DESTINATION_LIB_PREFIX}/${DESTINATION_NAME})
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config.xml DESTINATION ${DESTINATION_LIB_PREFIX}/${DESTINATION_NAME})
INSTALL(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/ DESTINATION ${DESTINATION_HEADER_PREFIX}
	FILES_MATCHING PATTERN "*.h" PATTERN "CMakeFiles" EXCLUDE
)


