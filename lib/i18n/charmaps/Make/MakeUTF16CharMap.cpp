#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

int
main(int argc, char ** argv)
{
	// U+0000 to U+D7FF and U+E000 to U+FFFF
	//
	// Both UTF-16 and UCS-2 encode code points in this range as single 16-bit
	// code units that are numerically equal to the corresponding code points.
	// These code points in the Basic Multilingual Plane (BMP) are the only
	// code points that can be represented in UCS-2m as this representation
	// precludes any other interpretation, as having two representations is
	// ambiguous. As of Unicode 9.0, some modern non-Latin Asian,
	// Middle-Eastern, and African scripts fall outside this range, as do
	// most emoji characters.
	//
	// 	Code points from U+010000 to U+10FFFF
	//
	// Code points from the other planes (called Supplementary Planes) are
	// encoded as two 16-bit code units called a surrogate pair, by the
	// following scheme:
	//
	// 0x10000 is subtracted from the code point (U), leaving a 20-bit number
	// (U') in the hex number range 0x00000–0xFFFFF. Note for these purposes,
	// U is defined to be no greater than 0x10FFFF.
	//
	// The high ten bits (in the range 0x000–0x3FF) are added to 0xD800 to give
	// the first 16-bit code unit or high surrogate (W1), which will be in the
	// range 0xD800–0xDBFF.
	//
	// The low ten bits (also in the range 0x000–0x3FF) are added to 0xDC00 to
	// give the second 16-bit code unit or low surrogate (W2), which will be
	// in the range 0xDC00–0xDFFF.
	//
	// UTF-16 decoder
	//
	//		             Low
	//        --------------------------------
	//	High  | DC00      DC01    …       DFFF
	//  ----  | ----      ----    ----    ----
	//	D800  | 010000    010001  …       0103FF
	//	D801  | 010400    010401	…       0107FF
	//  ⋮	    |    ⋮        ⋮      ⋱         ⋮
	// 	DBFF  | 10FC00    10FC01  …       10FFFF
	//

	uint64_t			Width = 1;
	uint64_t			Start = 0;
	uint64_t			End = 0x10ffff;
	uint64_t			H1, H2, H3, H4;
	uint64_t			At = Start;
	uint64_t			Left, Right, Tmp;

	uint32_t			C1, C2;

	for (At = Start; At <= End; At++) {

		if (At <= 0xd7ff || (At >= 0xe000 && At <= 0xffff)) {
			H1 = (At & 0xff00) >> 8;
			H2 = (At & 0xff);
			printf("<U%06X> /x%02x/%02x\n", At, H1, H2);

		} else if (At >= 0x010000 && At <= 0x10ffff) {
			Tmp = At - 0x10000;		// 20 bits are valid.

			Left = (Tmp >> 10) + 0xd800;
			H1 = (Left & 0xff00) >> 8;
			H2 = (Left & 0xff);

			Right = (Tmp & 0x3ff) + 0xdc00;
			H3 = (Right & 0xff) >> 8;
			H4 = (Right & 0xff);
			printf("<U%06X> /x%02x/%02x/%02x/%02x\n", At, H1, H2, H3,
			       H4);
		}

		if (At == 0xd7ff) {
			// Skip to next block.
			At = 0xe000 - 1;

		} else if (At == 0x10fff) {
			// Skip to next block.
			At = 0x010000 - 1;
		}

	}

	exit(0);
}
