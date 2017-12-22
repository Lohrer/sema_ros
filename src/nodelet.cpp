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

#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>

#include "Sema.h"

namespace sema
{

class SemaNodelet : public nodelet::Nodelet
{
public:
  SemaNodelet()
  {
  }
  ~SemaNodelet()
  {
  }

  void onInit(void)
  {
    node_.reset(new Sema(getNodeHandle(), getPrivateNodeHandle()));
  }

private:
  boost::shared_ptr<Sema> node_;
};

} // namespace sema

// Register this plugin with pluginlib.  Names must match nodelets.xml.
//
// parameters: class type, base class type
PLUGINLIB_EXPORT_CLASS(sema::SemaNodelet, nodelet::Nodelet);

