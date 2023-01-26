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

	//Hitbox terra
	CreateBuilding({ -50, -0.25, 10 }, { 250, 0.5, 250 }, White);

	//Hitbox bordes circuit
	CreateBuilding({ 5, 0, -5 }, { 0.5, 1, 160 }, White);
	CreateBuilding({ -5, 0, -5 }, { 0.5, 1, 140 }, White);
	CreateBuilding({ -10, 0, 75 }, { 30, 1, 0.5 }, White);
	CreateBuilding({ -20, 0, 65 }, { 30, 1, 0.5 }, White);
	CreateBuilding({ -35, 0, 80 }, { 0.5, 1, 30 }, White);
	CreateBuilding({ -25, 0, 90 }, { 0.5, 1, 30 }, White);
	CreateBuilding({ -60, 0, 95 }, { 50, 1, 0.5 }, White);
	CreateBuilding({ -60, 0, 105 }, { 70, 1, 0.5 }, White);
	CreateBuilding({ -85, 0, 75 }, { 0.5, 1, 40 }, White);
	CreateBuilding({ -95, 0, 75 }, { 0.5, 1, 60 }, White);
	CreateBuilding({ -82.5, 0, 55 }, { 5, 1, 0.5 }, White);
	CreateBuilding({ -82.5, 0, 45 }, { 25, 1, 0.5 }, White);
	CreateBuilding({ -80, 0, 70 }, { 0.5, 1, 30 }, White);
	CreateBuilding({ -70, 0, 60 }, { 0.5, 1, 30 }, White);
	CreateBuilding({ -62.5, 0, 85 }, { 35, 1, 0.5 }, White);
	CreateBuilding({ -62.5, 0, 75 }, { 15, 1, 0.5 }, White);
	CreateBuilding({ -55, 0, 55 }, { 0.5, 1, 40 }, White);
	CreateBuilding({ -45, 0, 55 }, { 0.5, 1, 60 }, White);
	CreateBuilding({ -67.5, 0, 35 }, { 25, 1, 0.5 }, White);
	CreateBuilding({ -57.5, 0, 25 }, { 25, 1, 0.5 }, White);
	CreateBuilding({ -80, 0, 2.5 }, { 0.5, 1, 65 }, White);
	CreateBuilding({ -70, 0, -7.5 }, { 0.5, 1, 65 }, White);
	CreateBuilding({ -82.5, 0, -40 }, { 25, 1, 0.5 }, White);
	CreateBuilding({ -92.5, 0, -30 }, { 25, 1, 0.5 }, White);
	CreateBuilding({ -105, 0, -57.5 }, { 0.5, 1, 55 }, White);
	CreateBuilding({ -95, 0, -57.5 }, { 0.5, 1, 35 }, White);
	CreateBuilding({ -50, 0, -75 }, { 90, 1, 0.5 }, White);
	CreateBuilding({ -50, 0, -85 }, { 110, 1, 0.5 }, White);


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
	c->SetPos(pos.x, pos.y, pos.z);
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

	Cube floor(250, 0.5, 250);
	floor.SetPos(-50, -0.25, 10);
	floor.color.r = 0;
	floor.color.g = 256;
	floor.color.b = 0;
	floor.Render();

	Cube r1(0.5, 1, 160);
	r1.SetPos(5, 0, -5);
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

	Cube r15(35, 1, 0.5);
	r15.SetPos(-62.5, 0, 85);
	r15.color.r = 256;
	r15.color.g = 0;
	r15.color.b = 0;
	r15.Render();

	Cube r16(15, 1, 0.5);
	r16.SetPos(-62.5, 0, 75);
	r16.color.r = 256;
	r16.color.g = 0;
	r16.color.b = 0;
	r16.Render();

	Cube r17(0.5, 1, 40);
	r17.SetPos(-55, 0, 55);
	r17.color.r = 256;
	r17.color.g = 0;
	r17.color.b = 0;
	r17.Render();

	Cube r18(0.5, 1, 60);
	r18.SetPos(-45, 0, 55);
	r18.color.r = 256;
	r18.color.g = 0;
	r18.color.b = 0;
	r18.Render();

	Cube r19(25, 1, 0.5);
	r19.SetPos(-67.5, 0, 35);
	r19.color.r = 256;
	r19.color.g = 0;
	r19.color.b = 0;
	r19.Render();

	Cube r20(25, 1, 0.5);
	r20.SetPos(-57.5, 0, 25);
	r20.color.r = 256;
	r20.color.g = 0;
	r20.color.b = 0;
	r20.Render();

	Cube r21(0.5, 1, 65);
	r21.SetPos(-80, 0, 2.5);
	r21.color.r = 256;
	r21.color.g = 0;
	r21.color.b = 0;
	r21.Render();

	Cube r22(0.5, 1, 65);
	r22.SetPos(-70, 0, -7.5);
	r22.color.r = 256;
	r22.color.g = 0;
	r22.color.b = 0;
	r22.Render();

	Cube r23(25, 1, 0.5);
	r23.SetPos(-82.5, 0, -40);
	r23.color.r = 256;
	r23.color.g = 0;
	r23.color.b = 0;
	r23.Render();

	Cube r24(25, 1, 0.5);
	r24.SetPos(-92.5, 0, -30);
	r24.color.r = 256;
	r24.color.g = 0;
	r24.color.b = 0;
	r24.Render();

	Cube r25(0.5, 1, 55);
	r25.SetPos(-105, 0, -57.5);
	r25.color.r = 256;
	r25.color.g = 0;
	r25.color.b = 0;
	r25.Render();

	Cube r26(0.5, 1, 35);
	r26.SetPos(-95, 0, -57.5);
	r26.color.r = 256;
	r26.color.g = 0;
	r26.color.b = 0;
	r26.Render();

	Cube r27(90, 1, 0.5);
	r27.SetPos(-50, 0, -75);
	r27.color.r = 256;
	r27.color.g = 0;
	r27.color.b = 0;
	r27.Render();

	Cube r28(110, 1, 0.5);
	r28.SetPos(-50, 0, -85);
	r28.color.r = 256;
	r28.color.g = 0;
	r28.color.b = 0;
	r28.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}