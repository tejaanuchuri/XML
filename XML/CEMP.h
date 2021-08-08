#pragma once
#include <afx.h>
class CEMP :
	public CObject
{
public:
	CString empid;
	CString age;
	CString tag;
	CString remove_spaces(CString s);
	CEMP(void);
	~CEMP(void);
public:
	virtual void Serialize(CArchive& ar);
	DECLARE_SERIAL(CEMP);
};

