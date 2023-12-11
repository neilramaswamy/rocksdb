// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

package org.rocksdb;

import org.rocksdb.RocksDB;

/**
 * Enum NativeLoggerType
 * 
 * <p>
 * RocksDB can log in two ways: to a Java logger that you supply,
 * or via a native logger. The specific native logger can be specified
 * using this enumeration.
 * 
 * This cannot be used in conjunction with setLogger.
 */
public enum NativeLoggerType {
  // In the future, we can add support for Auto-roll, Env logger, or
  // Win logger.
  DEVNULL((byte) 0x0),
  STDERR((byte) 0x1);

  private final byte value;

  NativeLoggerType(final byte value) {
    this.value = value;
  }

  /**
   * Get the internal representation value.
   *
   * @return the internal representation value.
   */
  public byte getValue() {
    return value;
  }

  /**
   * Get the NativeLoggerType from the internal representation value.
   *
   * @param value the internal representation value.
   *
   * @return the NativeLoggerType
   *
   * @throws IllegalArgumentException if the value does not match a
   *                                  NativeLoggerType
   */
  static NativeLoggerType fromValue(final byte value)
      throws IllegalArgumentException {
    for (final NativeLoggerType loggerType : NativeLoggerType.values()) {
      if (loggerType.value == value) {
        return loggerType;
      }
    }
    throw new IllegalArgumentException("Unknown value for NativeLoggerType: "
        + value);
  }
}
