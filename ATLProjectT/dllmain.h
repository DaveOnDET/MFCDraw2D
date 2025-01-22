// dllmain.h: 模块类的声明。

class CATLProjectTModule : public ATL::CAtlDllModuleT< CATLProjectTModule >
{
public :
	DECLARE_LIBID(LIBID_ATLProjectTLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECTT, "{c25cbe06-94c7-422c-950e-ddab8f3df68a}")
};

extern class CATLProjectTModule _AtlModule;
