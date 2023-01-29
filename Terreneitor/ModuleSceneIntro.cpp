#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"
#include "ModuleAudio.h"

float loseTime = 10.0f;

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
	App->player->canmove = true;
	canwin = false;
	App->audio->PlayMusic("Audio/WaluigiPinball.wav");
	temps.Start();
	LOG("Loading Intro assets");
	bool ret = true;

	//Hitbox terra
	CreateCollision({ 0, 20, -5 }, { 10, 0.5, 160 }, White);
	CreateCollision({ -20, 20, 70 }, { 30, 0.5, 10 }, White);
	CreateCollision({ -30, 20, 90 }, { 10, 0.5, 30 }, White);
	CreateCollision({ -42.5, 20, 100 }, { 15, 0.5, 10 }, White);
	CreateCollision({ -80, 20, 100 }, { 30, 0.5, 10 }, White);
	CreateCollision({ -90, 20, 70 }, { 10, 0.5, 50 }, White);
	CreateCollision({ -77.5, 20, 50 }, { 15, 0.5, 10 }, White);
	CreateCollision({ -75, 20, 70 }, { 10, 0.5, 30 }, White);
	CreateCollision({ -57.5, 20, 80 }, { 25, 0.5, 10 }, White);
	CreateCollision({ -50, 20, 50 }, { 10, 0.5, 50 }, White);
	CreateCollision({ -67.5, 20, 30 }, { 25, 0.5, 10 }, White);
	CreateCollision({ -75, 20, -7.5 }, { 10, 0.5, 65 }, White);
	CreateCollision({ -92.5, 20, -35 }, { 25, 0.5, 10 }, White);
	CreateCollision({ -100, 20, -62.5 }, { 10, 0.5, 45 }, White);
	CreateCollision({ -50, 13.3, -80 }, { 55, 0.5, 10 }, White);

	//Hitbox bordes circuit
	CreateCollision({ 5, 20, 20 }, { 0.5, 2, 110 }, White);
	CreateCollision({ -5, 20, -5 }, { 0.5, 2, 140 }, White);
	CreateCollision({ -10, 20, 75 }, { 30, 2, 0.5 }, White);
	CreateCollision({ -20, 20, 65 }, { 30, 2, 0.5 }, White);
	CreateCollision({ -35, 20, 80 }, { 0.5, 2, 30 }, White);
	CreateCollision({ -25, 20, 90 }, { 0.5, 2, 30 }, White);
	CreateCollision({ -60, 20, 95 }, { 50, 2, 0.5 }, White);
	CreateCollision({ -60, 20, 105 }, { 70, 2, 0.5 }, White);
	CreateCollision({ -85, 20, 75 }, { 0.5, 2, 40 }, White);
	CreateCollision({ -95, 20, 75 }, { 0.5, 2, 60 }, White);
	CreateCollision({ -82.5, 20, 55 }, { 5, 2, 0.5 }, White);
	CreateCollision({ -82.5, 20, 45 }, { 25, 2, 0.5 }, White);
	CreateCollision({ -80, 20, 70 }, { 0.5, 2, 30 }, White);
	CreateCollision({ -70, 20, 60 }, { 0.5, 2, 30 }, White);
	CreateCollision({ -62.5, 20, 85 }, { 35, 2, 0.5 }, White);
	CreateCollision({ -62.5, 20, 75 }, { 15, 2, 0.5 }, White);
	CreateCollision({ -55, 20, 55 }, { 0.5, 2, 40 }, White);
	CreateCollision({ -45, 20, 55 }, { 0.5, 2, 60 }, White);
	CreateCollision({ -67.5, 20, 35 }, { 25, 2, 0.5 }, White);
	CreateCollision({ -57.5, 20, 25 }, { 25, 2, 0.5 }, White);
	CreateCollision({ -80, 20, 2.5 }, { 0.5, 2, 65 }, White);
	CreateCollision({ -70, 20, -7.5 }, { 0.5, 2, 65 }, White);
	CreateCollision({ -82.5, 20, -40 }, { 25, 2, 0.5 }, White);
	CreateCollision({ -92.5, 20, -30 }, { 25, 2, 0.5 }, White);
	CreateCollision({ -105, 20, -57.5 }, { 0.5, 2, 55 }, White);
	CreateCollision({ -95, 20, -57.5 }, { 0.5, 2, 35 }, White);
	CreateCollision({ -50, 17, -75 }, { 90, 8, 0.5 }, White);
	CreateCollision({ -50, 17, -85 }, { 110, 8, 0.5 }, White);
	CreateCollision({ 5, 22, -77.5 }, { 0.5, 6, 15 }, White);
	
	//Hitbox ramps
	CreateRamp({ -50, 20, 100 }, { 10, 1, 10 }, White, 15, { 0, 0, -1 });
	CreateRamp({ -86, 16.6, -80 }, { 20, 0.5, 10 }, White, 20, { 0, 0, -1 });
	CreateRamp({ -14, 16.7, -80 }, { 20, 0.5, 10 }, White, 20, { 0, 0, 1 });
	
	Cube sorra(10, 4, 50);
	sensorsorra = App->physics->AddBody(sorra, 0.00);
	sensorsorra->SetAsSensor(true);
	sensorsorra->SetPos(-90, 21, 70);
	sensorsorra->collision_listeners.add(this);

	Cube ice(10,4,65);
	sensorgel = App->physics->AddBody(ice, 0.0);
	sensorgel->SetAsSensor(true);
	sensorgel->SetPos(-75,21,-7.5);
	sensorgel->collision_listeners.add(this);

	Cube aigua(90, 7, 10);
	sensoraigua = App->physics->AddBody(aigua, 0.0);
	sensoraigua->SetAsSensor(true);
	sensoraigua->SetPos(-50, 17, -80);
	sensoraigua->collision_listeners.add(this);

	Cube vent(10, 5, 20);
	sensorvent = App->physics->AddBody(vent, 0.0);
	sensorvent->SetAsSensor(true);
	sensorvent->SetPos(0, 19, -55);
	sensorvent->collision_listeners.add(this);

	Cube meta(10, 15, 3);
	sensormeta = App->physics->AddBody(meta, 0.0);
	sensormeta->SetAsSensor(true);
	sensormeta->SetPos(0, 20, 0);
	sensormeta->collision_listeners.add(this);

	App->camera->Move(vec3(1.0f, 30.0f, 0.0f));
	App->camera->LookAt(vec3(0, 30, 0));
	onsand = false;
	onfan = false;
	onice = false;
	onwater = false;
	onwin = false;
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

