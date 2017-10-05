/// \file OpcUaPrototyping.h
/// \brief This file contains functions taken from OpcUA-C prototyping branch.
///
#ifndef SUGUS_DETAIL_OPCUAPROTOTYPING_H
#define SUGUS_DETAIL_OPCUAPROTOTYPING_H

// OpcUa includes
#include <opcua.h>


#define OpcUa_Guid_CopyTo(xSource, xDestination) OpcUa_MemCpy(xDestination, sizeof(OpcUa_Guid), xSource, sizeof(OpcUa_Guid))
#define OpcUa_String_CopyTo(xSource, xDestination) OpcUa_String_StrnCpy((xDestination), (xSource), OPCUA_STRING_LENDONTCARE)

OpcUa_StatusCode OpcUa_NodeId_CopyTo(const OpcUa_NodeId* a_pSource, OpcUa_NodeId* a_pDestination);

void* OpcUa_ExtensionObject_CreateFromType(OpcUa_ExtensionObject* a_pExtension, OpcUa_EncodeableType* a_pType);


#endif  // SUGUS_DETAIL_OPCUAPROTOTYPING_H
