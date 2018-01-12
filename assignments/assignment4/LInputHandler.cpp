

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
#ifdef GLUT_SUPPORT_ENABLED        
        key = _fix_mayus_letters_keys( key );
#endif
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

    int LInputHandler::_fix_mayus_letters_keys( int keyLetter )
    {
        int key = keyLetter - 32;

        if ( key == L_KEY_A || key == L_KEY_B || key == L_KEY_C ||
             key == L_KEY_D || key == L_KEY_E || key == L_KEY_F ||
             key == L_KEY_G || key == L_KEY_H || key == L_KEY_I ||
             key == L_KEY_J || key == L_KEY_K || key == L_KEY_L ||
             key == L_KEY_M || key == L_KEY_N || key == L_KEY_O ||
             key == L_KEY_P || key == L_KEY_Q || key == L_KEY_R ||
             key == L_KEY_S || key == L_KEY_T || key == L_KEY_U ||
             key == L_KEY_V || key == L_KEY_W || key == L_KEY_X ||
             key == L_KEY_Y || key == L_KEY_Z )
        {
            return key;
        }

        return keyLetter;
    }

}