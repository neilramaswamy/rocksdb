// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#pragma once

#include <memory>

#include "rocksdb/env.h"
#include "rocksdb/rocksdb_namespace.h"

namespace ROCKSDB_NAMESPACE {

class NativeLogger {
 public:
  explicit NativeLogger(std::shared_ptr<Logger> logger) : logger(logger) {}

  std::shared_ptr<Logger> logger;
};
}  // namespace ROCKSDB_NAMESPACE
