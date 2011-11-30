#pragma once
#include "TVScreen.h"

class MobileEntity;

class Teleporter : public TVScreen {
public:
	Teleporter();
	~Teleporter();

	void update();
	Teleporter* pair() { return _pair; }
	void unpair();
	bool paired() const { return _pair != NULL; }
	vec3 teleportSite() const;
	void teleport(MobileEntity* e) const;

	static void setPair(Teleporter* a, Teleporter* b);

private:
	static const float SITE_OFFSET;

	Teleporter(const Teleporter&);
	Teleporter& operator=(const Teleporter&);

	TVCamera* _camera;
	Teleporter* _pair;
};

