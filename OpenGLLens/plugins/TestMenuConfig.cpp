#include "TestMenuConfig.h"

#include "ClearColorTest.h"
#include "FrameBuffersTest.h"

namespace OpenGLLens
{
	void TestMenuConfig::RegisterTests(TestMenu& menu)
	{
		// Register tests here	
		menu.registerTest<ClearColorTest>("Clear Color Test");
		menu.registerTest<FrameBuffersTest>("Frame Buffers Test");
	}
}
