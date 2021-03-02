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

#include "mars_agent_logical_common/behavior/SetCurrentTime.h"
#include "mars_common/Logger.h"

BT::NodeStatus mars::agent::logical::common::behavior::SetCurrentTime::tick()
{
  BT::Result lResult;

  lResult = this->setOutput<ros::Time>(BEHAVIOR_SETCURRENTTIME_PARAM_NAME_TIME, ros::Time::now());
  if (!lResult)
  {
    MARS_LOG_ERROR(lResult.error());
    return BT::NodeStatus::FAILURE;
  }

  return BT::NodeStatus::SUCCESS;
}