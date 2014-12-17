#pragma once

#include "dirtreectrl.h"
#include "resource.h"

//#ifdef COMMONLIB_MODULE
//#define COMMONLIBDLLIMPEXP __declspec(dllexport)
//#else
//#define COMMONLIBDLLIMPEXP __declspec(dllimport)
//#endif

// CDlgSelPath 对话框

class  CDlgSelPath : public CAcUiDialog
{
	DECLARE_DYNAMIC(CDlgSelPath)

public:
	CDlgSelPath(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSelPath();

// 对话框数据
	enum { IDD = IDD_DLG_SELPATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	/// <summary>
	/// 获取一个值，用于指示是否是选择文件。
	/// </summary>
	/// <remarks></remarks>
	/// <returns>如果是选择到文件，则返回 true；否则返回 false。</returns>
	/// <author name="peishengh" date="2011.10.12   15:20"/>
	BOOL GetIsSelectFile() const;

	/// <summary>
	/// 设置当前对话框是否是选择文件。
	/// </summary>
	/// <remarks></remarks>
	/// <param name="val">[I] true，选择到文件；false，选择到目录。</param>
	/// <returns></returns>
	/// <author name="peishengh" date="2011.10.12   15:21"/>
	void SetIsSelectFile(BOOL val);

	/// <summary>
	/// 获取用户选择的完整路径。
	/// </summary>
	/// <remarks></remarks>
	/// <returns>返回用户选择的完整路径。</returns>
	/// <author name="peishengh" date="2011.10.12   15:22"/>
	CString GetSelectPath() const;

	/// <summary>
	/// 设置对话框开始时显示的路径。
	/// </summary>
	/// <remarks></remarks>
	/// <param name="val">[I] 指定对话框开始时显示的路径。</param>
	/// <returns></returns>
	/// <author name="peishengh" date="2011.10.12   15:23"/>
	void SetStartPath(CString val);

	/// <summary>
	/// 设置对话框的标题。
	/// </summary>
	/// <remarks></remarks>
	/// <param name="pTitle">[I] 指定对话框的标题。</param>
	/// <returns></returns>
	/// <author name="peishengh" date="2011.10.12   15:24"/>
	void SetTitle(const TCHAR* pTitle);

	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);

private:
	/// <summary>
	/// 显示系统目录结构的树形控件。
	/// </summary>
	CDirTreeCtrl m_tree;

	/// <summary>
	/// 保存用户选择的路径。
	/// </summary>
	CString m_sPath;

	/// <summary>
	/// 对话框标题。
	/// </summary>
	CString m_sTitle;

	/// <summary>
	/// 指示选择到文件还是目录。
	/// </summary>
	BOOL m_bSelFile;
};
