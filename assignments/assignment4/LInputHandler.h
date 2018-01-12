

#pragma once

#include "LWindow.h"
#include <iostream>

namespace engine
{

	class LInputHandler
	{
		private :

		LWindow* m_window;

		LInputHandler();

		int m_keys[L_MAX_KEYS];
		int m_buttons[L_MAX_BUTTONS];
		float m_mouseX;
		float m_mouseY;

        static int _fix_mayus_letters_keys( int key );

		public :

		~LInputHandler();

		static LInputHandler* INSTANCE;
		static void create( LWindow* pWindow );
		static void release();

		static void callback_key( int key, int action );
        static void callback_keyUp( int key, int action );
		static void callback_mouse( int button, int action, double x, double y );
        static void callback_mouseMove( double x, double y );


		bool isKeyPressed( int key );
		bool isButtonPressed( int button );
		void getMousePosition( float& x, float& y );

	};



}



