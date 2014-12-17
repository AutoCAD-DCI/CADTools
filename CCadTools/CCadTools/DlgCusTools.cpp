// DlgCusTools.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgCusTools.h"
#include "DlgSelPath.h"
#include "Utils.h"
#include "axlock.h"
// CDlgCusTools �Ի���

IMPLEMENT_DYNAMIC(CDlgCusTools, CAcUiDialog)

CDlgCusTools::CDlgCusTools(CWnd* pParent /*=NULL*/)
	: CAcUiDialog(CDlgCusTools::IDD, pParent)
{
}

CDlgCusTools::~CDlgCusTools()
{
}

void CDlgCusTools::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_SET_COLOR, m_btnSetColor);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_STATIC_ING, m_TextProgress);
	DDX_Control(pDX, IDC_COMBO_COLOR,m_cmbColor);
	DDX_Control(pDX,IDC_CHECK_DG,m_btnDG);
}


BEGIN_MESSAGE_MAP(CDlgCusTools, CAcUiDialog)
	ON_BN_CLICKED(IDC_BROWSE_CHOOSE_ORG, &CDlgCusTools::OnBnClickedBrowseChooseOrg)
	ON_BN_CLICKED(IDC_BROWSE_CHOOSE_DEST, &CDlgCusTools::OnBnClickedBrowseChooseDest)
	ON_BN_CLICKED(IDC_BTN_BEGIN, &CDlgCusTools::OnBnClickedBtnBegin)
	ON_MESSAGE( WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
END_MESSAGE_MAP()


// CDlgCusTools ��Ϣ�������

void CDlgCusTools::OnBnClickedBrowseChooseOrg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAcModuleResourceOverride ov;
	CDlgSelPath dlg;
	dlg.SetStartPath(CUtils::GetWorkingDirectory());
	dlg.SetIsSelectFile(FALSE);
	dlg.SetTitle(_T("ѡ����� *.dwg �ļ���Դ�ļ���"));

	if (dlg.DoModal() != IDOK)
		return;

	CString selectOrgPath = dlg.GetSelectPath();
	if (((CComboBox*)GetDlgItem(IDC_COMBO_ORG))->FindString(0, selectOrgPath) == CB_ERR)
	{
		int index = ((CComboBox*)GetDlgItem(IDC_COMBO_ORG))->AddString(selectOrgPath);
		((CComboBox*)GetDlgItem(IDC_COMBO_ORG))->SetCurSel(index);
	}
}

void CDlgCusTools::OnBnClickedBrowseChooseDest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAcModuleResourceOverride ov;
	CDlgSelPath dlg;
	dlg.SetStartPath(CUtils::GetWorkingDirectory());
	dlg.SetIsSelectFile(FALSE);
	dlg.SetTitle(_T("ѡ��Ҫ����ת�����ļ���Ŀ���ļ���"));

	if (dlg.DoModal() != IDOK)
		return;

	CString selectDestPath = dlg.GetSelectPath();
	if (((CComboBox*)GetDlgItem(IDC_COMBO_DEST))->FindString(0, selectDestPath) == CB_ERR)
	{
		int index = ((CComboBox*)GetDlgItem(IDC_COMBO_DEST))->AddString(selectDestPath);
		((CComboBox*)GetDlgItem(IDC_COMBO_DEST))->SetCurSel(index);
	}
}

void CDlgCusTools::OnBnClickedBtnBegin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AcAxDocLock lock;
	CString strOrgDir = this->GetSelectOrgDirectory();
	CString strDestDir = this->GetSelectDestDirectory();

	if (strOrgDir.IsEmpty()||strDestDir.IsEmpty())
	{
		MessageBox(_T("δѡ��Դ�ļ�·������Ŀ���ļ�·�������ʵ�����ԣ�"),_T("��ʾ"),MB_OK);
		return;
	}

	vector<CString> files;
	int nCount;// = CFilePath::GetAllFiles(files, directory, _T("dwg"), TRUE);	
	nCount = CUtils::GetAllFiles(files, strOrgDir,  _T("dwg"), TRUE);

	if (nCount == 0)
	{
		AfxMessageBox(_T("��ѡ�ļ���û��dwg�ļ�"));
		return;
	}

	CStringArray dbFiles;
	this->CollectOrgDbs(dbFiles);
	this->Trans(dbFiles);
}

