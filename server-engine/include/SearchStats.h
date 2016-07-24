/*
 *  Copyright (c) 2016, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

namespace SearchService {

/**
 * Just some dummy class containing request count. Since we keep
 * one instance of this in each class, there is no need of
 * synchronization
 */
class SearchStats {
 public:
  virtual ~SearchStats() {

  }

  // NOTE: We make the following methods `virtual` so that we can
  //       mock them using Gmock for our C++ unit-tests. SearchStats
  //       is an external dependency to handler and we should be
  //       able to mock it.

  virtual void recordRequest() {
    std::cout << " recording request " << reqCount_ << std::endl;
    ++reqCount_;
    std::cout << "icremented recording request " << reqCount_ << std::endl;
  }

  virtual uint64_t getRequestCount() {
    return reqCount_;
  }

 private:
  uint64_t reqCount_{0};
};

}