/*********************************************************************
 * Software License Agreement (Proprietary and Confidential)
 *
 *  Copyright (c) 2016-2018, Dataspeed Inc.
 *  All rights reserved.
 *
 *  NOTICE:  All information contained herein is, and remains the
 *  property of Dataspeed Inc. The intellectual and technical concepts
 *  contained herein are proprietary to Dataspeed Inc. and may be
 *  covered by U.S. and Foreign Patents, patents in process, and are
 *  protected by trade secret or copyright law. Dissemination of this
 *  information or reproduction of this material is strictly forbidden
 *  unless prior written permission is obtained from Dataspeed Inc.
 *********************************************************************/

#include "Sema.h"
#include <sema/EApi.h>

namespace sema
{

Sema::Sema(ros::NodeHandle &nh, ros::NodeHandle &nh_priv)
{
  if (EApiLibInitialize() != EAPI_STATUS_SUCCESS) {
    ROS_ERROR_STREAM("[SEMA] Error initializing EAPI library");
  }

  // Setup Publishers
  pub_sema_data_ = nh.advertise<sema_ros::Values>("com_status", 0, false);

  // Set up timers
  timer_ = nh.createWallTimer(ros::WallDuration(0.1), &Sema::timerCallback, this);
}

Sema::~Sema()
{
  if (EApiLibUnInitialize() != EAPI_STATUS_SUCCESS) {
    ROS_ERROR_STREAM("[SEMA] Error uninitializing EAPI library");
  }
}

void Sema::timerCallback(const ros::WallTimerEvent& event)
{
  sema_ros::Values msg;
  msg.header.stamp = ros::Time::now();

  uint32_t value;
  if (EApiBoardGetValue(EAPI_ID_BOARD_BOOT_COUNTER_VAL, &value) == EAPI_STATUS_SUCCESS) {
    msg.boot_count = value;
  }
  if (EApiBoardGetValue(EAPI_ID_BOARD_RUNNING_TIME_METER_VAL, &value) == EAPI_STATUS_SUCCESS) {
    msg.running_time = ros::Duration(double(value)*60);
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_CPU_TEMP, &value) == EAPI_STATUS_SUCCESS) {
    msg.temp_cpu = float(value-EAPI_KELVINS_OFFSET)/10;
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_CHIPSET_TEMP, &value) == EAPI_STATUS_SUCCESS) {
    msg.temp_chipset = float(value-EAPI_KELVINS_OFFSET)/10;
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_SYSTEM_TEMP, &value) == EAPI_STATUS_SUCCESS) {
    msg.temp_system = float(value-EAPI_KELVINS_OFFSET)/10;
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_VOLTAGE_VCORE, &value) == EAPI_STATUS_SUCCESS) {
    msg.vcore = float(value)/1000;
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_VOLTAGE_2V5, &value) == EAPI_STATUS_SUCCESS) {
    msg.v2_5 = float(value)/1000;
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_VOLTAGE_3V3, &value) == EAPI_STATUS_SUCCESS) {
    msg.v3_3 = float(value)/1000;
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_VOLTAGE_VBAT, &value) == EAPI_STATUS_SUCCESS) {
    msg.vbat = float(value)/1000;
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_VOLTAGE_5V, &value) == EAPI_STATUS_SUCCESS) {
    msg.v5 = float(value)/1000;
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_VOLTAGE_5VSB, &value) == EAPI_STATUS_SUCCESS) {
    msg.v5sb = float(value)/1000;
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_VOLTAGE_12V, &value) == EAPI_STATUS_SUCCESS) {
    msg.v12 = float(value)/1000;
  }
  if (EApiBoardGetValue(EAPI_ID_HWMON_FAN_CPU, &value) == EAPI_STATUS_SUCCESS) {
    msg.fan_cpu = value;
  }

  pub_sema_data_.publish(msg);
}

} // namespace sema
