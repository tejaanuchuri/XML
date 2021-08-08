
// XMLDlg.h : header file
//

#include "CEMP.h"
#include <fstream>
#include <tchar.h>
#include <vector>
#include <string>
#include <stack>
using namespace std;
#pragma once

// CXMLDlg dialog
class CXMLDlg : public CDialogEx
{
	// Construction
public:
	CXMLDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XML_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CString remove_spaces(CString s);
	bool isvalidxml(vector<CString>& v);
	bool isstarttag(CString s);
	bool isendtag(CString s);
	CString stagname(CString s);
	CString etagname(CString s);
	void m_ResetListControl();
	bool ismatchingtagname(CString s, CString d);
	DECLARE_MESSAGE_MAP()
public:
	CString age;
	CString empid;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonOpen();
	CListCtrl emp_list;
};
