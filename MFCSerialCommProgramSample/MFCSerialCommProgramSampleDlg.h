
// MFCSerialCommProgramSampleDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CommThread.h"

// CMFCSerialCommProgramSampleDlg dialog
class CMFCSerialCommProgramSampleDlg : public CDialogEx
{
// Construction
public:
	CMFCSerialCommProgramSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCSERIALCOMMPROGRAMSAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CComboBox m_Combo_PortOpen;
	CComboBox m_Combo_BaudRate;
	CEdit m_Edit_AsciiSendData;
	CEdit m_Edit_AsciiRecvData;
	
public:
	CCommThread SerialPort;

public:
	
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonAsciiSend();
	afx_msg long OnCommunication(WPARAM wParam, LPARAM lParam);

public:
	CString byIndexComPort(int xPort);
	DWORD byIndexBaud(int xBaud);
	BYTE byIndexData(int xData);
	BYTE byIndexStop(int xStop);
	BYTE byIndexParity(int xParity);
};
