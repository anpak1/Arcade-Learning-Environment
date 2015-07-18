//#ifndef EXAMPLE_REMOTE_PLAYER_HPP
//#define EXAMPLE_REMOTE_PLAYER_HPP

//#include <xitari/ale_interface.hpp>
#include <remote/idl.hpp>

//using namespace ale;

#define REMOTE_CLASS									\
REMOTE_CLASS_BEGIN(remote_ALEInterface)					\
    REMOTE_METHOD_M0(void, play)                      \
REMOTE_CLASS_END
#include <remote/idl/class.hpp>


#define REMOTE_REGISTER_CLASS remote_ALEInterface
#include <remote/idl/register_class.hpp>

//#endif