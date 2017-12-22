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

#include <ros/ros.h>
#include "SemaDriver.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sema_driver");
  ros::NodeHandle nh;
  ros::NodeHandle nh_priv("~");

  // create SemaDriver class
  sema_driver::SemaDriver n(nh, nh_priv);

  // handle callbacks until shut down
  ros::spin();

  return 0;
}
