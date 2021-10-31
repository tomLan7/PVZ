#include "PVZHeader.h"
PVZBase::PVZBase()
{
}
bool PVZBase::init()
{
	if (!Unit::init()) {
		return false;
	}


	return true;
}

PVZBase::~PVZBase()
{
}
