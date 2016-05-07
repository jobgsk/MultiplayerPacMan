#ifndef RENDER_H_
#define RENDER_H_

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>

#include "StaticModelLoader.h"
#include "Graphics.h"
#include "../physics/Vector3.h"

class Render{
protected:
	
public:
	
	Render()
	{

	};

	virtual void render()
	{

	};

	virtual void render(float mat[])
	{

	};
};


class SphereRender : public Render{
public:
	float m_radius;
	GLUquadricObj* m_quad;
	float m_r, m_g, m_b;

	SphereRender(float r, float g, float b, float radius) : 
		Render(),
		m_radius(radius),
		m_r(r), m_g(g), m_b(b)
	{
		m_quad = gluNewQuadric();
	};

	virtual ~SphereRender()
	{
		gluDeleteQuadric(m_quad);
	};

	virtual void render(float mat[])
	{
		//std::cout << " test " << m_radius << std::endl;
		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation

		//glColor3f(m_r, m_g, m_b);
		gluSphere(m_quad, m_radius, 20, 20);
		glColor4f(1.f, 1.f, 1.f, 1.f);
		glPopMatrix();
	};
};

class BoxRender : public Render{
public:
	Vector3<float> m_extent;
	GLuint m_texture;

	BoxRender(GLuint texture, Vector3<float> extent) :
		Render(), m_extent(extent), m_texture(texture)
	{
		
	};

	virtual void render(float mat[])
	{
		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation

		//glEnable(GL_COLOR_MATERIAL);
		//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0 }; //
		GLfloat mat_ambient[] = { 1, 1, 0, 1.0 }; //yello
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//top of cube
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0, 1);	
		glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0, 0);	
		glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
		glNormal3f(0, 1, 0);
		glTexCoord2f(1, 0);	
		glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
		glNormal3f(0, 1, 0);
		glTexCoord2f(1, 1);	
		glVertex3f(m_extent.x, m_extent.y, m_extent.z);
		glEnd();

		// bottom of cube
		glBegin(GL_QUADS);
		//glTexCoord2f(0, 1);	
		glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
		//glTexCoord2f(0, 0); 
		glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
		//glTexCoord2f(1, 0); 
		glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
		//glTexCoord2f(1, 1); 
		glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
		glEnd();

		// front of cube
		glBegin(GL_QUADS);

		//glNormal3f(0, 0, 1);
		//glTexCoord2f(0, 0);
		glVertex3f(m_extent.x, m_extent.y, m_extent.z);
		
		//glNormal3f(0, 0, 1);
		//glTexCoord2f(1, 0);
		glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
		
		//glNormal3f(0, 0, 1);
		//glTexCoord2f(1, 1);
		glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
		
		//glNormal3f(0, 0, 1);
		//glTexCoord2f(0, 1);
		glVertex3f(m_extent.x, -m_extent.y, m_extent.z);

		glEnd();

		// back of cube.
		glBegin(GL_QUADS);

		//glNormal3f(0, 0, -1);
		//glTexCoord2f(0, 0);
		glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
		
		//glNormal3f(0, 0, -1);
		//glTexCoord2f(1, 0);
		glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
		
		//glNormal3f(0, 0, -1);
		//glTexCoord2f(1, 1);
		glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
		
		//glNormal3f(0, 0, -1);
		//glTexCoord2f(0, 1);
		glVertex3f(m_extent.x, m_extent.y, -m_extent.z);

		glEnd();

		// left of cube
		glBegin(GL_QUADS);
		//glTexCoord2f(0, 1); 
		glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
		//glTexCoord2f(0, 0); 
		glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
		//glTexCoord2f(1, 0); 
		glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
		//glTexCoord2f(1, 1); 
		glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
		glEnd();

		// Right of cube
		glBegin(GL_QUADS);
		//glTexCoord2f(0, 1); 
		glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
		//glTexCoord2f(0, 0); 
		glVertex3f(m_extent.x, m_extent.y, m_extent.z);
		//glTexCoord2f(1, 0); 
		glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
		//glTexCoord2f(1, 1); 
		glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
		glEnd();


		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	};
};

class MeshRender : public Render {
protected:
	
public:
	ModelsStruct *m_mesh;
	//Matrix4<float> m_matrix;

	MeshRender(ModelsStruct * mesh) : Render()
	{
		//m_matrix = Matrix4<float>();
		StaticModelLoader * loader = mesh->loader;
		m_mesh = CopyModel(loader);
	};

