#include <string>
#include <iostream>
#include <ale_interface.hpp>
#include "ale_player_ri.hpp"

ALEInterface ale;

// Display ALE welcome message
void ale_player::play()
{
    std::cout << "ale player playing " << std::endl;
    m_playing = true;

    std::cout << "ale m_playing=true" << std::endl;



    std::cout << "ale init" << std::endl;
    //		remote::server server;
    //		server.bind<aleR::remote_ALEInterface>(&ale, "nice player");
    //		server.start(remote::make_tcp_binding(8888));
    //
    //		std::cin.get();

    // Get & Set the desired settings
    ale.setInt("random_seed", 123);
    std::cout << "ale setInt" << std::endl;
    //The default is already 0.25, this is just an example
    ale.setFloat("repeat_action_probability", 0.25);
    std::cout << "ale set repeat_action_probability" << std::endl;

    // Load the ROM file. (Also resets the system for new settings to
    // take effect.)
    //    ale.loadROM(argv[1]);
    ale.loadROM("breakout.bin");
    std::cout << "ale loadRom " << std::endl;
    // Get the vector of legal actions
    ActionVect legal_actions = ale.getLegalActionSet();

    clock_t t = clock();
    // Play 10 episodes
    for (int episode=0; episode<10; episode++) {
        float totalReward = 0;
        while (!ale.game_over()) {
            Action a = legal_actions[rand() % legal_actions.size()];
            // Apply the action and get the resulting reward
            float reward = ale.act(a);
            totalReward += reward;
        }
        std::cout << "Episode " << episode << " ended with score: " << totalReward << std::endl;
        ale.reset_game();
    }
    std::cout << clock() - t << std::endl;
    //		return 0;
}