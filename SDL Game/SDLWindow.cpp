#include "SDLWindow.h"
#include "Font.h"
extern State* CurrentState;
SDLWindow::SDLWindow()
{	// Clear log file
	ofstream filelog;
	filelog.open(LOG_FILE, ios::trunc);
	filelog << "";
	filelog.close();
	GameObjects.clear();
	GameTimer.start();
	Update.start();
	PreviousTime = GameTimer.get_ticks();
	Frames = 0;
	UpdateTime = false;
	// Clear game objects and what not

}
SDLWindow::~SDLWindow()
{
	GameObjects.clear();
	delete FrameRate;
	Shutdown();
}
bool SDLWindow::Tick(map<string, GameObject*>& GameObjects)
{
	SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(Screen->format, 0x00, 0x00, 0x00));

	Uint8 state = SDL_GetAppState();
	if(!(state & SDL_APPINPUTFOCUS) || (!state)){
		GameTimer.pause();
		SDL_Delay(500);
	}else{
		SDL_Delay(0);
		GameTimer.unpause();
	}
	float Ticks = GameTimer.get_ticks();
	float DeltaTime = ((Ticks - PreviousTime) / 1000);
	if(CurrentState != NULL)
	{
		if(CurrentState->Event(SDLEvent))
		{		
			return true;
		}
	}
	if(CurrentState != NULL && !GameTimer.is_paused() && GameTimer.is_started() && DeltaTime > 0.01f)
	{
		if(DeltaTime > 1.0f)
		{
			DeltaTime = 1.0f;
		}
		CurrentState->Process(GameObjects, DeltaTime);
		UpdateTime = true;
	}else{
		UpdateTime = false;
	}

	std::map<std::string, GameObject*>::iterator itr;

	for(itr = GameObjects.begin(); itr != GameObjects.end(); itr++)
	{
		GameObject* Object = itr->second;
		if(Object->isVisible() && Object != NULL)
		{	
			Object->Render(Screen);
		}
	}

	Frames++;
	if(Update.get_ticks() > 1000)
	{
		stringstream FrameString;
		int GameTicks = int(GameTimer.get_ticks());
		int FramesPerSecond = int(Frames / (GameTicks / 1000));
		FrameString << "FPS: " << FramesPerSecond;
		FrameRate->sText = FrameString.str();
		FrameString.str("");
		Update.start();
	}
	FrameRate->Render(Screen);

	if(SDL_Flip(Screen) == -1)
	{
		Log(std::string("Screen failed to flip, ") + SDL_GetError());
		return true;
	}
	if(UpdateTime == true)
	{
		PreviousTime = GameTimer.get_ticks();
	}
	return false;
}
bool SDLWindow::Create(int Width, int Height, int Bpp, Uint32 Flags, int InitFlags)
{
	string sWidth = "", sHeight = "", sBpp = "";
	Log("Initializing...");
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Log(string("SDL_Init() failed to initialize SDL, ") + SDL_GetError());
		return false;
	}
	Uint32 bpp;
	
	ostringstream message;
	message << Height;	sHeight = message.str(); message.str(string());
	message << Width; sWidth = message.str(); message.str(string());
	message << Bpp; sBpp = message.str(); message.str(string());

	Log(string("Checking mode ") + sWidth + string("x") + sHeight + string("@") + sBpp);
	bpp = SDL_VideoModeOK(Width, Height, Bpp, Flags);
	if(!bpp)
	{
		message << bpp; sBpp = message.str(); message.str(string());
		Log("Mode not avaliable!");
		Log(string("SDL recommends ") + sWidth + string("x") + sHeight + string("@") + sBpp);
		Screen = SDL_SetVideoMode(Width, Height, bpp, Flags);
	}else{
		Screen = SDL_SetVideoMode(Width, Height, Bpp, Flags);
	}
	if(Screen == NULL)
	{
		Log(string("Could not create SDL screen, ") + SDL_GetError());
		return false;
	}
	Log("SDL screen created successfully");
	if(InitFlags & FIMAGE_INIT)
	{
		int nImageFlags = IMG_INIT_JPG | IMG_INIT_PNG;
		int nInit = IMG_Init(nImageFlags);
		if((nInit & nImageFlags) != nImageFlags)
		{
			Log(string("IMG_Init failed to initialize JPG and PNG support, ") + IMG_GetError());
			return false;
		}
		Log("IMG_Init successfully initialized");
	}
	if(InitFlags & FTTF_INIT)
	{
		if(TTF_Init() == -1)
		{
			Log(string("SDL_ttf failed to initialization of True Type Font support, ") + TTF_GetError());
			return false;
		}
		Log("SDL_ttf True Type Font support initialized");
	}
	if(InitFlags & FMIXER_INIT)
	{
		int audio_rate = 22050;
		Uint16 audio_format = AUDIO_S16SYS;
		int audio_channels = 2;
		int audio_buffers = 4096;
		 
		if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
			Log(string("Unable to initialize audio, ") + Mix_GetError());
			return false;
		}
		Log("SDL_Mixer audio initialized");
	}
	SDL_WM_SetCaption(GAME_NAME, NULL);
	FrameRate = new Font("FahmonNormal.ttf", 36, "Initializing...", 15, 15);
	FrameRate->cX = (Screen->w / 2) - (FrameRate->Surface->w / 2);
	Log("Initialized successfully");
	SDL_ShowCursor(SDL_DISABLE);
	return true;
}

void SDLWindow::Shutdown()
{
	StopSDL();
}

void SDLWindow::StopSDL()
{
	SDL_FreeSurface(Screen);
	
	GameObjects.clear();
	FrameRate = NULL;
	Frames = NULL;
	PreviousTime = NULL;
	if(TTF_WasInit())
		TTF_Quit();

	while(Mix_Init(0))
		Mix_Quit();
	
	SDL_Quit();
}