	MeshRender(char *meshpath, char *matpath, char * texpath) : Render()
	{
		StaticModelLoader* loader = new StaticModelLoader(meshpath, matpath);
		loader->load_texture(texpath);
		m_mesh = CopyModel(loader);

		std::cout << m_mesh->rx << " " << m_mesh->ry << " " << m_mesh->rz << std::endl;
	};

	MeshRender(char *meshpath, char *matpath, char * texpath, float scale) : Render()
	{
		StaticModelLoader* loader = new StaticModelLoader(meshpath, matpath);
		loader->load_texture(texpath);
		m_mesh = CopyModel(loader, scale);

		std::cout << m_mesh->rx << " " << m_mesh->ry << " " << m_mesh->rz << std::endl;
	};

	ModelsStruct* get_mesh()
	{
		return m_mesh;
	};

	virtual ~MeshRender()
	{
		delete[] m_mesh->v_array;
	};

	virtual void render(float mat[])
	{
		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation

		glEnable(GL_TEXTURE_2D);

		GLuint texture = -1;
		for (int i = 0; i < m_mesh->f_num; i++)
		{
			if (texture == -1 || texture != m_mesh->f_array[i].material->TexID)
			{
				if (m_mesh->f_array[i].material->map_kd.size() > 0)
				{
					texture = m_mesh->f_array[i].material->TexID;
					//std::cout << " GL_TEXTURE_2D " << texture << std::endl;
					glBindTexture(GL_TEXTURE_2D, texture);
					//glBindTexture(GL_TEXTURE_2D, 1);
				}
			}
			draw_poligon(i);
		}

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	};

	void draw_poligon(int i)
	{
		glBegin(GL_POLYGON);
		/*if (model->f_array[i].material->kdr) {
			glColor3f(m_model->f_array[i].material->kdr,
			m_model->f_array[i].material->kdg,	m_model->f_array[i].material->kdb);
		}
		*/
		for (int j = 0; j < m_mesh->f_array[i].fi_num; j++) {

			if (m_mesh->vn_num > 0)
			{
				glNormal3f(
					m_mesh->f_array[i].fi_array[j].vn->x,
					m_mesh->f_array[i].fi_array[j].vn->y,
					m_mesh->f_array[i].fi_array[j].vn->z);
			}
				

			if (m_mesh->vt_num > 0)
			{
				glTexCoord2f(
					m_mesh->f_array[i].fi_array[j].vt->u,
					m_mesh->f_array[i].fi_array[j].vt->v);

				//std::cout << " GL_TEXTURE_2D " << m_mesh->f_array[i].material->TexID << std::endl;
			}
				

			glVertex3f(
				m_mesh->f_array[i].fi_array[j].v->x,
				m_mesh->f_array[i].fi_array[j].v->y,
				m_mesh->f_array[i].fi_array[j].v->z);
		}
		glEnd();
	};
};

class TextRender : public Render{
public:
	
	std::string m_init_text;
	std::string m_render_text;
	int m_x, m_y;


	TextRender(std::string text, int x, int y) : Render(),
		m_render_text(text), m_x(x), m_y(y)
	{
		m_init_text = text;
	};

	virtual void render()
	{
		const char * text = m_render_text.data();
		int length = m_render_text.size();
		
		// change the current matrix to PROJECTION
		glMatrixMode(GL_PROJECTION);
		// 16 doubles in stack memory
		double matrix[16];
		// get the values from PROJECTION matrix to local variable
		glGetDoublev(GL_PROJECTION_MATRIX, matrix);
		// reset PROJECTION matrix to identity matrix
		glLoadIdentity();
		// orthographic perspective
		glOrtho(0, 800, 0, 600, -5, 5);
		// change current matrix to MODELVIEW matrix again
		glMatrixMode(GL_MODELVIEW);
		// reset it to identity matrix
		glLoadIdentity();
		// push current state of MODELVIEW matrix to stack
		glPushMatrix();
		// reset it again. (may not be required, but it my convention)
		glLoadIdentity();
		// raster position in 2D
		glRasterPos2i(m_x, m_y);
		for (int i = 0; i<length; i++)
		{
			// generation of characters in our text with 9 by 15 GLU font
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
		}
		// get MODELVIEW matrix value from stack
		glPopMatrix();
		// change current matrix mode to PROJECTION
		glMatrixMode(GL_PROJECTION);
		// reset
		glLoadMatrixd(matrix);
		// change current matrix mode to MODELVIEW
		glMatrixMode(GL_MODELVIEW);
	};

};

#endif /* RENDER_H_ */