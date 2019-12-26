#ifndef __DOTTH_FRAMEBUFFER_HPP__
#define __DOTTH_FRAMEBUFFER_HPP__

#include "dotth.hpp"

namespace dotth {
	namespace render {
		class framebuffer {
			static framebuffer create(void)
			{
				framebuffer fb;
                return fb;
				//glGenFramebuffers(1, &fb._id);
				//glBindFramebuffer(GL_FRAMEBUFFER, fb._id);
				//
				//return fb;
				//glClearColor(0.f, 0.f, 0.f, 0.f);
				//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				//glEnable(GL_DEPTH_TEST);
				//glBindFramebuffer(GL_FRAMEBUFFER, 0);
				//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
				//{
				//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 999, 0);
				//}
				//glBindFramebuffer(GL_FRAMEBUFFER, 0);
				//glDeleteFramebuffers(1, &fb._id);
			}
			unsigned int _id = 0;

			bool bind(void)
			{
				return true;
			}
			bool unbind(void)
			{
				return true;
			}

			void destroy(void)
			{

			}
		};
	};
};

#endif // __DOTTH_FRAMEBUFFER_HPP__
