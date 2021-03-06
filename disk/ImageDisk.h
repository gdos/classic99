//
// (C) 2011 Mike Brent aka Tursi aka HarmlessLion.com
// This software is provided AS-IS. No warranty
// express or implied is provided.
//
// This notice defines the entire license for this code.
// All rights not explicity granted here are reserved by the
// author.
//
// You may redistribute this software provided the original
// archive is UNCHANGED and a link back to my web page,
// http://harmlesslion.com, is provided as the author's site.
// It is acceptable to link directly to a subpage at harmlesslion.com
// provided that page offers a URL for that purpose
//
// Source code, if available, is provided for educational purposes
// only. You are welcome to read it, learn from it, mock
// it, and hack it up - for your own use only.
//
// Please contact me before distributing derived works or
// ports so that we may work out terms. I don't mind people
// using my code but it's been outright stolen before. In all
// cases the code must maintain credit to the original author(s).
//
// -COMMERCIAL USE- Contact me first. I didn't make
// any money off it - why should you? ;) If you just learned
// something from this, then go ahead. If you just pinched
// a routine or two, let me know, I'll probably just ask
// for credit. If you want to derive a commercial tool
// or use large portions, we need to talk. ;)
//
// If this, itself, is a derived work from someone else's code,
// then their original copyrights and licenses are left intact
// and in full force.
//
// http://harmlesslion.com - visit the web page for contact info
//

// Image style disk access (not using TI DSR)
// TODO: Today limited to reading sector-based disks only
class ImageDisk : public BaseDisk {
public:
	ImageDisk();
	~ImageDisk();

	// basic DSR operations
	virtual void Startup();								// powerup routine
//	virtual bool SetFiles(int n);						// base class ok

	// emulation functions
//	virtual void SetPath(const char *pszPath);			// base class ok
	virtual int  GetDiskType() { return DISK_SECTOR; }	// return the disk type
//	virtual bool CheckOpenFiles();						// base class ok
//	virtual void CloseAllFiles();						// base class ok
	virtual void SetOption(int nOption, int nValue);
	virtual bool GetOption(int nOption, int &nValue);
//	virtual FileInfo *AllocateFileInfo();				// base class ok
//	virtual FileInfo *FindFileInfo(CString csFile);		// base class ok
	virtual CString BuildFilename(FileInfo *pFile);		// the real filename is the disk image name

	// disk support
	virtual bool Flush(FileInfo *pFile);
	virtual bool TryOpenFile(FileInfo *pFile);
	virtual bool CreateOutputFile(FileInfo *pFile);
	virtual bool BufferFile(FileInfo *pFile);
	virtual CString GetDiskName();

	// standard PAB opcodes
	virtual FileInfo *Open(FileInfo *pFile);
//	virtual bool Close(FileInfo *pFile);				// base class ok
//	virtual bool Read(FileInfo *pFile);					// base class ok
//	virtual bool Write(FileInfo *pFile);				// base class ok
//	virtual bool Restore(FileInfo *pFile);				// base class ok
	virtual bool Load(FileInfo *pFile);
	virtual bool Save(FileInfo *pFile);
	virtual bool Delete(FileInfo *pFile);
//	virtual bool Scratch(FileInfo *pFile);				// not supported
//	virtual void MapStatus(FileInfo *src, FileInfo *dest);// base class ok
//	virtual bool GetStatus(FileInfo *pFile);			// base class ok

	// SBRLNK opcodes (files is handled by shared handler)
	virtual bool ReadSector(FileInfo *pFile);
	virtual bool WriteSector(FileInfo *pFile);
	virtual bool ReadFileSectors(FileInfo *pFile);
//	virtual bool WriteFileSectors(FileInfo *pFile);		// TODO
//	virtual bool FormatDisk(FileInfo *pFile);			// TODO - maybe someday
//	virtual bool ProtectFile(FileInfo *pFile);			// not supported
//	virtual bool UnProtectFile(FileInfo *pFile);		// not supported
//	virtual bool RenameFile(FileInfo *pFile);			// TODO - maybe someday

	// class-specific functions
	bool BufferSectorFile(FileInfo *pFile);
	bool ReadVIB(FileInfo *pFile);
	bool GetSectorFromDisk(FILE *fp, int nSector, unsigned char *buf);
	bool PutSectorToDisk(FILE *fp, int nSector, unsigned char *buf);
	bool FindFileFDR(FILE *fp, FileInfo *pFile, unsigned char *fdr);
	void CopyFDRToFileInfo(unsigned char *fdr, FileInfo *pFile);
	int *ParseClusterList(unsigned char *fdr);
	int  GetDirectory(FileInfo *pFile, FileInfo *&Filenames);
	const char* GetAttributes(int nType);
	bool freeSectorFromBitmap(FILE *fp, int nSec);
	bool lockSectorInBitmap(FILE *fp, int nSec);
	bool WriteOutFile(FileInfo *pFile, FILE *fp, unsigned char *pBuffer, int cnt);
	int findFreeSector(FILE *fp, int lastFileSector);
	void FreePartialFile(FILE *fp, int fdr, int *sectorList, int sectorCnt);


	// configuration data
	bool bUseV9T9DSSD;			// use the reverse sector order for DSSD disks that V9T9 did
};

