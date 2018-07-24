

// ProjectPayrollDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProjectPayroll.h"
#include "ProjectPayrollDlg.h"
#include "afxdialogex.h"
#include ".\projectpayrolldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

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


// CProjectPayrollDlg dialog



CProjectPayrollDlg::CProjectPayrollDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROJECTPAYROLL_DIALOG, pParent)
	
	, employeenbr(0)
	, hourlySalary(0)
	, monday1(0)
	, tuesday1(0)
	, wednesday1(0)
	, thursday1(0)
	, friday1(0)
	, saturday1(0)
	, sunday1(0)
	, monday2(0)
	, tuesday2(0)
	, wednesday2(0)
	, thursday2(0)
	, friday2(0)
	, saturday2(0)
	, sunday2(0)
	, regularhours(0)
	, regularamount(0)
	, overtimehours(0)
	, overtimeamount(0)
	, totalearnings(0)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectPayrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, txtEmployeeNbr, employeenbr);
	DDX_Text(pDX, txtHourlySalary, hourlySalary);
	DDX_Control(pDX, txtStartingDate, startDate);
	DDX_Control(pDX, dtpEndDate, endDate);
	DDX_Text(pDX, txtMonday1, monday1);
	DDX_Text(pDX, txtTuesday1, tuesday1);
	DDX_Text(pDX, txtWednesday1, wednesday1);
	DDX_Text(pDX, txtThursday1, thursday1);
	DDX_Text(pDX, txtFriday1, friday1);
	DDX_Text(pDX, txtSaturday1, saturday1);
	DDX_Text(pDX, txtSunday1, sunday1);
	DDX_Text(pDX, txtMonday2, monday2);
	DDX_Text(pDX, txtTuesday2, tuesday2);
	DDX_Text(pDX, txtWednesday2, wednesday2);
	DDX_Text(pDX, txtThursday2, thursday2);
	DDX_Text(pDX, txtFriday2, friday2);
	DDX_Text(pDX, txtSaturday2, saturday2);
	DDX_Text(pDX, txtSunday2, sunday2);
	DDX_Text(pDX, txtRegularHours, regularhours);
	DDX_Text(pDX, txtRegularAmount, regularamount);
	DDX_Text(pDX, txtOvertimeHours, overtimehours);
	DDX_Text(pDX, txtOvertimeAmount, overtimeamount);
	DDX_Text(pDX, txtTotalEarnings, totalearnings);
	
}

BEGIN_MESSAGE_MAP(CProjectPayrollDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	
	ON_BN_CLICKED(IDCLOSE, &CProjectPayrollDlg::OnBnClickedClose)
	ON_BN_CLICKED(btnProcessIt, &CProjectPayrollDlg::OnBnClickedbtnprocessit)
END_MESSAGE_MAP()


// CProjectPayrollDlg message handlers

BOOL CProjectPayrollDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	

	// Add "About..." menu item to system menu.

	// Set the icon for this dialog. The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

							 // TODO: Add extra initialization here
	CTime today = CTime::GetCurrentTime();
	CTimeSpan tmeSpan(14, 0, 0, 0);
	CTime twoWeeksAgo = today - tmeSpan;

	this->startDate.SetTime(&twoWeeksAgo);

	return TRUE; // return TRUE unless you set the focus to a control

	
		}

void CProjectPayrollDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
}

void CProjectPayrollDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

HCURSOR CProjectPayrollDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon); 
}

void CProjectPayrollDlg::OnDtnCloseupdtpenddate(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CTime dteStart, dteEnd;

	// Get the starting date
	this->startDate.GetTime(dteStart);
	// Get the ending date
	this->endDate.GetTime(dteEnd);

	// Make sure the first day of the period is Monday
	if (dteStart.GetDayOfWeek() != 2)
	{
		AfxMessageBox(_T("The starting date you selected in invalid\n The time period should start on a Monday"));

		this->startDate.SetFocus();
	}

	// Find the number of days that separates the start and end
	CTimeSpan timeDifference = dteEnd - dteStart;
	LONGLONG fourteenDaysLater = timeDifference.GetDays();

	if ((dteEnd.GetDayOfWeek() != 1) || (fourteenDaysLater != 13))
	{
		AfxMessageBox(_T("The ending date you selected in invalid\n The time period should span 2 weeks on a Sunday"));

		this->endDate.SetFocus();
	}
}



