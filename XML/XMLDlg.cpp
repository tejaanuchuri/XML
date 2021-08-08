
// XMLDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "XML.h"
#include "XMLDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CXMLDlg dialog



CXMLDlg::CXMLDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XML_DIALOG, pParent)
	, age(_T(""))
	, empid(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXMLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AGE, age);
	DDX_Text(pDX, IDC_EDIT_EMPID, empid);
	DDX_Control(pDX, IDC_LIST_LISTVIEWCONTROL, emp_list);
}

BEGIN_MESSAGE_MAP(CXMLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CXMLDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CXMLDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CXMLDlg message handlers

BOOL CXMLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXMLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXMLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXMLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CXMLDlg::remove_spaces(CString s)
{
	s.TrimRight();
	s.TrimLeft();
	return s;
}

bool CXMLDlg::isvalidxml(vector<CString>& v)
{
	//MessageBox(L"Enter isvalidxml");
	stack<CString> s;
	for (int i = 0; i < v.size(); i++) {
		if (isstarttag(v[i])) {
			s.push(stagname(v[i]));
			//MessageBox(stagname(v[i]));
		}
		else if (isendtag(v[i])) {
			CString temp = s.top();
			if ((ismatchingtagname(temp, etagname(v[i])))) {
				s.pop();
			}
			//MessageBox(etagname(v[i]));
		}
	}
	return s.empty();
}



bool CXMLDlg::isstarttag(CString s)
{
	int n = s.GetLength();
	for (int i = 0; i < s.GetLength(); i++) {
		if (s[0] != '<') {
			return false;
		}
		if (s[1] == '/') {
			return false;
		}
		if (s[n - 1] != '>') {
			return false;
		}
	}
	return true;
	/*int l = s.GetLength();
	if (l <= 2)
		return false;

	if (s[0] != '<') {
		return false;
	}
	if (s[1] == '/') {
		return false;
	}

	if (s[l - 1] != '>') {
		return false;
	}
	return true;*/

}

bool CXMLDlg::isendtag(CString s)
{
	int l = s.GetLength();
	if (l <= 2)
		return false;
	if (s[0] != '<')
		return false;
	if (s[1] != '/')
		return false;
	if (s[l - 1] != '>')
		return false;
	return true;
}

CString CXMLDlg::stagname(CString s)
{
	CString temp;
	temp.Empty();
	for (int i = 1; i < s.GetLength() - 1; i++) {
		temp.AppendChar(s[i]);
	}
	return temp;
}

CString CXMLDlg::etagname(CString s)
{
	CString temp;
	temp.Empty();
	for (int i = 2; i < s.GetLength() - 1; i++) {
		temp.AppendChar(s[i]);
	}
	return temp;
}

void CXMLDlg::m_ResetListControl()
{
	emp_list.DeleteAllItems();
	int iNbrOfColumns = 0, i;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)emp_list.GetDlgItem(0);
	if (pHeader) {
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (i = iNbrOfColumns; i >= 0; i--) {
		emp_list.DeleteColumn(i);
	}
}

bool CXMLDlg::ismatchingtagname(CString s, CString d)
{
	if (s.GetLength() >= d.GetLength()) {
		for (int i = 0; i < d.GetLength(); i++) {
			if (s[i] != d[i]) {
				return false;
			}
		}
	}
	else {
		return false;
	}
	return true;
}

void CXMLDlg::OnBnClickedButtonSave()
{
	UpdateData(TRUE);
	CEMP emp;
	CStdioFile file;
	file.Open(L"Emp.xml", CStdioFile::modeCreate | CStdioFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	file.WriteString(L"<Employee>");
	//file.WriteString(_T("\n"));
	file.WriteString(L"<id>" + empid + L"</id>");
	file.WriteString(L"<Age>" + age + L"</Age>");
	file.WriteString(L"</Employee>");
	ar.Close();
}

void CXMLDlg::OnBnClickedButtonOpen()
{
	CString sFilter = _T("XML Files (*.xml)|*.xml");

	CFileDialog dlg(TRUE, _T("*.xml"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, sFilter, this);

	if (dlg.DoModal() == IDOK)
	{
		CString fullPathName = dlg.GetPathName();
		CStdioFile file;

		file.Open(fullPathName, CStdioFile::modeRead | CStdioFile::typeText);

		CString sl;
		CString chReadString;
		vector<CString> v;
		vector<CString> out;
		v.clear();
		sl.Empty();
		chReadString.Empty();
		int flag = 1;
		while (file.ReadString(sl))
		{
			sl.TrimLeft();
			sl.TrimRight();
			chReadString += sl;
		}

		file.Close();
		CString temp;
		CString hold = chReadString;
		for (long long int i = 0; i < hold.GetLength(); i++) {
			if (hold[i] == '<') {
				if (temp.IsEmpty()) {
					temp.AppendChar(hold[i]);
				}
				else {
					v.push_back(temp);
					temp.Empty();
					temp.AppendChar(hold[i]);
				}
			}
			else if (hold[i] != '>') {
				temp.AppendChar(hold[i]);
			}
			else if ((hold[i] == '>') && (temp[0] == '<')) {
				temp.AppendChar(hold[i]);
				v.push_back(temp);
				temp.Empty();
			}
			else if ((hold[i] == '>') && (temp[0] != '<')) {
				v.push_back(temp);
				temp.Empty();
			}
		}
		hold.Empty();
		flag = 0;
		for (vector<CString>::iterator i = v.begin(); i != v.end(); i++) {
			*i = remove_spaces(*i);
			CString t = *i;

			for (unsigned int j = 0; j < t.GetLength(); j++) {
				if (t[j] != ' ') {
					flag = 1;
				}
			}
			if (flag == 1) {
				out.push_back(t);
				flag = 0;
			}
			//MessageBox(t);
			//CString x;
			//x.Format(_T(" = %d"), t.GetLength());
			//t = t + x;
			//MessageBox(t);
		}
		v.clear();
		for (vector<CString>::iterator k = out.begin(); k != out.end(); k++) {
			*k = remove_spaces(*k);
			CString t = *k;
			/*for (unsigned int j = 0; j < t.GetLength(); j++) {
				if (t[j] != ' ') {
					flag = 1;
				}
			}
			if (flag == 0) {
				v.erase(k);
			}*/
			//MessageBox(t);
			CString x;

			x.Format(_T(" = %d"), t.GetLength());
			t = t + x;
			//MessageBox(t);
		}
		if (isvalidxml(out)) {
			MessageBox(L"It Is valid xml file");
		}
		else {
			MessageBox(L"It Is not a valid xml file");
		}
		vector<pair<CString, CString>> res;
		vector< vector<pair<CString, CString>>> emp;
		stack<CString> s;
		CString temp_value;
		temp.Empty();
		temp_value.Empty();
		for (int i = 0; i < out.size(); i++) {
			if (isstarttag(out[i])) {
				s.push(stagname(out[i]));
			}
			else if (isendtag(out[i])) {
				temp = s.top();
				if ((ismatchingtagname(temp, etagname(out[i]))) && !(temp_value.IsEmpty())) {
					res.push_back(make_pair(etagname(out[i]), temp_value));
					temp.Empty();
					temp_value.Empty();
					s.pop();
				}
				else if (temp == etagname(out[i])) {
					emp.push_back(res);
					res.clear();
				}
			}
			else {
				temp_value.Append(out[i]);
			}
		}

		UpdateData(FALSE); // flow direction database -> ui

		/*CString e_id;
		CString e_age;
		CString e_title;
		CString e_firstname;
		CString e_lastname;
		CString e_gender;
		CString e_phonenumber;
		CString e_email;
		CString e_birthdate;
		CString e_address;
		CString e_jobtitle;
		CString e_salary;
		CString e_hiredate;
		CString e_yrsofexp;
		*/
		int iRec = 0;
		m_ResetListControl();
		ListView_SetExtendedListViewStyle(emp_list, LVS_EX_FULLROWSELECT);
		for (int i = 0; i < emp[0].size(); i++) {
			emp_list.InsertColumn(i, emp[0][i].first, LVCFMT_CENTER, 120);
		}
		/*emp_list.InsertColumn(
			0,
			L"EmpID",
			LVCFMT_LEFT,
			70);
		emp_list.InsertColumn(1, L"HireDate", LVCFMT_LEFT, 100);
		emp_list.InsertColumn(2, L"YearsOfExp", LVCFMT_LEFT, 100);

		emp_list.InsertColumn(3, L"Title", LVCFMT_CENTER, 90);
		emp_list.InsertColumn(4, L"Age", LVCFMT_LEFT, 70);
		emp_list.InsertColumn(5, L"FirstName", LVCFMT_CENTER, 130);
		emp_list.InsertColumn(6, L"LastName", LVCFMT_LEFT, 130);
		emp_list.InsertColumn(7, L"Gender", LVCFMT_CENTER, 120);
		emp_list.InsertColumn(8, L"MobilePhone", LVCFMT_LEFT, 160);
		emp_list.InsertColumn(9, L"EMail", LVCFMT_CENTER, 230);
		emp_list.InsertColumn(13, L"BirthDate", LVCFMT_LEFT, 100);
		emp_list.InsertColumn(10, L"Address", LVCFMT_CENTER, 180);
		emp_list.InsertColumn(11, L"JobTitle", LVCFMT_LEFT, 100);
		emp_list.InsertColumn(12, L"Salary", LVCFMT_CENTER, 100);*/

		for (int i = 0; i < emp.size(); i++) {
			vector<pair<CString, CString>> record = emp[i];
			for (int j = 0; j < record.size(); j++) {
				if (j == 0) {
					iRec = emp_list.InsertItem(0, record[j].second, 0);
				}
				else {
					emp_list.SetItemText(0, j, record[j].second);
				}
			}
			record.clear();
		}
		/* Insert values into the list control
		iRec = emp_list.InsertItem(0, e_id, 0);
		emp_list.SetItemText(0, 1, e_hiredate);
		emp_list.SetItemText(0, 2, e_yrsofexp);
		emp_list.SetItemText(0, 3, e_title);
		emp_list.SetItemText(0, 4, e_age);
		emp_list.SetItemText(0, 5, e_firstname);
		emp_list.SetItemText(0, 6, e_lastname);
		emp_list.SetItemText(0, 7, e_gender);
		emp_list.SetItemText(0, 8, e_phonenumber);
		emp_list.SetItemText(0, 9, e_email);
		emp_list.SetItemText(0, 10, e_birthdate);
		emp_list.SetItemText(0, 11, e_address);
		emp_list.SetItemText(0, 12, e_jobtitle);
		emp_list.SetItemText(0, 13, e_salary);*/

	}

}
