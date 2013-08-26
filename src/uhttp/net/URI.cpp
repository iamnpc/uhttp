/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002-2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/


#include <uhttp/net/URI.h>
#include <uhttp/util/StringUtil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

const char *uHTTP::URI::HTTP = "http";
const char *uHTTP::URI::HTTPS = "https";

int uHTTP::URI::HTTP_PORT = 80;
int uHTTP::URI::HTTPS_PORT = 443;


const char *uHTTP::URI::PROTOCOL_DELIM = "://";
const char *uHTTP::URI::USER_DELIM = "@";
const char *uHTTP::URI::COLON_DELIM = ":";
const char *uHTTP::URI::SLASH_DELIM = "/";
const char *uHTTP::URI::SBLACET_DELIM = "[";
const char *uHTTP::URI::EBLACET_DELIM = "]";
const char *uHTTP::URI::SHARP_DELIM = "#";
const char *uHTTP::URI::QUESTION_DELIM = "?";

////////////////////////////////////////////////
//	uHTTP::URI::URI
////////////////////////////////////////////////

uHTTP::URI::URI()
{
}

uHTTP::URI::URI(const std::string &value)
{
	setString(value);
}

////////////////////////////////////////////////
// setString
////////////////////////////////////////////////

void uHTTP::URI::setString(const std::string &value)
{
	uriStr = value;

	// Protocol
	size_t idx = uriStr.find(PROTOCOL_DELIM);
	if (idx != (int)std::string::npos) {
		int protocolStrLen = strlen(PROTOCOL_DELIM);
		// Thanks for Jay Deen (03/26/04)
		protocol = uriStr.substr(0, idx/* + protocolStrLen*/);
		idx += protocolStrLen;
	}
	else
		idx = 0;

	// User (Password)
	int atIdx = uriStr.find(USER_DELIM, idx);
	if (atIdx != (int)std::string::npos) {
		std::string userPassStr = uriStr.substr(idx, atIdx - idx);
		int colonIdx = userPassStr.find(COLON_DELIM);
		if (colonIdx != (int)std::string::npos) {
			user = userPassStr.substr(0, colonIdx);
			password = userPassStr.substr(colonIdx + 1, userPassStr.length() - colonIdx -1);
		}
		else
			user = userPassStr;
		idx = atIdx + 1;
	}

	// Host (Port)
	int shashIdx = uriStr.find(SLASH_DELIM, idx);
	if (shashIdx != (int)std::string::npos)
		host = uriStr.substr(idx, shashIdx - idx);
	else
		host = uriStr.substr(idx, uriStr.length() - idx);
	int colonIdx = host.rfind(COLON_DELIM);
	int eblacketIdx = host.rfind(EBLACET_DELIM);
	if (colonIdx != (int)std::string::npos && eblacketIdx < colonIdx) {
		std::string hostStr = host;
		host = hostStr.substr(0, colonIdx);
		if (0 < host.length()) {
			if (host.at(0) == '[' && host.at(host.length()-1) == ']')
				host = host.substr(1, colonIdx-2);
		}
		std::string portStr = hostStr.substr(colonIdx + 1, hostStr.length() - colonIdx -1);
		port = atoi(portStr.c_str());
	}
	else {
		port = URI_KNKOWN_PORT;
        if (isHTTP())
            port = HTTP_PORT;
        else if (isHTTPS())
            port = HTTPS_PORT;
    }
    
	if (shashIdx == (int)std::string::npos)
		return;
	idx = shashIdx/* + 1*/;

	// Path (Query/Fragment)
	path = uriStr.substr(idx, uriStr.length() - idx);
	int sharpIdx = path.find(SHARP_DELIM);
	if (sharpIdx != (int)std::string::npos) {
		std::string pathStr = path;
		path = pathStr.substr(0, sharpIdx);
		fragment = pathStr.substr(sharpIdx + 1, pathStr.length() - sharpIdx -1);
	}
	int questionIdx = path.find(QUESTION_DELIM);
	if (questionIdx != (int)std::string::npos) {
		std::string pathStr = path;
		path = pathStr.substr(0, questionIdx);
		query = pathStr.substr(questionIdx + 1, pathStr.length() - questionIdx -1);
	}
	
}

////////////////////////////////////////////////
// IsAbsoluteURI
////////////////////////////////////////////////

bool uHTTP::URI::IsAbsoluteURI()
{
	if (0 < protocol.length())
		return true;
	return false;
}

////////////////////////////////////////////////
// print
////////////////////////////////////////////////

void uHTTP::URI::print()
{
#if !defined(CG_NOUSE_STDOUT)
	printf("URI = %s\n", uriStr.c_str());
	printf("  protocol = %s\n", protocol.c_str());
	printf("  user = %s\n", user.c_str());
	printf("  password = %s\n", password.c_str());
	printf("  host = %s\n", host.c_str());
	printf("  port = %d\n", port);
	printf("  path = %s\n", path.c_str());
	printf("  query = %s\n", query.c_str());
	printf("  fragment = %s\n", fragment.c_str());
#endif
}

