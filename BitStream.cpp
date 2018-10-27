#include "stdafx.h"
#include "BitStream.h"

namespace BitSerializing
{
	inline void BitStream::Initialize()
	{
		this->hBitPosition = 1;
		this->hBuffer = 0;
		this->NeedToRead = true;
		this->stream = nullptr;
	}

	BitStream::BitStream(String ^ Filepath, FileMode mode)
	{
		this->Initialize();
		this->stream = gcnew FileStream(Filepath, mode);
	}

	BitStream::BitStream(Stream ^ stream)
	{
		this->Initialize();
		this->stream = stream;
	}

	void BitStream::WriteBits(const unsigned char % BitsHolder, const unsigned char % Amount)
	{
		signed char ToShift = 9 - (this->hBitPosition + Amount);

		if (ToShift > 0)
		{
			unsigned char value = (BitsHolder << ToShift);
			this->hBuffer |= value;
			this->hBitPosition += Amount;
		}
		else if (ToShift == 0)
		{
			this->hBuffer |= BitsHolder;
			stream->WriteByte(this->hBuffer);
			this->hBuffer = 0;

			this->hBitPosition = 1;			
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

	unsigned char BitStream::ReadBits(const unsigned char % Amount)
	{
		unsigned char out;
		signed char ToShift = 9 - (this->hBitPosition + Amount);

		if (this->NeedToRead)
		{
			this->hBuffer = stream->ReadByte();
			this->NeedToRead = false;
		}

		if (ToShift < 0)
		{
			ToShift = -ToShift;
			unsigned char I = this->hBitPosition;
			out = ReadBits(9 - I) << (Amount - (9 - I));
			out |= ReadBits(ToShift);
		}
		else if (ToShift == 0)
		{
			out = this->hBuffer & this->AmountBitsMask[Amount];
			this->hBitPosition = 1;
			this->hBuffer = stream->ReadByte();
		}
		else
		{
			out = (this->hBuffer >> ToShift) & this->AmountBitsMask[Amount];
			this->hBitPosition += Amount;
		}

		return out;
	}
	
	Stream ^ BitStream::GetBaseStream()
	{
		return this->stream;
	}

	void BitStream::Flush()
	{
		this->stream->Flush();
	}

	void BitStream::Close()
	{
		this->stream->Flush();
	}
}