// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// This file implements the callback "bridge" between Java and C++ for
// ROCKSDB_NAMESPACE::Logger

#ifndef JAVA_ROCKSJNI_LOGGERJNICALLBACK_H_
#define JAVA_ROCKSJNI_LOGGERJNICALLBACK_H_

#include <jni.h>

#include <memory>
#include <string>

#include "port/port.h"
#include "rocksdb/env.h"
#include "rocksjni/jnicallback.h"

namespace ROCKSDB_NAMESPACE {

class LoggerJniCallback : public JniCallback, public Logger {
 public:
  LoggerJniCallback(JNIEnv* env, jobject jLogger);
  ~LoggerJniCallback();

  using Logger::GetInfoLogLevel;
  using Logger::SetInfoLogLevel;
  // Write an entry to the log file with the specified format.
  virtual void Logv(const char* format, va_list ap);
  // Write an entry to the log file with the specified log level
  // and format.  Any log with level under the internal log level
  // of *this (see @SetInfoLogLevel and @GetInfoLogLevel) will not be
  // printed.
  virtual void Logv(const InfoLogLevel log_level, const char* format,
                    va_list ap);

 private:
  // Logging thread that stays attached to the JVM.
  // It's shared by all LoggerJniCallback instances.
  static port::Mutex logging_thread_mtx;
  static port::Thread logging_thread;  // guarded by logging_thread_mtx

  // Shared memory needed for message-passing
  static port::Mutex message_mtx;
  static port::CondVar message_cond;
  static std::unique_ptr<char[]> message;    // guarded by message_mtx
  static volatile bool is_messaging_active;  // guarded by message_mtx

  void log_thread_loop();

  jmethodID m_jLogMethodId;
  jobject m_jdebug_level;
  jobject m_jinfo_level;
  jobject m_jwarn_level;
  jobject m_jerror_level;
  jobject m_jfatal_level;
  jobject m_jheader_level;
  std::unique_ptr<char[]> format_str(const char* format, va_list ap) const;
};
}  // namespace ROCKSDB_NAMESPACE

#endif  // JAVA_ROCKSJNI_LOGGERJNICALLBACK_H_
