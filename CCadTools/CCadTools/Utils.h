#pragma once

#include <vector>
using namespace std;

typedef struct
{
	CString			strPath;
	vector< CString > strFiles;
}FOLDER_FILES;

class CUtils
{
public:
	CUtils(void);
	~CUtils(void);

	static CString GetWorkingDirectory();
	static int GetAllFiles(vector<CString>& aryFileName, const CString &strPath, const CString &strDefExt = _T("*"),BOOL bRecursive = FALSE);
	static int	GetAllFiles(vector<FOLDER_FILES>& vInfo, const CString &strPath, const CString &strDefExt = _T("*"),BOOL bRecursive = FALSE);
	static void changeBlockTableRecordColor(AcDbObjectId& blkId,int iColor);
	static BOOL changeColor( AcDbDatabase* pDb,int nColor);
};
