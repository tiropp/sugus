set(SOURCES
  Client.cpp
  Client.h
  EndpointContainer.h
  Endpoint.h
  Types.h
  Exception.h
  Exceptions.h
  
  detail/ClientImpl.cpp
  detail/ClientImpl.h
  detail/Platform.cpp
  detail/Platform.h
  detail/ProxyStub.cpp
  detail/ProxyStub.h
  detail/Channel.cpp
  detail/Channel.h
  detail/EndpointContainer.cpp
  detail/EndpointContainer.h
  detail/Conversion.cpp
  detail/Conversion.h
  detail/String.cpp
  detail/String.h
  detail/Handlers.h
  detail/Handler.h
  detail/HandlerArray.h
  detail/OpcUaPrototyping.cpp
  detail/OpcUaPrototyping.h
  detail/Session.cpp
  detail/Session.h
  )

add_definitions(-DOPCUA_HAVE_CLIENTAPI)
include_directories(
  .
  ..
  ${OPCUA_INCLUDE_DIR}/platforms/linux/
  ${OPCUA_INCLUDE_DIR}/proxystub/clientproxy
  ${OPCUA_INCLUDE_DIR}/core
  ${OPCUA_INCLUDE_DIR}/stackcore
  )

add_library(sugus ${SOURCES})
target_link_libraries(sugus
  libuastack.a
  ssl crypto
  pthread
  )



  
