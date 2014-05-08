#include "Player.h"
Player::Player()
{

}
Player::Player(std::string SpriteSheet, int x, int y, Map_Info* CurrentLevel)
{
	cX = x;
	cY = y;
	yVel = xVel = 0.0f;
	Surface = Load_Image(SpriteSheet);
	Accelerate = LeftDown = RightDown = JumpBoost = false;
	InAir = true;
	Level = CurrentLevel;
	CurrentState = Alive;
	Lives = StartingLives;
	// Set our clips
	TextScore = new Font("FahmonNormal.ttf", 24, "Score: ", 50, 50);
	TextScore->cX = WIDTH - TextScore->Surface->w;
	TextCoins = new Font("FahmonNormal.ttf", 24, "Coins: ", 50, 50);
	TextCoins->cX = WIDTH - TextScore->Surface->w - TextCoins->Surface->w;
	TextLives = new Font("FahmonNormal.ttf", 24, "Lives: ", 50, 50);
	TextLives->cX = 10;
	for(int i = 0; i <= 3; i++)
	{
		ClipsWalkingRight[i].x = Player_Width + Player_Width * i;
		ClipsWalkingRight[i].y = 0;
		ClipsWalkingRight[i].w = Player_Width;
		ClipsWalkingRight[i].h = Player_Height;
	}
	for(int i = 0; i <= 3; i++)
	{
		ClipsWalkingLeft[i].x = Player_Width + Player_Width * i;
		ClipsWalkingLeft[i].y = Player_Height;
		ClipsWalkingLeft[i].w = Player_Width;
		ClipsWalkingLeft[i].h = Player_Height;
	}
	
	ClipsStandingLeft.h = Player_Height;
	ClipsStandingLeft.w = Player_Width;
	ClipsStandingLeft.x = 0;
	ClipsStandingLeft.y = Player_Height;

	ClipsStandingRight.h = Player_Height;
	ClipsStandingRight.w  = Player_Width;
	ClipsStandingRight.x = 0;
	ClipsStandingRight.y = 0;

	ClipsJumpingLeft.h = Player_Height;
	ClipsJumpingLeft.w = Player_Width;
	ClipsJumpingLeft.x = Player_Width * 5;
	ClipsJumpingLeft.y = Player_Height;

	ClipsJumpingRight.h = Player_Height;
	ClipsJumpingRight.w = Player_Width;
	ClipsJumpingRight.x = Player_Width * 5;
	ClipsJumpingRight.y = 0;

	ClipsCrouchingLeft.h = Player_Height;
	ClipsCrouchingLeft.w = Player_Width;
	ClipsCrouchingLeft.x = Player_Width * 6;
	ClipsCrouchingLeft.y = Player_Height;

	ClipsCrouchingRight.h = Player_Height;
	ClipsCrouchingRight.w = Player_Width;
	ClipsCrouchingRight.x = Player_Width * 6;
	ClipsCrouchingRight.y = 0;

	Status = PLAYER_STANDRIGHT;
	Crouch = false;
	Direction = true;
	Frame = 0;
	Coins = 0;
	Score = 0;
} // Initializes player
Player::~Player()
{
	SDL_FreeSurface(Surface);
	delete TextScore;
	delete TextCoins;
	delete TextLives;

} // Deinitialize player
void Player::Render(SDL_Surface* Screen)
{
	if(Frame > 2){
		Frame = 0;
	}
	if(Status == PLAYER_RIGHT)
	{
		Apply_Surface(cX - Level->sX, cY, Surface, Screen, &ClipsWalkingRight[Frame]);
	}else if(Status == PLAYER_LEFT)
	{
		Apply_Surface(cX - Level->sX, cY, Surface, Screen, &ClipsWalkingLeft[Frame]);
	}else if(Status == PLAYER_STANDLEFT)
	{
		Apply_Surface(cX - Level->sX, cY, Surface, Screen, &ClipsStandingLeft);
	}else if(Status == PLAYER_STANDRIGHT)
	{
		Apply_Surface(cX - Level->sX, cY, Surface, Screen, &ClipsStandingRight);
	}else if(Status == PLAYER_JUMPLEFT)
	{
		Apply_Surface(cX - Level->sX, cY, Surface, Screen, &ClipsJumpingLeft);
	}else if(Status == PLAYER_JUMPRIGHT)
	{
		Apply_Surface(cX - Level->sX, cY, Surface, Screen, &ClipsJumpingRight);
	}else if(Status == PLAYER_CROUCHRIGHT)
	{
		Apply_Surface(cX - Level->sX, cY, Surface, Screen, &ClipsCrouchingRight);
	}else if(Status == PLAYER_CROUCHLEFT)
	{
		Apply_Surface(cX - Level->sX, cY, Surface, Screen, &ClipsCrouchingLeft);
	}

	TextScore->cX = WIDTH - TextScore->Surface->w - 5;
	TextCoins->cX = WIDTH - TextScore->Surface->w - TextCoins->Surface->w - 50;

	std::string sScore, sCoins, sLives;
	std::stringstream LineStream;

	LineStream << "Score: " << Score;
	sScore = LineStream.str();
	LineStream.str("");
	LineStream << "Coins: " << Coins;
	sCoins = LineStream.str();
	LineStream.str("");
	LineStream << "Lives: " << Lives;
	sLives = LineStream.str();
	LineStream.str("");

	TextScore->sText = sScore;
	TextCoins->sText = sCoins;
	TextLives->sText = sLives;

	TextScore->Render(Screen);
	TextCoins->Render(Screen);
	TextLives->Render(Screen);
} // Renders player to screen
void Player::UpdatePosition(float DeltaTime)
{
	cX += int(xVel * DeltaTime);
	cY += int(yVel * DeltaTime);

    if(cX < 0)
    {
        cX = 0;
    }
    else if(cX + Player_Width >= Level->maxX)
    {
        cX = Level->maxX - Player_Width - 1;
    }
	if(cY < 0)
	{
		cY = 0;
	}
	if(cY > 800 + Player_Height) // Go under and die :o
	{
		CurrentState = Dead;
	}
} // Update position of player
void Player::ManageAnimation(float DeltaTime)
{	
	if(xVel < 0)
	{
		Status = PLAYER_LEFT;
	}
	if(xVel > 0)
	{
		Status = PLAYER_RIGHT;
	}
	if(xVel == 0)
	{
		if(Direction == true)
		{
			Status = PLAYER_STANDRIGHT;
		}else{
			Status = PLAYER_STANDLEFT;
		}
	}

	if(InAir && xVel > 0)
	{
		Status = PLAYER_JUMPRIGHT;
	}else if(InAir && xVel < 0)
	{
		Status = PLAYER_JUMPLEFT;
	}else if(InAir && xVel == 0)
	{
		if(Direction == true)
		{
			Status = PLAYER_JUMPRIGHT;
		}else{
			Status = PLAYER_JUMPLEFT;
		}
	}

	if(Crouch && Direction)
	{
		Status = PLAYER_CROUCHRIGHT;
	}else if(Crouch && !Direction)
	{
		Status = PLAYER_CROUCHLEFT;
	}
	
	Frame += 65 * DeltaTime;
} // Manages the images of the player
bool Player::CheckCollisions(float DeltaTime)
{
	int i = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	InAir = true;
	i = (Player_Height > Tile_Height) ? Tile_Height : Player_Height;

	// Checking Horizantal Movement First!
	for(;;)
	{
		x1 = int((cX + (xVel * DeltaTime)) / Tile_Width); // Left Side
		x2 = int((cX + (xVel * DeltaTime) + Player_Width - 1) / Tile_Width); // Right Side

		y1 = cY / Tile_Height; // Top
		y2 = (cY + i - 1) / Tile_Height; // Bottom
		if(x1 >= 0 && x2 < Level->maxX && y1 >= 0 && y2 < Level->maxY) // If we are in the bounds of the map
		{
			if(xVel > 0)	// We are moving right ->
			{
				if((Level->Tile[x2][y1] != TILE_TYPE_EMPTY) || (Level->Tile[x2][y2] != TILE_TYPE_EMPTY)) // If we run into a block
				{
					cX = x2 * Tile_Width;
					cX -= Player_Width + 1;
					
				}
				if(Level->Tile[x2][y1] == TILE_TYPE_FLAG) // Win
				{
					BGMusic = Mix_LoadWAV("Music/LevelClear.wav");
					if(BGMusic == NULL) {
						Log(string("Unable to load WAV file, ") + Mix_GetError());
					}
					Channel = Mix_PlayChannel(1, BGMusic, 0);
					if(Channel == -1) {
						Log(string("Unable to play WAV file, ") + Mix_GetError());
					}
					return true;
				}
				if(Level->Tile[x2][y2] == TILE_TYPE_FLAG)
				{
					BGMusic = Mix_LoadWAV("Music/LevelClear.wav");
					if(BGMusic == NULL) {
						Log(string("Unable to load WAV file, ") + Mix_GetError());
					}
					Channel = Mix_PlayChannel(1, BGMusic, 0);
					if(Channel == -1) {
						Log(string("Unable to play WAV file, ") + Mix_GetError());
					}
					return true;
				}
			}
			else if(xVel < 0)  // We are moving left <---
			{
				if((Level->Tile[x1][y1] != TILE_TYPE_EMPTY) || (Level->Tile[x1][y2] != TILE_TYPE_EMPTY))
				{
					cX = (x1 + 1) * Tile_Width;
					
				}
			}
		}

		if(i == Player_Height)
		{
			break;
		}
		
		i += Tile_Height;

		if(i > Player_Height)
		{
			i = Player_Height;
		}
	}
	// Testing Vertical Movement

	i = (Player_Width > Tile_Width) ? Tile_Width : Player_Width;

	for(;;)
	{
		x1 = cX / Tile_Width;
		x2 = (cX + i) / Tile_Width;

		y1 = int((cY + (yVel * DeltaTime)) / Tile_Height);
		y2 = int((cY + (yVel * DeltaTime) + Player_Height) / Tile_Height);

		if(x1 >= 0 && x2 < Level->maxX && y1 >= 0 && y2 < Level->maxY)
		{
			if(yVel > 0) // We are going down
			{
				if((Level->Tile[x1][y2] != TILE_TYPE_EMPTY) || (Level->Tile[x2][y2] != TILE_TYPE_EMPTY))
				{
					InAir = false;
					cY = y2 * Tile_Height;
					cY -= Player_Height;
					yVel = 0.0f;
				}
			}
			else if(yVel < 0) // We are going up
			{
				if((Level->Tile[x1][y1] != TILE_TYPE_EMPTY) || (Level->Tile[x2][y1] != TILE_TYPE_EMPTY))
				{
					cY = (y1 + 1) * Tile_Height;
					yVel = 0.0f;
					JumpBoost = false;
				}
				if(Level->Tile[x1][y1] == TILE_TYPE_BRICK)
				{
					BGMusic = Mix_LoadWAV("Music/BreakBlock.wav");
					if(BGMusic == NULL) {
						Log(string("Unable to load WAV file, ") + Mix_GetError());
					}
					Channel = Mix_PlayChannel(1, BGMusic, 0);
					if(Channel == -1) {
						Log(string("Unable to play WAV file, ") + Mix_GetError());
					}
					Score += 50;
					Level->Tile[x1][y1] = 0;
					JumpBoost = false;
					// Play brick crush noise
					// particle brick?
				}
				if(Level->Tile[x2][y1] == TILE_TYPE_BRICK)
				{
					BGMusic = Mix_LoadWAV("Music/BreakBlock.wav");
					if(BGMusic == NULL) {
						Log(string("Unable to load WAV file, ") + Mix_GetError());
					}
					Channel = Mix_PlayChannel(1, BGMusic, 0);
					if(Channel == -1) {
						Log(string("Unable to play WAV file, ") + Mix_GetError());
					}
					Score += 50;
					Level->Tile[x2][y1] = 0;
					JumpBoost = false;
				}
				if(Level->Tile[x1][y1] == TILE_TYPE_BRICKBLOCK)
				{
					BGMusic = Mix_LoadWAV("Music/Coin.wav");
					if(BGMusic == NULL) {
						Log(string("Unable to load WAV file, ") + Mix_GetError());
					}
					Channel = Mix_PlayChannel(1, BGMusic, 0);
					if(Channel == -1) {
						Log(string("Unable to play WAV file, ") + Mix_GetError());
					}
					Score += 100;
					Coins += 1;
					Level->Tile[x1][y1] = TILE_TYPE_EMPTYBLOCK;
					JumpBoost = false;
				}
				if(Level->Tile[x2][y1] == TILE_TYPE_BRICKBLOCK)
				{
					BGMusic = Mix_LoadWAV("Music/Coin.wav");
					if(BGMusic == NULL) {
						Log(string("Unable to load WAV file, ") + Mix_GetError());
					}
					Channel = Mix_PlayChannel(1, BGMusic, 0);
					if(Channel == -1) {
						Log(string("Unable to play WAV file, ") + Mix_GetError());
					}
					Score += 100;
					Coins += 1;
					Level->Tile[x2][y1] = TILE_TYPE_EMPTYBLOCK;
					JumpBoost = false;
				}
				if(Level->Tile[x1][y1] == TILE_TYPE_BLOCK)
				{
					BGMusic = Mix_LoadWAV("Music/Coin.wav");
					if(BGMusic == NULL) {
						Log(string("Unable to load WAV file, ") + Mix_GetError());
					}
					Channel = Mix_PlayChannel(1, BGMusic, 0);
					if(Channel == -1) {
						Log(string("Unable to play WAV file, ") + Mix_GetError());
					}
					Score += 125;
					Coins += 1;
					Level->Tile[x1][y1] = TILE_TYPE_EMPTYBLOCK;
					JumpBoost = false;
				}
				if(Level->Tile[x2][y1] == TILE_TYPE_BLOCK)
				{
					BGMusic = Mix_LoadWAV("Music/Coin.wav");
					if(BGMusic == NULL) {
						Log(string("Unable to load WAV file, ") + Mix_GetError());
					}
					Channel = Mix_PlayChannel(1, BGMusic, 0);
					if(Channel == -1) {
						Log(string("Unable to play WAV file, ") + Mix_GetError());
					}			
					Score += 125;
					Coins += 1;
					Level->Tile[x2][y1] = TILE_TYPE_EMPTYBLOCK;
					JumpBoost = false;
				}
			}
		}
		
		if((Level->Tile[x1][y2] != TILE_TYPE_EMPTY) || (Level->Tile[x2][y2] != TILE_TYPE_EMPTY))
		{
			InAir = false;
		}

		if(i == Player_Width)
		{
			break;
		}
		i += Tile_Height;

		if(i > Player_Width)
		{
			i = Player_Width;
		}
	}
	return false;

} // Checks collisions of player to the map
void Player::UpdateVelocity(float DeltaTime)
{
	int GravityInfluence = int(GravityMultiplier * (9.81));
	if(Accelerate && xVel != 0 && !InAir)
	{
		xVel += (xVel < 0) ? (-1 * (RunSpeed)) : (RunSpeed);
	}
	// Jumping
	if(yVel > -(MaxJumpVel) && JumpBoost)
	{
		yVel -= JumpSpeed;
	}else{
		JumpBoost = false;
	}

	if(yVel > MaxFallSpeed)
	{
		yVel = MaxFallSpeed;
	}
	if(InAir)
	{
		yVel += GravityInfluence;
	}
	if(xVel > MaxRunSpeed)
	{
		xVel = MaxRunSpeed;
	}else if(xVel < -MaxRunSpeed)
	{
		xVel = -MaxRunSpeed;
	}
} // Updates the velocities
bool Player::Process(float DeltaTime)
{
	ManageAnimation(DeltaTime);
	if(CheckCollisions(DeltaTime))
	{
		return true;
	}
	UpdateVelocity(DeltaTime);
	UpdatePosition(DeltaTime);
	if(CurrentState == Dead)
	{
		Lives -= 1;
		// Play die sound
		cX = 50;
		cY = 50;
		if(Lives < 0)
		{
			Lives = -1;
			//change state gameover which goes to menu
			return true;
		}
		CurrentState = Alive;
		//Remove Powerups
	}
	if(Coins >= 100)
	{
		Lives += 1;
		Coins = 0;
	}

	return false;
} // Processes the player
bool Player::HandleEvents(SDL_Event& Event)
{
	while(SDL_PollEvent(&Event)){
		switch(Event.type)
		{
		case SDL_KEYDOWN:
			switch(Event.key.keysym.sym){
				case SDLK_DOWN:
					Crouch = true;
					//Crouch animation
				break;
				case SDLK_UP:
					if(!InAir)
					{
					BGMusic = Mix_LoadWAV("Music/Jump.wav");
					if(BGMusic == NULL) {
						Log(string("Unable to load WAV file, ") + Mix_GetError());
					}
					Channel = Mix_PlayChannel(1, BGMusic, 0);
					if(Channel == -1) {
						Log(string("Unable to play WAV file, ") + Mix_GetError());
					}
						JumpBoost = true;
						yVel -= JumpForce;
					}
				break;
				case SDLK_LEFT:
					LeftDown = true;
					if(!RightDown && !Crouch)
					{
						xVel = -RunSpeed;
					}
				break;
				case SDLK_RIGHT:
					RightDown = true;
					if(!LeftDown && !Crouch)
					{
						xVel = RunSpeed;
					}
				break;
				case SDLK_a:
					Accelerate = true;
				break;
				default:
				break;
			}
		break;

		case SDL_KEYUP:
			switch(Event.key.keysym.sym)
			{
				case SDLK_DOWN:
					Crouch = false;
				break;
				case SDLK_UP:
					JumpBoost = false;
				break;
				case SDLK_LEFT:
					LeftDown = false;
					Direction = false;
					if(!RightDown)
					{
						xVel = 0.0f;
					}else{
						xVel = 500.0f;
					}
				break;
				case SDLK_RIGHT:
					RightDown = false;
					Direction = true;
					if(!LeftDown)
					{
						xVel = 0.0f;
					}else{
						xVel = -500.0f;
					}
				break;
				case SDLK_a:
					Accelerate = false;
				break;
				default:
				break;
			}
		break;

		case SDL_QUIT:
			return true;
		break;
		
		default:
		break;
		}
	}
	return false;
} // Handles any events such as keyboard input