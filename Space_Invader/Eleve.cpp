#pragma warning( disable : 4996 ) 

 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "G2D.h"

using namespace std;

// differents ecrans 
enum ecran { ECRAN_ACCEUIL, ECRAN_JEU, ECRAN_GAME_OVER, ECRAN_VICTOIRE,ECRAN_OPTIONS };


struct Bullet
{
	V2 Pos;
	string texture =
		"[G]";

};
struct SpaceShip
{
string texture =
		"[       WWW       ]"
		"[       WOW       ]"
		"[       WOW       ]"
		"[       WOW       ]"
		"[      WWOWW      ]"
		"[      WOOOW      ]"
		"[   WWWWOOOWWWW   ]"
		"[   WRWWOOOWWRW   ]"
		"[   WRWWOOOWWRW   ]"
		"[WWWWOWOOOOOWOWWWW]"
		"[WRWWOBOOROOBOWWRW]"
		"[WRWWBOORRROOBWWRW]"
		"[WOWWOOOROROOOWWOW]"
		"[WOWOOOOOOOOOOOWOW]"
		"[WOOOOOROOOROOOOOW]"
		"[WOOWWRRWOWRRWWOOW]"
  	    "[WOOWWRRWOWRRWWOOW]"
		"[WOWWWWWWOWWWWWWOW]"
		"[WWW    WWW    WWW]";
	V2 Size;
	int IdTex;
	V2 Pos = V2(150, 50);
	vector <Bullet> balls = {};
	bool canShoot = false;
};

struct Alien
{
string texture =

		"[  G     G  ]"
		"[   G   G   ]"
		"[  GGGGGGG  ]"
		"[ GG GGG GG ]"
		"[GGGGGGGGGGG]"
  	    "[G GGGGGGG G]"
		"[G G     G G]"
		"[   GG GG   ]";
	V2 Size;
	int IdTex;
	V2 Pos = V2(240, 250);
	bool deplacementDroite = true;

};
struct Shield {
	string texture = 
		"[ GGGGGGGGG ]"
		"[ GGG   GGG ]"
		"[GGGG   GGGG]"
		"[GGG     GGG]"
		"[GGGG   GGGG]"
		"[GGGG   GGGG]";
	string texture2 =
		"[ RRRRRRRRR ]"
		"[ RRR   RRR ]"
		"[RRRR   RRRR]"
		"[RRR     RRR]"
		"[RRRR   RRRR]"
		"[RRRR   RRRR]";
	string texture3 =
		"[ BBBBBBBBB ]"
		"[ BBB   BBB ]"
		"[BBBB   BBBB]"
		"[BBB     BBB]"
		"[BBBB   BBBB]"
		"[BBBB   BBBB]";
	int ShieldLife = 3;
	V2 Size;
	int IdTex;
	int IdTex2;
	int IdTex3;
	V2 Pos = V2(150, 100);
};
struct GameData
{
	int HeighPix = 800;   // hauteur de la fenêtre d'application
	int WidthPix = 600;   // largeur de la fenêtre d'application
	int Life = 3;
	int idFrame = 0;
	int score = 0;
	double speed_level = 0.5;
	double speed_level_init = 0.5;

	bool redraw = true;

	SpaceShip spaceShip;

	ecran SCREEN = ECRAN_ACCEUIL;

	V2 CurrentSpaceShipPos = spaceShip.Pos;

	vector <Alien> Aliens;
	vector <Bullet> Aliensballs = {};
	vector <Shield> Shields = {};
	
		 
};

// Initialise les elements de base du jeu 
void InitGame(GameData & G) // permet d'initialiser ou re initialliser les parametres de bases du jeu 
{

	int placement = 0;
	int hauteur = 500;
	int placementShield = 30;
	
	G.spaceShip.Pos= V2(150, 50);
	G.score = 0;
	G.Life = 3;

	
	if (G.redraw)
	{
		G.speed_level = G.speed_level_init;
		for (int i = 0; i < 4; i++)
		{
			Shield s;
			s.Pos.x = placementShield;
			s.Pos.y = 150;
			G.Shields.push_back(s);
			placementShield += 150;
		}

		while (placement < 600 && hauteur >= 400)
		{

			Alien ali;
			ali.Pos.y = hauteur;

			ali.Pos.x = placement;

			G.Aliens.push_back(ali);
			placement += 50;
			if (placement > 590)
			{
				hauteur -= 40;
				placement = 0;
			}

		}
		G.redraw = false;
		for (int i = 0; i < G.Shields.size(); i++)
		{
			G.Shields[i].ShieldLife = 3;
		}
	}
	else
		G.redraw = false;
}


