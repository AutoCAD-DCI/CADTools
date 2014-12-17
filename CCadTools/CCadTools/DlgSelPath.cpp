// DlgSelPath.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgSelPath.h"


// CDlgSelPath 对话框

IMPLEMENT_DYNAMIC(CDlgSelPath, CAcUiDialog)

CDlgSelPath::CDlgSelPath(CWnd* pParent /*=NULL*/)
	: CAcUiDialog(CDlgSelPath::IDD, pParent)
{

}

CDlgSelPath::~CDlgSelPath()
{
}

void CDlgSelPath::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_tree);
}


BEGIN_MESSAGE_MAP(CDlgSelPath, CAcUiDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CDlgSelPath::OnTvnSelchangedTree)
END_MESSAGE_MAP()


// CDlgSelPath 消息处理程序

BOOL CDlgSelPath::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	TCHAR  szWorkDir[MAX_PATH];

	m_tree.DisplayTree( NULL,m_bSelFile);

	m_tree.SetSelPath( m_sPath );

	SetWindowText(m_sTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSelPath::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	m_sPath=m_tree.GetFullPath(pNMTreeView->itemNew.hItem);
	*pResult = 0;
}

void CDlgSelPath::SetTitle(const TCHAR* pTitle)
{
	m_sTitle = pTitle;
}

BOOL CDlgSelPath::GetIsSelectFile() const
{
	return this->m_bSelFile;
}

void CDlgSelPath::SetIsSelectFile(BOOL val)
{
	this->m_bSelFile = val;
}

CString CDlgSelPath::GetSelectPath() const
{
	return this->m_sPath;
}

void CDlgSelPath::SetStartPath(CString val)
{
	this->m_sPath = val;
}