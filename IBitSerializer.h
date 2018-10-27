/*ISC License

Copyright (c) 2018, Daan Verstraten, daanverstraten@hotmail.com

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.*/

#pragma once

#ifndef BitSerializing_IBitSerializer_Interface_Included
#define BitSerializing_IBitSerializer_Interface_Included

using namespace System;

namespace BitSerializing
{
	//An interface that an BitSerializer should implement.
	public interface class IBitSerializer
	{
	public:
		//Write an amount of bits from the BitsHolder into the current stream/buffer
		void WriteBits(const unsigned char % BitsHolder, const unsigned char % Amount);

		//Returns a byte containg the amount of bits requested. note that more than 8 bits is impossible
		unsigned char ReadBits(const unsigned char % Amount);

		//Gets the position of the serializers in the buffer
		property long long BytePosition { virtual long long get(); };

		//Gets the position of the serializer on which bit it is currently working
		property unsigned char BitPosition { virtual unsigned char get(); };

		//Gets the length of the buffer
		property long long Length { virtual long long get(); };
	};
}

#endif