/************************************************************************
 ** This file is part of the network simulator Shawn.                  **
 ** Copyright (C) 2004-2007 by the SwarmNet (www.swarmnet.de) project  **
 ** Shawn is free software; you can redistribute it and/or modify it   **
 ** under the terms of the BSD License. Refer to the shawn-licence.txt **
 ** file in the root of the Shawn source tree for further details.     **
 ************************************************************************
 **                                                                    **
 ** \author Axel Wegener <wegener@itm.uni-luebeck.de>                  **
 **                                                                    **
 ************************************************************************/

#include "storage.h"

#ifdef BUILD_TCPIP

#include <iostream>


using namespace std;

//#define NULLITER static_cast<list<unsigned char>::iterator>(0)

namespace tcpip
{

	// ----------------------------------------------------------------------
	Storage::Storage()
	{
		init();
	}

	// ----------------------------------------------------------------------
	Storage::Storage(unsigned char packet[], int length)
	{
		// Length is calculated, if -1, or given
		if (length == -1) length = sizeof(packet) / sizeof(unsigned char);
		
		store.reserve(length);
		// Get the content
		for(int i = 0; i < length; ++i) store.push_back(packet[i]);

		init();
	}


	// ----------------------------------------------------------------------
	void Storage::init()
	{
		// Initialize local variables
		pos_=0;
		iterValid_ = iterEndValid_ = false;
		valid_pos();

        short a = 0x0102;
        unsigned char *p_a = reinterpret_cast<unsigned char*>(&a);
        bigEndian_ = (p_a[0] == 0x01); // big endian?
	}

	// ----------------------------------------------------------------------
	Storage::~Storage()
	{}

	// ----------------------------------------------------------------------
	bool Storage::valid_pos()
	{
		if (size() == 0) return false;

		// Check iterator iterEnd_ for validity
		if ( !iterEndValid_ )
		{
			iterEnd_ = store.end();
			iterEndValid_ = true;
		}

		// Check Iterator iter_ for validity
		if ( !iterValid_ ) 
		{
			iter_ = store.begin();
			unsigned int i = 0;
			while ( i < pos_ 
				&& iter_ != iterEnd_)
			{
				++i;
				++iter_;
			}
			iterValid_ = true;
		}

		return (iter_ != iterEnd_);
	}

	// ----------------------------------------------------------------------
	unsigned int Storage::position() const
	{
		// pos_ contains everytime the correct position, 
		// even if iterValid == false
		return pos_;
	}

	// ----------------------------------------------------------------------
	void Storage::reset()
	{
		store.clear();
		pos_=0;
		iterValid_ = false;
		iterEndValid_ = false;
	}

	// ----------------------------------------------------------------------
	/**
	* Reads a char form the array
	* @return The read char (between 0 and 255)
	*/
	unsigned char Storage::readChar() throw(std::invalid_argument)
	{
		if ( !valid_pos() )
		{
			throw std::invalid_argument("Storage::readChar(): invalid position");
		}
		char hb = *iter_;
		++iter_;
		++pos_;
		return hb;
	}

	// ----------------------------------------------------------------------
	/**
	*
	*/
	void Storage::writeChar(unsigned char value) throw()
	{
		store.push_back(value);
	}

	// ----------------------------------------------------------------------
	/**
	* Reads a byte form the array
	* @return The read byte (between -128 and 127)
	*/
	int Storage::readByte()	throw(std::invalid_argument)
	{
		int i = static_cast<int>(readChar());
		if (i < 128) return i; 
		else return (i - 256);
	}

	// ----------------------------------------------------------------------
	/**
	*
	*/
	void Storage::writeByte(int value) throw(std::invalid_argument)
	{
		if (value < -128 || value > 127)
		{
			throw std::invalid_argument("Storage::writeByte(): Invalid value, not in [-128, 127]");
		}
		writeChar( static_cast<unsigned char>( (value+256) % 256 ) );
	}

