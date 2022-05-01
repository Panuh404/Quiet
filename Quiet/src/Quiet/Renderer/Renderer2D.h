#pragma once

#include "Quiet/Renderer/OrthographicCamera.h"
#include "Quiet/Renderer/Texture.h"
#include "Quiet/Renderer/SubTexture2D.h"

#include <glm/glm.hpp>

namespace Quiet
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));		
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));		

		// Rotations in Radians
		static void DrawQuadRotated(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuadRotated(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		static void DrawQuadRotated(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawQuadRotated(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));

		static void DrawQuadRotated(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));
		static void DrawQuadRotated(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4 tintColor = glm::vec4(1.0f));

		// Stats
		struct Stats
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static void ResetStats();
		static Stats GetStats();

	private:
		static void FlushAndReset();

	};
}