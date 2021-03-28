#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

const sf::Vector2i std_vect(0, 0);
static sf::Sprite std_sprite;

namespace gobj
{

	class Table
	{
	protected:
		sf::Sprite& sprite;
		sf::Vector2i draw_pos;
		size_t width;
		size_t height;
		size_t frame_w;
	public:
		Table();
		Table(const size_t, const size_t, const size_t, sf::Sprite&, const sf::Vector2i&);	//	whole width, whole height, frame_w
		Table(sf::RenderWindow&, const size_t, const size_t, sf::Sprite&, const sf::Vector2i& = std_vect);					//	width_screen, heigth_screen
		virtual void draw(sf::RenderWindow&) const;
	};

	class Game_button : public Table
	{
		sf::Sprite& background;
		sf::Sprite& second_sprite;
		void draw_background(sf::RenderWindow&, const size_t, const size_t, const size_t, const size_t) const;	// x0, y0, width, height
	public:
		Game_button();
		Game_button(const size_t, const size_t, const size_t, sf::Sprite&, sf::Sprite&, sf::Sprite&, const sf::Vector2i&);
		Game_button(sf::RenderWindow&, const size_t, const size_t, sf::Sprite&, sf::Sprite&, sf::Sprite&, const sf::Vector2i& = std_vect);
		Game_button(Game_button&&);
		void set_background(sf::Sprite&);
		bool is_mouse_this(sf::RenderWindow&) const;
		void draw(sf::RenderWindow&) const;
		void turn_over(sf::RenderWindow&);
		void set_all_fields(const size_t = 0, const size_t = 0, const size_t = 0, sf::Sprite & = std_sprite, sf::Sprite & = std_sprite, sf::Sprite & = std_sprite, const sf::Vector2i & = std_vect);
		void print_all_fields() const;
		sf::Sprite& get_sprite() const;
	};

	class Game_grid
	{
		Game_button** grid;
		sf::Texture** tex_array;
		sf::Texture** sec_tex_array;
		sf::Texture** back_tex_array;
		size_t count_x;
		size_t count_y;
	public:
		//Game_grid(const size_t, const size_t, const size_t, std::string**, std::string**, std::string**);	//	window, width_screen, height_screen, frame_w, texture_names, second_texture_names, background_names
		Game_grid(const size_t, const size_t, const size_t, const size_t, const size_t, std::string**, std::string**, std::string**);	//	count_x, count_y, one_size_x, one_size_y, frame_w, texture_names, second_texture_names, background_names
		~Game_grid();
		sf::Texture& get_texture(const size_t, const size_t) const;
		void draw(sf::RenderWindow&) const;
		Game_button* operator[](const int);
	};

}	//	namespace tbl