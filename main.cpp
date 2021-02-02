#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#define L long long
#define LD long double
#include "TextField.h"

using namespace sf;

bool create_image(std::vector<Color> colors, bool is_gif, std::complex<LD> C, int im_size, LD x0, LD y0, LD scale, int im_n);

int main()
{
    RenderWindow window(VideoMode(1000, 700), "Julian");
	window.setFramerateLimit(60);

	srand(time(0));

	Font font;
    font.loadFromFile("fonts/font.otf");

    Texture bgt;
    bgt.loadFromFile("images/bg.jpg", IntRect(400, 100, 1000, 700));
    Sprite bg(bgt);

	std::vector<TextField> options_tf;
    options_tf.push_back(TextField(Vector2f(310, 50), font, 30, "Размер картинки в пиксилях"));
    options_tf.push_back(TextField(Vector2f(60, 180), font, 30, "Вещественная часть точки отсчёта"));
    options_tf.push_back(TextField(Vector2f(545, 180), font, 30, "Мнимая часть точки отсчёта"));
    options_tf.push_back(TextField(Vector2f(60, 300), font, 30, "Абсцисса центра картинки"));
    options_tf.push_back(TextField(Vector2f(545, 300), font, 30, "Ордината центра картинки"));
    options_tf.push_back(TextField(Vector2f(310, 420), font, 30, "Границы картинки от центра"));
    options_tf.push_back(TextField(Vector2f(310, 540), font, 30, "Нажмите, чтобы создать картинку"));
    options_tf.back().is_button = true;
    options_tf.back().second_text = "Подождите, картинка создаётся...";
    options_tf.push_back(TextField(Vector2f(40, 580), font, 15, "Плавные цвета"));
    options_tf.back().is_button = true;
    options_tf.back().second_text = "Случайные цвета";
    options_tf.push_back(TextField(Vector2f(750, 580), font, 15, "Одна картинка"));
    options_tf.back().is_button = true;
    options_tf.back().second_text = "Серия картинок";

    std::vector<Color> colors(256);
    for (int i=0; i < 256; ++i)
        colors[i] = Color(rand() % 256, rand() % 256, rand() % 256);

    std::vector<LD> options(6, 0);
    options[0] = 200;
    options[5] = 2;

    L im_n = 1;

    Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
		    for (int i=0; i < options_tf.size(); ++i)
            {
                if (options_tf[i].input(event))
                {
                    if (i < 6)
                    {
                        try
                        {
                            options[i] = stod(options_tf[i].getText().toAnsiString());
                        }
                        catch(...)
                        {
                            options_tf[i].setPlaceholder("Вообще-то сюда надо вводить число");
                        }
                    }
                }
            }
			if (event.type == Event::Closed)
                window.close();
		}

		window.clear();
		window.draw(bg);
		for (int i=0; i < options_tf.size(); ++i)
                options_tf[i].render(window);
		window.display();

		if (options_tf[6].dk)
        {
            if (options_tf[7].dk)
                colors[0] = Color::White;
            create_image(colors, options_tf[8].dk, std::complex<LD>(options[1], options[2]), options[0], options[3], options[4], options[5], im_n);
            options_tf[6].regen();
            im_n++;
        }
	}

	return 0;
}

bool create_image(std::vector<Color> colors, bool is_gif, std::complex<LD> C, int im_size, LD x0, LD y0, LD scale, int im_n)
{
    Image im;
	im.create(im_size, im_size, Color::White);

	bool use_colors = colors[0] != Color::White;

	const int it_count = 256;

    int n;
    for (long double a = 0, n = 0; a < 2 * 3.141592; a += 0.03, ++n)
    {
        for (L x=0; x < im_size; ++x)
        {
            for (L y=0; y < im_size; ++y)
            {
                int k=0;
                LD x1 = x0 - scale + 2 * scale * x / im_size, y1 = y0 - scale + 2 * scale * y / im_size;
                std::complex<LD> c = C, z(x1, y1);
                if (is_gif)
                    c += std::complex<LD>(0.6 * sin(a), 0.6 * cos(a));

                for (int i=0; i < it_count; ++i)
                {
                    z = z * z + c;
                    if (abs(z) > 2)
                    {
                        k = i + 1;
                        break;
                    }
                }

                if (use_colors)
                {
                    long double t = k;
                    int g, b, r = 255 * (1 - t / ((int)it_count / 2)) * (1 - pow(sin(t / it_count * 3.1415 - 1), 2));
                    g = 255 * (1 - t / ((int)it_count / 2)) * (1 - pow(sin(t / it_count * 3.1415 + 2), 2));
                    b = 255 * (1 - t / ((int)it_count / 2)) * (1 - pow(sin(t / it_count * 3.1415 - 7), 2));

                    im.setPixel(x, im_size - y - 1, k != 0 ? Color(r, g, b) : Color(249, 166, 2));
                }
                else
                {
                    im.setPixel(x, im_size - y - 1, colors[k]);
                }
            }
        }

        im.saveToFile("images/ready/" + std::to_string((int)(is_gif ? n : im_n)) + (is_gif ? "to_gif" : "") + ".jpg");

        if (!is_gif)
            break;
    }
}
