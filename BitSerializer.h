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
#ifndef Class_BitSerializing_BitSerializer_Included
#define Class_BitSerializing_BitSerializer_Included

#include "IBitSerializer.h"
#include "IBitSerializable.h"

using namespace System;

namespace BitSerializing
{
	//A class that helps writing and reading bits from a buffer
	public ref class BitSerializer : public IBitSerializer
	{
	private:
		long long hBytePosition;
		unsigned char hBitPosition;
		array<unsigned char, 1>^ hBuffer;

		_AmountBitsMask

		inline void Initialize();

	public:
		//The buffer of this BitSerializing
		property array<unsigned char, 1>^ Buffer 
		{ 
			array<unsigned char, 1>^ get() { return hBuffer; }
			void set(array<unsigned char, 1>^ values)
			{
				delete[] hBuffer;
				hBuffer = values;
			}
		};

		//Gets the position of the serializers in the buffer
		property long long BytePosition
		{
			virtual long long get()
			{
				return hBytePosition;
			}
			virtual void set(long long value)
			{
				hBytePosition = value;
			}
		};

		//Gets the position of the serializer on which bit is currently working
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
		property long long Length
		{
			virtual long long get()
			{
				return this->hBuffer->Length;
			}
		};

		//Gets the length of the buffer as a long
		property long long LongLength
		{
			virtual long long get()
			{
				return this->hBuffer->LongLength;
			}
		};

		//Initializes a new instance of BitSerializing
		BitSerializer();
		//Initializes a new instance of BitSerializing
		BitSerializer(const long% AmountBitsToWriteBitsToWrite);
		//Deconstructs this BitSerializing
		~BitSerializer();

		//write bits into the buffer and moves the position
		virtual void WriteBits(const unsigned char % BitsHolder, const unsigned char % Amount);
		//read bits from the buffer and moves the position
		virtual unsigned char ReadBits(const unsigned char % Amount);

		//Save the buffer into the a file
		void Save(String^ Filepath);
		//Load the file into the buffer
		void Load(String^ Filepath);

		//Resets the Indexes and the buffer as if this instance was created anew
		void Reset();

		//Resizes the buffer
		void ResizeBuffer(const long% BufferSize);		
	};
}

#endif // !Class_BitSerializing_BitSerializing