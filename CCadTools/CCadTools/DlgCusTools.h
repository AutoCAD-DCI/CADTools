#pragma once


// CDlgCusTools �Ի���
#include "resource.h"
class CDlgCusTools : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgCusTools)

public:
	CDlgCusTools(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCusTools();

// �Ի�������
	enum { IDD = IDD_DLG_TOOLS };

	CString GetSelectOrgDirectory();
	CString GetSelectDestDirectory();

	void CollectOrgDbs(CStringArray &dbFiles);


	CAcUiColorComboBox   m_cmbColor;
	CButton m_btnSetColor;
	CButton m_btnDG;
	CProgressCtrl m_Progress;
	CStatic m_TextProgress;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBrowseChooseOrg();
	afx_msg void OnBnClickedBrowseChooseDest();
	afx_msg void OnBnClickedBtnBegin();
protected:
	virtual void PostNcDestroy();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();

	void Init();

	void Trans(CStringArray& strDbFiles);

	LRESULT  OnAcadKeepFocus (WPARAM, LPARAM);
};