void CDlgCusTools::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���

	CAcUiDialog::PostNcDestroy();
}

void CDlgCusTools::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	DestroyWindow();
}

BOOL CDlgCusTools::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
    Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgCusTools::Init()
{
	((CComboBox*)GetDlgItem(IDC_COMBO_FORMAT))->ResetContent();//����������������

	//CString seg = _T("ConvertType");
	//CString file = CFilePath::Combine(CEnvironment::GetWorkingDirectory(), _T("convertconfig.ini"));
	//	CString file = CFilePath::Combine(CEnvironment::GetProjectDirectory(), _T("convertconfig.ini"));
	//if (CFilePath::IsFileExist(file) == FALSE)
	//{
	((CComboBox*)GetDlgItem(IDC_COMBO_FORMAT))->InsertString(0, _T("AutoCAD 2007 ͼ�� (*.dwg) "));
	((CComboBox*)GetDlgItem(IDC_COMBO_FORMAT))->InsertString(1, _T("AutoCAD 2004/LT 2004 ͼ�� (*.dwg)"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FORMAT))->InsertString(2, _T("AutoCAD 2000/LT 2000 ͼ�� (*.dwg)"));
	((CComboBox*)GetDlgItem(IDC_COMBO_FORMAT))->InsertString(3, _T("AutoCAD R14/LT98/LT97 ͼ�� (*.dwg)"));
	//}
	//else
	//{
	//	List<CString> keys;
	//	List<CString> vals;
	//	CIniFile::GetSegValue(keys, vals, file, _T("ConvertType"));

	//	for (int i = 0; i < keys.Count(); ++i)
	//	{
	//		if (vals[i] == _T("1"))
	//			((CComboBox*)GetDlgItem(IDC_COMBO_CONVERT_TYPE))->InsertString(i, keys[i]);
	//	}
	//}

	((CComboBox*)GetDlgItem(IDC_COMBO_FORMAT))->SetCurSel(0);



	int nColor = 253;
	int nIndex = m_cmbColor.FindItemByColorIndex(nColor);
	if (nIndex < 0)
	{
		int nItem = -1;
		nItem = m_cmbColor.AddColorToMRU(nColor);
		m_cmbColor.SetCurSel(nItem);
	}
	else
	{
		m_cmbColor.SetCurSel(nIndex);
	}
    m_btnDG.SetCheck(TRUE);
	m_btnSetColor.SetCheck(TRUE);
	m_Progress.SetPos(0);
	m_TextProgress.SetWindowText(_T("��׼������"));
}

