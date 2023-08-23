# QuickDownloader
It is C++ application to download file from network by muti-thread.

# 代码基本结构
```mermaid
graph TD;
	DownLoadBusiness-->Main;
	FileVerify-->Main;
	ProtocolFactory-->DownLoadBusiness;
	HTTPProtocol-->ProtocolFactory;
	CUrlDownloader-->HTTPProtocol;
```

# 如何去编译
```bash
cd QuickDownloader && make
```



