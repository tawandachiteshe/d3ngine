#include <d3gpch.h>
#include <D3NGINE/Renderer/RendererAPI.h>
#include "D3NGINE/Platform/OpenGL/Renderer/OpenGLGraphicsContext.h"
#include <D3NGINE/Renderer/GraphicsContext.h>
#include <D3NGINE/Platform/DirectX/Renderer/D3DGraphicsContext.h>

namespace D3G
{


	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:    D3G_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::Opengl:  return CreateScope<OpenGLGraphicsContext>(static_cast<SDL_Window*>(window));
			case RendererAPI::API::DirectX: return CreateScope<D3DGraphicsContext>(static_cast<SDL_Window*>(window));
		}

		D3G_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

} /* namespace D3G */
