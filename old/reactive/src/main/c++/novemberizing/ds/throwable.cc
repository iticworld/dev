#include "throwable.hh"

namespace novemberizing { namespace ds {

Throwable::Throwable(void) : __msg("") {}

Throwable::Throwable(const std::string & v) : __msg(v) {}

Throwable::Throwable(const std::string && v) : __msg(v) {}

Throwable::~Throwable(void){}

const std::string & Throwable::msg(void) const { return __msg; }

std::ostream & operator<<(std::ostream & o, const Throwable & e) { return o<<e.msg(); }

} }
