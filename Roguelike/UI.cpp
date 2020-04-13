#include "UI.h"

#include "Chars.h"


#include <sstream>
#include <iostream>

std::vector<SDL_Rect> UI::createMessage(const char *message)
{
	std::vector<SDL_Rect> result;

	for (int i = 0; message[i] != '\0'; i++) 
	{
		switch (message[i])
		{
		case ' ':
			result.push_back(Chars::charSpace);
			break;
		case '!':
			result.push_back(Chars::charExMark);
			break;
		case '?':
			result.push_back(Chars::charQuestionMark);
			break;
		case ':':
			result.push_back(Chars::charColon);
			break;
		case ';':
			result.push_back(Chars::charSemiColon);
			break;
		case '.':
			result.push_back(Chars::charFullStop);
			break;
		case ',':
			result.push_back(Chars::charComma);
			break;
		case '-':
			result.push_back(Chars::charDash);
			break;
		case '[':
			result.push_back(Chars::charLeftSquare);
			break;
		case ']':
			result.push_back(Chars::charRightSquare);
			break;

		// numbers
		case '0':
			result.push_back(Chars::char0);
			break;
		case '1':
			result.push_back(Chars::char1);
			break;
		case '2':
			result.push_back(Chars::char2);
			break;
		case '3':
			result.push_back(Chars::char3);
			break;
		case '4':
			result.push_back(Chars::char4);
			break;
		case '5':
			result.push_back(Chars::char5);
			break;
		case '6':
			result.push_back(Chars::char6);
			break;
		case '7':
			result.push_back(Chars::char7);
			break;
		case '8':
			result.push_back(Chars::char8);
			break;
		case '9':
			result.push_back(Chars::char9);
			break;


		// Uppercase letters
		case 'A':
			result.push_back(Chars::charCa);
			break;
		case 'B':
			result.push_back(Chars::charCb);
			break;
		case 'C':
			result.push_back(Chars::charCc);
			break;
		case 'D':
			result.push_back(Chars::charCd);
			break;
		case 'E':
			result.push_back(Chars::charCe);
			break;
		case 'F':
			result.push_back(Chars::charCf);
			break;
		case 'G':
			result.push_back(Chars::charCg);
			break;
		case 'H':
			result.push_back(Chars::charCh);
			break;
		case 'I':
			result.push_back(Chars::charCi);
			break;
		case 'J':
			result.push_back(Chars::charCj);
			break;
		case 'K':
			result.push_back(Chars::charCk);
			break;
		case 'L':
			result.push_back(Chars::charCl);
			break;
		case 'M':
			result.push_back(Chars::charCm);
			break;
		case 'N':
			result.push_back(Chars::charCn);
			break;
		case 'O':
			result.push_back(Chars::charCo);
			break;
		case 'P':
			result.push_back(Chars::charCp);
			break;
		case 'Q':
			result.push_back(Chars::charCq);
			break;
		case 'R':
			result.push_back(Chars::charCr);
			break;
		case 'S':
			result.push_back(Chars::charCs);
			break;
		case 'T':
			result.push_back(Chars::charCt);
			break;
		case 'U':
			result.push_back(Chars::charCu);
			break;
		case 'V':
			result.push_back(Chars::charCv);
			break;
		case 'W':
			result.push_back(Chars::charCw);
			break;
		case 'X':
			result.push_back(Chars::charCx);
			break;
		case 'Y':
			result.push_back(Chars::charCy);
			break;
		case 'Z':
			result.push_back(Chars::charCz);
			break;

		// Lowercase letters
		case 'a':
			result.push_back(Chars::charLa);
			break;
		case 'b':
			result.push_back(Chars::charLb);
			break;
		case 'c':
			result.push_back(Chars::charLc);
			break;
		case 'd':
			result.push_back(Chars::charLd);
			break;
		case 'e':
			result.push_back(Chars::charLe);
			break;
		case 'f':
			result.push_back(Chars::charLf);
			break;
		case 'g':
			result.push_back(Chars::charLg);
			break;
		case 'h':
			result.push_back(Chars::charLh);
			break;
		case 'i':
			result.push_back(Chars::charLi);
			break;
		case 'j':
			result.push_back(Chars::charLj);
			break;
		case 'k':
			result.push_back(Chars::charLk);
			break;
		case 'l':
			result.push_back(Chars::charLl);
			break;
		case 'm':
			result.push_back(Chars::charLm);
			break;
		case 'n':
			result.push_back(Chars::charLn);
			break;
		case 'o':
			result.push_back(Chars::charLo);
			break;
		case 'p':
			result.push_back(Chars::charLp);
			break;
		case 'q':
			result.push_back(Chars::charLq);
			break;
		case 'r':
			result.push_back(Chars::charLr);
			break;
		case 's':
			result.push_back(Chars::charLs);
			break;
		case 't':
			result.push_back(Chars::charLt);
			break;
		case 'u':
			result.push_back(Chars::charLu);
			break;
		case 'v':
			result.push_back(Chars::charLv);
			break;
		case 'w':
			result.push_back(Chars::charLw);
			break;
		case 'x':
			result.push_back(Chars::charLx);
			break;
		case 'y':
			result.push_back(Chars::charLy);
			break;
		case 'z':
			result.push_back(Chars::charLz);
			break;
		default:
			result.push_back(Chars::charSpace);
			break;
		}
	}

	return result;
}


