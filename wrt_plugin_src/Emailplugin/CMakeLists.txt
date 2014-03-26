SET(TARGET_NAME ${emailplugin_target})
SET(DESTINATION_NAME ${emailplugin_dest})
SET(TARGET_IMPL_NAME ${emailplugin_impl})

cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

include(FindPkgConfig)

PKG_CHECK_MODULES(amb REQUIRED gio-2.0 wrt-plugins-tizen-common json-glib-1.0 glib-2.0 gthread-2.0 vconf db-util uw-imap-toolkit contacts-service2 drm-client email-service)

INCLUDE_DIRECTORIES(
	${INCLUDE_COMMON}
	${amb_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/utilities/test-application/include
	${CMAKE_SOURCE_DIR}/email-api/include
	${CMAKE_SOURCE_DIR}/email-common-use/include
	${CMAKE_SOURCE_DIR}/email-core/include
	${CMAKE_SOURCE_DIR}/email-core/email-storage/include
	${CMAKE_SOURCE_DIR}/email-ipc/include
	/usr/include/email-service	
)

SET(CMAKE_INSTALL_RPATH
	${CMAKE_INSTALL_RPATH}
	${CMAKE_INSTALL_PREFIX}/${DESTINATION_LIB_PREFIX}/${tizen_dest}
	${CMAKE_INSTALL_PREFIX}/${DESTINATION_LIB_PREFIX}/${DESTINATION_NAME}
)

SET(SRCS_IMPL
	JSEmailplugin.cpp
	Emailplugin.cpp
	email_stubs.cpp
)

ADD_LIBRARY(${TARGET_IMPL_NAME} SHARED ${SRCS_IMPL})

TARGET_LINK_LIBRARIES(${TARGET_IMPL_NAME}
	${LIBS_COMMON}
	${amb_LIBRARIES}
    email-api
	-L/usr/lib/wrt-plugins/tizen-tizen
)

SET(SRCS
	plugin_initializer.cpp
)

ADD_LIBRARY(${TARGET_NAME} SHARED ${SRCS})

TARGET_LINK_LIBRARIES(${TARGET_NAME}
	${TARGET_IMPL_NAME}
)

INSTALL(TARGETS ${TARGET_NAME} ${TARGET_IMPL_NAME} LIBRARY DESTINATION ${DESTINATION_LIB_PREFIX}/${DESTINATION_NAME})
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config.xml DESTINATION ${DESTINATION_LIB_PREFIX}/${DESTINATION_NAME})
INSTALL(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION ${DESTINATION_HEADER_PREFIX}/emailplugin
	FILES_MATCHING PATTERN "*.h" PATTERN "CMakeFiles" EXCLUDE
)


