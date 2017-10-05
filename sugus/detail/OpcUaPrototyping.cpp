#include "OpcUaPrototyping.h"




OpcUa_StatusCode
OpcUa_NodeId_CopyTo(const OpcUa_NodeId* a_pSource, OpcUa_NodeId* a_pDestination)
{
    OpcUa_InitializeStatus(OpcUa_Module_ProxyStub, "OpcUa_NodeId_CopyTo");

    OpcUa_ReturnErrorIfArgumentNull(a_pSource);
    OpcUa_ReturnErrorIfArgumentNull(a_pDestination);

    OpcUa_NodeId_Clear(a_pDestination);

    a_pDestination->IdentifierType = a_pSource->IdentifierType;
    a_pDestination->NamespaceIndex = a_pSource->NamespaceIndex;

    switch (a_pSource->IdentifierType) {
        case OpcUa_IdentifierType_Numeric:
        {
            a_pDestination->Identifier.Numeric = a_pSource->Identifier.Numeric;
            break;
        }
        case OpcUa_IdentifierType_String:
        {
            OpcUa_String_StrnCpy(&a_pDestination->Identifier.String, &a_pSource->Identifier.String, OPCUA_STRING_LENDONTCARE);
            break;
        }
        case OpcUa_IdentifierType_Opaque:
        {
            a_pDestination->Identifier.ByteString.Length = a_pSource->Identifier.ByteString.Length;

            if (a_pDestination->Identifier.ByteString.Length > 0)
                {
                    a_pDestination->Identifier.ByteString.Data = (OpcUa_Byte*)OpcUa_Alloc(a_pSource->Identifier.ByteString.Length);
                    OpcUa_GotoErrorIfAllocFailed(a_pDestination->Identifier.ByteString.Data);
                    OpcUa_MemCpy(a_pDestination->Identifier.ByteString.Data, a_pDestination->Identifier.ByteString.Length, a_pSource->Identifier.ByteString.Data, a_pSource->Identifier.ByteString.Length);
                }
            else
                {
                    a_pDestination->Identifier.ByteString.Data = OpcUa_Null;
                }
            break;
        }
        case OpcUa_IdentifierType_Guid:
        {
            if (a_pSource->Identifier.Guid != OpcUa_Null)
                {
                    a_pDestination->Identifier.Guid = (OpcUa_Guid*)OpcUa_Alloc(sizeof(OpcUa_Guid));
                    OpcUa_GotoErrorIfAllocFailed(a_pDestination->Identifier.Guid);
                    OpcUa_Guid_CopyTo(a_pSource->Identifier.Guid, a_pDestination->Identifier.Guid);
                }
            else
                {
                    a_pDestination->Identifier.Guid = OpcUa_Null;
                }
            break;
        }
        default:
        {
            OpcUa_GotoErrorWithStatus(OpcUa_BadInvalidArgument);
        }
    }

    OpcUa_ReturnStatusCode;
    OpcUa_BeginErrorHandling;

    OpcUa_NodeId_Clear(a_pDestination);

    OpcUa_FinishErrorHandling;
}

void*
OpcUa_ExtensionObject_CreateFromType(OpcUa_ExtensionObject* a_pExtension, OpcUa_EncodeableType* a_pType)
{
    if ((a_pExtension == OpcUa_Null) || (a_pType == OpcUa_Null))
    {
        return OpcUa_Null;
    }

    OpcUa_StatusCode uStatus = OpcUa_EncodeableObject_Create(a_pType, &a_pExtension->Body.EncodeableObject.Object);

    if (OpcUa_IsBad(uStatus))
    {
        return OpcUa_Null;
    }

    a_pExtension->TypeId.NodeId.IdentifierType = OpcUa_IdentifierType_Numeric;
    a_pExtension->TypeId.NodeId.Identifier.Numeric = a_pType->BinaryEncodingTypeId;
    a_pExtension->Encoding = OpcUa_ExtensionObjectEncoding_EncodeableObject;
    a_pExtension->Body.EncodeableObject.Type = a_pType;

    return a_pExtension->Body.EncodeableObject.Object;
}
