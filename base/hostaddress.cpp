/**
 * Copyright 2017 Shusheng Shao <iblackangel@163.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "hostaddress.h"

BASE_BEGIN_NAMESPACE

HostAddress::HostAddress()
{
	_ip4addr = 0x00000000;
}

HostAddress::HostAddress(SpecialAddress address)
{
	setAddress(address);
}

HostAddress::HostAddress(const HostAddress &copy)
{
	_ip4addr = copy._ip4addr;
}

HostAddress::HostAddress(uint32_t ip4Addr)
{
	setAddress(ip4Addr);
}

HostAddress::HostAddress(const std::string &address)
{
	setAddress(address);
}

HostAddress::~HostAddress()
{
}

HostAddress &HostAddress::operator=(const HostAddress &other)
{
	_ip4addr = other._ip4addr;
	return *this;
}

HostAddress &HostAddress::operator=(SpecialAddress address)
{
	setAddress(address);
	return *this;
}


void HostAddress::setAddress(uint32_t ip4Addr)
{
	_ip4addr = ip4Addr;
}

bool HostAddress::setAddress(const std::string &address)
{
	int res;
	struct in_addr ipv4addr;
	res = inet_pton(AF_INET, address.c_str(), &ipv4addr);
	if (res > 0) {
		_ip4addr = ipv4addr.s_addr;
		return true;
	}
	return false;
}

void HostAddress::setAddress(SpecialAddress address)
{
	uint32_t ip4 = INADDR_ANY;
	switch (address) {
	case Null:
		ip4 = INADDR_NONE;
		break;;
	case Broadcast:
		ip4 = INADDR_BROADCAST;
		break;
	case LocalHost:
		ip4 = INADDR_LOOPBACK;
		break;
	case Any:
		break;
	}

	_ip4addr = ntohl(ip4);
}


uint32_t HostAddress::toIPv4Address() const
{
	return _ip4addr;
}

std::string HostAddress::toString() const
{
	char str[INET_ADDRSTRLEN] = { 0x00 };
	if (NULL == inet_ntop(AF_INET, &_ip4addr, str, sizeof(str))) {
		return std::string();
	}
	return std::string(str);
}

BASE_END_NAMESPACE
