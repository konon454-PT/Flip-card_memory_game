#include <SFML/Graphics.hpp>
#include "Game_objects.h"
#include <iostream>

const int standart_x = 200;
const int standart_y = 100;

namespace gobj
{
	Table::Table(const size_t w, const size_t h, const size_t fr_w, sf::Sprite& s, const sf::Vector2i& start_pos)
		: width(w), height(h), frame_w(fr_w), sprite(s), draw_pos(start_pos)
	{
		if (frame_w * 2 >= std::min(width, height))
		{
			frame_w = std::max(width, height) / 2;
		}
	}

	Table::Table(sf::RenderWindow& win, const size_t s_w, const size_t s_h, sf::Sprite& s, const sf::Vector2i& start_pos)
		: frame_w(1), sprite(s), draw_pos(start_pos)
	{
		width = s_w / 6 - 1;
		height = s_h / 6 - 1;
	}

	Table::Table()
		:	sprite(*(new sf::Sprite)), draw_pos(sf::Vector2i(0, 0)), width(0), height(0), frame_w(0)
	{

	}

	void Table::draw(sf::RenderWindow& window) const
	{
		sprite.setScale(sf::Vector2f(float(width - 2 * frame_w) / standart_x, float(height - 2 * frame_w) / standart_y));
		sprite.setPosition(sf::Vector2f(draw_pos.x + frame_w, draw_pos.y + frame_w));
		window.draw(sprite);
	}

	Game_button::Game_button(const size_t w, const size_t h, const size_t fr_w, sf::Sprite& s, sf::Sprite& sec_s, sf::Sprite& back, const sf::Vector2i& start_pos)
		: Table(w, h, fr_w, s, start_pos), second_sprite(sec_s), background(back)
	{}

	Game_button::Game_button(sf::RenderWindow& win, const size_t s_w, const size_t s_h, sf::Sprite& s, sf::Sprite& sec_s, sf::Sprite& back, const sf::Vector2i& start_pos)
		: Table(win, s_w, s_h, s, start_pos), second_sprite(sec_s), background(back)
	{}

	Game_button::Game_button(Game_button&& new_r_button)
		: Table(new_r_button.width, new_r_button.height, new_r_button.frame_w, new_r_button.sprite, new_r_button.draw_pos), second_sprite(new_r_button.second_sprite), background(new_r_button.background)
	{}

	Game_button::Game_button()
		:	background(*(new sf::Sprite)), second_sprite(*(new sf::Sprite))
	{

	}

