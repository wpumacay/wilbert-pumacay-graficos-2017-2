

#include "LInputHandler.h"



namespace engine
{

	LInputHandler* LInputHandler::INSTANCE = NULL;

	LInputHandler::LInputHandler()
	{
		for ( int q = 0; q < L_MAX_KEYS; q++ )
		{
			m_keys[q] = L_RELEASE;
		}

		for ( int q = 0; q < L_MAX_BUTTONS; q++ )
		{
			m_buttons[q] = L_RELEASE;
		}

		m_mouseX = 0.0f;
		m_mouseY = 0.0f;
	}



	LInputHandler::~LInputHandler()
	{
		if ( m_window != NULL )
		{
			m_window->registerKeyCallback( NULL );
			m_window->registerMouseCallback( NULL );
		}
	}

	void LInputHandler::create( LWindow* pWindow )
	{
		if ( LInputHandler::INSTANCE != NULL )
		{
			delete LInputHandler::INSTANCE;
		}

		LInputHandler::INSTANCE = new LInputHandler();

		// register callbacks for window
		pWindow->registerKeyCallback( LInputHandler::callback_key );
		pWindow->registerMouseCallback( LInputHandler::callback_mouse );
        pWindow->registerMouseMoveCallback( LInputHandler::callback_mouseMove );
	}

	void LInputHandler::release()
	{
		if ( LInputHandler::INSTANCE != NULL )
		{
			delete LInputHandler::INSTANCE;
			LInputHandler::INSTANCE = NULL;	
		}
	}


	void LInputHandler::callback_key( int key, int action )
	{
		if ( LInputHandler::INSTANCE == NULL )
		{
			return;
		}

		LInputHandler::INSTANCE->m_keys[key] = action;
	}

	void LInputHandler::callback_mouse( int button, int action, double x, double y )
	{
		if ( LInputHandler::INSTANCE == NULL )
		{
			return;
		}

		LInputHandler::INSTANCE->m_buttons[button] = action;
		LInputHandler::INSTANCE->m_mouseX = x;
		LInputHandler::INSTANCE->m_mouseY = y;
	}

    void LInputHandler::callback_mouseMove( double x, double y )
    {
        if ( LInputHandler::INSTANCE == NULL )
        {
            return;
        }

        LInputHandler::INSTANCE->m_mouseX = x;
        LInputHandler::INSTANCE->m_mouseY = y;
    }

	bool LInputHandler::isKeyPressed( int key )
	{
		if ( key < 0 || key >= L_MAX_KEYS )
		{
			std::cout << "LInputHandler::isKeyPressed> wrong key requested: " << key << std::endl;
			return false;
		}

		return m_keys[key] == L_PRESS;
	}

	bool LInputHandler::isButtonPressed( int button )
	{
		if ( button < 0 || button >= L_MAX_BUTTONS )
		{
			std::cout << "LInputHandler::isButtonPressed> wrong button requested: " << button << std::endl;
			return false;
		}

		return m_buttons[button] == L_PRESS;
	}

	void LInputHandler::getMousePosition( float& x, float& y )
	{
		x = m_mouseX;
		y = m_mouseY;
	}


}