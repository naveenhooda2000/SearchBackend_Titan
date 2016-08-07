/*
 *  Copyright (c) 2016.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#include <gflags/gflags.h>
#include <folly/Memory.h>
#include <folly/io/async/EventBaseManager.h>
#include <proxygen/httpserver/HTTPServer.h>

#include "AggregatorHandler.h"
#include "AggregatorStats.h"

using namespace AggregatorService;
using namespace proxygen;
using namespace std;

using folly::EventBase;
using folly::EventBaseManager;
using folly::SocketAddress;

using Protocol = HTTPServer::Protocol;

DEFINE_int32(http_port, 21000, "Port to listen on with HTTP protocol");
DEFINE_string(ip, "localhost", "IP/Hostname to bind to");
DEFINE_int32(threads, 0, "Number of threads to listen on. Numbers <= 0 will use the number of cores on this machine.");

class AggregatorHandlerFactory : public RequestHandlerFactory {

public:
    void onServerStart(folly::EventBase *evb) noexcept override {
        stats_.reset(new AggregatorStats);
    }

    void onServerStop() noexcept override {
        stats_.reset();
    }

    RequestHandler *onRequest(RequestHandler *, HTTPMessage *) noexcept override {
        cout << "Got Search Request" << endl;
        return new AggregatorHandler(stats_.get());
    }

private:
    folly::ThreadLocalPtr<AggregatorStats> stats_;

};

int main(int argc, char *argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
    std::cout << FLAGS_ip << "\t" << FLAGS_http_port << std::endl;
    std::vector<HTTPServer::IPConfig> IPs = {{SocketAddress(FLAGS_ip, FLAGS_http_port, true), Protocol::HTTP}};

    if (FLAGS_threads <= 0) {
        FLAGS_threads = sysconf(_SC_NPROCESSORS_ONLN);
        std::cout << "Threads \t " << FLAGS_threads << std::endl;
        CHECK(FLAGS_threads > 0);
    }

    HTTPServerOptions options;
    options.threads = static_cast<size_t>(FLAGS_threads);
    options.idleTimeout = std::chrono::milliseconds(60000);
    options.shutdownOn = {SIGINT, SIGTERM};
    options.enableContentCompression = false;
    options.handlerFactories = RequestHandlerChain().addThen<AggregatorHandlerFactory>().build();

    HTTPServer server(std::move(options));
    server.bind(IPs);

    // Start HTTPServer mainloop in a separate thread
    std::thread t([&]() {
        server.start();
    });

    t.join();
    return 0;
}
