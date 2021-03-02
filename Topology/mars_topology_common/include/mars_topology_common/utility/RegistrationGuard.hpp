//  Copyright 2020 Fraunhofer-Gesellschaft zur Förderung der angewandten Forschung e.V.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  https:www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#ifndef MARS_TOPOLOGY_COMMON_UTILITY_REGISTRATION_GUARD_H
#define MARS_TOPOLOGY_COMMON_UTILITY_REGISTRATION_GUARD_H

#include <string>
#include <unordered_set>

#include <ros/ros.h>

#include "mars_common/Id.h"
#include "mars_topology_msgs/Registration.h"

namespace mars
{
namespace topology
{
namespace common
{
namespace utility
{
class RegistrationGuard  // static
{
public:
  template <typename... Strings>
  RegistrationGuard(Strings... pIds)
  {
    static ros::NodeHandle sNH;
    std::unordered_set<std::string> lIdStrings({pIds...});

    for (const std::string& iIdString : lIdStrings)
    {
      mRequiredRegistrations.insert(mars::common::Id(iIdString));
    }

    ros::Subscriber lSub = sNH.subscribe("/topology/topology_register", 1000, &RegistrationGuard::checkRegistration, this);

    ros::Rate lRate(10);
    while (!mRequiredRegistrations.empty())
    {
      ros::spinOnce();
      lRate.sleep();
    }
  };

private:
  std::unordered_set<mars::common::Id> mRequiredRegistrations;
  
  void checkRegistration(const mars_topology_msgs::RegistrationConstPtr& pRegistrationMsg)
  {
    if (pRegistrationMsg->registration_action ==
        mars_topology_msgs::Registration::REGISTRATION_ACTION_REGISTER)
    {
      mars::common::Id lRegistrationId(pRegistrationMsg->entity.id);
      std::unordered_set<mars::common::Id>::const_iterator lIterator = mRequiredRegistrations.find(lRegistrationId);

      if (lIterator != mRequiredRegistrations.end())
      {
        mRequiredRegistrations.erase(lIterator);
      }
    }
  };
};
}  // namespace utility
}  // namespace common
}  // namespace topology
}  // namespace mars

#endif  // MARS_TOPOLOGY_COMMON_UTILITY_REGISTRATION_GUARD_H