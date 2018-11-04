#ifndef WEB_REQUEST_IMPL_H
#define WEB_REQUEST_IMPL_H

#include "WebRequest.h"

WEB_RESPONSE* PerformWebRequest(WEB_REQUEST *request);
void ReleaseWebResponse(WEB_RESPONSE *response);

#endif
