#include "pch.h"
#include "CEMP.h"

IMPLEMENT_SERIAL(CEMP, CObject, 0)
CString CEMP::remove_spaces(CString s)
{
	return CString();
}
CEMP::CEMP()
{
}

CEMP::~CEMP(void)
{
}

void CEMP::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << empid << age;
	}
	else
	{
		ar >> empid >> age;
	}
}
