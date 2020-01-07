#include <novemberizing/rx/observable.hh>
#include <novemberizing/rx/subscribers.hh>

#include <string>

using namespace novemberizing::rx;
using namespace novemberizing::util;

int main(void)
{
    Log::o.disable(0xFFFFFFFF);
    Observable<std::string> * observable = Observable<std::string>::Just({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});
    observable->subscribe(Subscribers::Just<std::string>("just >"));
    return 0;
}
