// client.cpp

#include "remote_ALEInterface.hpp"
#include <remote/session.hpp>
#include <remote/make_tcp_binding.hpp>

using namespace std;

int main()
{

    remote::session session;
    session.start(remote::make_tcp_binding("localhost", 8888));
    if(session.wait_for_ready() != remote::session::started)
        return -1;

    session.set_call_timeout( boost::chrono::milliseconds(10000));
    boost::shared_ptr<remote_ALEInterface> tgt
            = session.get<remote_ALEInterface>("nice player");

    // get a remote pointer with name "tgt"
    // and use it like local object
    cout << session.call_timeout() << endl;
    tgt->play();

    return 0;
}