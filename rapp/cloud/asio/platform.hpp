#ifndef RAPP_ASIO_PLATFORM
#define RAPP_ASIO_PLATFORM
/**
 * Copyright 2016 Ortelio
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <string>
namespace rapp
{
namespace cloud
{
/**
 * @struct platform
 * @version 0.7.2
 * @date 19 December 2016
 * @author Alex Giokas <a.giokas@ortelio.co.uk>
 *
 * @brief use to construct a service controller with correct params
 *
 * Set the correct RAPP platform endpoint using an address (host name)
 * the port, your RAPP authentication token and (optionally) the protocol.
 */
struct platform
{
   std::string address;
   std::string port;
   std::string token;
   std::string user;
   std::string protocol;
};
}
}
#endif
