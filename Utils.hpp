#pragma once

#ifndef __UTILS__H_
#define __UTILS__H_

#include <vector>
#include <memory>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <cassert>

#include "Uint256.hpp"

using std::vector;
using std::uint8_t;
using std::unique_ptr;
using std::shared_ptr;

typedef vector<uint8_t> Bytes;


namespace Utils {
	 void appendBytes(Bytes &orig, const Bytes &toAppend);
	 void appendBytesArr(Bytes &orig, const uint8_t *toAppend, const size_t size);
	 Bytes hexBytes(const char *str);
	 Bytes strBytes(const char *str);
	 Bytes Uint256Bytes(const Uint256 &value);
	
	template< typename B >
	const char* hexify(B i) {
		std::stringbuf buf;
		//std::ostream os(&buf);

		std::stringstream os;

		// @fix typecast to integer invalid for cases - ?
		os << std::setfill('0') << std::setw(sizeof(B)*2)
			<< std::hex << int(i);

		return os.str().c_str();
		//return buf.str().c_str();
	}
};

#endif
