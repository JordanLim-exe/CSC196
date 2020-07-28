#include "Locator.h"

void nc::Locator::Update(float dt)
{
	//matrix * parent_matrix
	if(m_parent) {
		m_transform.Update(m_parent->GetTransform().matrix);
	}
	else {
		m_transform.Update();
	}
}