//fonction de rendu - reçoit en paramètre les données du jeu par référence
void Render(const GameData& G)
{
	// Switch case pour savoir quoi affichier en fonction de l'écran
	switch (G.SCREEN) {

	case ECRAN_ACCEUIL:
		G2D::clearScreen(Color::Black);
		G2D::drawStringFontRoman(V2(120, 500), "SPACE INVADERS", 50, 3, Color::White);
		G2D::drawStringFontRoman(V2(120, 400), "Appuyez sur ESPACE pour commencer", 20, 1.5f, Color::White);
		G2D::drawStringFontRoman(V2(200, 50), "Appuyez sur O pour acceder aux Options", 20, 1.5f, Color::White);
		G2D::Show();
		break;

	case ECRAN_JEU:
		G2D::clearScreen(Color::Black);

		// le vaisseau
		G2D::drawRectWithTexture(G.spaceShip.IdTex, G.spaceShip.Pos, G.spaceShip.Size);

		// les aliens
		for (int i = 0; i < G.Aliens.size(); i++) {
			G2D::drawRectWithTexture(G.Aliens[i].IdTex, G.Aliens[i].Pos, G.Aliens[i].Size);
		}

		// les balles vaisseau
		for (int i = 0; i < G.spaceShip.balls.size(); i++) 
			G2D::drawCircle(G.spaceShip.balls[i].Pos, 10, Color::Green, true);
		
		// les ballles aliens
		for (int i = 0; i < G.Aliensballs.size(); i++)
			G2D::drawCircle(G.Aliensballs[i].Pos, 10, Color::Green, true);
			
		// Dessiner les Shields
		for (int i =0; i<G.Shields.size();i++)
		{
			if(G.Shields[i].ShieldLife==3)
				G2D::drawRectWithTexture(G.Shields[i].IdTex, G.Shields[i].Pos, G.Shields[i].Size);
			if(G.Shields[i].ShieldLife==2)
				G2D::drawRectWithTexture(G.Shields[i].IdTex2, G.Shields[i].Pos, G.Shields[i].Size);
			if(G.Shields[i].ShieldLife==1)
				G2D::drawRectWithTexture(G.Shields[i].IdTex3, G.Shields[i].Pos, G.Shields[i].Size);
		}

		G2D::drawStringFontRoman(V2(10, 10), "Score: " + to_string(G.score), 20, 2, Color::White);
		G2D::drawStringFontRoman(V2(G.WidthPix - 120, 10), "Lifes: " + to_string(G.Life), 20, 2, Color::White);
		G2D::Show();
		break;
		
	case ECRAN_GAME_OVER:
		G2D::clearScreen(Color::Black);
		G2D::drawStringFontRoman(V2(120, 600), "SPACE INVADERS", 50, 3, Color::White);
		G2D::drawStringFontRoman(V2(150,500), "Game Over", 60, 5, Color::Red);
		G2D::drawStringFontRoman(V2(150,400), "Score final: " + to_string(G.score), 60, 3, Color::White);
		G2D::drawStringFontRoman(V2(150, 300), "Press R to restart ", 40, 3, Color::White);
		G2D::Show();
		break;

	case ECRAN_VICTOIRE:
		G2D::clearScreen(Color::Black);
		G2D::drawStringFontRoman(V2(120, 700), "SPACE INVADERS", 50, 3, Color::White);
		G2D::drawStringFontRoman(V2(150, 400), "You won GG !", 50, 1.0, Color::White);
		G2D::drawStringFontRoman(V2(150, 600), "VICTOIRY !", 50, 2, Color::White);
		G2D::drawStringFontRoman(V2(150, 500), "Score final: " + to_string(G.score), 60, 3, Color::White);
		G2D::drawStringFontRoman(V2(150, 300), "Press R to restart ", 50, 3, Color::White);
		G2D::Show();
		break;

	case ECRAN_OPTIONS:
		G2D::clearScreen(Color::Black);
		G2D::drawStringFontRoman(V2(120, 500), "SPACE INVADERS", 50, 3, Color::White);
		G2D::drawStringFontRoman(V2(150, 300), "Choose the difficulty:", 20, 1.5, Color::White);
		G2D::drawStringFontRoman(V2(200, 350), "Press A. Easy", 20, 1.5, Color::White);
		G2D::drawStringFontRoman(V2(200, 400), "Press B. Normal", 20, 1.5, Color::White);
		G2D::drawStringFontRoman(V2(200, 450), "Press C. Hard", 20, 1.5, Color::White);
		G2D::drawStringFontRoman(V2(450, 750), "Back (F2)", 30, 3, Color::White);
		G2D::Show();
		break;

	default:
		G2D::Show();
		break;
	}
}



