/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002-2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/


#ifndef _CIO_INPUTSTREAM_H_
#define _CIO_INPUTSTREAM_H_

#include <string>

namespace uHTTP {

class InputStream
{

public:

	InputStream()
	{
	}

	virtual ~InputStream()
	{
	}

	virtual int read(std::string &b, int len) = 0;
	virtual int read(char *b, int len) = 0;

	int read(unsigned char *b, int len)
	{
		return read((char *)b, len);
	}

	virtual void unread(std::string &b, int off, int len) = 0;  

	void unread(std::string &b, int len)
	{
		 unread(b, 0, len);  
	}

	void unread(std::string &b)
	{
		 unread(b, 0, (int)b.size());  
	}

	void unread(char c)
	{
		std::string b;
		b.append(&c, 0, 1);
		unread(b, 0, 1);  
	}

	virtual long skip(long n) = 0;

	virtual void close() = 0;
};

}

#endif
