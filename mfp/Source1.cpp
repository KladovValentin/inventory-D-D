#pragma once
#include "mainHeader.h"
#include "Item.h"
#include "Button.h"


vector<Item> sortItems(vector<Item> ovect) {
	//sort, need to place it in function
	//set in first cells
	for (size_t i = 0; i < ovect.size(); i++)
		ovect[i].setCell(i);
	Item tempCell("a", "b");
	//bubble sort, main thing - swap parameters, but cell is not important (I place then according to vector index)
	for (size_t i = 0; i < ovect.size(); i++) {
		for (size_t j = 0; j < ovect.size() - i - 1; j++) {
			if (ovect[j].name > ovect[j + 1].name) {
				tempCell = ovect[j];
				ovect[j] = ovect[j + 1];
				ovect[j + 1] = tempCell;
			}
		}
	}
	//place according to position in vector
	for (size_t i = 0; i < ovect.size(); i++) {
		ovect[i].setCell(i);
		ovect[i].setInCell();
	}
	return ovect;
}

int main() {
	setlocale(LC_ALL, "Rus");

	char revslash = (char)92;  // \ //
	string revslashstr = string(1, revslash);
	//std::string strR = "python C:" + revslashstr + "disk" + revslashstr + "python" + revslashstr + "scriptR.py";
	std::string strR = "python scriptR.py";
	std::vector<char> cstrR(strR.c_str(), strR.c_str() + strR.size() + 1);
	system(&cstrR[0]);



	RenderWindow window(VideoMode(900, 850), "inventory");
	window.setFramerateLimit(60);
	//RenderWindow windowt(VideoMode(200, 100), "inventory");
	//windowt.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("OpenSans-Regular.ttf"))
	{
		cout << "cant load font" << endl;
	}

	//text for names/descriptions
	sf::Text text;
	// select the font
	text.setFont(font); // font is a sf::Font
	text.setCharacterSize(14); // in pixels, not points!
	text.setFillColor(sf::Color::Blue);

	RectangleShape whiteBack;
	whiteBack.setSize(Vector2f(800,800));
	whiteBack.setPosition(Vector2f(0,50));
	Texture t1;
	t1.loadFromFile("images/net_8x8.png");
	Sprite s1(t1);
	s1.setPosition(0, 50);

	Texture t2;
	t2.loadFromFile("images/sword.png");
	Texture tmash;
	tmash.loadFromFile("images/mashiro.png");
	Sprite mashiro;
	mashiro.setTexture(tmash);
	mashiro.setPosition(0, 650);

	Texture itemsTextures[12];
	Sprite itemsSprites[12];
	{
		itemsTextures[0].loadFromFile("images/amulet.png");
		itemsTextures[1].loadFromFile("images/armor.png");
		itemsTextures[2].loadFromFile("images/boots.png");
		itemsTextures[3].loadFromFile("images/box.png");
		itemsTextures[4].loadFromFile("images/cloak.png");
		itemsTextures[5].loadFromFile("images/crossbow.png");
		itemsTextures[6].loadFromFile("images/gloves.png");
		itemsTextures[7].loadFromFile("images/helmet.png");
		itemsTextures[8].loadFromFile("images/potion.png");
		itemsTextures[9].loadFromFile("images/ring.png");
		itemsTextures[10].loadFromFile("images/scroll.png");
		itemsTextures[11].loadFromFile("images/sword.png");
	}
	for (size_t i = 0; i < 12; i++) {
		itemsSprites[i].setTexture(itemsTextures[i]);
		itemsSprites[i].setPosition((i-8*(i/8))*100,450+100*(i/8));
	}

	vector<Item> items;
	//addItems From file
	ifstream myfile("items.txt");
	string line;
	Item tempItem("a","b");
	while (myfile.get()!=EOF) {
		getline(myfile, line);
		bool newName = true;
		for (size_t i = 0; i < items.size(); i++) {
			if (line == items[i].name) {
				items[i].amount += 1;
				newName = false;
			}
		}
		if (newName) {
			tempItem.name = line;
			getline(myfile, line);
			tempItem.type = line;
			getline(myfile, line);
			tempItem.description = line;
			myfile >> tempItem.mass >> tempItem.value >> tempItem.amount;
			getline(myfile, line);
			tempItem.sprite = itemsSprites[3];
			items.push_back(tempItem);
		}
	}
	items = sortItems(items);

	//variables for moving dragg and drop items
	float dx = 0., dy = 0.;

	//text for input
	string textInput;
	sf::Text txtInput;
	txtInput.setFont(font); // font is a sf::Font
	txtInput.setCharacterSize(14); // in pixels, not points!
	txtInput.setFillColor(sf::Color::White);
	txtInput.setPosition(s1.getPosition().x + 10, s1.getPosition().y - 20);

	string a = "a";
	sf::String b = String(a);

	///new Item section///
	//New Item Button
	Button newItemButt("פûגûפג", font, (double)s1.getPosition().x + 810, (double)s1.getPosition().y + 10, 80, 25);
	newItemButt.text.setFont(font);
	//confirm Item Buttom
	Button confItemButt("confirm item",font, (double)s1.getPosition().x + 810, (double)s1.getPosition().y + 40, 80, 25);
	confItemButt.text.setFont(font);
	//other
	bool newItemBool = false;
	string newIName;
	string newIType;
	int nICount = 0;
	int newItemSpriteInd = 0;

	//Choose type Buttons
	vector<string> itemTypes = { "equipment" , "usefull gear" , "spendable" , "quest items" , "random stuff"};
	vector<Button> chooseTypeButt;
	for (size_t i = 0; i < itemTypes.size(); i++) {
		chooseTypeButt.push_back(Button(itemTypes[i], font, (double)s1.getPosition().x + 10 + 100 * (int)i, (double)s1.getPosition().y - 50, 80, 25));
		chooseTypeButt[i].text.setFont(font);
	}
	string currentType = itemTypes[0];

	///texts for amount
	vector<Text> amounts;
	for (size_t i = 0; i < items.size(); i++) {
		amounts.push_back(Text(to_string(items[i].amount),font,14));
		amounts.back().setPosition(sf::Vector2f(items[i].sprite.getPosition().x + 100 - items[i].amount * 14, items[i].sprite.getPosition().y + 100 - 20));
		amounts.back().setFillColor(sf::Color::Black);
	}


	///moveing items
	vector<bool> isMove;
	size_t moveInd = 0;
	for (size_t i = 0; i < items.size(); i++)
		isMove.push_back(false);
	
	///changing sprites
	bool changeSpriteBool = false;
	int changeSpriteInd = 0;

	//items = sortItems(items);

	//main loop
	while (window.isOpen())
	{
		window.clear();
		Vector2i pos = Mouse::getPosition(window);
		//std::cout << pos.x << "	" << pos.y << std::endl;
		//std::cout << s2.getGlobalBounds().height << std::endl;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			//////_________writing text_______//////
			if (e.type == sf::Event::TextEntered && newItemBool)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					if (textInput.size() >= 1)
						textInput.erase(textInput.size() - 1, 1); //need to change it to iterator "end"
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					textInput.append("\n");
				}
				//adding info about new Item
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					switch (nICount) {
					case 0:
						newIName = textInput;
						cout << "name is entered" << endl;
						break;
					case 1:
						newIType = textInput;
						cout << "type is entered" << endl;
						nICount = -1;
						break;
					}
					nICount += 1;
					textInput.clear();
				}
				else
					textInput += e.text.unicode;
				txtInput.setString(textInput);
			}

			
			if (e.type == Event::MouseButtonPressed) {
				if (e.key.code == Mouse::Left) {

					////drag and drop////
					for (size_t i = 0; i < items.size(); i++) {
						if (items[i].sprite.getGlobalBounds().contains(pos.x, pos.y) && items[i].type == currentType)
						{
							isMove[i] = true;
							moveInd = i;
							dx = pos.x - items[i].sprite.getPosition().x;
							dy = pos.y - items[i].sprite.getPosition().y;
						}
					}
					//choose current type button
					for (size_t i = 0; i < chooseTypeButt.size(); i++)
						if (chooseTypeButt[i].background.getGlobalBounds().contains(pos.x, pos.y))
							currentType = itemTypes[i];
					//
					if (newItemButt.background.getGlobalBounds().contains(pos.x, pos.y) && !newItemBool)
					{
						newItemBool = true;
					}
					//confirm new button
					if (confItemButt.background.getGlobalBounds().contains(pos.x, pos.y) && newItemBool)
					{
						//check for existance of an item with this name, if so -> +1 to amount
						newItemBool = false;
						bool sameName = false;
						for (size_t i = 0; i < items.size(); i++) {
							if (items[i].name == newIName) {
								items[i].amount += 1;
								sameName = true;
							}
						}
						if (!sameName) {
							//creating new item
							items.push_back(Item(newIName, newIType));
							items.back().sprite.setTexture(itemsTextures[newItemSpriteInd]);
							items.back().setCell(0);
							items.back().setInCell();

							//movement bool for new item
							isMove.push_back(false);

							//text for amount of new item
							amounts.push_back(Text(to_string(items.back().amount), font, 14));
							amounts.back().setFillColor(sf::Color::Black);

							//is type new?
							bool isTypeNew = true;
							for (size_t i = 0; i < itemTypes.size(); i++)
								if (newIType == itemTypes[i])
									isTypeNew = false;
							if (isTypeNew) {
								itemTypes.push_back(newIType);
								chooseTypeButt.push_back(Button(newIType, font, (double)s1.getPosition().x + 10 + 100 * ((int)itemTypes.size()-1), (double)s1.getPosition().y - 50, 80, 25));
								chooseTypeButt.back().text.setFont(font);
								
							}
							currentType = newIType;

							//sorting by name
							items = sortItems(items);
						}

					}
					//choosing the sprite
					for (size_t i = 0; i < 12; i++) {
						if (itemsSprites[i].getGlobalBounds().contains(pos.x, pos.y)) {
							//for new item
							if (newItemBool) {
								newItemSpriteInd = i;
								cout << "sprite is chosen" << endl;
							}
							//to change of the existing
							if (changeSpriteBool) {
								items[changeSpriteInd].sprite = itemsSprites[i];
								items[changeSpriteInd].setInCell();
								cout << "sprite is chaged" << endl;
								changeSpriteBool = false;
							}
						}

					}

				}
				
				if (e.key.code == Mouse::Right) {
					
					//start changing sprite section if click rmb on item
					for (size_t i = 0; i < items.size(); i++) {
						if (items[i].sprite.getGlobalBounds().contains(pos.x, pos.y) && items[i].type == currentType)
						{
							changeSpriteBool = true;
							changeSpriteInd = i;
						}
					}
				}
			}

			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Left) {
					/// fix moving item to cell
					isMove[moveInd] = false;
					float x = ((float)items[moveInd].sprite.getPosition().x + 50.) / 100;
					float y = ((float)items[moveInd].sprite.getPosition().y-50. + 50.) / 100;
					sf::Vector2f a = Vector2f( 100*int(x),100 * int(y)+50);
					items[moveInd].sprite.setPosition(a);
					items[moveInd].setCell((int(x)+8*int(y)));
				}
		}
		for (size_t i = 0; i < items.size(); i++) {
			if (isMove[i])
				items[i].sprite.setPosition(pos.x - dx, pos.y - dy);
		}

		//____///check_for_name_showing/////
		RectangleShape nameBox;
		bool showName = false;
		size_t showNameI = 0;
		for (size_t i = 0; i < items.size(); i++) {
			if (items[i].sprite.getGlobalBounds().contains(pos.x, pos.y) && items[i].type == currentType) {
				text.setString(items[i].name);
				nameBox.setPosition(sf::Vector2f(items[i].sprite.getPosition().x + 20, items[i].sprite.getPosition().y - 30));
				text.setPosition(sf::Vector2f(nameBox.getPosition().x + 5, nameBox.getPosition().y + 2));
				nameBox.setSize(Vector2f(text.getGlobalBounds().width + 10, text.getGlobalBounds().height + 10));
				showName = true;
				showNameI = i;
			}
		}

		//setInApropriateCell
		size_t j = 0;
		for (size_t i = 0; i < items.size(); i++) {
			if (items[i].type == currentType) {
				items[i].setCell(j);
				items[i].setInCell();
				j++;
			}
		}


		///draw
		
		window.draw(whiteBack);
		window.draw(s1);
		window.draw(mashiro);
		
		for (size_t i = 0; i < chooseTypeButt.size(); i++) {
			window.draw(chooseTypeButt[i].background);
			window.draw(chooseTypeButt[i].text);
		}

		if (!newItemBool) {
			window.draw(newItemButt.background);
			window.draw(newItemButt.text);
		}
		else {
			window.draw(confItemButt.background);
			window.draw(confItemButt.text);
		}
		if (newItemBool || changeSpriteBool) {
			for (size_t i = 0; i < 12; i++)
				window.draw(itemsSprites[i]);
		}
		
		for (size_t i = 0; i < items.size(); i++) {
			if (items[i].type == currentType) {
				window.draw(items[i].sprite);
				amounts[i].setString(to_string(items[i].amount));
				amounts[i].setPosition(sf::Vector2f(items[i].sprite.getPosition().x + 100 - ((int)items[i].amount / 10) * 14 - 14, items[i].sprite.getPosition().y + 100 - 20));
				window.draw(amounts[i]);
			}
		}
		if (showName) {
			window.draw(nameBox);
			window.draw(text);
		}
		window.draw(txtInput);
		window.display();
	}


	//write items to a storing file
	ofstream ofile("itemsOUT.txt");
	for (size_t i = 0; i < items.size(); i++) {
		ofile << endl << items[i].name << endl << items[i].type << endl << items[i].description << endl << items[i].mass << " " << items[i].value << " " << items[i].amount << endl;
	}
	ofile.close();

	//std::string strW = "python C:" + revslashstr + "disk" + revslashstr + "python" + revslashstr + "scriptW.py";
	std::string strW = "python scriptW.py";
	std::vector<char> cstrW(strW.c_str(), strW.c_str() + strW.size() + 1);
	system(&cstrW[0]);

}


//classes - item - type, cell_number (only in certain page), sprite, value, mass, amount

//features: add item - name, description, choose type or add new and also choose sprite from abailable
//it will have pages according to types
//if you add item that has an existing name - it just adds +1 to amount
//Ideally, it should be on some drive and all party members should have an acces to it, so it should load info from google table