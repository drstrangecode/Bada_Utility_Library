
#ifndef GL_COMMONS__
#define GL_COMMONS__

namespace DSBadaUtilityLib {

#define GL_ASSERT(msg) do {\
	GLenum error = glGetError(); \
	AppAssertf(error == GL_NO_ERROR, "GL_ASSERT failed on %s with error %d", msg, error); \
} while(0);

}

#endif
