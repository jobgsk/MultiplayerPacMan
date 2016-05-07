#ifndef TEXTURES_FACTORY_H_
#define TEXTURES_FACTORY_H_

#include <iostream>
#include <assert.h>
#include <map>
#include <sstream>

#include "../graphics/Graphics.h"

class TexturesFactory {

	static std::map<int, GLuint> e_texture;
	static std::map<int, GLuint> p_texture;
	static std::map<int, GLuint> v_texture;
	
	static GLuint w1_texture;

	static GLuint c1_texture;
	static GLuint c2_texture;

public:
	/*
		coints
	*/
	static GLuint getC1()
	{
		if (c1_texture == -1) {
			c1_texture = Graphics::LoadTexture("media/textures/c1.bmp");
			if (c1_texture == -1) {
				std::cout << "texture does not load media/textures/c1.bmp " << std::endl;
				assert(false);
			}
		}
		return c1_texture;
	};

	static GLuint getC2()
	{
		if (c2_texture == -1) {
			c2_texture = Graphics::LoadTexture("media/textures/c2.bmp");
			if (c2_texture == -1) {
				std::cout << "texture does not load media/textures/c2.bmp " << std::endl;
				assert(false);
			}
		}
		return c2_texture;
	};

	/*
		enemies
	*/

	static GLuint getE(int a, int b, int c)
	{
		std::map<int, GLuint>::iterator it;
		int index = a * 100 + b * 10 + c;
		it = e_texture.find(index);
		if (it == e_texture.end())
		{
			std::stringstream sstm1;
			sstm1 << "media/textures/e";
			sstm1 << index;
			sstm1 << ".bmp";
			const std::string filename = sstm1.str();

			GLuint texture_id = Graphics::LoadTexture(filename.c_str());
			if (texture_id == -1) {
				std::cout << "texture does not load " << sstm1.str() << std::endl;
				assert(false);
			}

			e_texture[index] = texture_id;
		}
		return e_texture[index];
	};

	
	/*
		player
	*/
	static GLuint getP(int a, int b)
	{
		std::map<int, GLuint>::iterator it;
		int index = a * 10 + b;
		it = p_texture.find(index);
		if (it == p_texture.end())
		{
			std::stringstream sstm1;
			sstm1 << "media/textures/p";
			sstm1 << index;
			sstm1 << ".bmp";
			const std::string filename = sstm1.str();

			GLuint texture_id = Graphics::LoadTexture(filename.c_str());
			if (texture_id == -1) {
				std::cout << "texture does not load " << sstm1.str() << std::endl;
				assert(false);
			}

			p_texture[index] = texture_id;
		}
		return p_texture[index];
	};

	/*
		victim
	*/
	static GLuint getV(int a, int b)
	{
		std::map<int, GLuint>::iterator it;
		int index = a * 10 + b;
		it = v_texture.find(index);
		if (it == v_texture.end())
		{
			std::stringstream sstm1;
			sstm1 << "media/textures/v";
			sstm1 << index;
			sstm1 << ".bmp";
			const std::string filename = sstm1.str();

			GLuint texture_id = Graphics::LoadTexture(filename.c_str());
			if (texture_id == -1) {
				std::cout << "texture does not load " << sstm1.str() << std::endl;
				assert(false);
			}

			v_texture[index] = texture_id;
		}
		return v_texture[index];
	};


	/*
		obstacles
	*/
	static GLuint getW1()
	{
		if (w1_texture == -1) {
			w1_texture = Graphics::LoadTexture("media/textures/w1.bmp");
			if (w1_texture == -1) {
				std::cout << "texture does not load media/textures/w1.bmp " << std::endl;
				assert(false);
			}
		}
		return w1_texture;
	};

};
#endif /* TEXTURES_FACTORY_H_ */