void CDlgCusTools::Trans( CStringArray& strDbFiles )
{
	if (strDbFiles.GetCount()<1)
	{
		MessageBox(_T("\n��ѡ·��������dwg�ļ�����˶Ժ�����\n"),_T("��ʾ"));
		return;
	}

	int nColor = m_cmbColor.GetCurrentItemColorIndex();
	CString strDestDir = GetSelectDestDirectory();
	CString strDestFile = strDestDir +_T("\\");
	m_Progress.SetRange(0,strDbFiles.GetCount());
	m_Progress.SetPos(0);
	for (int n=0;n<strDbFiles.GetCount();n++)
	{
		CString strFile = strDbFiles.GetAt(n);
		AcDbDatabase* pDb = new AcDbDatabase(false);
		Acad::ErrorStatus nRs = pDb->readDwgFile(strFile);

		CString strTips;
		strTips.Format(_T("���ڴ����ļ���%s"),strFile);
		m_TextProgress.SetWindowText(strTips);

		if (nRs != Acad::eOk)
		{

			delete pDb;
			pDb = NULL;
			continue;;
		}

		int nPos = strFile.ReverseFind('\\');
		CString strCurFile = strFile.Left(nPos)+_T("\\");

		AcAxDocLock lock(pDb); 
		const ACHAR* strFilename;
		pDb->getFilename(strFilename);

		CString strFilePath;
		strFilePath.Format(_T("%s%s"),strCurFile,strFilename);

		if (m_btnSetColor.GetCheck())
		{
			if (nColor>-1)
			{
				if (!CUtils::changeColor(pDb,nColor))
				{

					acutPrintf(_T("\n %s �ı���ɫʧ�ܣ�\n"),strFilename);
					delete pDb;
					pDb = NULL;
					continue;
				}	
			}
		}



		int nCurFormat = ((CComboBox*)GetDlgItem(IDC_COMBO_FORMAT))->GetCurSel();
		if (nCurFormat<0)
		{
			acutPrintf(_T("\n%s ���DWG��ʽ����\n"),strFilename);
		}
		CString strDestFilePath;
		CString strFileAllPath = strFilename;
		int nTmpPos = strFileAllPath.ReverseFind(_T('\\'));
		CString strOnlyFileName = strFileAllPath.Mid(nTmpPos+1);
		strDestFilePath.Format(_T("%s%s"),strDestFile,strOnlyFileName);
		if (nCurFormat==1)
		{
			nRs = acdbSaveAs2004(pDb,strDestFilePath);
			if (nRs!=Acad::eOk)
			{
				acutPrintf(_T("\n%s Ŀ���ļ��������\n"),strDestFilePath);
			}
			delete pDb;
			pDb = NULL;
		}
		else if(nCurFormat==2)
		{
			nRs = acdbSaveAs2000(pDb,strDestFilePath);
			if (nRs!=Acad::eOk)
			{
				acutPrintf(_T("\n%s Ŀ���ļ��������\n"),strDestFilePath);
			}
			delete pDb;
			pDb = NULL;
		}
		else if(nCurFormat==3)
		{
			nRs = acdbSaveAsR14(pDb,strDestFilePath);
			if (nRs!=Acad::eOk)
			{
				acutPrintf(_T("\n%s Ŀ���ļ��������\n"),strDestFilePath);
			}
			delete pDb;
			pDb = NULL;
		}
		else
		{
			nRs = pDb->saveAs(strDestFilePath);
			if (nRs!=Acad::eOk)
			{
				acutPrintf(_T("\n%s Ŀ���ļ��������\n"),strDestFilePath);
			}
			delete pDb;
			pDb = NULL;
		}

		m_Progress.SetPos(n+1);
	}

	m_TextProgress.SetWindowText(_T("�༭ת�����!"));
	acutPrintf(_T("\n�༭ת�����\n"));
}

CString CDlgCusTools::GetSelectOrgDirectory()
{
	CString directory;
	((CComboBox*)GetDlgItem(IDC_COMBO_ORG))->GetWindowText(directory);
	return directory;
}

CString CDlgCusTools::GetSelectDestDirectory()
{
	CString directory;
	((CComboBox*)GetDlgItem(IDC_COMBO_DEST))->GetWindowText(directory);
	return directory;
}

void CDlgCusTools::CollectOrgDbs( CStringArray &dbFiles )
{
	CString strDirectory;
	((CComboBox*)GetDlgItem(IDC_COMBO_ORG))->GetWindowText(strDirectory);
	vector<CString> tempDir;
	if (m_btnDG.GetCheck())
	{
		CUtils::GetAllFiles(tempDir, strDirectory, _T("DWG"), TRUE);
	}
	else
	{
		CUtils::GetAllFiles(tempDir, strDirectory, _T("DWG"), FALSE);
	}

	for (int i = 0; i < tempDir.size(); ++i)
		dbFiles.Add(tempDir[i]);
}

LRESULT CDlgCusTools::OnAcadKeepFocus( WPARAM, LPARAM )
{
	return TRUE;
}

