/*********************************************************************
 * Software License Agreement (Proprietary and Confidential)
 *
 *  Copyright (c) 2016-2017, Dataspeed Inc.
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
  //EApiStatus_t EApiLibInitialize(void);
  EApiLibInitialize();

  // Setup Publishers
  pub_sema_data_ = nh.advertise<std_msgs::Float32>("com_status", 10, false);

  // Set up timers
  timer_ = nh.createWallTimer(ros::WallDuration(0.1), &Sema::timerCallback, this);
}

Sema::~Sema()
{
}

void Sema::timerCallback(const ros::WallTimerEvent& event)
{
  std_msgs::Float32 msg;
  msg.data = 0.0f;
  pub_sema_data_.publish(msg);
}

} // namespace sema_driver