	// ----------------------------------------------------------------------
	/**
	* Reads an unsigned byte form the array
	* @return The read byte (between 0 and 255)
	*/
	int Storage::readUnsignedByte()	throw(std::invalid_argument)
	{
		return static_cast<int>(readChar());
	}

	// ----------------------------------------------------------------------
	/**
	*
	*/
	void Storage::writeUnsignedByte(int value) throw(std::invalid_argument)
	{
		if (value < 0 || value > 255)
		{
			throw std::invalid_argument("Storage::writeUnsignedByte(): Invalid value, not in [0, 255]");
		}
		writeChar( static_cast<unsigned char>( value ));
	}

	// -----------------------------------------------------------------------
	/**
	* Reads a string form the array
	* @return The read string
	*/
	std::string Storage::readString() throw(std::invalid_argument)
	{
		string tmp;
		int len = readInt();
        for (int i = 0; i < len; i++) {
			tmp += (char) readChar();
        }
		return tmp;
	}

	// ----------------------------------------------------------------------
	/**
	* Writes a string into the array;
	* @param s		The string to be written
	*/
	void Storage::writeString(std::string s) throw()
	{
		writeInt(static_cast<int>(s.length()));
        for (string::iterator it = s.begin(); it!=s.end() ; it++) {
			writeChar(*it);
        }
	}

	// -----------------------------------------------------------------------
	/**
	* Reads a string list form the array
	* @return The read string
	*/
    std::vector<std::string> Storage::readStringList() throw(std::invalid_argument)
	{
		std::vector<std::string> tmp;
		int len = readInt();
        for (int i = 0; i < len; i++) {
            tmp.push_back(readString());
        }
		return tmp;
	}

	// ----------------------------------------------------------------------
	/**
	* Writes a string into the array;
	* @param s		The string to be written
	*/
	void Storage::writeStringList(const std::vector<std::string> &s) throw()
	{
		writeInt(static_cast<int>(s.size()));
        for (std::vector<std::string>::const_iterator it = s.begin(); it!=s.end() ; it++) {
			writeString(*it);
        }
	}

	// ----------------------------------------------------------------------
	/**
	* Restores an integer, which was split up in two bytes according to the
	* specification, it must have been split by its row byte representation
	* with MSBF-order
	*
	* @return the unspoiled integer value (between -32768 and 32767)
	*/
	int Storage::readShort() throw(std::invalid_argument)
	{
                short value = 0;
                unsigned char *p_value = reinterpret_cast<unsigned char*>(&value);
                if (bigEndian_)
                {
                        // network is big endian
                        p_value[0] = readChar();
                        p_value[1] = readChar();
                } else {
                        // network is big endian
                        p_value[1] = readChar();
                        p_value[0] = readChar();
                }
                return value;
        }

	// ----------------------------------------------------------------------
	void Storage::writeShort( int value ) throw(std::invalid_argument)
	{
		if (value < -32768 || value > 32767)
		{
			throw std::invalid_argument("Storage::writeShort(): Invalid value, not in [-32768, 32767]");
		}

		short svalue = static_cast<short>(value);
		//assert(svalue == value);

                unsigned char *p_svalue = reinterpret_cast<unsigned char*>(&svalue);
                if (bigEndian_)
                {
                        // network is big endian
                        writeChar(p_svalue[0]);
                        writeChar(p_svalue[1]);
                } else {
                       // network is big endian
                       writeChar(p_svalue[1]);
                       writeChar(p_svalue[0]);
                }
	}

	// ----------------------------------------------------------------------

	/*
	* restores an integer, which was split up in four bytes acording to the
	* specification, it must have been split by its row byte representation
	* with MSBF-order
	*
	* @return the unspoiled integer value (between -2.147.483.648 and 2.147.483.647)
	*/
	int Storage::readInt() throw(std::invalid_argument)
	{
                int value = 0;
                unsigned char *p_value = reinterpret_cast<unsigned char*>(&value);
                if (bigEndian_)
                {
                        // network is big endian
                        p_value[0] = readChar();
                        p_value[1] = readChar();
                        p_value[2] = readChar();
                        p_value[3] = readChar();
                } else {
                        // network is big endian
                        p_value[3] = readChar();
                        p_value[2] = readChar();
                        p_value[1] = readChar();
                        p_value[0] = readChar();
                }
                return value;
	}