void ModuleSceneIntro::CreateCollision(const vec3 pos, const vec3 dim, Color bColor)
{
	Cube* c;
	c = new Cube(dim.x, dim.y, dim.z);
	c->color = bColor;
	c->SetPos(pos.x, pos.y, pos.z);
	buildings.prim_builds.PushBack(c);
	buildings.phys_builds.PushBack(App->physics->AddBody(*c, this, 0.0f));
}
void ModuleSceneIntro::CreateRamp(const vec3 pos, const vec3 dim, Color bColor, float angle, const vec3& u)
{
	Cube* c2;
	c2 = new Cube(dim.x, dim.y, dim.z);
	c2->color = bColor;
	c2->SetPos(pos.x, pos.y, pos.z);
	c2->SetRotation(angle, u);
	buildings.prim_builds.PushBack(c2);
	buildings.phys_builds.PushBack(App->physics->AddBody(*c2, this, 0.0f));
}
// Update
update_status ModuleSceneIntro::Update(float dt)
{
<<<<<<< Updated upstream
	
	//Camera
=======
	//temps.ReadSec();
	//if (temps.ReadSec() >= 10) printf("Lose");//Lose

	if (App->countdown <= 0) {
		App->audio->PlayMusic("Audio/gameover.wav");
		App->player->canmove = false;
	}
	/*Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();*/
	

>>>>>>> Stashed changes
	if(App->camera->isfollowing == true){
		
		vec3 look = BtToVec(App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition());
		if (App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().y() > 2) {
			vec3 move = look - 10 * BtToVec(App->player->vehicle->vehicle->getForwardVector());
			move.y = move.y + 5;
			App->camera->Look(move, look, true);
		}
		else {
			App->camera->LookAt(look);
		}
	}

<<<<<<< Updated upstream
	//Constrain


	//DeathField


	//Fan

	Cube fan1(2, 11, 16);
	fan1.SetPos(-8, 25, -55);
	fan1.color.r = 1;
	fan1.color.g = 1;
	fan1.color.b = 1;
	fan1.Render();

	Cylinder fan2(4.5, 1);
	fan2.SetPos(-6, 25, -55);
	fan2.SetRotation(0, { 0, 0, 1 });
	fan2.color.r = 0;
	fan2.color.g = 0;
	fan2.color.b = 0;
	fan2.Render();

	Cylinder fan3(1, 1);
	fan3.SetPos(-5.6, 25, -55);
	fan3.SetRotation(0, { 0, 0, 1 });
	fan3.color.r = 256;
	fan3.color.g = 256;
	fan3.color.b = 256;
	fan3.Render();

	Cube fan4(1, 0.8, 4);
	fan4.SetPos(-5.6, 27, -55);
	fan4.SetRotation(90, { 1, 0, 0 });
	fan4.color.r = 1;
	fan4.color.g = 1;
	fan4.color.b = 1;
	fan4.Render();

	Cube fan5(1, 0.8, 4);
	fan5.SetPos(-5.6, 24, -56.5);
	fan5.SetRotation(330, { 1, 0, 0 });
	fan5.color.r = 1;
	fan5.color.g = 1;
	fan5.color.b = 1;
	fan5.Render();

	Cube fan6(1, 0.8, 4);
	fan6.SetPos(-5.6, 24, -53.5);
	fan6.SetRotation(210, { 1, 0, 0 });
	fan6.color.r = 1;
	fan6.color.g = 1;
	fan6.color.b = 1;
	fan6.Render();



=======
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		//App->player->vehicle->SetLinearVelocity(0, 0, 0);
		App->player->vehicle->SetPos(0, 20, -10);
		App->player->acceleration = 0.0f;
		App->player->turn = 0.0f;
		App->player->canmove = true;
		//App->audio->PlayMusic("Audio/WaluigiPinball.wav");
		
		//App->player->vehicle->setWorldTransform(defaultTransform);
	}
