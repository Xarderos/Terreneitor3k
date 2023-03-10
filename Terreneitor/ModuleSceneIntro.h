#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

struct Buildings
{
	p2DynArray<PhysBody3D*>		phys_builds;
	p2DynArray<Cube*>			prim_builds;
};
struct Constraints
{
	p2DynArray<PhysBody3D*>		phys_constraints;
	p2DynArray<Cube*>			prim_constraints;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateCollision(const vec3 pos, const vec3 dim, Color bColor);

	void CreateRamp(const vec3 pos, const vec3 dim, Color bColor, float angle, const vec3& u);

public:
	Buildings buildings;
	Constraints constraints;

	p2DynArray<Primitive*>	primitives;
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	PhysBody3D* sensorsorra;
	PhysBody3D* sensorgel;
	PhysBody3D* sensoraigua;
	PhysBody3D* sensorvent;
	PhysBody3D* sensormeta;
	PhysBody3D* sensorrampa;

	bool onsand;
	bool onfan;
	bool onice;
	bool onwater;

	bool firstwin;
	bool win;
	bool lose;
	bool playmusic;
};
