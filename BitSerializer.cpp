#include "stdafx.h"
#include "BitSerializer.h"

using namespace System;
using namespace System::IO;

namespace BitSerializing
{
	inline void BitSerializer::Initialize()
	{
		this->hBuffer = gcnew array<unsigned char, 1>(0);
		this->hBytePosition = 0;
		this->hBitPosition = 1;
	}

	BitSerializer::BitSerializer()
	{
		this->Initialize();
	}

	BitSerializer::BitSerializer(const long % AmountBitsToWriteBitsToWrite)
	{
		this->Initialize();
		this->hBuffer = gcnew array<unsigned char, 1>(((8 - (AmountBitsToWriteBitsToWrite % 8)) + AmountBitsToWriteBitsToWrite) / 8);
	}

	BitSerializer::~BitSerializer()
	{
		delete[] this->hBuffer;
	}

	void BitSerializer::WriteBits(const unsigned char % BitsHolder, const unsigned char % Amount)
	{
		signed char ToShift = 9 - (this->hBitPosition + Amount);

		if (ToShift > 0)
		{
			unsigned char value = (BitsHolder << ToShift);
			this->hBuffer[this->hBytePosition] |= value;
			this->hBitPosition += Amount;
		}
		else if (ToShift == 0)
		{
			this->hBuffer[this->hBytePosition] |= BitsHolder;
			this->hBitPosition = 1;
			this->hBytePosition++;

			//if (this->hBytePosition >= this->hBuffer->LongLength)
			//	SetSize(this->hBuffer->LongLength + 10);
		}
		else
		{
			ToShift = -ToShift;
			WriteBits(BitsHolder >> ToShift, 9 - this->hBitPosition);
			WriteBits(BitsHolder & this->AmountBitsMask[ToShift], ToShift);
		}
	}

	unsigned char BitSerializer::ReadBits(const unsigned char % Amount)
	{
		unsigned char out;
		signed char ToShift = 9 - (this->hBitPosition + Amount);

		if (ToShift < 0)
		{
			ToShift = -ToShift;
			unsigned char I = this->hBitPosition;
			out = ReadBits(9 - I) << (Amount - (9 - I));
			out |= ReadBits(ToShift);
		}
		else if (ToShift == 0)
		{
			out = this->hBuffer[this->hBytePosition] & this->AmountBitsMask[Amount];
			this->hBitPosition = 1;
			this->hBytePosition++;
		}
		else
		{
			out = (this->hBuffer[this->hBytePosition] >> ToShift) & this->AmountBitsMask[Amount];
			this->hBitPosition += Amount;
		}

		return out;
	}

	void BitSerializer::Save(String ^ Filepath)
	{
		FileStream^ writer = gcnew FileStream(Filepath, FileMode::Create);
		writer->Write(this->hBuffer, 0, this->hBuffer->Length);
		writer->Close();
	}

	void BitSerializer::Load(String ^ Filepath)
	{
		FileStream^ reader = gcnew FileStream(Filepath, FileMode::Open);
		this->hBuffer = gcnew array<unsigned char, 1>((int)reader->Length);

		reader->Read(this->hBuffer, 0, (int)reader->Length);

		reader->Close();
	}

	void BitSerializer::Reset()
	{
		this->Initialize();
	}

	void BitSerializer::ResizeBuffer(const long% BufferSize)
	{
		Array::Resize(this->hBuffer, BufferSize);
	}

}