void UI::printMessage(const char* message)
{
	this->lastMessage2 = this->lastMessage;
	this->lastMessage = this->currentMessage;
	this->currentMessage = this->createMessage(message);
	std::cout << message << std::endl;
}

void UI::Update(int playerHealth, int playerMoney, int attackDamage, int armour)
{
	std::stringstream ss;
	ss << "Health: " << std::to_string(playerHealth) << "  Armour: " << std::to_string(armour) << "  Strength: " << attackDamage << "  Gold: " << std::to_string(playerMoney);
	std::string myString = ss.str();

	this->hud = createMessage(myString.c_str());
}


void UI::Render(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_Rect bottomRect = {0, 576, 800, 232};
	SDL_Rect topRect = { 0, 0, 800, 16 };
	SDL_SetRenderDrawColor(renderer, 0, 50, 0, 255);
	SDL_RenderFillRect(renderer, &bottomRect);
	SDL_RenderFillRect(renderer, &topRect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	int count = 0;
	for (auto& c : this->currentMessage)
	{
		SDL_Rect destRect = { count*16, 608, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}
	
	count = 0;
	for (auto& c : this->lastMessage)
	{
		SDL_Rect destRect = { count * 16, 592, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : this->lastMessage2)
	{
		SDL_Rect destRect = { count * 16, 576, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : this->hud)
	{
		SDL_Rect destRect = { count * 16, 0, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

}

void UI::RenderEndScreen(SDL_Renderer* renderer, SDL_Texture* texture, int monstersKilled, int money)
{
	std::vector<SDL_Rect> endText = this->createMessage("I Died.");
	std::vector<SDL_Rect> instruction1 = this->createMessage("[Q]uit");
	std::vector<SDL_Rect> instruction2 = this->createMessage("[R]estart");

	std::stringstream ss;
	ss << "Monsters Slain: " << monstersKilled << "  Gold Collected: " << money;
	std::vector<SDL_Rect> score = this->createMessage(ss.str().c_str());

	int count = 0;
	int xoffset = 128;

	for (auto& c : endText)
	{
		SDL_Rect destRect = { xoffset + count * 16, 250, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : score)
	{
		SDL_Rect destRect = { xoffset + count * 16, 300, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : instruction1)
	{
		SDL_Rect destRect = { xoffset + count * 16, 332, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}
	count = 0;
	for (auto& c : instruction2)
	{
		SDL_Rect destRect = { xoffset + count * 16, 348, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}
}

void UI::RenderWinScreen(SDL_Renderer* renderer, SDL_Texture* texture, int monstersKilled, int money)
{
	std::vector<SDL_Rect> endText = this->createMessage("I Escaped the caves, my pockets full.");
	std::vector<SDL_Rect> instruction1 = this->createMessage("[Q]uit");
	std::vector<SDL_Rect> instruction2 = this->createMessage("[R]estart");

	std::stringstream ss;
	ss << "Monsters Slain: " << monstersKilled << "  Gold Collected: " << money;
	std::vector<SDL_Rect> score = this->createMessage(ss.str().c_str());

	int count = 0;
	int xoffset = 128;

	for (auto& c : endText)
	{
		SDL_Rect destRect = { xoffset + count * 16, 250, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : score)
	{
		SDL_Rect destRect = { xoffset + count * 16, 300, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : instruction1)
	{
		SDL_Rect destRect = { xoffset + count * 16, 332, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}
	count = 0;
	for (auto& c : instruction2)
	{
		SDL_Rect destRect = { xoffset + count * 16, 348, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}
}

void UI::RenderMainMenu(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* men)
{
	std::vector<SDL_Rect> endText = this->createMessage("LEGEND OF CAVE");
	std::vector<SDL_Rect> instruction1 = this->createMessage("[S]tart");
	std::vector<SDL_Rect> instruction2 = this->createMessage("[H]igh Score");
	std::vector<SDL_Rect> instruction3 = this->createMessage("[Q]uit");


	SDL_Rect d = { 0,0,808,616 };
	SDL_RenderCopy(renderer, men, NULL, &d);


	int count = 0;
	int xoffset = 128;

	SDL_Rect backRect = { 100, 230, 300, 150 };
	SDL_SetRenderDrawColor(renderer, 57, 56, 86, 255);
	SDL_RenderFillRect(renderer, &backRect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	for (auto& c : endText)
	{
		SDL_Rect destRect = { xoffset + count * 16, 250, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : instruction1)
	{
		SDL_Rect destRect = { xoffset + count * 16, 300, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : instruction2)
	{
		SDL_Rect destRect = { xoffset + count * 16, 316, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : instruction3)
	{
		SDL_Rect destRect = { xoffset + count * 16, 332, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}
}

void UI::RenderHighScore(SDL_Renderer* renderer, SDL_Texture* texture, int highmoney, int highmonster)
{
	std::vector<SDL_Rect> title = this->createMessage("High Score");
	std::vector<SDL_Rect> instruction1 = this->createMessage("[B]ack");

	std::stringstream ss2;
	ss2 << "Monsters Slain: " << highmonster;
	std::vector<SDL_Rect> monsters = this->createMessage(ss2.str().c_str());

	std::stringstream ss;
	ss << "Gold Collected: " << highmoney;
	std::vector<SDL_Rect> money = this->createMessage(ss.str().c_str());



	int count = 0;
	int xoffset = 128;

	for (auto& c : title)
	{
		SDL_Rect destRect = { xoffset + count * 16, 250, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : monsters)
	{
		SDL_Rect destRect = { xoffset + count * 16, 300, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : money)
	{
		SDL_Rect destRect = { xoffset + count * 16, 316, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	count = 0;
	for (auto& c : instruction1)
	{
		SDL_Rect destRect = { xoffset + count * 16, 348, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}
}

void UI::RenderInventory(SDL_Renderer* renderer, SDL_Texture* texture, std::string inventory[3])
{
	std::vector<SDL_Rect> title = this->createMessage("Inventory");
	std::vector<SDL_Rect> back = this->createMessage("[B]ack");

	int count = 0;
	int xoffset = 128;
	for (auto& c : title)
	{
		SDL_Rect destRect = { xoffset + count * 16, 100, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	for (auto& c : back)
	{
		SDL_Rect destRect = { xoffset + count * 16, 450, 16, 16 };
		SDL_RenderCopy(renderer, texture, &c, &destRect);
		count++;
	}

	std::string itemPlaces[3] = {"Right Hand: ", "Left Hand: ", "Body: "};

	for (int i = 0; i < 3; i++)
	{
		std::stringstream ss;
		ss << itemPlaces[i] << inventory[i];
		std::vector<SDL_Rect> item = this->createMessage(ss.str().c_str());

		int count = 0;
		for (auto& c : item)
		{
			SDL_Rect destRect = { xoffset + count * 16, 150 + (i*20), 16, 16 };
			SDL_RenderCopy(renderer, texture, &c, &destRect);
			count++;
		}
	}
}