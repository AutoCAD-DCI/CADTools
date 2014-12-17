#include "StdAfx.h"
#include "Utils.h"

CUtils::CUtils(void)
{
}

CUtils::~CUtils(void)
{
}

CString CUtils::GetWorkingDirectory()
{
	TCHAR fullPath[FILENAME_MAX];
	fullPath[0]='\0';

	HMODULE hCallerModule = NULL;
	//void *callerAddress = _ReturnAddress();   
	//GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)callerAddress, &hCallerModule);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, _T("gzciiCCadTools"), &hCallerModule);

	::GetModuleFileName(hCallerModule, fullPath, FILENAME_MAX-1);

	TCHAR drive[_MAX_PATH];
	drive[0]='\0';

	TCHAR directory[_MAX_PATH];
	directory[0]='\0';

	CString rs;

	_tsplitpath(fullPath, drive, directory, NULL, NULL);
	rs.Format(_T("%s%s"), drive, directory);

	return rs;
}

int CUtils::GetAllFiles( vector<CString>& aryFileName, const CString &strPath, const CString &strDefExt /*= _T("*")*/,BOOL bRecursive /*= FALSE*/ )
{
	CString strPathSearch = strPath;
	if(strPathSearch.Right(1) != _T("\\"))
		strPathSearch += _T("\\");

	CStringArray aryPathNeedToSearch;
	aryPathNeedToSearch.Add(strPathSearch);

	while(aryPathNeedToSearch.GetSize() > 0)
	{
		CString strCurPath = aryPathNeedToSearch.GetAt(0);
		aryPathNeedToSearch.RemoveAt(0);

		CFileFind CfileFind;
		BOOL bFindOk = CfileFind.FindFile(strCurPath + _T("*.*"));
		while (bFindOk)
		{
			bFindOk = CfileFind.FindNextFile();
			if(CfileFind.IsDots())
				continue;

			CString strFileName = CfileFind.GetFileName();
			if(CfileFind.IsDirectory() && bRecursive)
			{
				CString strNewPath = strCurPath + strFileName + _T("\\");
				aryPathNeedToSearch.Add(strNewPath);
			}
			else
			{
				if (strDefExt != _T("*"))
				{
					CString strTemp = strFileName;
					CString strTitle = CfileFind.GetFileTitle();
					strTemp.Replace(strTitle,_T(""));
					strTemp.Replace(_T("."),_T(""));
					if (0 != strTemp.CompareNoCase(strDefExt))
					{
						continue;
					}
				}

				CString strFilePathName = strCurPath + strFileName;
				//aryFileName.Add(strFilePathName);
				//aryFileName.Append(strFilePathName);
				aryFileName.push_back(strFilePathName);
			}
		}
		CfileFind.Close();
	}

	//return aryFileName.GetSize();
	//return aryFileName.Count();
	return aryFileName.size();
}

int CUtils::GetAllFiles( vector<FOLDER_FILES>& vInfo, const CString &strPath, const CString &strDefExt /*= _T("*")*/,BOOL bRecursive /*= FALSE*/ )
{
	CString strPathSearch = strPath;
	if(strPathSearch.Right(1) != _T("\\"))
		strPathSearch += _T("\\");

	CStringArray aryPathNeedToSearch;
	aryPathNeedToSearch.Add(strPathSearch);

	while(aryPathNeedToSearch.GetSize() > 0)
	{
		CString strCurPath = aryPathNeedToSearch.GetAt(0);
		aryPathNeedToSearch.RemoveAt(0);

		FOLDER_FILES info;
		CStringArray aryFileName;
		info.strPath = strCurPath.Mid(0, strCurPath.GetLength() - 1);
		CFileFind CfileFind;
		BOOL bFindOk = CfileFind.FindFile(strCurPath + _T("*.*"));
		while (bFindOk)
		{
			bFindOk = CfileFind.FindNextFile();
			if(CfileFind.IsDots())
				continue;

			CString strFileName = CfileFind.GetFileName();
			if(CfileFind.IsDirectory() && bRecursive)
			{
				CString strNewPath = strCurPath + strFileName + _T("\\");
				aryPathNeedToSearch.Add(strNewPath);
			}
			else
			{
				if (strDefExt != _T("*"))
				{
					CString strTemp = strFileName;
					CString strTitle = CfileFind.GetFileTitle();
					strTemp.Replace(strTitle,_T(""));
					strTemp.Replace(_T("."),_T(""));
					if (0 != strTemp.CompareNoCase(strDefExt))
					{
						continue;
					}
				}

				CString strFilePathName = strCurPath + strFileName;
				info.strFiles.push_back(strFilePathName);
				//info.strFiles.Append(strFilePathName);
			}
		}
		vInfo.push_back(info);
		//vInfo.Append(info);
		CfileFind.Close();
	}
	return vInfo.size();
	//return vInfo.Count();
}

BOOL CUtils::changeColor( AcDbDatabase* pDb,int nColor)
{
	if (pDb == NULL)
	{
		return FALSE;
	}

	AcDbBlockTable *pBlockTable;
	if (pDb->getBlockTable(pBlockTable, AcDb::kForRead) != Acad::eOk)
	{
		acutPrintf(_T("\n打开块表失败!"));
		return FALSE;
	}

	AcDbBlockTableRecord *pBlockRec;

	CString strLayerFind;
	TCHAR *pszLayerFind;

	if (pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite)!= Acad::eOk)
	{
		pBlockTable->close();
		return FALSE;
	}

	AcDbBlockTableRecordIterator* pIterator;
	pBlockRec->newIterator(pIterator);
	pBlockTable->close();

	AcDbEntity*	pEnt = NULL;
	for(; !pIterator->done(); pIterator->step())
	{
		if(pIterator->getEntity(pEnt, AcDb::kForWrite)!=Acad::eOk)continue;
		pEnt->setColorIndex(nColor,Adesk::kTrue);
		pEnt->close();

		AcDbBlockReference *pRef = AcDbBlockReference::cast(pEnt);
		//改变块颜色
		if(pRef)
		{
			CUtils::changeBlockTableRecordColor(pRef->blockTableRecord(),nColor);
		}
	}
	pBlockRec->close();
	delete pIterator;
	pIterator = NULL;

	return TRUE;
}

void CUtils::changeBlockTableRecordColor(AcDbObjectId& blkId,int iColor)
{
	AcDbBlockTableRecord *pBlockRec;
	Acad::ErrorStatus es;
	es=acdbOpenObject(pBlockRec,blkId,AcDb::kForRead);
	if(es!=Acad::eOk)
		return;

	AcDbBlockTableRecordIterator* pIterator;
	pBlockRec->newIterator(pIterator);

	AcDbEntity*	pEnt = NULL;
	for(; !pIterator->done(); pIterator->step())
	{
		if(pIterator->getEntity(pEnt, AcDb::kForWrite)!=Acad::eOk)
			continue;

		pEnt->setColorIndex(iColor,Adesk::kTrue);
		pEnt->close();
		AcDbBlockReference *pRef = AcDbBlockReference::cast(pEnt);
		if(pRef)
		{
			changeBlockTableRecordColor(pRef->blockTableRecord(),iColor);
		}
	}
	pBlockRec->close();
	delete pIterator;
	pIterator = NULL;
}