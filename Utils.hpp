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
#include "Sha256Hash.hpp"

using std::vector;
using std::string;
using std::uint8_t;
using std::unique_ptr;
using std::shared_ptr;

// @fix replace with alias
typedef vector<uint8_t> Bytes;

namespace Utils {
	void appendBytes(Bytes &orig, const Bytes &toAppend);
	void appendBytesArr(Bytes &orig, const uint8_t *toAppend, const size_t size);

	/* --- Types Casting Functions ---*/
	Bytes hexStrToBytes(const char *str);
	Bytes Uint256ToBytes(const Uint256 &value);
	Bytes hashToBytes(const Sha256Hash &hash);
	Bytes toBytes(const Uint256 &value);
	Bytes toBytes(const Sha256Hash &hash);

	// std::string Utils::toStr(const Type&)
	string bytesToStr(const Bytes &orig);
	string toStr(const Bytes &bytes);
	string toStr(const Sha256Hash &hash);
	string toStr(const Uint256 &value);
	//string toStr(const CurvePoint& curvePoint);
	
	// @param length: number of bytes to display at either end
	string abridgeBytes(const Bytes &bytes, size_t length = 4);

	template< typename B >
		const std::string hexify(B i) {
			std::stringbuf buf;
			//std::ostream os(&buf);

			std::stringstream os;

			// @fix typecast to integer invalid for cases - ?
			os << std::setfill('0') << std::setw(sizeof(B)*2)
				<< std::hex << int(i);

			return os.str();
			//return os.str().c_str();
			//return buf.str().c_str();
		}

};

#endif
