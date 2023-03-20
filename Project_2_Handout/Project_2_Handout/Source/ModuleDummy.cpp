#include "ModuleDummy.h"

#include <conio.h>

bool ModuleDummy::Init()
{
	LOG("Dummy Init!\n");

	return true;
}

update_status ModuleDummy::PreUpdate()
{
	LOG("Dummy PreUpdate!\n");

	if (_kbhit() && _getch() == 27)
		return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleDummy::Update()
{
	LOG("Dummy Update!\n");

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleDummy::PostUpdate()
{
	LOG("Dummy PostUpdate!\n");

	return update_status::UPDATE_CONTINUE;
}

bool ModuleDummy::CleanUp()
{
	LOG("Dummy CleanUp!\n");

	return true;
}