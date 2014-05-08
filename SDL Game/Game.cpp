#include "Game.h"
Game::Game()
{

}
Game::Game(map<string, GameObject*>& Objects)
{
	CurrentLevel = 1;
	string LevelString;
	stringstream LineStream;
	LineStream << "Levels/Level" << CurrentLevel << ".txt";
	LineStream >> LevelString;
	Objects["Level"] = new Map();
	Level = static_cast<Map*>(Objects["Level"]);
	Level->InitializeMap(LevelString.c_str());
	LineStream.str("");
	Objects["Player"] = new Player("Images/ss_character.png", 50, 50, &Level->map);
	OurPlayer = static_cast<Player*>(Objects["Player"]);
	Objects["Background"] = new  Image("Images/ss_bg.png", 0, 0);
	Background = static_cast<Image*>(Objects["Background"]);
	CreateEnemies(Objects);

	BGMusic = Mix_LoadWAV("Music/Level.wav");
	if(BGMusic == NULL) {
		Log(string("Unable to load WAV file, ") + Mix_GetError());
	}
	Channel = Mix_PlayChannel(2, BGMusic, -1);
	if(Channel == -1) {
		Log(string("Unable to play WAV file, ") + Mix_GetError());
	}	
}

Game::~Game()
{
	Mix_Pause(Channel);
	Mix_Pause(Channel2);
	Mix_FreeChunk(BGMusic);
	delete Background;
	delete Level;
	delete OurPlayer;
}
void Game::ScrollBackground(float DeltaTime)
{
	Background->cX -= 150 * DeltaTime;
	if(Background->cX < -1600)
	{
		Background->cX = 0;
	}
}
void Game::Process(map<string, GameObject*>& Objects, float DeltaTime)
{
	ScrollBackground(DeltaTime);
	Level->Update(OurPlayer, DeltaTime);
	if(OurPlayer->Process(DeltaTime))
	{
		if(CurrentLevel != Levels)
		{
			CurrentLevel++;
			delete Level;
			Objects.erase("Level");
			string LevelString;
			stringstream LineStream;
			LineStream << "Levels/Level" << CurrentLevel << ".txt";
			LineStream >> LevelString;
			Objects["Level"] = new Map();
			Level = static_cast<Map*>(Objects["Level"]);
			Level->InitializeMap(LevelString.c_str());
			LineStream.str("");
			CreateEnemies(Objects);

			OurPlayer->cX = 50;
			OurPlayer->cY = 50;
		}else{
			Objects.clear();
			ChangeState(new Menu(Objects));
		}
	}
	ProcessEnemies(DeltaTime);
	if(OurPlayer->Lives < 0)
	{
		for(int i = 0; i < MaxEnemies; i++)
		{
			Baddie[i] = NULL;
		}
		Objects.clear();
		ChangeState(new Gameover(Objects));
	}
}

bool Game::Event(SDL_Event& Event)
{
	if(Event.type == SDL_QUIT)
	{
		return true;
	}
	if(OurPlayer->HandleEvents(Event)){
		return true;
	}
	return false;
}
void Game::CreateEnemies(map<string, GameObject*>& Objects)
{
	for(int i = 0; i < MaxEnemies; i++)
	{
		string BaddieString;
		stringstream LineStream;
		LineStream << "Baddie";
		LineStream << i;
		LineStream >> BaddieString;
		Objects[BaddieString] = new Enemy("Images/ss_enemy.png", 0, 0, &Level->map);
		Baddie[i] = static_cast<Enemy*>(Objects[BaddieString]);
		Baddie[i]->cX = rand() % (Level->map.sX - WIDTH) + WIDTH;
		Baddie[i]->cY = 0;
		LineStream.str("");
	}
}
void Game::ProcessEnemies(float DeltaTime)
{
	for(int i = 0; i < MaxEnemies; i++)
	{
		if(Baddie[i] != NULL) // Collision detection between enemies and players
		{
			Baddie[i]->Process(DeltaTime);
			SDL_Rect EnemyRect;
			EnemyRect.h = Baddie[i]->Surface->h;
			EnemyRect.w = Baddie[i]->Surface->w;
			EnemyRect.x = Baddie[i]->cX  - Level->map.sX;
			EnemyRect.y = Baddie[i]->cY;
			SDL_Rect PlayerRect;
			PlayerRect.h = Player_Height;
			PlayerRect.w = Player_Width;
			PlayerRect.x = OurPlayer->cX  - Level->map.sX;
			PlayerRect.y = OurPlayer->cY;
			int Collide = GameObject::Check_Collision(EnemyRect, PlayerRect);
			if(Collide == COLLISION_LEFT || Collide == COLLISION_RIGHT || Collide == COLLISION_BOTTOM)
			{
				BGMusic = Mix_LoadWAV("Music/MarioDie.wav");
				if(BGMusic == NULL) {
					Log(string("Unable to load WAV file, ") + Mix_GetError());
				}
				Channel2 = Mix_PlayChannel(1, BGMusic, 0);
				if(Channel2 == -1) {
					Log(string("Unable to play WAV file, ") + Mix_GetError());
				}				
				OurPlayer->CurrentState = Dead;
			}else if(Collide == COLLISION_TOP)
			{
				BGMusic = Mix_LoadWAV("Music/Jump.wav");
				if(BGMusic == NULL) {
					Log(string("Unable to load WAV file, ") + Mix_GetError());
				}
				Channel2 = Mix_PlayChannel(1, BGMusic, 0);
				if(Channel2 == -1) {
					Log(string("Unable to play WAV file, ") + Mix_GetError());
				}
 				Baddie[i]->bVisible = false;
				Baddie[i] = NULL;
				OurPlayer->yVel -= 400;
			}
	/*		for(int j = 0; j < MaxEnemies; j++)  // Collision detection between enemies
			{
				if(Baddie[j] != Baddie[i] && Baddie[j] != NULL && Baddie[i] != NULL)
				{
					SDL_Rect EnemyRect2;
					EnemyRect2.h = Baddie[j]->Surface->h;
					EnemyRect2.w = Baddie[j]->Surface->w;
					EnemyRect2.x = Baddie[j]->cX  - Level->map.sX;
					EnemyRect2.y = Baddie[j]->cY;
					int Collide2 = GameObject::Check_Collision(EnemyRect, EnemyRect2);
					if(Collide2 != COLLISION_NONE)
					{
						if(Collide2 == COLLISION_LEFT)
						{
							Baddie[j]->xVel = -200.0f;
							Baddie[i]->xVel = 200.0f;
						//	Baddie[j]->cX = Baddie[i]->cX - Baddie[i]->Surface->w - 1;
						}else if(Collide2 == COLLISION_RIGHT)
						{
							Baddie[j]->xVel = 200.0f;
							Baddie[i]->xVel = -200.0f;
						//	Baddie[j]->cX = Baddie[i]->cX + Baddie[i]->Surface->w + 1;
						}
					}
					//}else if(Collide2 == COLLISION_TOP)
				//	{
			//			Baddie[j]->cX = Baddie[i]->cX - Baddie[j]->Surface->h;
			//		}
				}
			}*/
		}
	}
}