/* *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare,
 *  Matthew Hausknecht, and the Reinforcement Learning and Artificial Intelligence 
 *  Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 *  sharedLibraryInterfaceExample.cpp 
 *
 *  Sample code for running an agent with the shared library interface. 
 **************************************************************************** */

#include <iostream>
#include <ale_interface.hpp>

#include "ale_player_ri.hpp"
#include "remote_ALEInterface.hpp"

#ifdef __USE_SDL
  #include <SDL.h>
#endif


#include <remote/server.hpp>
#include <remote/make_tcp_binding.hpp>

using namespace std;

//int main(int argc, char** argv) {
int main() {
    ale_player ale_p;

    remote::server server;
    server.bind<remote_ALEInterface>(&ale_p, "nice player");
    server.start(remote::make_tcp_binding(8888));

    std::cin.get();

//    if (argc < 2) {
//        std::cerr << "Usage: " << argv[0] << " rom_file" << std::endl;
//        return 1;
//    }

//    ALEInterface ale;
//
//    // Get & Set the desired settings
//    ale.setInt("random_seed", 123);
//    //The default is already 0.25, this is just an example
//    ale.setFloat("repeat_action_probability", 0.25);
//
//#ifdef __USE_SDL
//    ale.setBool("display_screen", true);
//    ale.setBool("sound", true);
//#endif
//
//    // Load the ROM file. (Also resets the system for new settings to
//    // take effect.)
////    ale.loadROM(argv[1]);
//    ale.loadROM("breakout.bin");
//
//    // Get the vector of legal actions
//    ActionVect legal_actions = ale.getLegalActionSet();
//
//    // Play 10 episodes
//    for (int episode=0; episode<10; episode++) {
//        float totalReward = 0;
//        while (!ale.game_over()) {
//            Action a = legal_actions[rand() % legal_actions.size()];
//            // Apply the action and get the resulting reward
//            float reward = ale.act(a);
//            totalReward += reward;
//        }
//        cout << "Episode " << episode << " ended with score: " << totalReward << endl;
//        ale.reset_game();
//    }

    return 0;
}
