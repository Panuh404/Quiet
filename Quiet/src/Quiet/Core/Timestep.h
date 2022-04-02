#pragma once

namespace Quiet {

	class Timestep {
		
	public:
		Timestep(float Time = 0.0f) : m_Time(Time) {}

		operator float() const { return m_Time; }
		
		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
		
	private:
		float m_Time;
	};
}