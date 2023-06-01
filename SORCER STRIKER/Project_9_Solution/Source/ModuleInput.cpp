#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keys[i] = KEY_IDLE;

	for (int i = 0; i < MAX_PADS; ++i)
	{
		GamePad& pad = pads[i];
		pad.a = KEY_IDLE;
	}
	memset(&pads[0], 0, sizeof(GamePad) * MAX_PADS);
}

ModuleInput::~ModuleInput()
{

}

bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_INIT_GAMECONTROLLER could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_InitSubSystem(SDL_INIT_HAPTIC) < 0)
	{
		LOG("SDL_INIT_HAPTIC could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

Update_Status ModuleInput::PreUpdate()
{
	//Read all keyboard data and update our custom array
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}
	

	
	//Read new SDL events
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
			case(SDL_CONTROLLERDEVICEADDED):
			{
				HandleDeviceConnection(event.cdevice.which);
				break;
			}
			case(SDL_CONTROLLERDEVICEREMOVED):
			{
				HandleDeviceRemoval(event.cdevice.which);
				break;
			}
			case(SDL_QUIT):
			{
				return Update_Status::UPDATE_STOP;
				break;
			}
		}
	}

	UpdateGamepadsInput();

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");

	// Stop rumble from all gamepads and deactivate SDL functionallity
	for (uint i = 0; i < MAX_PADS; ++i)
	{
		if (pads[i].haptic != nullptr)
		{
			SDL_HapticStopAll(pads[i].haptic);
			SDL_HapticClose(pads[i].haptic);
		}
		if (pads[i].controller != nullptr) SDL_GameControllerClose(pads[i].controller);
	}

	SDL_QuitSubSystem(SDL_INIT_HAPTIC);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	return true;
}

void ModuleInput::HandleDeviceConnection(int index)
{
	if (SDL_IsGameController(index))
	{
		for (int i = 0; i < MAX_PADS; ++i)
		{
			GamePad& pad = pads[i];

			if (pad.enabled == false)
			{
				if (pad.controller = SDL_GameControllerOpen(index))
				{
					LOG("Found a gamepad with id %i named %s", i, SDL_GameControllerName(pad.controller));
					pad.enabled = true;
					pad.l_dz = pad.r_dz = 0.1f;
					pad.haptic = SDL_HapticOpen(index);
					if (pad.haptic != nullptr)
						LOG("... gamepad has force feedback capabilities");
					pad.index = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(pad.controller));
				}
			}
		}
	}
}

void ModuleInput::HandleDeviceRemoval(int index)
{
	// If an existing gamepad has the given index, deactivate all SDL device functionallity
	for (int i = 0; i < MAX_PADS; ++i)
	{
		GamePad& pad = pads[i];
		if (pad.enabled && pad.index == index)
		{
			SDL_HapticClose(pad.haptic);
			SDL_GameControllerClose(pad.controller);
			memset(&pad, 0, sizeof(GamePad));
		}
	}
}

