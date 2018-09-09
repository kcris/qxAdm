#
# external libs
#

#
# floating point support - taken from googletest
# https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
#
HEADERS += $$PWD/gtest/FloatingPoint.h

#
# UUID support - taken from std proposal
# https://mariusbancila.ro/blog/2018/02/27/stduuid-a-cpp-library-for-universally-unique-identifiers/
#
# other ideeas: https://gist.github.com/fernandomv3/46a6d7656f50ee8d39dc
#
HEADERS += $$PWD/uuid/uuid.h


#
# experimental, self tests
#
HEADERS += $$PWD/self/uuid.hpp
