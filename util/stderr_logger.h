//  Copyright (c) Meta Platforms, Inc. and affiliates.
//
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#pragma once

#include <stdarg.h>
#include <stdio.h>

#include "rocksdb/env.h"

namespace ROCKSDB_NAMESPACE {

// Prints logs to stderr for faster debugging
class StderrLogger : public Logger {
 public:
  explicit StderrLogger(const InfoLogLevel log_level,
                        std::unique_ptr<char[]>& log_prefix);
  ~StderrLogger() override;

  // Brings overloaded Logv()s into scope so they're not hidden when we override
  // a subset of them.
  using Logger::Logv;

  virtual void Logv(const char* format, va_list ap) override;

 private:
  std::unique_ptr<const char[]> prefix;
};

}  // namespace ROCKSDB_NAMESPACE