void ModuleInput::UpdateGamepadsInput()
{
	/*bool buttonB, buttonX, buttonY, buttonStart, buttonBack, buttonGuide, buttonL, buttonR, buttonL2, buttonR2, buttonL3, buttonR3, buttonUp, buttonDown;*/
	bool buttonLeft, buttonRight, buttonUp, buttonDown, buttonStart, buttonBack, buttonGuide;
	// Iterate through all active gamepads and update all input data
	for (int i = 0; i < MAX_PADS; ++i)
	{
		GamePad& pad = pads[i];

		//code for making the gamepad trigger only once per press
		if (pad.enabled == true)
		{
			
			/*buttonA = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_A) == 1;
			if (buttonA)
				pad.a = (pad.a == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.a = (pad.a == KEY_REPEAT || pad.a == KEY_DOWN) ? KEY_UP : KEY_IDLE;

			buttonB = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_B) == 1;
			if (buttonB)
				pad.b = (pad.b == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.b = (pad.b == KEY_REPEAT || pad.b == KEY_DOWN) ? KEY_UP : KEY_IDLE;
			
			buttonX = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_X) == 1;
			if (buttonX)
				pad.x = (pad.x == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.x = (pad.x == KEY_REPEAT || pad.x == KEY_DOWN) ? KEY_UP : KEY_IDLE;

			buttonY = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_Y) == 1;
			if (buttonY)
				pad.y = (pad.y == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.y = (pad.y == KEY_REPEAT || pad.y == KEY_DOWN) ? KEY_UP : KEY_IDLE;
			
			
			
			buttonL = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_LEFTSTICK) == 1;
			if (buttonL)
				pad.l3 = (pad.l3 == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.l3 = (pad.l3 == KEY_REPEAT || pad.l3 == KEY_DOWN) ? KEY_UP : KEY_IDLE;
			
			buttonR = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK) == 1;
			if (buttonR)
				pad.r3 = (pad.r3 == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.r3 = (pad.r3 == KEY_REPEAT || pad.r3 == KEY_DOWN) ? KEY_UP : KEY_IDLE;
			
			buttonL2 = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == 1;
			if (buttonL2)
				pad.l1 = (pad.l1 == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.l1 = (pad.l1 == KEY_REPEAT || pad.l1 == KEY_DOWN) ? KEY_UP : KEY_IDLE;
			
			buttonR2 = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == 1;
			if (buttonR2)
				pad.r1 = (pad.r1 == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.r1 = (pad.r1 == KEY_REPEAT || pad.r1 == KEY_DOWN) ? KEY_UP : KEY_IDLE;
			
			
			
			*/
			buttonStart = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_START) == 1;
			if (buttonStart)
				pad.start = (pad.start == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.start = (pad.start == KEY_REPEAT || pad.start == KEY_DOWN) ? KEY_UP : KEY_IDLE;

			buttonBack = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_BACK) == 1;
			if (buttonBack)
				pad.back = (pad.back == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.back = (pad.back == KEY_REPEAT || pad.back == KEY_DOWN) ? KEY_UP : KEY_IDLE;

			buttonGuide = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_GUIDE) == 1;
			if (buttonGuide)
				pad.guide = (pad.guide == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.guide = (pad.guide == KEY_REPEAT || pad.guide == KEY_DOWN) ? KEY_UP : KEY_IDLE;

			buttonUp = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1;
			if (buttonUp)
				pad.up = (pad.up == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.up = (pad.up == KEY_REPEAT || pad.up == KEY_DOWN) ? KEY_UP : KEY_IDLE;

			buttonDown = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1;
			if (buttonDown)
				pad.down = (pad.down == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.down = (pad.down == KEY_REPEAT || pad.down == KEY_DOWN) ? KEY_UP : KEY_IDLE;

			buttonLeft = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1;
			if (buttonLeft)
				pad.left = (pad.left == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.left = (pad.left == KEY_REPEAT || pad.left == KEY_DOWN) ? KEY_UP : KEY_IDLE;

			buttonRight = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1;
			if (buttonRight)
				pad.right = (pad.right == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				pad.right = (pad.right == KEY_REPEAT || pad.right == KEY_DOWN) ? KEY_UP : KEY_IDLE;
			
			
				
			pad.a = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_A) == 1;
			pad.b = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_B) == 1;
			pad.x = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_X) == 1;
			pad.y = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_Y) == 1;
			pad.l1 = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == 1;
			pad.r1 = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == 1;
			pad.l3 = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_LEFTSTICK) == 1;
			pad.r3 = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK) == 1;
			/*pad.up = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1;
			pad.down = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1;*/
			

			/*pad.start = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_START) == 1;
			pad.guide = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_GUIDE) == 1;
			pad.back = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_BACK) == 1;*/
			/*pad.left = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1;
			pad.right = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1;*/

			pad.l2 = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT)) / 32767.0f;
			pad.r2 = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT)) / 32767.0f;

			pad.l_x = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_LEFTX)) / 32767.0f;
			pad.l_y = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_LEFTY)) / 32767.0f;
			pad.r_x = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_RIGHTX)) / 32767.0f;
			pad.r_y = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_RIGHTY)) / 32767.0f;

			//constexpr float l_dz = 0.3f;
			//constexpr float r_dz = 0.3f;

			//// Apply deadzone. All values below the deadzone will be discarded
			//pad.l_x = (fabsf(pad.l_x) > pad.l_dz) ? pad.l_x : 0.0f;
			//pad.l_y = (fabsf(pad.l_y) > pad.l_dz) ? pad.l_y : 0.0f;
			//pad.r_x = (fabsf(pad.r_x) > pad.r_dz) ? pad.r_x : 0.0f;
			//pad.r_y = (fabsf(pad.r_y) > pad.r_dz) ? pad.r_y : 0.0f;

			// Define a deadzone threshold 
			constexpr float PadDeadzone = 0.3f;

			// Apply deadzone only to the left joystick 
			pad.l_x = (fabsf(pad.l_x) > PadDeadzone) ? pad.l_x : 0.0f;
			pad.l_y = (fabsf(pad.l_y) > PadDeadzone) ? pad.l_y : 0.0f;
			pad.r_x = (fabsf(pad.r_x) > PadDeadzone) ? pad.r_x : 0.0f;
			pad.r_y = (fabsf(pad.r_y) > PadDeadzone) ? pad.r_y : 0.0f;


			if (pad.rumble_countdown > 0)
				pad.rumble_countdown--;
		}
	}
}

bool ModuleInput::ShakeController(int id, int duration, float strength)
{
	bool ret = false;

	// Check if the given id is valid within the array bounds
	if (id < 0 || id >= MAX_PADS) return ret;

	// Check if the gamepad is active and allows rumble
	GamePad& pad = pads[id];
	if (!pad.enabled || pad.haptic == nullptr || SDL_HapticRumbleSupported(pad.haptic) != SDL_TRUE) return ret;

	// If the pad is already in rumble state and the new strength is below the current value, ignore this call
	if (duration < pad.rumble_countdown && strength < pad.rumble_strength)
		return ret;

	if (SDL_HapticRumbleInit(pad.haptic) == -1)
	{
		LOG("Cannot init rumble for controller number %d", id);
	}
	else
	{
		SDL_HapticRumbleStop(pad.haptic);
		SDL_HapticRumblePlay(pad.haptic, strength, duration / 60 * 1000); //Conversion from frames to ms at 60FPS

		pad.rumble_countdown = duration;
		pad.rumble_strength = strength;

		ret = true;
	}

	return ret;
}

const char* ModuleInput::GetControllerName(int id) const
{
	// Check if the given id has a valid controller
	if (id >= 0 && id < MAX_PADS && pads[id].enabled == true && pads[id].controller != nullptr)
		return SDL_GameControllerName(pads[id].controller);

	return "unplugged";
}