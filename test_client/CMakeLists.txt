set(SOURCES
  main.cpp
  )

include_directories(..)
link_directories( ${OPCUA_LIBRARY_DIR} )

add_executable(opc_client ${SOURCES})
target_link_libraries(opc_client
  sugus
  )
