#include "pch.h"
#include "Scene.h"
#include "Actor.h"

namespace nc
{
	void Scene::Startup()
	{
		// nothing
	}

	void Scene::Shutdown()
	{
		RemoveAllActors();
	}

	void Scene::Update(float dt)
	{
		// iterate through the actors and call Update on each actor

		//check actor collisions
		std::vector<Actor*> actors{ m_actors.begin(), m_actors.end() };
		for (size_t i = 0; i < actors.size(); i++) {
			for (size_t j = i + 1; j < actors.size(); j++) {
				float distance = Vector2::Distance(actors[i]->GetTransform().position, actors[j]->GetTransform().position);
				if (distance <= (actors[i]->GetRadius() + actors[j]->GetRadius())) {
					actors[i]->OnCollision(actors[j]);
					actors[j]->OnCollision(actors[i]);
				}
			}
		}

		//remove destroyed actors
		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {
			if ((*iter)->IsDestroy()) {
				(*iter)->Destroy();
				delete* iter;
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		for (nc::Actor* actor : m_actors) {
			actor->Update(dt);
		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		// iterate through the actors and call Draw on each actor
		for (nc::Actor* actor : m_actors) {
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(Actor* actor)
	{
		// set the scene for the actor, use this
		// push back the actor on the actors list
		actor->SetScene(this);
		m_actors.push_back(actor);
	}

	void Scene::RemoveActor(Actor* actor)
	{
		auto iter = std::find(m_actors.begin(), m_actors.end(), actor);
		if (iter != m_actors.end())
		{
			delete* iter;
			m_actors.erase(iter);
		}
	}
	void Scene::RemoveAllActors()
	{
		for (Actor* actor : m_actors) {
			delete actor;
		}
		m_actors.clear();
	}
}
