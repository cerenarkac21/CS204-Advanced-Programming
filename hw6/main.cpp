// MFCApplication2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg dialog



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication2Dlg::IDD, pParent)
	, groupedRadioButtons(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, input1);
	DDX_Control(pDX, IDC_EDIT2, input2);
	DDX_Control(pDX, IDC_EDIT3, input3);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Control(pDX, IDC_CHECK1, check);
	DDX_Control(pDX, IDC_COMBO1, comboBox);
	DDX_Control(pDX, IDC_BUTTON1, button);
	DDX_Radio(pDX, IDC_RADIO1, groupedRadioButtons);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication2Dlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CMFCApplication2Dlg message handlers

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	comboBox.SetCurSel(0);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication2Dlg::OnPaint()
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
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication2Dlg::OnBnClickedCheck1()
{
	if (check.GetCheck())
	{
		comboBox.EnableWindow(TRUE);
		input3.EnableWindow(TRUE);

	}
	else  // to make sure that the check is unchecked, enable the comboBox again.
	{
		comboBox.EnableWindow(FALSE);
		input3.EnableWindow(FALSE);
	}
}

int maxSize = 0;

void CMFCApplication2Dlg::OnBnClickedButton1()
{
	CString operand1, operand2, result, numBits;
	bool trueInputs = true;
	CDC *pDC = GetDC();
	CFont *pOldFont = pDC->SelectObject(GetFont());
	CSize cz;

	input1.GetWindowTextW(operand1);
	input2.GetWindowTextW(operand2);

	if (operand1.IsEmpty() || operand2.IsEmpty()){
		result =  _T("At least one operand was not entered.");
		trueInputs = false;
	}

	if (check.GetCheck() == 1)  // shift is selected
	{
		input3.GetWindowTextW(numBits); // take the 3rd input
		if (numBits.IsEmpty())
		{
			result =  _T("Specify how many bits you want to shift");
			trueInputs = false;
		}
	}

	if (!result.IsEmpty())
	{
		list.AddString(result);
		cz = pDC->GetTextExtent(result);
		if(cz.cx > maxSize){
			maxSize = cz.cx;
		}
		list.SetHorizontalExtent(maxSize);
	}
	
	if (trueInputs)
	{
		// convert input1 and input2 to unsigned int
		unsigned int myOperand1, myOperand2;
		myOperand1 = _tcstoul(operand1,nullptr,10);
		myOperand2 = _tcstoul(operand2,nullptr,10);

		if (check.GetCheck() == 1)  // shift is selected
		{
			int selectedDirIdx = comboBox.GetCurSel();
			int howManyBitsInt = _ttoi(numBits);
		
			if (selectedDirIdx == 0)  // left is selected
			{
				myOperand1 = myOperand1 << howManyBitsInt;
				myOperand2 = myOperand2 << howManyBitsInt;
			}
			else if (selectedDirIdx == 1){ // right is selected
				myOperand1 = myOperand1 >> howManyBitsInt;
				myOperand2 = myOperand2 >> howManyBitsInt;
			}
		}
		CString myOp1, myOp2;
		UpdateData(TRUE);
		if ( groupedRadioButtons == 0)  // AND is selected  
		{
			result.Format(_T("%u"), myOperand1 & myOperand2); // do the operation and convert the result to CString
			myOp1.Format(_T("%u"), myOperand1);  // convert unsigned int to CString
			myOp2.Format(_T("%u"), myOperand2);
			result = myOp1 + _T(" AND ") + myOp2 + _T(" = ") + result; 
			list.AddString(result);
			cz = pDC->GetTextExtent(result);
			if(cz.cx > maxSize){
				maxSize = cz.cx;
			}
		}

		else if ( groupedRadioButtons == 1) // OR is selected
		{
			result.Format(_T("%u"), myOperand1 | myOperand2);
			myOp1.Format(_T("%u"), myOperand1);
			myOp2.Format(_T("%u"), myOperand2);
			result = myOp1 + _T(" OR ") + myOp2 + _T(" = ") + result; 
			list.AddString(result);
			cz = pDC->GetTextExtent(result);
			if(cz.cx > maxSize){
				maxSize = cz.cx;
			}
		}

		else if (groupedRadioButtons == 2) // XOR is selected
		{
			result.Format(_T("%u"), myOperand1 ^ myOperand2);
			myOp1.Format(_T("%u"), myOperand1);
			myOp2.Format(_T("%u"), myOperand2);
			result = myOp1 + _T(" XOR ") + myOp2 + _T(" = ") + result; 
			list.AddString(result);
			cz = pDC->GetTextExtent(result);
			if(cz.cx > maxSize){
				maxSize = cz.cx;
			}
		}
	}
	list.SetHorizontalExtent(maxSize);
}

