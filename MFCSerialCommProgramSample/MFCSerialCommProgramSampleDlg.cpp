
// MFCSerialCommProgramSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSerialCommProgramSample.h"
#include "MFCSerialCommProgramSampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSerialCommProgramSampleDlg dialog




CMFCSerialCommProgramSampleDlg::CMFCSerialCommProgramSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCSerialCommProgramSampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSerialCommProgramSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORTNAME, m_Combo_PortOpen);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_Combo_BaudRate);
	DDX_Control(pDX, IDC_EDIT_ASCII_SEND_DATA, m_Edit_AsciiSendData);
	DDX_Control(pDX, IDC_EDIT_ASCII_RECV_DATA, m_Edit_AsciiRecvData);
}

BEGIN_MESSAGE_MAP(CMFCSerialCommProgramSampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCSerialCommProgramSampleDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMFCSerialCommProgramSampleDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_ASCII_SEND, &CMFCSerialCommProgramSampleDlg::OnBnClickedButtonAsciiSend)
	ON_MESSAGE(WM_COMM_READ, OnCommunication)
END_MESSAGE_MAP()


// CMFCSerialCommProgramSampleDlg message handlers

BOOL CMFCSerialCommProgramSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCSerialCommProgramSampleDlg::OnPaint()
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
HCURSOR CMFCSerialCommProgramSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CMFCSerialCommProgramSampleDlg::byIndexComPort(int xPort)
{
	CString PortName;
	switch(xPort)
	{
		case 0:		PortName = "COM1"; 			break;
		case 1:		PortName = "COM2";			break;
		case 2:		PortName = "COM3"; 			break;
		case 3:		PortName = "COM4";			break;
		case 4:		PortName = "\\\\.\\COM5"; 	break;
		case 5:		PortName = "\\\\.\\COM6";	break;
		case 6:		PortName = "\\\\.\\COM7"; 	break;
		case 7:		PortName = "\\\\.\\COM8";	break;
		case 8:		PortName = "\\\\.\\COM9"; 	break;
		case 9:		PortName = "\\\\.\\COM10";	break;
	}

	return PortName;
}

DWORD CMFCSerialCommProgramSampleDlg::byIndexBaud(int xBaud)
{
	DWORD dwBaud;
	switch(xBaud)
	{
		case 0:		dwBaud = CBR_4800;		break;
		case 1:		dwBaud = CBR_9600;		break;
		case 2:		dwBaud = CBR_14400;		break;
		case 3:		dwBaud = CBR_19200;		break;
		case 4:		dwBaud = CBR_38400;		break;
		case 5:		dwBaud = CBR_56000;		break;
		case 6:		dwBaud = CBR_57600;		break;
		case 7:		dwBaud = CBR_115200;	break;
	}

	return dwBaud;
}

BYTE CMFCSerialCommProgramSampleDlg::byIndexData(int xData)
{
	BYTE byData;
	switch(xData)
	{
		case 0 :	byData = 5;			break;
		case 1 :	byData = 6;			break;
		case 2 :	byData = 7;			break;
		case 3 :	byData = 8;			break;
	}
	return byData;
}

BYTE CMFCSerialCommProgramSampleDlg::byIndexStop(int xStop)
{
	BYTE byStop;
	if(xStop == 0)
	{
		byStop = ONESTOPBIT;
	}
	else
	{
		byStop = TWOSTOPBITS;
	}
	return byStop;
}

BYTE CMFCSerialCommProgramSampleDlg::byIndexParity(int xParity)
{
	BYTE byParity;
	switch(xParity)
	{
		case 0 :	byParity = NOPARITY;	break;
		case 1 :	byParity = ODDPARITY;	break;
		case 2 :	byParity = EVENPARITY;	break;
	}

	return byParity;
}

void CMFCSerialCommProgramSampleDlg::OnBnClickedButtonOpen()
{
	// TODO: Add your control notification handler code here
	// 패리티 비드, 스탑 비트, 데이터 사이즈등을 결정할때는 이 함수를 사용함
	//SerialPort.OpenPort(byIndexComPort(8), byIndexBaud(7), byIndexData(3), byIndexStop(0), byIndexParity(0), m_hWnd);
	CString str_baudrate;
	m_Combo_BaudRate.GetWindowTextA(str_baudrate);
	SerialPort.OpenPort(byIndexComPort(m_Combo_PortOpen.GetCurSel()),_ttoi(str_baudrate), m_hWnd);
}


void CMFCSerialCommProgramSampleDlg::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here
	if (SerialPort.m_bConnected == TRUE)
	{
		SerialPort.ClosePort();
	}
}


void CMFCSerialCommProgramSampleDlg::OnBnClickedButtonAsciiSend()
{
	// TODO: Add your control notification handler code here
	if(SerialPort.m_bConnected == FALSE) return;
	CString	str;
	m_Edit_AsciiSendData.GetWindowTextA(str);
	SerialPort.WriteComm((BYTE *)(LPCSTR)str, str.GetLength());
}

long CMFCSerialCommProgramSampleDlg::OnCommunication(WPARAM wParam, LPARAM lParam)
{
	int serial_queue_size = SerialPort.m_QueueRead.GetSize();
	int i;
	byte temp[4096];

	memset(temp, 0, sizeof(temp));
	for(i = 0 ; i < serial_queue_size ; i++ )
	{
		SerialPort.m_QueueRead.GetByte(temp + i);
	}
	CString str;
	m_Edit_AsciiRecvData.GetWindowTextA(str);
	str.AppendFormat("%s",temp);
	m_Edit_AsciiRecvData.SetWindowTextA(str);
	//TRACE(str);
	return 1;
}