// pour les collisions
bool Proximite(int x1, int y1, int x2, int y2, int distmin) 
{
	return pow(x1 - x2, 2) + pow(y1 - y2, 2) < distmin * distmin;
}


// collisions Vaisseau et Alien
void CollisionSpaceShipAlien(GameData & G ) 
{
	for (int i = 0; i < G.Aliens.size(); i++)
	{
		if (Proximite(G.spaceShip.Pos.x, G.spaceShip.Pos.y, G.Aliens[i].Pos.x, G.Aliens[i].Pos.y, 40))
		{
			G.Life--;
			G.spaceShip.Pos =V2 (250, 150);
		}
	
	}
	
}

// deplacement du vaisseau
void DeplacementSpaceShip(GameData& G) 
{
	if (G2D::isKeyPressed(Key::RIGHT))
	{

		G.spaceShip.Pos.x++;
	}
	if (G2D::isKeyPressed(Key::LEFT))
	{
		G.spaceShip.Pos.x--;
	}

	if (G.spaceShip.Pos.x > 550 || G.spaceShip.Pos.x <2)
		G.spaceShip.Pos = G.CurrentSpaceShipPos;
	
}
// Tirs du vaisseau
void SpaceShoot(GameData& G) 
{
	if ((G2D::isKeyPressed(Key::SPACE)) && (G.spaceShip.canShoot))
	{
		Bullet b;
		b.Pos.y = G.spaceShip.Pos.y + 70;
		b.Pos.x = G.spaceShip.Pos.x + 30;
		G.spaceShip.balls.push_back(b);
		
	}
	G.spaceShip.canShoot = !G2D::isKeyPressed(Key::SPACE);

}
// Tirs aléatoires des aliens
void AlienShoot(GameData& G)  
{
	
	for (int i = 0; i < G.Aliens.size(); i++)
	{
		if (rand() % 2000 == 0)
		{
			Bullet b;
			b.Pos.y = G.Aliens[i].Pos.y;
			b.Pos.x = G.Aliens[i].Pos.x;
			G.Aliensballs.push_back(b);
		}
	}
}

//suppressions des balles une fois hors champs afin d'éviter de flood la mémoire
void delBullet(GameData& G) 
{
	for (int i = 0; i < G.spaceShip.balls.size(); )
	{
		if (G.spaceShip.balls[i].Pos.y > 800 || G.spaceShip.balls[i].Pos.y < 0 || G.spaceShip.balls[i].Pos.x > 600 || G.spaceShip.balls[i].Pos.x < 0)
		{
			G.spaceShip.balls.erase(G.spaceShip.balls.begin() + i);
			i++;
		}
		i++;
	}

	for (int i = 0; i < G.Aliensballs.size(); )
	{
		if (G.Aliensballs[i].Pos.y > 790 || G.Aliensballs[i].Pos.y < 5 || G.Aliensballs[i].Pos.x > 590 || G.Aliensballs[i].Pos.x < 10)
		{
			G.Aliensballs.erase(G.Aliensballs.begin() + i);
			i++;
		}
		i++;
	}
}

// deplacement des balles
void BallMove(GameData& G) 
{
	
	for (int i = 0; i<G.spaceShip.balls.size(); i++)
	{
		G.spaceShip.balls[i].Pos.y += 1;
	}
	for (int i = 0; i < G.Aliensballs.size(); i++)
	{
		G.Aliensballs[i].Pos.y -= 1;
	}
	
}

// repositionnement des aliens 
void ReplaceAliens(GameData& G)
{
	int t = G2D::elapsedTimeFromStartSeconds();

	for (int i = 0; i < G.Aliens.size(); i++)
	{

		G.Aliens[i].Pos.x += G.speed_level;
		if (G.Aliens[i].Pos.x > 550)
		{
			G.Aliens[i].Pos.y -= 110;
			G.Aliens[i].Pos.x = 0;
		}

		if (G.Aliens[i].Pos.y < 160)
		{
			G.Aliens[i].Pos.y = 500;
		}

	}
}

