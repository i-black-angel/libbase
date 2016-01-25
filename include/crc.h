#ifndef _CRC_H_
#define _CRC_H_

#include <stdint.h>
#include "define.h"

namespace base {
	uint16_t crc16_compute(const uint8_t *data, uint32_t length);
	uint32_t crc32_compute(const uint8_t *data, uint32_t length);
};

#endif /* _CRC_H_ */
