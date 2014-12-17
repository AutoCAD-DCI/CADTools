#pragma once

#include "dirtreectrl.h"
#include "resource.h"

//#ifdef COMMONLIB_MODULE
//#define COMMONLIBDLLIMPEXP __declspec(dllexport)
//#else
//#define COMMONLIBDLLIMPEXP __declspec(dllimport)
//#endif

// CDlgSelPath �Ի���

class  CDlgSelPath : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgSelPath)

public:
	CDlgSelPath(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSelPath();

// �Ի�������
	enum { IDD = IDD_DLG_SELPATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	/// <summary>
	/// ��ȡһ��ֵ������ָʾ�Ƿ���ѡ���ļ���
	/// </summary>
	/// <remarks></remarks>
	/// <returns>�����ѡ���ļ����򷵻� true�����򷵻� false��</returns>
	/// <author name="peishengh" date="2011.10.12   15:20"/>
	BOOL GetIsSelectFile() const;

	/// <summary>
	/// ���õ�ǰ�Ի����Ƿ���ѡ���ļ���
	/// </summary>
	/// <remarks></remarks>
	/// <param name="val">[I] true��ѡ���ļ���false��ѡ��Ŀ¼��</param>
	/// <returns></returns>
	/// <author name="peishengh" date="2011.10.12   15:21"/>
	void SetIsSelectFile(BOOL val);

	/// <summary>
	/// ��ȡ�û�ѡ�������·����
	/// </summary>
	/// <remarks></remarks>
	/// <returns>�����û�ѡ�������·����</returns>
	/// <author name="peishengh" date="2011.10.12   15:22"/>
	CString GetSelectPath() const;

	/// <summary>
	/// ���öԻ���ʼʱ��ʾ��·����
	/// </summary>
	/// <remarks></remarks>
	/// <param name="val">[I] ָ���Ի���ʼʱ��ʾ��·����</param>
	/// <returns></returns>
	/// <author name="peishengh" date="2011.10.12   15:23"/>
	void SetStartPath(CString val);

	/// <summary>
	/// ���öԻ���ı��⡣
	/// </summary>
	/// <remarks></remarks>
	/// <param name="pTitle">[I] ָ���Ի���ı��⡣</param>
	/// <returns></returns>
	/// <author name="peishengh" date="2011.10.12   15:24"/>
	void SetTitle(const TCHAR* pTitle);

	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);

private:
	/// <summary>
	/// ��ʾϵͳĿ¼�ṹ�����οؼ���
	/// </summary>
	CDirTreeCtrl m_tree;

	/// <summary>
	/// �����û�ѡ���·����
	/// </summary>
	CString m_sPath;

	/// <summary>
	/// �Ի�����⡣
	/// </summary>
	CString m_sTitle;

	/// <summary>
	/// ָʾѡ���ļ�����Ŀ¼��
	/// </summary>
	BOOL m_bSelFile;
};
