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

#ifndef _SEMA_H_
#define _SEMA_H_

#include <ros/ros.h>

// ROS messages
#include <std_msgs/Float32.h>

namespace sema
{

class Sema
{
public:
  Sema(ros::NodeHandle &nh, ros::NodeHandle &nh_priv);
  ~Sema();

private:
  void timerCallback(const ros::WallTimerEvent& event);

  // Timers
  ros::WallTimer timer_;

  // Published topics
  ros::Publisher pub_sema_data_;
};

} // namespace sema

#endif // _SEMA_H_