	bool Game_button::is_mouse_this(sf::RenderWindow& window) const
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		if (mouse_pos.x > (draw_pos.x + frame_w) && mouse_pos.x < (draw_pos.x + width - frame_w) && mouse_pos.y >(draw_pos.y + frame_w) && mouse_pos.y < (draw_pos.y + height - frame_w))
		{
			return true;
		}
		return false;
	}

	void Game_button::draw(sf::RenderWindow& window) const
	{
		if (is_mouse_this(window))
		{
			sprite.setColor(sf::Color(128, 128, 128));
		}
		else
		{
			sprite.setColor(sf::Color::White);
		}
		Table::draw(window);
	}

	void Game_button::draw_background(sf::RenderWindow& window, const size_t x0, const size_t y0, const size_t w, const size_t h) const
	{
		background.setScale(sf::Vector2f(float(w) / standart_x, float(h) / standart_y));
		background.setPosition(sf::Vector2f(x0, y0));
		//std::cout << x0 << "\t" << y0 << std::endl;
		window.draw(background);
	}

	void Game_button::turn_over(sf::RenderWindow& window)
	{
		//sprite.setColor(sf::Color::Blue);

		int speed = 1;

		std::cout << "it works" << std::endl;
		int basic_w = width;
		int basic_x = draw_pos.x;
		int basic_y = draw_pos.y;
		sf::Clock clock;
		float delay = 0.001;
		float timer = 0;
		while (width > 2 * frame_w)
		{
			clock.restart();
			timer += clock.getElapsedTime().asSeconds();
			if (timer > delay)
			{
				draw_pos.x += speed;
				width -= 2 * speed;
				draw_background(window, basic_x, basic_y, basic_w, height);
				draw(window);
				window.display();
				timer = 0;
			}
		}
		std::swap(sprite, second_sprite);
		while (width < basic_w)
		{
			clock.restart();
			timer += clock.getElapsedTime().asSeconds();
			if (timer > delay)
			{
				draw_pos.x -= speed;
				width += 2 * speed;
				draw_background(window, basic_x, basic_y, basic_w, height);
				draw(window);
				window.display();
				timer = 0;
			}
		}
		draw_pos.x = basic_x;
		draw_pos.y = basic_y;

	}

	void Game_button::set_background(sf::Sprite& back)
	{
		background = back;
	}

	void Game_button::set_all_fields(const size_t w, const size_t h, const size_t fr_w, sf::Sprite& s, sf::Sprite& sec_s, sf::Sprite& back, const sf::Vector2i& start_vec)
	{
		draw_pos = start_vec;
		width = w;
		height = h;
		frame_w = fr_w;
		sprite = s;
		second_sprite = sec_s;
		background = back;
	}

	void Game_button::print_all_fields() const
	{
		std::cout << "Width: " << width << "\tHeight: " << height << "\tStart_x: " << draw_pos.x << "\tStart_y: " << draw_pos.y << std::endl;
	}

	sf::Sprite& Game_button::get_sprite() const
	{
		return sprite;
	}


	Game_grid::Game_grid(const size_t c_x, const size_t c_y, const size_t one_x, const size_t one_y, const size_t fr_w, std::string** tex_name, std::string** sec_tex_name, std::string** back_name)
		:	count_x(c_x), count_y(c_y)
	{
		grid = new Game_button*[count_y];
		tex_array = new sf::Texture*[count_y];
		sec_tex_array = new sf::Texture * [count_y];
		back_tex_array = new sf::Texture * [count_y];
		size_t start_x = 0;
		size_t start_y = 0;
		for (int i = 0; i < count_y; i++)
		{
			grid[i] = new Game_button[count_x];
			tex_array[i] = new sf::Texture[count_x];
			sec_tex_array[i] = new sf::Texture[count_x];
			back_tex_array[i] = new sf::Texture[count_x];
			for (int j = 0; j < count_x; j++)
			{
				tex_array[i][j].loadFromFile(tex_name[i][j]);
				sec_tex_array[i][j].loadFromFile(sec_tex_name[i][j]);
				back_tex_array[i][j].loadFromFile(back_name[i][j]);
				sf::Sprite sprite, sec_sprite, back_sprite;
				sprite.setTexture(tex_array[i][j]);
				sec_sprite.setTexture(sec_tex_array[i][j]);
				back_sprite.setTexture(back_tex_array[i][j]);
				grid[i][j].set_all_fields(one_x, one_y, fr_w, sprite, sec_sprite, back_sprite, sf::Vector2i(start_x + j * one_x, start_y + i * one_y));
			}
		}
	}

	void Game_grid::draw(sf::RenderWindow& window) const
	{
		for (int i = 0; i < count_y; i++)
		{
			for (int j = 0; j < count_x; j++)
			{
				grid[i][j].draw(window);
			}
		}
	}

	Game_grid::~Game_grid()
	{
		for (int i = 0; i < count_y; i++)
		{
			delete[] tex_array[i];
			delete[] sec_tex_array[i];
			delete[] back_tex_array[i];
			delete[] grid[i];
		}
		delete[] tex_array;
		delete[] sec_tex_array;
		delete[] back_tex_array;
		delete[] grid;
	}

	sf::Texture& Game_grid::get_texture(const size_t i, const size_t j) const
	{
		return tex_array[i][j];
	}

	Game_button* Game_grid::operator[](const int index)
	{
		return grid[index];
	}

}	//	namespace gobj