#ifndef   __MESSENGER_DS__USER__HH__
#define   __MESSENGER_DS__USER__HH__

namespace messenger { namespace ds {

class User
{
public:     virtual const std::string & email(void) const = 0
public:     virtual const std::string & name(void) const = 0;
public:     virtual const std::string & nick(void) const = 0;
public:     virtual const std::string & phone(void) const = 0;
public:     User(void);
public:     virtual ~User(void);
};

} }

#endif // __MESSENGER_DS__USER__HH__
