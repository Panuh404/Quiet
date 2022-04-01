#include "Quiet_pch.h"
#include "Application.h"
#include "Input.h"

#include "glad/glad.h"

namespace Quiet {
	
	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case Quiet::ShaderDataType::Bool:		return GL_BOOL;
			case Quiet::ShaderDataType::Int:		return GL_INT;
			case Quiet::ShaderDataType::Int2:		return GL_INT;
			case Quiet::ShaderDataType::Int3:		return GL_INT;
			case Quiet::ShaderDataType::Int4:		return GL_INT;
			case Quiet::ShaderDataType::Float:		return GL_FLOAT;
			case Quiet::ShaderDataType::Float2:		return GL_FLOAT;
			case Quiet::ShaderDataType::Float3:		return GL_FLOAT;
			case Quiet::ShaderDataType::Float4:		return GL_FLOAT;
			case Quiet::ShaderDataType::Mat3:		return GL_FLOAT;
			case Quiet::ShaderDataType::Mat4:		return GL_FLOAT;
		}
		QUIET_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application() {
		QUIET_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[] = {

			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.7f, 0.2f, 1.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color"}
			};
			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element :layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		out vec3 v_Position;
		out vec4 v_Color;

		void main(){
			v_Color = a_Color;
			v_Position = a_Position;
			gl_Position = vec4(a_Position, 1.0);
		}
		)";

		std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;		
		in vec4 v_Color;

		void main(){
			color = vec4(v_Position * 0.5 + 0.5, 1.0);
			color = v_Color;
		}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}
	
	Application::~Application() {
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	
	void Application::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(event);
			if (event.m_Handled) {
				break;
			}
		}
	}
	
	bool Application::OnWindowClose(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}
	
	void Application::Run() {
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			
			m_Window->OnUpdate();
			
		}
	}
}
