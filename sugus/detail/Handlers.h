#ifndef SUGUS_DETAIL_HANDLERS_H
#define SUGUS_DETAIL_HANDLERS_H

// Sugus includes
#include <sugus/detail/Handler.h>
#include <sugus/detail/HandlerArray.h>
#include <sugus/detail/OpcUaPrototyping.h>



namespace Sugus {
namespace detail {

HandlerTypedef(ResponseHeader);
HandlerTypedef(RequestHeader);
HandlerTypedef(SignatureData);
HandlerTypedef(ApplicationDescription);
HandlerTypedef(ByteString);
HandlerTypedef(ExtensionObject);
HandlerTypedef(ReadValueId);

HandlerCopyableTypedef(NodeId);

HandlerArrayTypedef(SignedSoftwareCertificate);
HandlerArrayTypedef(StatusCode);
HandlerArrayTypedef(DiagnosticInfo);
HandlerArrayTypedef(DataValue);


} // End namespace detail
} // End namespace Sugus


#endif  // SUGUS_DETAIL_HANDLERS_H
