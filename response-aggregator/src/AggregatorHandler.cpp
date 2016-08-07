/*
 *  Copyright (c) 2016, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */


#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>

#include "AggregatorHandler.h"
#include "AggregatorStats.h"


using namespace proxygen;

namespace AggregatorService {

    AggregatorHandler::AggregatorHandler(AggregatorStats *stats) : stats_(stats) {
    }

    void AggregatorHandler::onRequest(std::unique_ptr<HTTPMessage> headers) noexcept {
        stats_->recordRequest();
    }

    void AggregatorHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept {
        if (body_) {
            body_->prependChain(std::move(body));
        } else {
            body_ = std::move(body);
        }
    }

    void AggregatorHandler::onEOM() noexcept {
        std::string body{"{ documentNo :  1, brands : [{brandId : 1}, {brandId : 2}]}\n"};
        ResponseBuilder(downstream_)
                .status(200, "OK")
                .header("Request-Number", folly::to<std::string>(stats_->getRequestCount()))
                .body(body)
                .sendWithEOM();
    }

    void AggregatorHandler::onUpgrade(UpgradeProtocol protocol) noexcept {
        // handler doesn't support upgrades
    }

    void AggregatorHandler::requestComplete() noexcept {
        delete this;
    }

    void AggregatorHandler::onError(ProxygenError err) noexcept {
        delete this;
    }

}
