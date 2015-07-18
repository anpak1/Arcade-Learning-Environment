#ifndef EXAMPLE_AUDIO_PLAYER_HPP
#define EXAMPLE_AUDIO_PLAYER_HPP

#include <string>
#include <iostream>
#include <ale_interface.hpp>



class ale_player
{
public:
	void play();

	void stop()
	{
		std::cout << "audio player stopped" << std::endl;
		m_playing = false;
	}

	int rewind(int position)
	{
		// take long time to rewind...
		std::cout << "audio player rewinding..." << std::endl;
		return position;
	}

	bool is_playing() const { return m_playing; }

	std::string name() const { return "no name"; }

private:
	bool m_playing;
};

#endif
