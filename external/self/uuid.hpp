#pragma once

#include <string>
#include <cstdlib>

//
// https://gist.github.com/fernandomv3/46a6d7656f50ee8d39dc
//

class uuid
{
  explicit uuid(const std::string & bytes) : m_bytes{bytes} {}

public:
  uuid() : uuid(create()) {}

  //copy ctor/asgn
  uuid(const uuid & other) = default;
  uuid& operator=(const uuid & other) = default;

  //move ctor/asgn
  uuid(uuid && other) = default;
  uuid& operator=(uuid && other) = default;

  //conversions
  explicit operator std::string() const { return m_bytes; }
  const std::string & str() const & { return m_bytes; }
  std::string && str() && { return std::move(m_bytes); }

private:
  static uuid create()
  {
    static const std::string CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::string bytes = std::string(36, ' ');

    bytes[8] = bytes[13] = bytes[18] = bytes[23] = '-';
    bytes[14] = '4';

    int rnd = 0;

    for(int i=0;i<36;i++)
    {
      if (i != 8 && i != 13 && i != 18 && i != 14 && i != 23)
      {
        if (rnd <= 0x02)
        {
            rnd = 0x2000000 + ((std::rand() * 0x1000000) | 0);
        }
        rnd >>= 4;
        bytes[i] = CHARS[(i == 19) ? ((rnd & 0xf) & 0x3) | 0x8 : rnd & 0xf];
      }
    }

    return uuid(bytes);
  }

private:
  /*const*/ std::string m_bytes; //const will disable assignment
};
