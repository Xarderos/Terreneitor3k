#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"

vec3 BtToVec(btVector3 A) {
	vec3 B;
	B.x = A.x();
	B.y = A.y();
	B.z = A.z();
	return B;
}
ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	CreateBuilding({ 10,  14, 90 }, { 30, 30, 30 }, White);
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

void ModuleSceneIntro::CreateBuilding(const vec3 pos, const vec3 dim, Color bColor)
{
	// Create a cube to render a building
	Cube* c;
	c = new Cube(dim.x, dim.y, dim.z);
	c->color = bColor;
	c->SetPos(pos.x, pos.y + 1, pos.z);
	buildings.prim_builds.PushBack(c);
	buildings.phys_builds.PushBack(App->physics->AddBody(*c, this, 0.0f));
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{


	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	vec3 look = BtToVec(App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition());
	App->camera->LookAt(look);

	Cube floor(500, 0.5, 500);
	floor.SetPos(0, -0.25, 0);
	floor.color.r = 0;
	floor.color.g = 256;
	floor.color.b = 0;
	floor.Render();

	Cube r1(0.5, 1, 155);
	r1.SetPos(5, 0, -2.5);
	r1.color.r = 256;
	r1.color.g = 0;
	r1.color.b = 0;
	r1.Render();

	Cube r2(0.5, 1, 140);
	r2.SetPos(-5, 0, -5);
	r2.color.r = 256;
	r2.color.g = 0;
	r2.color.b = 0;
	r2.Render();

	Cube r3(30, 1, 0.5);
	r3.SetPos(-10, 0, 75);
	r3.color.r = 256;
	r3.color.g = 0;
	r3.color.b = 0;
	r3.Render();

	Cube r4(30, 1, 0.5);
	r4.SetPos(-20, 0, 65);
	r4.color.r = 256;
	r4.color.g = 0;
	r4.color.b = 0;
	r4.Render();

	Cube r5(0.5, 1, 30);
	r5.SetPos(-35, 0, 80);
	r5.color.r = 256;
	r5.color.g = 0;
	r5.color.b = 0;
	r5.Render();
	
	Cube r6(0.5, 1, 30);
	r6.SetPos(-25, 0, 90);
	r6.color.r = 256;
	r6.color.g = 0;
	r6.color.b = 0;
	r6.Render();

	Cube r7(50, 1, 0.5);
	r7.SetPos(-60, 0, 95);
	r7.color.r = 256;
	r7.color.g = 0;
	r7.color.b = 0;
	r7.Render();
	
	Cube r8(70, 1, 0.5);
	r8.SetPos(-60, 0, 105);
	r8.color.r = 256;
	r8.color.g = 0;
	r8.color.b = 0;
	r8.Render();

	Cube r9(0.5, 1, 40);
	r9.SetPos(-85, 0, 75);
	r9.color.r = 256;
	r9.color.g = 0;
	r9.color.b = 0;
	r9.Render();

	Cube r10(0.5, 1, 60);
	r10.SetPos(-95, 0, 75);
	r10.color.r = 256;
	r10.color.g = 0;
	r10.color.b = 0;
	r10.Render();

	Cube r11(5, 1, 0.5);
	r11.SetPos(-82.5, 0, 55);
	r11.color.r = 256;
	r11.color.g = 0;
	r11.color.b = 0;
	r11.Render();

	Cube r12(25, 1, 0.5);
	r12.SetPos(-82.5, 0, 45);
	r12.color.r = 256;
	r12.color.g = 0;
	r12.color.b = 0;
	r12.Render();

	Cube r13(0.5, 1, 30);
	r13.SetPos(-80, 0, 70);
	r13.color.r = 256;
	r13.color.g = 0;
	r13.color.b = 0;
	r13.Render();

	Cube r14(0.5, 1, 30);
	r14.SetPos(-70, 0, 60);
	r14.color.r = 256;
	r14.color.g = 0;
	r14.color.b = 0;
	r14.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

