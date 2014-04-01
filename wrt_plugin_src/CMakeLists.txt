# -----------------------------------------------------------------------------
# Common Module
# -----------------------------------------------------------------------------
SET(COMMON_DESTINATION_NAME  "tizen-tizen")

SET(CMAKE_INSTALL_RPATH
  ${CMAKE_INSTALL_RPATH}
  ${CMAKE_INSTALL_PREFIX}/${DESTINATION_LIB_PREFIX}/${COMMON_DESTINATION_NAME}
)

SET(LIBS_TEST
  ${LIBS_COMMON}
  "standaloneconsole"
)

# -----------------------------------------------------------------------------
# Plugin Modules
# -----------------------------------------------------------------------------

add_plugin(
	Vehicle
	MediaServer
	Speech
	Locale
    voiceplugin
    Testplugin 
    Emailplugin
	Fingerprintplugin
)

