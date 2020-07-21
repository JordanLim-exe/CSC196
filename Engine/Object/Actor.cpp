#include "pch.h"
#include "Actor.h"
#include <fstream>

namespace nc {
	bool nc::Actor::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open()) {
			success = true;

			//stream >> into transform
			Load(stream);

			stream.close();
		}
	return success;
	}

	void Actor::Load(std::istream& stream)
	{
		//stream >> into transform
		stream >> m_transform.position;
		stream >> m_transform.scale;
		stream >> m_transform.angle;

		std::string shapename;
		stream >> shapename;
		m_shape.Load(shapename);
	}

	void nc::Actor::Update(float dt)
	{
	}

	void nc::Actor::Draw(Core::Graphics& graphics)
	{
		m_shape.Draw(graphics, m_transform);
	}

}