>>>>>>> Stashed changes
	//Meta

	Cylinder c1(0.2, 7);
	c1.SetPos(5, 24, 0);
	c1.SetRotation(90, { 0, 0, 1 });
	c1.color.r = 0;
	c1.color.g = 0;
	c1.color.b = 0;
	c1.Render();

	Cylinder c2(0.2, 7);
	c2.SetPos(-5, 24, 0);
	c2.SetRotation(90, { 0, 0, 1 });
	c2.color.r = 0;
	c2.color.g = 0;
	c2.color.b = 0;
	c2.Render();

	Cube meta(10, 2, 0.2);
	meta.SetPos(0, 26, 0);
	meta.color.r = 256;
	meta.color.g = 256;
	meta.color.b = 256;
	meta.Render();

	

	//Floor
	Cube f1(10, 0.5, 160);
	f1.SetPos(0, 20, -5);
	f1.color.r = 0;
	f1.color.g = 1;
	f1.color.b = 0;
	f1.Render();

	Cube f2(30, 0.5, 10);
	f2.SetPos(-20, 20, 70);
	f2.color.r = 0;
	f2.color.g = 1;
	f2.color.b = 0;
	f2.Render();

	Cube f3(10, 0.5, 30);
	f3.SetPos(-30, 20, 90);
	f3.color.r = 0;
	f3.color.g = 1;
	f3.color.b = 0;
	f3.Render();

	Cube f4(15, 0.5, 10);
	f4.SetPos(-42.5, 20, 100);
	f4.color.r = 0;
	f4.color.g = 1;
	f4.color.b = 0;
	f4.Render();

	Cube f4_(30, 0.5, 10);
	f4_.SetPos(-80, 20, 100);
	f4_.color.r = 0;
	f4_.color.g = 1;
	f4_.color.b = 0;
	f4_.Render();

	Cube f5(10, 0.5, 50);
	f5.SetPos(-90, 20, 70);
	f5.color.r = 1;
	f5.color.g = 1;
	f5.color.b = 0;
	f5.Render();

	Cube f6(15, 0.5, 10);
	f6.SetPos(-77.5, 20, 50);
	f6.color.r = 0;
	f6.color.g = 1;
	f6.color.b = 0;
	f6.Render();

	Cube f7(10, 0.5, 30);
	f7.SetPos(-75, 20, 70);
	f7.color.r = 0;
	f7.color.g = 1;
	f7.color.b = 0;
	f7.Render();

	Cube f8(25, 0.5, 10);
	f8.SetPos(-57.5, 20, 80);
	f8.color.r = 0;
	f8.color.g = 1;
	f8.color.b = 0;
	f8.Render();

	Cube f9(10, 0.5, 50);
	f9.SetPos(-50, 20, 50);
	f9.color.r = 0;
	f9.color.g = 1;
	f9.color.b = 0;
	f9.Render();

	Cube f10(25, 0.5, 10);
	f10.SetPos(-67.5, 20, 30);
	f10.color.r = 0;
	f10.color.g = 1;
	f10.color.b = 0;
	f10.Render();

	Cube f11(10, 0.5, 65);
	f11.SetPos(-75, 20, -7.5);
	f11.color.r = 0;
	f11.color.g = 1;
	f11.color.b = 1;
	f11.Render();

	Cube f12(25, 0.5, 10);
	f12.SetPos(-92.5, 20, -35);
	f12.color.r = 0;
	f12.color.g = 1;
	f12.color.b = 0;
	f12.Render();

	Cube f13(10, 0.5, 45);
	f13.SetPos(-100, 20, -62.5);
	f13.color.r = 0;
	f13.color.g = 1;
	f13.color.b = 0;
	f13.Render();

	Cube f14(55, 0.5, 10);
	f14.SetPos(-50, 13.3, -80);
	f14.color.r = 0;
	f14.color.g = 1;
	f14.color.b = 0;
	f14.Render();

	//Water

	Cube w1(90, 1, 10);
	w1.SetPos(-50, 20, -80);
	w1.color.r = 0;
	w1.color.g = 1;
	w1.color.b = 256;
	w1.Render();
	
	Cube w2(65, 0.5, 100);
	w2.SetPos(-37.5, 19, -25);
	w2.color.r = 0;
	w2.color.g = 1;
	w2.color.b = 256;
	w2.Render();

	Cube sand(25, 1, 25);
	sand.SetPos(-37.5, 19, -25);
	sand.color.r = 1;
	sand.color.g = 1;
	sand.color.b = 0;
	sand.Render();

	Cube sand2(10, 1, 10);
	sand2.SetPos(-20, 19, -25);
	sand2.color.r = 1;
	sand2.color.g = 1;
	sand2.color.b = 0;
	sand2.Render();

	Cylinder tree1(0.4, 8);
	tree1.SetPos(-32.5, 24, -28);
	tree1.SetRotation(90, { 0, 0, 1 });
	tree1.color.r = 0;
	tree1.color.g = 0;
	tree1.color.b = 0;
	tree1.Render();

	Cube tree2(6, 1, 6);
	tree2.SetPos(-32.5, 26, -28);
	tree2.color.r = 0;
	tree2.color.g = 1;
	tree2.color.b = 0;
	tree2.Render();

	Cube tree3(4, 1, 4);
	tree3.SetPos(-32.5, 28, -28);
	tree3.color.r = 0;
	tree3.color.g = 1;
	tree3.color.b = 0;
	tree3.Render();

	Cube tree4(5, 1, 5);
	tree4.SetPos(-32.5, 27, -28);
	tree4.color.r = 0;
	tree4.color.g = 1;
	tree4.color.b = 0;
	tree4.Render();

	Cube w3(25, 0.5, 35);
	w3.SetPos(-82.5, 19, -57.5);
	w3.color.r = 0;
	w3.color.g = 1;
	w3.color.b = 256;
	w3.Render();

	Cube w4(40, 0.5, 45);
	w4.SetPos(-25, 19, 42.5);
	w4.color.r = 0;
	w4.color.g = 1;
	w4.color.b = 256;
	w4.Render();

	Cube w5(10, 0.5, 30);
	w5.SetPos(-40, 19, 80);
	w5.color.r = 0;
	w5.color.g = 1;
	w5.color.b = 256;
	w5.Render();

	Cube w6(50, 0.5, 10);
	w6.SetPos(-60, 19, 90);
	w6.color.r = 0;
	w6.color.g = 1;
	w6.color.b = 256;
	w6.Render();

	Cube w7(5, 0.5, 30);
	w7.SetPos(-82.5, 19, 70);
	w7.color.r = 0;
	w7.color.g = 1;
	w7.color.b = 256;
	w7.Render();
		
	//Limits circuit
	Cube r1(0.5, 2, 110);
	r1.SetPos(5, 20, 20);
	r1.color.r = 1;
	r1.color.g = 0;
	r1.color.b = 0;
	r1.Render();
	
	Cube r2(0.5, 2, 140);
	r2.SetPos(-5, 20, -5);
	r2.color.r = 1;
	r2.color.g = 0;
	r2.color.b = 0;
	r2.Render();

	Cube r3(30, 2, 0.5);
	r3.SetPos(-10, 20, 75);
	r3.color.r = 1;
	r3.color.g = 0;
	r3.color.b = 0;
	r3.Render();

	Cube r4(30, 2, 0.5);
	r4.SetPos(-20, 20, 65);
	r4.color.r = 1;
	r4.color.g = 0;
	r4.color.b = 0;
	r4.Render();

	Cube r5(0.5, 2, 30);
	r5.SetPos(-35, 20, 80);
	r5.color.r = 1;
	r5.color.g = 0;
	r5.color.b = 0;
	r5.Render();
	
	Cube r6(0.5, 2, 30);
	r6.SetPos(-25, 20, 90);
	r6.color.r = 1;
	r6.color.g = 0;
	r6.color.b = 0;
	r6.Render();

	Cube r7(50, 2, 0.5);
	r7.SetPos(-60, 20, 95);
	r7.color.r = 1;
	r7.color.g = 0;
	r7.color.b = 0;
	r7.Render();
	
	Cube r8(70, 2, 0.5);
	r8.SetPos(-60, 20, 105);
	r8.color.r = 1;
	r8.color.g = 0;
	r8.color.b = 0;
	r8.Render();

	Cube r9(0.5, 2, 40);
	r9.SetPos(-85, 20, 75);
	r9.color.r = 1;
	r9.color.g = 0;
	r9.color.b = 0;
	r9.Render();

	Cube r10(0.5, 2, 60);
	r10.SetPos(-95, 20, 75);
	r10.color.r = 1;
	r10.color.g = 0;
	r10.color.b = 0;
	r10.Render();

	Cube r11(5, 2, 0.5);
	r11.SetPos(-82.5, 20, 55);
	r11.color.r = 1;
	r11.color.g = 0;
	r11.color.b = 0;
	r11.Render();

	Cube r12(25, 2, 0.5);
	r12.SetPos(-82.5, 20, 45);
	r12.color.r = 1;
	r12.color.g = 0;
	r12.color.b = 0;
	r12.Render();

	Cube r13(0.5, 2, 30);
	r13.SetPos(-80, 20, 70);
	r13.color.r = 1;
	r13.color.g = 0;
	r13.color.b = 0;
	r13.Render();

	Cube r14(0.5, 2, 30);
	r14.SetPos(-70, 20, 60);
	r14.color.r = 1;
	r14.color.g = 0;
	r14.color.b = 0;
	r14.Render();

	Cube r15(35, 2, 0.5);
	r15.SetPos(-62.5, 20, 85);
	r15.color.r = 1;
	r15.color.g = 0;
	r15.color.b = 0;
	r15.Render();

	Cube r16(15, 2, 0.5);
	r16.SetPos(-62.5, 20, 75);
	r16.color.r = 1;
	r16.color.g = 0;
	r16.color.b = 0;
	r16.Render();

	Cube r17(0.5, 2, 40);
	r17.SetPos(-55, 20, 55);
	r17.color.r = 1;
	r17.color.g = 0;
	r17.color.b = 0;
	r17.Render();

	Cube r18(0.5, 2, 60);
	r18.SetPos(-45, 20, 55);
	r18.color.r = 1;
	r18.color.g = 0;
	r18.color.b = 0;
	r18.Render();

	Cube r19(25, 2, 0.5);
	r19.SetPos(-67.5, 20, 35);
	r19.color.r = 1;
	r19.color.g = 0;
	r19.color.b = 0;
	r19.Render();

	Cube r20(25, 2, 0.5);
	r20.SetPos(-57.5, 20, 25);
	r20.color.r = 1;
	r20.color.g = 0;
	r20.color.b = 0;
	r20.Render();

	Cube r21(0.5, 2, 65);
	r21.SetPos(-80, 20, 2.5);
	r21.color.r = 1;
	r21.color.g = 0;
	r21.color.b = 0;
	r21.Render();

	Cube r22(0.5, 2, 65);
	r22.SetPos(-70, 20, -7.5);
	r22.color.r = 1;
	r22.color.g = 0;
	r22.color.b = 0;
	r22.Render();

	Cube r23(25, 2, 0.5);
	r23.SetPos(-82.5, 20, -40);
	r23.color.r = 1;
	r23.color.g = 0;
	r23.color.b = 0;
	r23.Render();

	Cube r24(25, 2, 0.5);
	r24.SetPos(-92.5, 20, -30);
	r24.color.r = 1;
	r24.color.g = 0;
	r24.color.b = 0;
	r24.Render();

	Cube r25(0.5, 2, 55);
	r25.SetPos(-105, 20, -57.5);
	r25.color.r = 1;
	r25.color.g = 0;
	r25.color.b = 0;
	r25.Render();

	Cube r26(0.5, 2, 35);
	r26.SetPos(-95, 20, -57.5);
	r26.color.r = 1;
	r26.color.g = 0;
	r26.color.b = 0;
	r26.Render();

	Cube r27(90, 8, 0.5);
	r27.SetPos(-50, 17, -75);
	r27.color.r = 1;
	r27.color.g = 0;
	r27.color.b = 0;
	r27.Render();

	Cube r28(110, 8, 0.5);
	r28.SetPos(-50, 17, -85);
	r28.color.r = 1;
	r28.color.g = 0;
	r28.color.b = 0;
	r28.Render();

	Cube r29(0.5, 6, 15);
	r29.SetPos(5, 22, -77.5);
	r29.color.r = 1;
	r29.color.g = 0;
	r29.color.b = 0;
	r29.Render();

	//Rampes
	Cube ramp1(10, 1, 10);
	ramp1.SetPos(-50, 20, 100);
	ramp1.SetRotation(15, { 0, 0, -1 });
	ramp1.color.r = 0;
	ramp1.color.g = 1;
	ramp1.color.b = 0;
	ramp1.Render();

	Cube ramp2(20, 0.5, 10);
	ramp2.SetPos(-86, 16.6, -80);
	ramp2.SetRotation(20, { 0, 0, -1 });
	ramp2.color.r = 0;
	ramp2.color.g = 1;
	ramp2.color.b = 0;
	ramp2.Render();

	Cube ramp3(20, 0.5, 10);
	ramp3.SetPos(-14, 16.7, -80);
	ramp3.SetRotation(20, { 0, 0, 1 });
	ramp3.color.r = 0;
	ramp3.color.g = 1;
	ramp3.color.b = 0;
	ramp3.Render();

	//Terrain

	Cube t1(20, 0.5, 110);
	t1.SetPos(15, 20, 20);
	t1.color.r = 1;
	t1.color.g = 0;
	t1.color.b = 1;
	t1.Render();

	Cube t2(120, 0.5, 20);
	t2.SetPos(-35, 20, 115);
	t2.color.r = 1;
	t2.color.g = 0;
	t2.color.b = 1;
	t2.Render();

	Cube t3(50, 0.5, 30);
	t3.SetPos(0, 20, 90);
	t3.color.r = 1;
	t3.color.g = 0;
	t3.color.b = 1;
	t3.Render();

	Cube t4(130, 0.5, 20);
	t4.SetPos(-40, 20, -95);
	t4.color.r = 1;
	t4.color.g = 0;
	t4.color.b = 1;
	t4.Render();

	Cube t5(20, 0.5, 75);
	t5.SetPos(-115, 20, -67.5);
	t5.color.r = 1;
	t5.color.g = 0;
	t5.color.b = 1;
	t5.Render();

	Cube t6(45, 0.5, 75);
	t6.SetPos(-102.5, 20, 7.5);
	t6.color.r = 1;
	t6.color.g = 0;
	t6.color.b = 1;
	t6.Render();

	Cube t7(20, 0.5, 80);
	t7.SetPos(-105, 20, 85);
	t7.color.r = 1;
	t7.color.g = 0;
	t7.color.b = 1;
	t7.Render();

	Cube t8(25, 0.5, 10);
	t8.SetPos(-67.5, 20, 40);
	t8.color.r = 1;
	t8.color.g = 0;
	t8.color.b = 1;
	t8.Render();

	Cube t9(15, 0.5, 30);
	t9.SetPos(-62.5, 20, 60);
	t9.color.r = 1;
	t9.color.g = 0;
	t9.color.b = 1;
	t9.Render();

	Cube t10(20, 0.5, 10);
	t10.SetPos(15, 20, -80);
	t10.color.r = 1;
	t10.color.g = 0;
	t10.color.b = 1;
	t10.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2 == sensorsorra) {
		onsand = true;
	}
	if (body2 == sensorgel) {
		onice = true;
	}
	if (body2 == sensoraigua) {
		onwater = true;
	}
	if (body2 == sensorvent) {
		onfan = true;
		canwin = true;
	}
	if (body2 == sensormeta) {
		onwin = true;
	}
}