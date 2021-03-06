#pragma once
#include <ecm.h>

class HPComponent : public Component {
protected:
	int hp;

public:
  void update(double dt) override;
  void render() override {}
  int getHP();
  void setHP(int in);
  explicit HPComponent(Entity* p);
  HPComponent() = delete;
};
