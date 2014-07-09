/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/


#ifndef _CHTTP_PARAMETERLIST_H_
#define _CHTTP_PARAMETERLIST_H_

#include <uhttp/util/Vector.h>
#include <uhttp/util/StringUtil.h>
#include <uhttp/http/Parameter.h>

namespace uHTTP {

class ParameterList : public uHTTP::Vector<Parameter> {
public:
  
  ParameterList() 
  {
  }
  
  ~ParameterList() 
  {
    size_t nLists = size();
    for (size_t n = 0; n < nLists; n++) {
      Parameter *param = at(n);
      delete param;
    }
  }

  Parameter *at(size_t n) {
    return Vector::get(n);
  }

  Parameter *getParameter(int n) {
    return Vector::get(n);
  }

  Parameter *getParameter(const std::string &name) 
  {
    size_t nLists = size();
    for (size_t n = 0; n < nLists; n++) {
      Parameter *param = at(n);
      if (uHTTP::StringEquals(name, param->getName()) == true)
        return param;
    }
    return NULL;
  }

  const char *getValue(const std::string &name) 
  {
    Parameter *param = getParameter(name);
    if (param == NULL)
      return "";
    return param->getValue();
  }
};

}

#endif
