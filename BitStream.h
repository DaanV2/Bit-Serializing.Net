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
#ifndef Class_BitSerializing_BitStream_Included
#define Class_BitSerializing_BitStream_Included

#include "IBitSerializable.h"
#include "IBitSerializer.h"

using namespace System;
using namespace System::IO;

namespace BitSerializing
{
	//TODO
	public ref class BitStream : public IBitSerializer
	{
		unsigned char hBitPosition;
		unsigned char hBuffer;
		bool NeedToRead;
		Stream^ stream;

		_AmountBitsMask

		inline void Initialize();

	public:
		//Initializes a new Bitstream
		BitStream(String^ Filepath, FileMode mode);
		//Initializes a new Bitstream
		BitStream(Stream^ stream);

		//Write an amount of bits from the BitsHolder into the current stream/buffer
		virtual void WriteBits(const unsigned char % BitsHolder, const unsigned char % Amount);
		//Returns a byte containg the amount of bits requested. note that more than 8 bits is impossible
		virtual unsigned char ReadBits(const unsigned char % Amount);

		//Gets the position of the serializers in the buffer
		property long long BytePosition
		{
			virtual long long get()
			{
				return stream->Length;
			}
		};
		//Gets the position of the serializer on which bit it is currently working
		property unsigned char BitPosition
		{
			virtual unsigned char get()
			{
				return hBitPosition;
			}
			virtual void set(unsigned char value)
			{
				hBitPosition = value;
			}
		};
		//Gets the length of the buffer
		property long long Length {
			virtual long long get() { return stream->Length; }
		}

		//Returns the base stream this instance of Bitstream uses to write data
		Stream^ GetBaseStream();

		//Clears all buffers for this stream and causes any buffered data to be written to the underlying device.
		void Flush();
		//loses the current stream and releases any resources (such as sockets and file handles) associated with the current stream. Instead of calling this method, ensure that the stream is properly disposed.
		void Close();
	};
}

#endif // !Class_BitSerializing_BitStream