#pragma once

#include <vector>
#include <memory>
#include <iomanip>
#include <sstream>

using std::vector;
using std::uint8_t;
using std::unique_ptr;
using std::shared_ptr;

typedef vector<uint8_t> Bytes;


namespace Utils {
	static void appendBytes(shared_ptr<Bytes> orig, const shared_ptr<Bytes> toAppend);
	static char* intToHexStr(uint8_t &val);
	
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
