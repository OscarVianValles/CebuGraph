#pragma once
#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

#include<SFML/Graphics.hpp>

#include "StateManager.hpp"

class TestState : public StateManager
{
	private:
		void pauseState();
	public:
		virtual void draw(const float dt);
		virtual void update(const float dt);
		virtual void handleInput();

		TestState(Application* app);
};

#endif