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
#ifndef _HOSTADDRESS_H_
#define _HOSTADDRESS_H_

#include <base/global.h>

BASE_BEGIN_NAMESPACE

class HostAddress
{
public:
	enum SpecialAddress {
		Null,
		Broadcast,
		LocalHost,
		// LocalHostIPv6,
		Any,
		// AnyIPv6,
		// AnyIPv4
	};
	HostAddress();
	HostAddress(SpecialAddress address);
	HostAddress(const HostAddress &copy);
	explicit HostAddress(uint32_t ip4Addr);
	explicit HostAddress(const std::string &address);
	virtual ~HostAddress();

	HostAddress &operator=(const HostAddress &other);
	HostAddress &operator=(SpecialAddress address);

	void setAddress(uint32_t ip4Addr);
	bool setAddress(const std::string &address);
	void setAddress(SpecialAddress address);

	uint32_t toIPv4Address() const;
	std::string toString() const;

	bool isEqual(const HostAddress &address) const;
	bool operator ==(const HostAddress &address) const;
	bool operator ==(SpecialAddress address) const;
	inline bool operator !=(const HostAddress &address) const
		{ return !operator==(address); }
	inline bool operator !=(SpecialAddress address) const
		{ return !operator==(address); }
	bool isNull() const;
	bool isLoopback() const;
	bool isMulticast() const;
private:
	uint32_t _ip4addr;
};

inline bool operator ==(HostAddress::SpecialAddress address1, const HostAddress &address2)
{ return address2 == address1; }
inline bool operator !=(HostAddress::SpecialAddress address1, const HostAddress &address2)
{ return address2 != address1; }

std::ostream &operator<<(std::ostream &, const HostAddress &);
std::istream &operator>>(std::istream &, HostAddress &);

BASE_END_NAMESPACE

#endif /* _HOSTADDRESS_H_ */