	// ----------------------------------------------------------------------
	void Storage::writeInt( int value ) throw()
	{
                unsigned char *p_value = reinterpret_cast<unsigned char*>(&value);
                if (bigEndian_)
                {
                        // network is big endian
                        writeChar(p_value[0]);
                        writeChar(p_value[1]);
                        writeChar(p_value[2]);
                        writeChar(p_value[3]);
                } else {
                        // network is big endian
                        writeChar(p_value[3]);
                        writeChar(p_value[2]);
                        writeChar(p_value[1]);
                        writeChar(p_value[0]);
                }
	}

	// ----------------------------------------------------------------------

	/*
	* restores a float , which was split up in four bytes acording to the
	* specification, it must have been split by its row byte representation
	* with MSBF-order
	*
	* @return the unspoiled float value
	*/
	float Storage::readFloat() throw(std::invalid_argument)
	{
                float value = 0;
                unsigned char *p_value = reinterpret_cast<unsigned char*>(&value);
                if (bigEndian_)
                {
                        // network is big endian
                        p_value[0] = readChar();
                        p_value[1] = readChar();
                        p_value[2] = readChar();
                        p_value[3] = readChar();
                } else {
                        // network is big endian
                        p_value[3] = readChar();
                        p_value[2] = readChar();
                        p_value[1] = readChar();
                        p_value[0] = readChar();
                }

        return value;

	}

	// ----------------------------------------------------------------------
	void Storage::writeFloat( float value ) throw()
	{
                unsigned char *p_value = reinterpret_cast<unsigned char*>(&value);
                if (bigEndian_)
                {
                        // network is big endian
                        writeChar(p_value[0]);
                        writeChar(p_value[1]);
                        writeChar(p_value[2]);
                        writeChar(p_value[3]);
                } else {
                        // network is big endian
                        writeChar(p_value[3]);
                        writeChar(p_value[2]);
                        writeChar(p_value[1]);
                        writeChar(p_value[0]);
                }
        }
        // ----------------------------------------------------------------------
        void Storage::writeDouble( double value ) throw ()
	{
                unsigned char *p_value = reinterpret_cast<unsigned char*>(&value);
                if (bigEndian_)
                {
                        // network is big endian
                        for (int i=0; i<8; ++i)
			{
                                writeChar(p_value[i]);
                        }
                } else {
                        // network is big endian
                        for (int i=7; i>=0; --i)
	                {
                                writeChar(p_value[i]);
                        }
                }
        }

        // ----------------------------------------------------------------------
        double Storage::readDouble( ) throw (std::invalid_argument)
	{
                double value = 0;
                unsigned char *p_value = reinterpret_cast<unsigned char*>(&value);
                if (bigEndian_)
                {
                        // network is big endian
                        for (int i=0; i<8; ++i)
		        {
                                p_value[i] = readChar();
                        }
                } else {
                        // network is big endian
                        for (int i=7; i>=0; --i) {
                                p_value[i] = readChar();
                        }
                }
                return value;
        }

        // ----------------------------------------------------------------------

		void Storage::writePacket(unsigned char* packet, int length)
		{
			store.reserve(length);
			for(int i = 0; i < length; ++i) store.push_back(packet[i]);
			//init();
		}

        // ----------------------------------------------------------------------

		void Storage::writeStorage(tcpip::Storage& store)
		{
			while (store.valid_pos())
				writeChar( store.readChar() );
		}
}

#endif // BUILD_TCPIP

/*-----------------------------------------------------------------------
 * Source  $Source: $
 * Version $Revision: 333 $
 * Date    $Date: 2009-02-19 13:30:30 +0100 (Thu, 19 Feb 2009) $
 *-----------------------------------------------------------------------
 * $Log: $
 *-----------------------------------------------------------------------*/
