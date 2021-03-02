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

#ifndef UTILS_HPP
#define UTILS_HPP

// Behavior tree
#include <behaviortree_cpp_v3/behavior_tree.h>
// Logger
#include "mars_common/Logger.h"

namespace mars
{
namespace common
{
namespace behavior
{

template <typename T> bool setOutput(std::string parameterName, T& parameter)
{
  BT::Result setOutputResult;
  bool successful = true;

  setOutputResult = setOutput<T>(parameterName, parameter);

  if (!setOutputResult)
  {
    MARS_LOG_ERROR(setOutputResult.error());
    successful = false;
  }

  return successful;
}

} // namespace behavior
} // namespace common
} // namespace mars

#endif // UTILS_HPP
