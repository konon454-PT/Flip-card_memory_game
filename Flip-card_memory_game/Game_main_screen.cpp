#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <thread>
#include "Game_objects.h"
#include "Service.h"

namespace gms
{
	sf::Mutex mutex;

	void execute_game(sf::RenderWindow&);
	void initialization_texture_names(svc::Triple_string_arr&);
	void smart_turn_over(svc::Pair_for_thread);

	void smart_turn_over(svc::Pair_for_thread pair)
	{
		mutex.lock();
		//std::cout << "Prallel is work" << std::endl;
		pair.but.turn_over(pair.win);
		mutex.unlock();
	}

	void initialization_texture_names(svc::Triple_string_arr& name_arr)
	{
		for (int i = 0; i < name_arr.get_y_count(); i++)
		{
			for (int j = 0; j < name_arr.get_x_count(); j++)
			{
				name_arr[svc::TEX_NAMES][i][j] = "Red_rect.png";
				name_arr[svc::SEC_TEX_NAMES][i][j] = "Star.png";
				name_arr[svc::BACK_TEX_NAMES][i][j] = "Black_rect.png";
			}
		}
	}

	void execute_game(sf::RenderWindow& window)
	{
		sf::Event event;
		window.clear(sf::Color::Black);
		
		const int width_count = 6;
		const int height_count = 6;

		svc::Triple_string_arr tex_names_arr(width_count, height_count);
		initialization_texture_names(tex_names_arr);
		
		gobj::Game_grid my_grid(width_count, height_count, 200, 100, 5, tex_names_arr[svc::TEX_NAMES], tex_names_arr[svc::SEC_TEX_NAMES], tex_names_arr[svc::BACK_TEX_NAMES]);

		while (window.isOpen())
		{
			//window.clear(sf::Color::Green);
			//my_button.draw(window);
			//window.draw(test_spr);
			my_grid.draw(window);
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					return;
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.key.code == sf::Mouse::Left)
					{
						bool is_pressed_yet = false;
						for (int i = 0; i < height_count; i++)
						{
							for (int j = 0; j < width_count; j++)
							{
								if (my_grid[i][j].is_mouse_this(window))
								{
									svc::Pair_for_thread my_pair(my_grid[i][j], window);
									//void (gobj::Game_button:: *turn_over_ptr)(sf::RenderWindow&) = &(gobj::Game_button::turn_over);
									//sf::Thread thr(smart_turn_over, my_pair);
									//thr.launch();

									my_grid[i][j].turn_over(window);

									is_pressed_yet = true;
									break;
								}
							}
							if (is_pressed_yet)
							{
								break;
							}
						}
					}
				}
			}
			window.display();
		}
	}
}	//	namespace gms