void CProjectPayrollDlg::OnDtnDatetimechangeStartingdate(NMHDR * pNMHDR, LRESULT * pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	// Get the starting date
	CTime dteStart;

	this->startDate.GetTime(dteStart);

	// Find out if the user selected a day that is not Monday
	if (dteStart.GetDayOfWeek() != 2)
	{
		AfxMessageBox(_T("The date you selected in invalid\n The time period should start on a Monday"));
		this->startDate.SetFocus();
	}
}


void CProjectPayrollDlg::OnBnClickedClose()
{
	CDialogEx::OnClose();
	exit(0);

}


void CProjectPayrollDlg::OnBnClickedbtnprocessit()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	double monday1 = 0.00, tuesday1 = 0.00, wednesday1 = 0.00,
		thursday1 = 0.00, friday1 = 0.00, saturday1 = 0.00,
		sunday1 = 0.00, monday2 = 0.00, tuesday2 = 0.00,
		wednesday2 = 0.00, thursday2 = 0.00, friday2 = 0.00,
		saturday2 = 0.00, sunday2 = 0.00;
	double totalHoursWeek1, totalHoursWeek2;

	double regHours1 = 0.00, regHours2 = 0.00, ovtHours1 = 0.00, ovtHours2 = 0.00;
	double regAmount1 = 0.00, regAmount2 = 0.00, ovtAmount1 = 0.00, ovtAmount2 = 0.00;
	double regularHours, overtimeHours;
	double regularAmount, overtimeAmount, totalEarnings;

	double hourlySalary = 0.00;

	// Retrieve the hourly salary
	hourlySalary = this->hourlySalary;

	monday1 = this->monday1;
	tuesday1 = this->tuesday1;
	wednesday1 = this->wednesday1;
	thursday1 = this->thursday1;
	friday1 = this->friday1;
	saturday1 = this->saturday1;
	sunday1 = this->sunday1;

	monday2 = this->monday2;
	tuesday2 = this->tuesday2;
	wednesday2 = this->wednesday2;
	thursday2 = this->thursday2;
	friday2 = this->friday2;
	saturday2 = this->saturday2;
	sunday2 = this->sunday2;

	// Calculate the total number of hours for each week
	totalHoursWeek1 = monday1 + tuesday1 + wednesday1 + thursday1 +
		friday1 + saturday1 + sunday1;
	totalHoursWeek2 = monday2 + tuesday2 + wednesday2 + thursday2 +
		friday2 + saturday2 + sunday2;

	// The overtime is paid time and half
	double ovtSalary = hourlySalary * 1.5;

	// If the employee worked under 40 hours, there is no overtime
	if (totalHoursWeek1 < 40)
	{
		regHours1 = totalHoursWeek1;
		regAmount1 = hourlySalary * regHours1;
		ovtHours1 = 0.00;
		ovtAmount1 = 0.00;
	} // If the employee worked over 40 hours, calculate the overtime
	else if (totalHoursWeek1 >= 40)
	{
		regHours1 = 40;
		regAmount1 = hourlySalary * 40;
		ovtHours1 = totalHoursWeek1 - 40;
		ovtAmount1 = ovtHours1 * ovtSalary;
	}

	if (totalHoursWeek2 < 40)
	{
		regHours2 = totalHoursWeek2;
		regAmount2 = hourlySalary * regHours2;
		ovtHours2 = 0.00;
		ovtAmount2 = 0.00;
	}
	else if (totalHoursWeek2 >= 40)
	{
		regHours2 = 40;
		regAmount2 = hourlySalary * 40;
		ovtHours2 = totalHoursWeek2 - 40;
		ovtAmount2 = ovtHours2 * ovtSalary;
	}

	regularHours = regHours1 + regHours2;
	overtimeHours = ovtHours1 + ovtHours2;
	regularAmount = regAmount1 + regAmount2;
	overtimeAmount = ovtAmount1 + ovtAmount2;
	totalEarnings = regularAmount + overtimeAmount;

	this->regularhours = regularHours;
	this->overtimehours= overtimeHours;
	this->regularamount = regularAmount;
	this->overtimeamount = overtimeAmount;

	this->totalearnings = totalEarnings;
	UpdateData(FALSE);
}