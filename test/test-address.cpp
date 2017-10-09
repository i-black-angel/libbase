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
#include <base.h>

int main(int argc, char *argv[])
{
	base::HostAddress address;
	if (address.setAddress("www.sina.com")) {
		std::cout << address.toString() << std::endl;
		printf ("0x%x\n", address.toIPv4Address());
	} else {
		std::cout << "address failure" << std::endl;
	}

	base::HostAddress testaddr1(base::HostAddress::Null);
	base::HostAddress testaddr2(base::HostAddress::Broadcast);
	base::HostAddress testaddr3 = base::HostAddress::LocalHost;
	base::HostAddress testaddr4(base::HostAddress::Any);
	std::cout << testaddr1.toString() << std::endl;
	printf ("0x%08x\n", testaddr1.toIPv4Address());

	std::cout << testaddr2.toString() << std::endl;
	printf ("0x%08x\n", testaddr2.toIPv4Address());

	std::cout << testaddr3.toString() << std::endl;
	printf ("0x%08x\n", testaddr3.toIPv4Address());

	std::cout << testaddr4.toString() << std::endl;
	printf ("0x%08x\n", testaddr4.toIPv4Address());

	base::HostAddress addr5 = address;
	std::cout << addr5.toString() << std::endl;

	base::HostAddress addr6(0x7f213347);
	std::cout << addr6.toString() << std::endl;
    return 0;
}
