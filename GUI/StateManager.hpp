#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include "Application.hpp"

class StateManager{
	protected:
		Application* app;
	public:
		virtual void draw(const float dt) = 0;
		virtual void update(const float dt) = 0;
		virtual void handleInput() = 0;
};

#endif