// differentes collisions entre les balles et les objets du jeu 
void CollisionsAvecBalles(GameData& G)
{
	for (int i = 0; i < G.Aliens.size(); i++) // collision entre la balle du vaisseau et des aliens
	{
		for (int j = 0; j < G.spaceShip.balls.size(); j++)
		{
			if (Proximite(G.spaceShip.balls[j].Pos.x, G.spaceShip.balls[j].Pos.y, G.Aliens[i].Pos.x, G.Aliens[i].Pos.y, 30))
			{
				G.spaceShip.balls.erase(G.spaceShip.balls.begin() + j);
				G.Aliens.erase(G.Aliens.begin() + i);
				G.score += 1;
				
				if (G.Aliens.size() <= 24)
					G.speed_level += 0.2;
				if (G.Aliens.size() <= 12)
					G.speed_level += 0.2;
				i--;
				break; 
			}
		}
	}
	for (int i = 0; i < G.Aliensballs.size(); i++) // collision entre les balles des aliens et du vaisseau
	{
		if (Proximite(G.Aliensballs[i].Pos.x, G.Aliensballs[i].Pos.y, G.spaceShip.Pos.x, G.spaceShip.Pos.y, 40))
		{
			G.Aliensballs.erase(G.Aliensballs.begin() + i);
			G.Life--;
			break;
		}
	}

	for (int i = 0; i < G.Aliensballs.size(); i++) // Collisions entre la balle du vaisseau et ceux des aliens
	{
		for (int j = 0; j < G.spaceShip.balls.size(); j++)
		{
			if (Proximite(G.spaceShip.balls[j].Pos.x, G.spaceShip.balls[j].Pos.y, G.Aliensballs[i].Pos.x, G.Aliensballs[i].Pos.y, 20))
			{
				G.spaceShip.balls.erase(G.spaceShip.balls.begin() + j);
				G.Aliensballs.erase(G.Aliensballs.begin() + i);
				break;
			}
		}
	}

	for (int i = 0; i < G.Aliensballs.size(); i++) // Collisions entre les balles du vaisseau et ceux des aliens
	{
		for (int j = 0; j < G.spaceShip.balls.size(); j++)
		{
			if (Proximite(G.spaceShip.balls[j].Pos.x, G.spaceShip.balls[j].Pos.y, G.Aliensballs[i].Pos.x, G.Aliensballs[i].Pos.y, 20))
			{
				G.spaceShip.balls.erase(G.spaceShip.balls.begin() + j);
				G.Aliensballs.erase(G.Aliensballs.begin() + i);
				break;
			}
		}
	}

	for (int i = 0; i < G.Shields.size(); i++) // Collisions entre les balles du vaisseau et les shields
	{
		for (int j = 0; j < G.spaceShip.balls.size(); j++)
		{
			if (Proximite(G.spaceShip.balls[j].Pos.x, G.spaceShip.balls[j].Pos.y, (G.Shields[i].Pos.x+45), G.Shields[i].Pos.y,30))
			{
				G.spaceShip.balls.erase(G.spaceShip.balls.begin() + j);
				if (G.Shields[i].ShieldLife <= 0)
					G.Shields.erase(G.Shields.begin() + i);
				break;
			}
		}
	}

	for (int i = 0; i < G.Shields.size(); i++) // Collisions entre les balles des aliens et les shields
	{
		for (int j = 0; j < G.Aliensballs.size(); j++)
		{
			if (Proximite(G.Aliensballs[j].Pos.x, G.Aliensballs[j].Pos.y, (G.Shields[i].Pos.x+45), G.Shields[i].Pos.y, 30))
			{
				if (G.Shields[i].ShieldLife <= 0) {
					G.Shields.erase(G.Shields.begin() + i);
					break;
				}

				G.Aliensballs.erase(G.Aliensballs.begin() + j);
				G.Shields[i].ShieldLife--;	
				break;
			}
		}
	}

	for (int i = 0; i < G.Shields.size(); i++) // collisions vaisseau et shields
	{
		if (Proximite(G.spaceShip.Pos.x, G.spaceShip.Pos.y, G.Shields[i].Pos.x, G.Shields[i].Pos.y, 60))
		{
			G.spaceShip.Pos = G.CurrentSpaceShipPos;
		}
	}
}

// relancer le jeu 
void Restart(GameData & G)
{
	if (G2D::isKeyPressed(Key::R) && G.redraw)
	{
		G.Aliens.clear();
		G.Shields.clear();
		G.spaceShip.balls.clear();
		G.Aliensballs.clear();
		InitGame(G);
		AssetsInit(G);
		G.SCREEN = ECRAN_ACCEUIL;
		G.redraw = false;
	}
}



