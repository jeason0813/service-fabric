// ------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License (MIT). See License.txt in the repo root for license information.
// ------------------------------------------------------------

#include "stdafx.h"

using namespace Common;
using namespace Federation;
using namespace Transport;
using namespace Reliability;
using namespace Naming;
using namespace std;

using namespace Management::ClusterManager;


AsyncOperationSPtr CreateServiceAsyncOperation::BeginAcceptRequest(
    ClientRequestSPtr && clientRequest,
    TimeSpan const timeout,
    AsyncCallback const & callback,
    AsyncOperationSPtr const & root)
{
    CreateServiceMessageBody body;
    if (this->Request.GetBody(body))
    {
        return this->Replica.BeginAcceptCreateService(
            body.ServiceDescription,
            move(clientRequest),
            timeout,
            callback,
            root);
    }
    else
    {
        return this->Replica.RejectInvalidMessage(
            move(clientRequest),
            callback,
            root);
    }
}

ErrorCode CreateServiceAsyncOperation::EndAcceptRequest(AsyncOperationSPtr const & operation)
{
    return this->Replica.EndAcceptCreateService(operation);
}
