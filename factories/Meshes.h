#ifndef MESH_FACTORY_H_
#define MESH_FACTORY_H_

#include "../graphics/render.h"
//class MeshRender;
class MeshFactory {

	static MeshRender *box1_render;

public:

	//static MeshRender* getBox1();
	static MeshRender* getBox1()
	{
		if (!MeshFactory::box1_render) {
			MeshFactory::box1_render = new MeshRender(
				"media/models/box/1/box1.obj", 
				"media/models/box/1/box1.mtl", 
				"media/models/box/1/");
		}
		return MeshFactory::box1_render;
	};
	
};
#endif /* MESH_FACTORY_H_ */
