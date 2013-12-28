#ifndef GPUPARTICLES_H
#define GPUPARTICLES_H

#ifndef _IRR_WINDOWS_API_
#define GL_GLEXT_PROTOTYPES 1
#endif
#include "graphics/glwrap.hpp"
#include <ISceneManager.h>

void initGL();
GLuint LoadProgram(const char * vertex_file_path, const char * fragment_file_path);
GLuint LoadTFBProgram(const char * vertex_file_path, const char **varyings, unsigned varyingscount);
GLuint getTextureGLuint(irr::video::ITexture *tex);
void bindUniformToTextureUnit(GLuint location, GLuint texid, unsigned textureUnit);


class GPUParticle : public scene::ISceneNode {
protected:
	video::SMaterial fakemat;
	virtual void simulate() = 0;
	virtual void draw() = 0;
public:
    //GPUParticle(unsigned c, float *initialSamples, GLuint tex, GLuint rtt);
	GPUParticle(scene::ISceneManager* mgr, ITexture *tex);
	virtual void render();
	virtual void OnRegisterSceneNode();
};

class RainNode : public GPUParticle
{
protected:
	GLuint SimulationProgram, RenderProgram, tfb_vertex_buffer[2];
	unsigned count;
	GLuint texture, normal_and_depth;
	GLuint loc_campos, loc_viewm, loc_time;
	GLuint loc_screenw, loc_screen, loc_invproj, texloc_tex, texloc_normal_and_depths;
	s32 area;
	core::aabbox3d<f32> box;

	virtual void simulate();
	virtual void draw();
public:
	RainNode(scene::ISceneManager* mgr, ITexture *tex);
	virtual const core::aabbox3d<f32>& getBoundingBox() const;
	virtual u32 getMaterialCount() const { return 1; }
};

#endif // GPUPARTICLES_H