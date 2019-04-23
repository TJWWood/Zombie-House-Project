#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
#include "../components/cmp_weapon_system.h"
#include "../components/cmp_hp.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <LevelSystem.h>


using namespace std;
using namespace sf;
static shared_ptr<Entity> player;
std::map<std::string, MyKeys> m_keys;
void MenuScene::Load() {
  cout << "Menu Load \n";

  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
		
        "Platformer\nInteract (E) with the door to start/continue\nPress F1 to enter fullscreen\nInteract with blue square to remap controls");
  }

  if (ctrl_change == false)
  {
	  MyKeys key;
	  key.key_pressed = Keyboard::Left;
	  m_keys["Left"] = key;
	  key.key_pressed = Keyboard::Right;
	  m_keys["Right"] = key;
	  key.key_pressed = Keyboard::Space;
	  m_keys["Shoot"] = key;
  }

  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("res/levels/menu.txt", 40.0f);

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  // Create player
  {
	  player = makeEntity();
	  player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	  //shared_ptr<Texture> ss;
	  //if (!ss->loadFromFile("res/sprites/1.png")) {
	  //	cerr << "Failed to load spritesheet!" << std::endl;
	  //}
	  //auto sp = player->addComponent<SpriteComponent>();
	  //sp->setTexure(ss);
	  auto s = player->addComponent<ShapeComponent>();
	  s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
	  s->getShape().setFillColor(Color::Magenta);
	  s->getShape().setOrigin(10.f, 15.f);

	  player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	  player->addComponent<WeaponSystemComponent>();
  }

  // Add physics colliders to level tiles.
  {
	  auto walls = ls::findTiles(ls::WALL);
	  for (auto w : walls) {
		  auto pos = ls::getTilePosition(w);
		  pos += Vector2f(20.f, 20.f); //offset to center
		  auto e = makeEntity();
		  e->setPosition(pos);
		  e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
	  }
  }



  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

	if (ls::getTileAt(player->getPosition()) == ls::END && Keyboard::isKeyPressed(Keyboard::E)) {
		Engine::ChangeScene((Scene*)&level1);
	}

	if (ls::getTileAt(player->getPosition()) == ls::WAYPOINT && Keyboard::isKeyPressed(Keyboard::E)) {
		Engine::ChangeScene((Scene*)&controls);
	}


  Scene::Update(dt);
}

void MenuScene::UnLoad()
{
	cout << "Scene 1 Unload" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void MenuScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}