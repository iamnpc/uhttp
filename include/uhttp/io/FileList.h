/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _CIO_FILELIST_H_
#define _CIO_FILELIST_H_

#include <uhttp/util/Vector.h>

namespace uHTTP {
class File;

class FileList : public uHTTP::Vector<File>  {
public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  FileList() 
  {
  }

  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////

 public:
  File *getFile(size_t n) {
    return Vector::get(n);
  }
};

}

#endif