void AssetsInit(GameData& G)
{
	// Size passé en ref et texture en param

	G.spaceShip.IdTex = G2D::initTextureFromString(G.spaceShip.Size, G.spaceShip.texture);
	G.spaceShip.Size = G.spaceShip.Size * 3; // on peut zoomer la taille du sprite


	for (int i = 0; i < G.Aliens.size(); i++)
	{
		G.Aliens[i].IdTex = G2D::initTextureFromString(G.Aliens[i].Size, G.Aliens[i].texture);
		G.Aliens[i].Size = G.Aliens[i].Size * 3; 
	}
	for (int i = 0; i < G.Shields.size(); i++)
	{
		G.Shields[i].IdTex = G2D::initTextureFromString(G.Shields[i].Size, G.Shields[i].texture);
		G.Shields[i].Size = G.Shields[i].Size * 6; 

		G.Shields[i].IdTex2 = G2D::initTextureFromString(G.Shields[i].Size, G.Shields[i].texture2);
		G.Shields[i].Size = G.Shields[i].Size * 6; 

		G.Shields[i].IdTex3 = G2D::initTextureFromString(G.Shields[i].Size, G.Shields[i].texture3);
		G.Shields[i].Size = G.Shields[i].Size * 6; 
	}
}


// Pendant la partie de jeu 
void GestionEcranJeu(GameData& G)
{
	DeplacementSpaceShip(G);
	SpaceShoot(G);
	BallMove(G);
	CollisionSpaceShipAlien(G);
	delBullet(G);
	ReplaceAliens(G);
	CollisionsAvecBalles(G);
	AlienShoot(G);
		
	if (G.score >= 36)
	{
		G.redraw = true;
		G.SCREEN = ECRAN_VICTOIRE;
		return;
	}
	if (G.Life <= 0)
	{
		G.SCREEN = ECRAN_GAME_OVER;
		G.redraw = true;
		G.Life = 0;
	}

}
// Ecran Acceuil
void GestionEcranAcceuil(GameData& G) 
{

	if (G2D::isKeyPressed(Key::SPACE))
	{
		G.SCREEN = ECRAN_JEU;
		InitGame(G);
		AssetsInit(G);
	}
	if (G2D::isKeyPressed(Key::O))
		G.SCREEN = ECRAN_OPTIONS;
}
// les options
void GestionEcranOptions(GameData& G) 
{
	

	if (G2D::isKeyPressed(Key::A))
	{
		G.speed_level = 0.3;
		G.speed_level_init = 0.3;
		G.SCREEN = ECRAN_ACCEUIL;
	}
	if (G2D::isKeyPressed(Key::B))
	{
		G.speed_level = 0.5;
		G.speed_level_init = 0.5;
		G.SCREEN = ECRAN_ACCEUIL;
	}
	if (G2D::isKeyPressed(Key::C))
	{
		G.speed_level = 0.7;
		G.speed_level_init = 0.7;
		G.SCREEN = ECRAN_ACCEUIL;
	}
	if (G2D::isKeyPressed(Key::F2))
	{
		G.SCREEN = ECRAN_ACCEUIL;
	}
} 

void Logic(GameData & G) // appelé 20 fois par seconde
{
	
	
	G.idFrame += 1;
	G.CurrentSpaceShipPos = G.spaceShip.Pos; // pour replacer le vaisseau si il touche un mur

		switch (G.SCREEN)
		{
		case ECRAN_ACCEUIL:
			GestionEcranAcceuil(G);
			break;
		case ECRAN_JEU:
			GestionEcranJeu(G);	
			break;
		case ECRAN_GAME_OVER:
			Restart(G);
			break;
		case ECRAN_OPTIONS:
			GestionEcranOptions(G);
			break;
		case ECRAN_VICTOIRE:
			Restart(G);
		default:
			break;
		
	}
	
}


int main(int argc, char* argv[])
{
	GameData G;   // instanciation de l'unique objet GameData qui sera passé aux fonctions render et logic
	srand(time(nullptr)); 
	// crée la fenêtre de l'application
	G2D::initWindow(V2(G.WidthPix, G.HeighPix), V2(20, 20), string("SPACE INVADERS"));

	// nombre de fois où la fonction Logic est appelée par seconde
	
	int callToLogicPerSec = 100;  
	InitGame(G);
	AssetsInit(G);
	
	
	// lance l'application en spécifiant les deux fonctions utilisées et l'instance de GameData

	G2D::Run(Logic, Render, G, callToLogicPerSec,true);

	// aucun code ici
}





